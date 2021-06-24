#include"codeGen.h"
#include <stdarg.h>
#define codeBlockNum (90)
char *TypeName[] = {"int", "float", "bool","java.lang.String","array","void"};
const char* printStmt[] = {"print","println"};
char *program_name;
int outTabs = 0; 
char fcodeBuffer[200];
char beautifulCodeBuffer[200];
char ArgsBuffer[100];
bool inFunction = false;

struct codeBlock * codeArray;
int blockNum; // for code Array

int boolOperandLabel;


FILE *outFile;
/*********** init ***********/
void initCodeGen(const char *name)
{
    char buf[30];
    int pos = strlen(name) - 1;
    while(name[pos] != '.' ) pos--;
    strncpy(buf, name, pos + 1);
    sprintf(buf + pos + 1, "jasm");
    buf[pos + 5] = '\0';
    printf("outputFile=%s\n",buf);
    outFile = fopen(buf, "w");
    codeArray = NULL;
    codeArray = malloc(sizeof(struct codeBlock) * codeBlockNum);
    for(int i = 0; i < codeBlockNum; i++) initString(&codeArray[i].code);
    blockNum = 0;
    boolOperandLabel = 0;
    inFunction = false;
}
void EndCodeGen()
{
    for(int i = 0; i < codeBlockNum; i++) destroyString(&codeArray[i].code);
    free(codeArray);
    fclose(outFile);
}


void genIncrement(const char *name, int num)
{
    if(num < 0) return;
    struct SymTableEntry *var = getSymbol(name);
    //global variable
    if(var->level == 1)
    {
        genLoadVar(var->name);
        fgenCode("sipush %d\n", num);
        genOperand(Op_PLUS);
        genStoreVar(var->name);
    }
    else
    {
        fgenCode("iinc %d %d\n",var->attr.localId, num);
    }
}

/*********** general function ***********/

void fgenCode(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsprintf(fcodeBuffer, fmt, ap);
    va_end(ap);

    genCode(fcodeBuffer);
    fcodeBuffer[0] = '\0';
}

char *beautifulCode(const char *text)
{
    for(int i = 0; i < outTabs; i++) beautifulCodeBuffer[i] = '\t';
    int length = strlen(text);
    strncpy(beautifulCodeBuffer + outTabs, text, length);
    *(beautifulCodeBuffer + outTabs + length) = '\0';
    return beautifulCodeBuffer;
}

void genCodeAt(const char *text, int label) 
{
    int strSize = codeArray[label].code.size;
    if(strSize != 0 && codeArray[label].code.buf[strSize - 1] == '\n')
    {
        appendString(&codeArray[label].code, beautifulCode(text));
    }
    else appendString(&codeArray[label].code, text);
}

void genCode(const char *text)
{
    if(inFunction)
    {
        if(codeArray[blockNum].code.size != 0)
        {
            appendString(&codeArray[blockNum].code, beautifulCode(text));
        }
        else appendString(&codeArray[blockNum].code, text);
    } 
    else 
    {
        for(int i = 0; i < outTabs; i++) fprintf(outFile, "\t");
        fprintf(outFile, text);
    }
}

int genLabel() 
{
    blockNum++;
    if(blockNum == codeBlockNum)
    {
        printf("Buffer isn't enought\n");
        exit(-1);
    } 
    
    
    
    clearString(&codeArray[blockNum].code);
    codeArray[blockNum].hasLabel = false;
    return blockNum - 1;
}

struct PathList* createPathList(int label)
{
    struct PathList *n = malloc(sizeof(struct PathList));
    n->label = label;
    n->next = n->prev = n;
    return n;
}

struct LogicExpr createLogicExpr(enum Operator op, struct LogicExpr op1, struct LogicExpr op2) 
{
  struct LogicExpr n;
  n.isLogicExpr = false;
  n.FList = NULL;
  n.TList = NULL;
  n.expr = createExpr(op, op1.expr, op2.expr);
  return n;
}

void backPath(struct PathList *path, int label)
{
    if (path == NULL) return;
    struct PathList *cur = path;
    do {
        char buf[25];
        sprintf(buf, "Label%d\n", label + 1);
        genCodeAt(buf, cur->label);
        struct PathList *next = cur->next;
        free(cur);
        cur = next;
    }while (cur != path);
    codeArray[label + 1].hasLabel = true;
}

struct LogicExpr ExprToLogicExpr(struct Expr* expr)
{
  struct LogicExpr n;
  n.isLogicExpr = false;
  n.FList = NULL;
  n.TList = NULL;
  n.expr = expr;
  return n;
}

struct Expr *LogicExprToExpr(struct LogicExpr expr) 
{
//   if (expr.isLogicExpr) {
//     LogicExpr_toImmed(&expr);
//   }
  return expr.expr;
}


struct PathList *mergePathList(struct PathList *p1, struct PathList *p2) 
{
  if (p1 == NULL) return p2;
  if (p2 == NULL) return p1;
  struct PathList *p1Last = p1->prev;
  p1Last->next = p2;
  p1->prev = p2->prev;
  p2->prev->next = p1;
  p2->prev = p1Last;
  return p1;
}


//for function, help generate args,and storing into ArgsBuffer
void genArgs(struct Args *argsRef)
{
    char *tmp = ArgsBuffer;
    *tmp = '\0'; 
    char *tmpTypeName;
    while(argsRef)
    {
        tmpTypeName = TypeName[argsRef->type->type];
        if(tmp != ArgsBuffer)
        {
            *tmp++ = ',';
            *tmp++ = ' ';
        }
        strncpy(tmp, tmpTypeName, strlen(tmpTypeName));
        tmp += strlen(tmpTypeName);
        *tmp = '\0';
        argsRef = argsRef->NEXT;
    }
}

void initProg(const char *progName)
{
    fgenCode("class %s\n", progName);
    fgenCode("{\n");
    outTabs = 1;
}

void genMain()
{
    fgenCode("method public static void main(java.lang.String[])\n");
    fgenCode("max_stack 15\n");
    fgenCode("max_locals 15\n");
    fgenCode("{\n");
    blockNum = 0;
    boolOperandLabel = 0;
    inFunction = true;
}


void genFunDeclar(const char *name)
{
    struct SymTableEntry *fun = getSymbol(name);
    struct Args *argsRef = fun->attr.args;

    genArgs(argsRef);
    fgenCode("method public static %s %s(%s)\n", TypeName[fun->type->type], name, ArgsBuffer);
    fgenCode("max_stack 15\n");
    fgenCode("max_locals 15\n");
    fgenCode("{\n");

    ArgsBuffer[0] = '\0';
    blockNum = 0;
    boolOperandLabel = 0;
    inFunction = true;
}

void genFunDeclarEnd()
{
    inFunction = false;
    for(int i = 0; i <= blockNum; i++)
    {
        if(codeArray[i].code.size == 0) continue;
        if (codeArray[i].hasLabel) fprintf(outFile, "\tLabel%d:\n", i);
        genCode(codeArray[i].code.buf);
        clearString(&codeArray[i].code);
    }
    blockNum = 0;
    boolOperandLabel = 0;
}

void genFunCallEnd(const char *name)
{
    struct SymTableEntry *fun = getSymbol(name);
    struct Args *argsRef = fun->attr.args;
    genArgs(argsRef);
    fgenCode("invokestatic %s %s.%s(%s)\n", TypeName[fun->type->type], program_name, name,ArgsBuffer);
    ArgsBuffer[0] = '\0';
}

void genGlobalVar(struct SymbolStack *top, struct Type* type,bool init, int value)
{
    if(top == NULL) return;
    else
    {
        genGlobalVar(top->NEXT, type, init, value);
        int curType = type->type;
        if(type->type == Type_BOOL) curType = Type_INT;
        
        if(init) fgenCode("field static %s %s = %d\n", TypeName[curType], top->node->name, value);
        else fgenCode("field static %s %s\n", TypeName[curType], top->node->name);
    }
}

void genDeclarLocalVar(struct SymbolStack *top, int value)
{
    if(top == NULL) return;
    else
    {
        genDeclarLocalVar(top->NEXT, value);
        fgenCode("sipush %d\n", value);
        genStoreVar(top->node->name);
    }
}

void genStoreVar(const char *name)
{
    struct SymTableEntry *var = getSymbol(name);
    // global variable
    if (var->level == 1) fgenCode("putstatic int %s.%s\n",program_name, name);
    // local variable
    else fgenCode("istore %d\n",var->attr.localId);
}

void genLoadVar(const char *name)
{
    struct SymTableEntry *var = getSymbol(name);
    //constant variable
    if (var->kind == SymbolKind_constant) 
    {
        if(var->type->type == Type_STR) fgenCode("ldc \"%s\"\n", var->attr.value.str);
        else
        {
            int value;
            if(var->type->type == Type_BOOL) value = var->attr.value.boolean ? 1 : 0;
            else value = var->attr.value.integer;
            fgenCode("sipush %d\n", value);
        }
    }
    // global variable
    else if (var->level == 1) fgenCode("getstatic int %s.%s\n",program_name, name);
    // local variable
    else fgenCode("iload %d\n",var->attr.localId);
}


void genOperand(enum Operator oper)
{
    switch (oper)
    {
        //-(neg)
        case Op_UMINUS: genCode("ineg\n"); break;
        case Op_PLUS: genCode("iadd\n"); break;
        case Op_MINUS: genCode("isub\n"); break;
        case Op_MULTIPLY: genCode("imul\n"); break;
        case Op_DIVIDE: genCode("idiv\n"); break;
        case Op_LESS: genCode("if_icmplt "); break;
        case Op_LEQUAL: genCode("if_icmple "); break;
        case Op_EQUAL: genCode("if_icmpeq "); break;
        case Op_GEQUAL: genCode("if_icmpge "); break;
        case Op_GREATER: genCode("if_icmpgt "); break;
        case Op_NOTEQUAL: genCode("if_icmpne "); break;
        case Op_AND: genCode("iand\n"); break;
        case Op_OR: genCode("ior\n"); break;
        case Op_NOT: genCode("ixor\n"); break;
    }
}



void genConstant(struct Constant value)
{
    switch (value.type)
    {
        case Type_STR: fgenCode("ldc \"%s\"\n", value.str); break;
        case Type_INT: fgenCode("sipush %d\n", value.integer); break;
        case Type_BOOL: fgenCode("iconst_%d\n", value.boolean ? 1 : 0); break;
    }
}
/**** for print statement ****/
void genPrintStart()
{
    fgenCode("getstatic java.io.PrintStream java.lang.System.out\n");
}

void genPrintEnd(bool ln,enum TypeEnum type)
{
    if(type == Type_BOOL) type == Type_INT;
    fgenCode("invokevirtual void java.io.PrintStream.%s(%s)\n", printStmt[(ln ? 1 : 0)], TypeName[type]);
}


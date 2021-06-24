#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"
#define  SYMTABSIZE 1000


struct SymTableEntry *symbolTable[SYMTABSIZE];
struct SymbolStack *varList;
struct SymbolStack *declaration;
static char *typeName[] = {"Integer","Real", "Boolean", "String", "Array", "Void"};
static char *typeKind[] = {"Program","Procedure", "Parameter", "Variable", "Constant"};
static char *argMsg[30];
int curScopeLevel;
int curLocalVarId;

void printLine(int n)
{
    if(n == 0) return;
    while(n--) printf("-");
    printf("\n");
}

/*************  for symbolEntry ******************/
void destroy_Args(struct Args* args)
{
    if(args == NULL) return;

    struct Args* cur;
    cur = args;
    destroy_type(cur->type);

    cur = args->NEXT;
    free(args);
    destroy_Args(cur);
}

struct SymTableEntry* destroy_SymbolEntry(struct SymTableEntry* entry)
{
    struct SymTableEntry *cur = entry;
    if(cur->name != NULL) free(cur->name);

    if(cur->kind == SymbolKind_procedure) destroy_Args(cur->attr.args);
    destroy_type(cur->type);
    
    
    entry = cur;
    cur = cur->NEXT;
    free(entry);
    return cur;
}


void destroy_Entry(struct SymTableEntry* entry)
{
    while(entry) entry = destroy_SymbolEntry(entry);
}
/*************  for symbolstack ******************/
void pop_symbol(struct SymbolStack** top)
{
    if(*top)
    {
        struct SymbolStack *tmp = *top;
        (*top) = (*top)->NEXT;
        tmp->node = NULL;
        free(tmp);
    }
}
void push_symbol(struct SymbolStack** top, struct SymTableEntry *node)
{
    struct SymbolStack *tmp = malloc(sizeof(struct SymbolStack));
    tmp->node = node;
    tmp->NEXT = *top;
    *top = tmp;
}
void clear_stack(struct SymbolStack** top)
{
    while(*top) pop_symbol(top);
}


void end_declar()
{
    while(declaration)
    {
        push_symbol(&varList, declaration->node);
        pop_symbol(&declaration);
    }
}

//for constant variable
void assign_constant_value(struct Constant initValue)
{
    struct SymbolStack *cur = declaration;
    do{
        if(initValue.type == Type_STR)
        {
            int length = strlen(initValue.str);
            char *tmp = malloc(sizeof(char) * length);
            strncpy(tmp, initValue.str, length);
            tmp[length] = '\0';
            cur->node->attr.value.str = tmp;
            cur->node->attr.value.type = initValue.type;
        }
        else cur->node->attr.value = initValue; 
        cur = cur->NEXT;
    }while(cur);
}

void assign_type(struct Type *type, bool constant)
{
    if(declaration == NULL) return;

    struct SymbolStack *cur = declaration;
    do{
        cur->node->type = copyType(type);
        if(constant)
        {
            cur->node->kind = SymbolKind_constant;
        }
         
        cur = cur->NEXT;
    }while(cur);
}

void assign_localId(struct SymbolStack *cur)
{
    if(!cur) return;

    assign_localId(cur->NEXT);
    cur->node->attr.localId = curLocalVarId;
    curLocalVarId++;
}
/*************  for symboltable ******************/



//According the current level to determine whether variable belong to function
struct Args* getArgs()
{
    struct SymbolStack* top = varList;
    if(top == NULL || top->node->level != curScopeLevel) return NULL;
    struct Args *n = malloc(sizeof(struct Args)), *tmp = n;
    tmp->type = copyType(top->node->type);
    tmp->NEXT = NULL;
    tmp->PREV = NULL;
    top = top->NEXT;
    while(top && top->node->level == curScopeLevel)
    {
        tmp->NEXT = malloc(sizeof(struct Args));
        tmp->NEXT->PREV = tmp;
        tmp = tmp->NEXT;
        tmp->type = copyType(top->node->type);
        tmp->NEXT = NULL;
        top = top->NEXT;
    }
    n = tmp;
    while(tmp)
    {
        tmp->NEXT = tmp->PREV;
        tmp->PREV = NULL;
        tmp = tmp->NEXT;
    }
    return n;
}

//push all symbol in declaration into varList  
void nextScope()
{
    curScopeLevel ++;
    while(declaration)
    {
        push_symbol(&varList, declaration->node);
        pop_symbol(&declaration);
    }
}

void prevScope()
{
    int lineLength = 109;
    printf("Discard Var:\n");
    printLine(lineLength);
    printf("|    %-9s|     %-9s|   %-9s| %-7s|  %-18s|          %-15s| %-8s|\n", "Name","Type","Kind","level","ItemType / Value","Args","LocalId");
    printLine(lineLength);
    int pos;
    curScopeLevel --;
    while(varList->node->level > curScopeLevel)
    {
        PrintSymbolEntry(varList->node);
        pos = getSymbolPos(varList->node->name);
        symbolTable[pos] = destroy_SymbolEntry(varList->node);
        pop_symbol(&varList);
    }
    printLine(lineLength);
    printf("Now ");
    PrintSymbolTable();
}
int hash(const char *name)
{
    unsigned long hash = 5381;
    int c;

    while (c = *name++)
        hash = ((hash << 4) + hash) + c;
    
    return ((int)((hash)%SYMTABSIZE));
}



int getSymbolPos(const char *name)
{
    int c1 = 2, c2= 3, i = 0;
    bool flag = false;
    int pos = hash(name);

    while(symbolTable[pos] != NULL)
    {
        //if two identifier same name
        if(!strcmp(symbolTable[pos]->name, name)) break;
        //quadratic probing
        pos = (pos + c1 * i + c2 * i * i) % SYMTABSIZE;
        i++;
    }
    return pos;
}

struct SymTableEntry* getSymbol(const char *name)
{
    int pos = getSymbolPos(name);
    if(symbolTable[pos] == NULL) return NULL;
    else return symbolTable[pos];
}

// init symbol table
void initSymbolTable()
{
    for(int i = 0; i< SYMTABSIZE; i++) symbolTable[i] = NULL;
    curScopeLevel = 0;
    varList = NULL;
    declaration = NULL;
}

void destroySymbolTable()
{
    struct SymTableEntry *tmp = NULL;
    for(int i = 0; i< SYMTABSIZE; i++)
    {
        if(symbolTable[i] != NULL)
        {
            destroy_Entry(symbolTable[i]);
            symbolTable[i] = NULL;
        }
    }
    clear_stack(&varList);
    clear_stack(&declaration);
}

void PrintSymbolEntry(const struct SymTableEntry *cur)
{
    int nameLength;
    if(cur == NULL) 
    {
        printf("Some Error occur in PrintSymbolEntry!\n");
        return;
    }
    printf("| %-12s", cur->name);

    //None type
    if(cur->type == NULL) printf("| %-13s", "None");
    else printf("| %-13s", typeName[cur->type->type]);

    printf("| %-11s| %-6d ", typeKind[cur->kind],cur->level);

    if(cur->type && cur->type->type == Type_ARRAY)
    {
        printf("| %-19s", typeName[cur->type->itemType->type]);
    }
    else if(cur->kind == SymbolKind_constant)
    {
        switch (cur->attr.value.type)
        {
            case Type_INT: printf("| %-19d",cur->attr.value.integer); break;
            case Type_BOOL: printf("| %-19s",cur->attr.value.boolean ? "true" : "false"); break;
            case Type_STR: printf("| %-19s",cur->attr.value.str); break;
        }
    }
    else
    {
        printf("| %-19s","");
    }

    if(cur->kind == SymbolKind_procedure && cur->attr.args != NULL)
    {
        argMsg[0] = '\0';
        char *start = argMsg;
        struct Args* tmp = cur->attr.args;
        printf("|");
        while (tmp)
        {
            if(start != argMsg)
            {
                *start = ',';
                start++;
            }
            
            nameLength = strlen(typeName[tmp->type->type]);
            strncpy(start, typeName[tmp->type->type], nameLength);
            //printf("length=%d\n",nameLength);
            start += nameLength;
            tmp = tmp->NEXT;
        }
        *start = '\0';
        printf(" %-24s|",argMsg);
        //printf("|");
    }
    else
    {
        printf("| %-24s|","");
    }
    if(cur->kind == SymbolKind_variable && cur->level != 1)
    {
        printf(" %-8d|",cur->attr.localId);
    }
    else
    {
        printf(" %-8s|","");
    }
    printf("\n");
}



void PrintSymbolTable()
{
    int lineLength = 109;
    printf("SymbolTable: \n");
    printLine(lineLength);
    
    printf("|    %-9s|     %-9s|   %-9s| %-7s|  %-18s|          %-15s| %-8s|\n", "Name","Type","Kind","level","ItemType / Value","Args","LocalId");
    printLine(lineLength);


    struct SymbolStack *top = varList;
    while(top)
    {
        PrintSymbolEntry(top->node);
        top = top->NEXT;
    }
    printLine(lineLength);
}

// Add new identifer
void addVar(char *name, enum SymbolKind kind)
{
    struct SymTableEntry *newVar = malloc(sizeof(struct SymTableEntry));
    newVar->name = name;
    newVar->level = curScopeLevel;
    newVar->kind = kind;
    newVar->type = NULL;
    newVar->attr.args = NULL;
    newVar->PREV = NULL;
    newVar->NEXT = NULL;
    int pos = getSymbolPos(name);

    //if two identifer have same name, then linked them
    if(symbolTable[pos] != NULL)
    {
        if(symbolTable[pos]->level == newVar->level)
        {
            semanticError("redeclaration of name %s\n", newVar->name);
        }
        newVar->NEXT = symbolTable[pos];
        symbolTable[pos]->PREV = newVar;
    }
    symbolTable[pos] = newVar;
    push_symbol(&declaration, newVar);
}



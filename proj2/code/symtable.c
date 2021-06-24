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
    destroy_type(cur->type);
    destroy_Args(cur->args);
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
//for use type keywords
void assign_type(struct Type *type, bool constant)
{
    if(declaration == NULL) return;
    do{
        declaration->node->type = copyType(type);
        declaration->node->constant = constant;
        push_symbol(&varList, declaration->node);
        pop_symbol(&declaration);
    }while(declaration);
}

void assign_type_byEnum(enum TypeEnum type, bool constant)
{
    if(declaration == NULL) return;
    struct Type *tmp = createType(type);
    do{
        declaration->node->type = copyType(tmp);
        declaration->node->constant = constant;
        push_symbol(&varList, declaration->node);
        pop_symbol(&declaration);
    }while(declaration);
    destroy_type(tmp);
}
/*************  for symboltable ******************/




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

void nextScope()
{
    curScopeLevel ++;
    //push all symbol in varList to declaration

    while(declaration)
    {
        push_symbol(&varList, declaration->node);
        pop_symbol(&declaration);
    }
    //printf("Now Scope = %d!\n", curScopeLevel);
    //PrintSymbolTable();
}

void prevScope()
{
    printf("Discard Var:\n");
    printLine(90);
    printf("|    %-9s|     %-9s|   %-9s| %-7s|  %-10s|          %-15s|\n", "Name","Type","Kind","level","ItemType","Args");
    printLine(90);
    int pos;
    curScopeLevel --;
    while(varList->node->level != curScopeLevel)
    {
        PrintSymbolEntry(varList->node);
        pos = getSymbolPos(varList->node->name);
        symbolTable[pos] = destroy_SymbolEntry(varList->node);
        pop_symbol(&varList);
    }
    printLine(90);
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
        printf("| %-11s", typeName[cur->type->itemType->type]);
    }
    else
    {
        printf("| %-11s","");
    }

    if(cur->args != NULL)
    {
        argMsg[0] = '\0';
        char *start = argMsg;
        struct Args* tmp = cur->args;
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
    printf("\n");
}



void PrintSymbolTable()
{
    printf("SymbolTable: \n");
    printLine(90);
    
    printf("|    %-9s|     %-9s|   %-9s| %-7s|  %-10s|          %-15s|\n", "Name","Type","Kind","level","ItemType","Args");
    printLine(90);


    struct SymbolStack *top = varList;
    while(top)
    {
        PrintSymbolEntry(top->node);
        top = top->NEXT;
    }
    printLine(90);
}

// Add new identifer
void addVar(char *name, enum SymbolKind kind)
{
    struct SymTableEntry *newVar = malloc(sizeof(struct SymTableEntry));
    newVar->name = name;
    newVar->level = curScopeLevel;
    newVar->kind = kind;
    newVar->type = NULL;
    newVar->constant = false;
    newVar->args = NULL;
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



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"
#define  SYMTABSIZE 1000

#define DEBUG_FLAG (false)
struct SymTableEntry *symbolTable[SYMTABSIZE];
struct SymbolStack *top;
int curScopeLevel;

/*************  for symbolstack ******************/
void pop_symbol()
{
    if(top)
    {
        struct SymbolStack *tmp = top;
        top = top->NEXT;
        tmp->node = NULL;
        free(tmp);
    }
}
void push_symbol(struct SymTableEntry *node)
{
    struct SymbolStack *tmp = malloc(sizeof(struct SymbolStack));
    tmp->node = node;
    tmp->NEXT = top;
    top = tmp;
}
void clear_stack()
{
    while(top) pop_symbol();
}

void assign_type(enum TypeEnum type, bool constant)
{
    if(top == NULL) return;
    do{
        top->node->type.type = type;
        top->node->constant = constant;
        pop_symbol();
    }while(top);
}

void assign_list_type(struct Type type)
{
    int i = 0;

    //TODO 當有複數個元素時，是否要觸發語意錯誤(因為不可以在array宣告同一行放兩個變數)
    if(top == NULL) return;
    do{
        top->node->type.type = type.type;
        top->node->type.itemType = type.itemType;
        top->node->type.size = type.size;
        pop_symbol();
    }while(top);
    
}

/*************  for symboltable ******************/

void nextScope()
{
    curScopeLevel ++;
}
void prevScope()
{
    curScopeLevel --;
}
int hash(char *name)
{
    unsigned long hash = 5381;
    int c;

    while (c = *name++)
        hash = ((hash << 4) + hash) + c;
    
    return ((int)((hash)%SYMTABSIZE));
}




// init symbol table
void initSymbolTable()
{
    struct SymTableEntry *tmp = NULL;
    for(int i = 0; i< SYMTABSIZE; i++)
    {
        if(symbolTable[i] != NULL)
        {
            struct SymTableEntry *cur = symbolTable[i];
            while(cur)
            {
                if(cur->name != NULL) free(cur->name);
                tmp = cur;
                cur = cur->NEXT;
                free(tmp);
            }
            symbolTable[i] = NULL;
        }
    }
    curScopeLevel = 0;
    clear_stack();
}
void PrintSymbolTable()
{
    printf("Print SymbolTable: \n");
    static char *typeName[] = {"Integer","Real", "Boolean", "String", "Array", "Void"};
    static char *typeKind[] = {"Program","Procedure", "Parameter", "Variable", "Constant", "LoopVar"};
    for(int i = 0, t; i< SYMTABSIZE;i++)
    {
        struct SymTableEntry *cur = symbolTable[i];
        while(cur)
        {
            printf("Name: %5s,", cur->name);
            if(cur->kind == SymbolKind_program)
            {
                printf(" Type: %8s,", "None");
            }
            else{
                printf(" Type: %8s,", typeName[cur->type.type]);
            }
            
            printf(" Kind: %9s, Level: %2d\n", typeKind[cur->kind],cur->level);
            cur = cur->NEXT;
        }
    }
}


// Add new identifer
void addVar(char *name, enum SymbolKind kind)
{
    
    struct SymTableEntry *newVar = malloc(sizeof(struct SymTableEntry));
    
    int c1 = 2, c2= 3, i = 0;
    bool flag = false;
    int pos = hash(name);

    while(symbolTable[pos] != NULL)
    {
        //if two identifier same name
        if(!strcmp(symbolTable[pos]->name, name))
        {
            flag = true;
            break;
        }
        //quadratic probing
        pos = (pos + c1 * i + c2 * i * i) % SYMTABSIZE;
        i++;
    }
    newVar->name = name;
    newVar->level = curScopeLevel;
    newVar->kind = kind;
    newVar->PREV = NULL;
    newVar->NEXT = NULL;

    //if two identifer have same name, then linked them
    if(flag)
    {
        newVar->NEXT = symbolTable[pos];
        symbolTable[pos]->PREV = newVar;
    }
    symbolTable[pos] = newVar;
    
    push_symbol(newVar);
}



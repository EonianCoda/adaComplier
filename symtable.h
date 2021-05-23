#pragma once
#include "util.h"

enum SymbolKind {
  SymbolKind_program, SymbolKind_procedure, SymbolKind_parameter,
  SymbolKind_variable, SymbolKind_constant, SymbolKind_loopVar
};

struct SymTableEntry
{
    char *name;
    enum SymbolKind kind;
    int level;
    struct Type type;
    bool constant;
    struct SymTableEntry *PREV;
    struct SymTableEntry *NEXT;
};

struct SymbolStack
{
    struct SymTableEntry *node;
    struct SymbolStack *NEXT;
};


//for symboltable
int hash(char *name);
void addVar(char *name, enum SymbolKind kind);
void initSymbolTable();
void PrintSymbolTable();


//for SymbolStack
void clear_stack();
void pop_symbol();
void push_symbol(struct SymTableEntry *node);
void assign_type(enum TypeEnum type, bool constant);
void assign_list_type(struct Type type);




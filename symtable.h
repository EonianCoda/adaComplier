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
    struct Type *type;
    bool constant; //whether it is a constant variable
    struct SymTableEntry *PREV;
    struct SymTableEntry *NEXT;
};

struct SymbolStack
{
    struct SymTableEntry *node;
    struct SymbolStack *NEXT;
};


//for SymTableEntry
void destroy_SymbolEntry(struct SymTableEntry* entry);


//for symboltable
int hash(const char *name);
void addVar(char *name, enum SymbolKind kind);
void initSymbolTable();
int getSymbolPos(const char *name);
struct SymTableEntry* getSymbol(const char *name);
void PrintSymbolTable();
void nextScope();
void prevScope();

//for SymbolStack
void clear_stack();
void pop_symbol();
void push_symbol(struct SymTableEntry *node);
void assign_type(struct Type *type, bool constant);
void assign_type_byEnum(enum TypeEnum type, bool constant);




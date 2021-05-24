#pragma once
#include "util.h"
extern int curScopeLevel;
enum SymbolKind {
  SymbolKind_program, SymbolKind_procedure, SymbolKind_parameter,
  SymbolKind_variable, SymbolKind_constant, SymbolKind_loopVar
};


struct Args
{
  struct Type *type;
  struct Args *NEXT;
  struct Args *PREV;
};

struct SymTableEntry
{
    char *name;
    enum SymbolKind kind;
    int level;
    struct Type *type;
    bool constant; //whether it is a constant variable
    struct Args *args;
    struct SymTableEntry *PREV;
    struct SymTableEntry *NEXT;
};


struct SymbolStack
{
    struct SymTableEntry *node;
    struct SymbolStack *NEXT;
};


struct Args* getArgs();



//for SymTableEntry
void destroy_Args(struct Args* args);
void destroy_Entry(struct SymTableEntry* entry);
struct SymTableEntry* destroy_SymbolEntry(struct SymTableEntry* entry);



//for symboltable
int hash(const char *name);
void addVar(char *name, enum SymbolKind kind);
void initSymbolTable();
int getSymbolPos(const char *name);
struct SymTableEntry* getSymbol(const char *name);
void destroySymbolTable();
void PrintSymbolEntry(const struct SymTableEntry *cur);
void PrintSymbolTable();
void nextScope();
void prevScope();

//for SymbolStack
void clear_stack(struct SymbolStack** top);
void pop_symbol(struct SymbolStack** top);
void push_symbol(struct SymbolStack** top, struct SymTableEntry *node);
void assign_type(struct Type *, bool );
void assign_type_byEnum(enum TypeEnum type, bool constant);





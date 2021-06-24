#pragma once
#include "util.h"
extern int curScopeLevel;
extern int curLocalVarId;
extern struct SymbolStack *varList;
extern struct SymbolStack *declaration;

enum SymbolKind {
  SymbolKind_program, SymbolKind_procedure, SymbolKind_parameter,
  SymbolKind_variable, SymbolKind_constant,
};




struct Args
{
  struct Type *type;
  struct Args *NEXT;
  struct Args *PREV;
};


struct Attribute
{
  union 
  {
      struct Args *args;
      //for constant variable
      struct Constant value;
      //for local variable
      int localId;
  };
};

struct SymTableEntry
{
    char *name;
    enum SymbolKind kind;
    int level; // if level = 1, means that it is a global variable
    struct Type *type;
    struct Attribute attr;
    //struct Args *args;
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
void assign_constant_value(struct Constant initValue);


//for SymbolStack
void clear_stack(struct SymbolStack** top);
void pop_symbol(struct SymbolStack** top);
void push_symbol(struct SymbolStack** top, struct SymTableEntry *node);
void assign_type(struct Type *, bool constant);
void assign_localId(struct SymbolStack* top);
void end_declar();





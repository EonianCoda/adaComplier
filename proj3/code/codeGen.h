#pragma once
#include "util.h"
#include "symtable.h"
#include "stringBuf.h"

extern char* program_name;
extern int outTabs;
extern int boolOperandLabel;
struct codeBlock{
    struct String code;
    bool hasLabel;
};


//label and expression process
struct LogicExpr ExprToLogicExpr(struct Expr* expr);
struct LogicExpr createLogicExpr(enum Operator op, struct LogicExpr op1, struct LogicExpr op2);
struct Expr *LogicExprToExpr(struct LogicExpr expr);
struct PathList *mergePathList(struct PathList *p1, struct PathList *p2);
void backPath(struct PathList *path, int label);
struct PathList* createPathList(int label);

//for for loop
void genIncrement(const char *name, int num);

//code generation init and end
void initCodeGen(const char *name);
void EndCodeGen();
void initProg(const char *progName);

//general code generation
void fgenCode(const char *fmt, ...);
void genCode(const char *text);
void genCodeAt(const char *text, int label);
int genLabel();

//function
void genFunDeclar(const char *name);
void genFunCallEnd(const char *name);
void genFunDeclarEnd();
void genMain(); // main function is also a function

//variabel declaration and SL
void genGlobalVar(struct SymbolStack *top, struct Type* type,bool init, int value);
void genDeclarLocalVar(struct SymbolStack *top, int value);
void genStoreVar(const char *name);
void genLoadVar(const char *name);
void genConstant(struct Constant value);

//for +, -, *, /, <= , =  ...
void genOperand(enum Operator oper);

//for print statement
void genPrintStart();
void genPrintEnd(bool ln,enum TypeEnum type);

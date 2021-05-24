#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define DEBUG_FLAG (true)
#define ENABLE_BEFORE_LINENUMBER (true)
#define DEBUG_BEFORE_LINENUMBER (9)

extern char *OpName[];
enum TypeEnum {
    Type_INT, Type_REAL, Type_BOOL, Type_STR, Type_ARRAY, Type_VOID, Type_NONE
};
enum Operator {
  Op_NONE,
  Op_OR, Op_AND, Op_NOT,
  Op_LESS, Op_LEQUAL, Op_NOTEQUAL, Op_GEQUAL, Op_GREATER, Op_EQUAL, Op_DIVIDEEQ,
  Op_PLUS, Op_MINUS,
  Op_MULTIPLY, Op_DIVIDE,
  Op_UMINUS, // -num
  Op_FUNC, // f(x)
  Op_INDEX, // a[i]
  Op_LIT, // literal
  Op_VAR // variable reference
};

struct Constant{
  enum TypeEnum type;
  union {
    char *str;
    int integer;
    float real;
    bool boolean;
  };
};

struct ArrayItems{
  enum TypeEnum type;
  int size;
};

struct Type{
  enum TypeEnum type;
  // For Array Type
  struct ArrayItems * itemType;
};

struct Expr {
  enum Operator op;
  struct Type *type;
  union {
    struct Constant lit;
    struct Expr *args;
    char *name; //for var
  };
  struct Expr *next;
};

//error Report
void semanticError(const char *fmt, ...);


//other

void destroyConst(struct Constant c);

//for type
struct Type * copyType(struct Type *type);
void destroy_type(struct Type *type);
struct Type *createType(enum TypeEnum type);
void showType(struct Type *type);
void printType(enum TypeEnum type);
bool isSameType(struct Type *t1, struct Type *t2);
bool canConvertTypeImplicitly(struct Type *from, struct Type *to);
bool isScalarType(struct Type *type);

//for expression
struct Expr *createExpr(enum Operator op, struct Expr *op1, struct Expr *op2);
struct Expr *createLitExpr(struct Constant lit);
struct Expr *createVarExpr(char *name);
struct Expr *createFuncExpr(char *name, struct Expr *args);
void destroyExpr(struct Expr *expr);
#pragma once

#include "symtable.h"

// check variable type
void varTypeCheck(struct Expr *var);

// check array type
void arrayTypeCheck(struct Expr *arr);

// check print and read statement
void printCheck(struct Expr *expr);

// check arithmetic operator
void arithOpCheck(struct Expr *expr);
void boolOpCheck(struct Expr *expr);
void relOpCheck(struct Expr *expr);
void unaryOpCheck(struct Expr *expr);

// check function call
void functionCheck(struct Expr *expr);

// check if return type match the actual type
void returnCheck(struct Expr *expr, struct Type *expected);
// check condition expr is boolean
void conditionCheck(struct Expr *exp);
// check for assignment
void assignCheck(struct Expr *var, struct Expr *expr);
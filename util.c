#include "util.h"
#include <stdio.h>
#include <stdarg.h>

extern int linenum;
int errorCount = 0;

char *OpName[] = {
  "NONE",
  "or", "and", "not",
  "<", "<=", "<>", ">=", ">", "=",
  "+", "-",
  "*", "/", "mod",
  "UMINUS", // -num
  "FUNC", // f(x)
  "INDEX", // a[i]
  "", // literal
  "VAR" // variable reference
};


void semanticError(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  printf("<Error> found in Line %d:", linenum);
  vprintf(fmt, ap);
  va_end(ap);
  errorCount++;
  exit(-1);
}

/******************************* Other ********************************/
void destroy_const(struct Constant c) 
{
  if (c.type == Type_STR) {
    free(c.str);
  }
}

/********************************   for Type   ********************************/
void destroy_type(struct Type *type)
{
    if(type == NULL) return;
    if(type->type == Type_ARRAY) free(type->itemType);
    free(type);
}

struct Type * copyType(struct Type *type)
{
    if(type == NULL) return NULL;
    struct Type *n = malloc(sizeof(struct Type));
    n->type = type->type;
    n->itemType = NULL;
    //if type is a array
    if(type->type == Type_ARRAY)
    {
        n->itemType = malloc(sizeof(struct ArrayItems));
        n->itemType->type = type->itemType->type;
        n->itemType->size = type->itemType->size;
    }
    return n;
}

struct Type *createType(enum TypeEnum type)
{
    struct Type *n = malloc(sizeof(struct Type));
    n->type = type;
    n->itemType = NULL;
    return n;
}

void printType(enum TypeEnum type)
{
    switch (type) 
    {
        case Type_INT: printf("integer"); break;
        case Type_REAL: printf("real"); break;
        case Type_BOOL: printf("boolean"); break;
        case Type_STR: printf("string"); break;
        case Type_VOID: printf("void"); break;
        default: printf("None"); break;
    }
}

void showType(struct Type *type) 
{
  if (type == NULL) printf("void");

  if(type->type != Type_ARRAY)
  {
      printType(type->type);
  }
  //Array Type
  else
  {
      printType(type->itemType->type);
      printf(" Array");
  }
}

bool isSameType(struct Type *t1, struct Type *t2) 
{
    if (t1->type != t2->type) return false;
    else if (t1->type == Type_ARRAY)
    {
        if(t1->itemType->type != t2->itemType->type || t1->itemType->size == t2->itemType->size) return false;
    }
    return true;
}

bool canConvertTypeImplicitly(struct Type *from, struct Type *to) {
  // I think integer [5] is not real [5]

  //bool y = isSameType(from, to);
  //if (y) return True;
  //if (from->type == Type_INTEGER && to->type == Type_REAL) return True;
  //return false;

//   while (from->type == Type_ARRAY && to->type == Type_ARRAY) {
//     // check size of each dimension
//     if (from->upperBound - from->lowerBound != to->upperBound - to->lowerBound) {
//       return false;
//     }
//     from = from->itemType;
//     to = to->itemType;
//   }
  if (from->type == to->type) return true;
  if (from->type == Type_INT && to->type == Type_REAL) return true;
  return false;
}

bool isScalarType(struct Type *type)
{
  if (type == NULL) return false;
  return type->type == Type_INT || type->type == Type_REAL
    || type->type == Type_BOOL || type->type == Type_STR;
}
/************************   for Expression  ************************/
struct Expr *createExpr(enum Operator op, struct Expr *arg1, struct Expr *arg2) 
{
    struct Expr *n = malloc(sizeof(struct Expr));
    n->op = op;
    n->type = NULL;
    n->next = NULL;
    n->args = arg1;
    if (arg1 != NULL) arg1->next = arg2;
    return n;
}

struct Expr *createLitExpr(struct Constant lit) 
{
    struct Expr *n = malloc(sizeof(struct Expr));
    n->op = Op_LIT;
    n->type = createType(lit.type);
    n->next = NULL;
    n->lit = lit;
    return n;
}

struct Expr *createVarExpr(char *name) {
    struct Expr *n = malloc(sizeof(struct Expr));
    n->op = Op_VAR;
    n->type = NULL;
    n->next = NULL;
    n->name = name;
    return n;
}

struct Expr *createFuncExpr(char *name, struct Expr *args) {
    struct Expr *n = malloc(sizeof(struct Expr));
    n->op = Op_FUNC;
    n->type = NULL;
    n->next = NULL;
    n->args = createVarExpr(name);
    n->args->next = args;
    return n;
}

void destroyExpr(struct Expr *expr) {
  struct Expr *p = expr, *q;
  while (p != NULL) {
    if (p->op == Op_VAR) {
      free(p->name);
    }
    else if (p->op == Op_LIT) {
      destroy_const(p->lit);
    }
    else {
      destroyExpr(p->args);
    }
    if (p->type != NULL) destroy_type(p->type);
    q = p;
    p = p->next;
    free(q);
  }
}


void initExprList(struct ExprList *list) 
{
    list->first = list->last = NULL;
}

void addToExprList(struct ExprList *list, struct Expr *expr) 
{
    if (list->first == NULL) 
    {
       list->first = expr;
    }
    else 
    {
        list->last->next = expr;
    }
    list->last = expr;
}

#include "semcheck.h"

static struct SymTableEntry *VarReadCheck(const char *name, const char *vararr) 
{
  struct SymTableEntry *a = getSymbol(name);
  if (a == NULL)  semanticError("symbol '%s' is not defined\n", name);
  if (a->kind == SymbolKind_program || a->kind == SymbolKind_procedure)  semanticError("symbol '%s' is not %s\n", name, vararr);
  return a;
}

static void binaryOpErr(struct Expr *op1, struct Expr *op2, enum Operator op) 
{
  semanticError("invalid operand to binary '%s'", OpName[op]);
}

void returnCheck(struct Expr *expr, struct Type *expected) 
{
    if (expected->type == Type_VOID) semanticError("procedure cannot be returned\n");
    else if (expr->type == NULL) return;
    else if (!isSameType(expr->type, expected)) semanticError("return type mismatch\n");
}

void conditionCheck(struct Expr *expr) 
{
  if (expr->type == NULL) return;
  else if (expr->type->type != Type_BOOL) semanticError("operand statement is not boolean type\n");
}

void assignCheck(struct Expr *var, struct Expr *expr) 
{
    //Some Error
    if (var->type == NULL || expr->type == NULL) return;
    
    if(!isSameType(expr->type, var->type)) semanticError("Assign type mismatch\n");
    if(var->op == Op_VAR)
    {
        struct SymTableEntry *a = getSymbol(var->name);
        //Constant Variable
        if(a->kind == SymbolKind_constant) semanticError("constant Variable '%s' cannot be assigned\n", var->name);
    }
}

void varTypeCheck(struct Expr *var) 
{
  struct SymTableEntry *a = VarReadCheck(var->name, "a variable");
  if (a == NULL) return ;
  var->type = copyType(a->type);
}

void arrayTypeCheck(struct Expr *arr) 
{
  struct Expr *var = arr->args;
  struct Expr *idx = var->next;
  struct SymTableEntry *a = VarReadCheck(var->name, "an array");
  bool lhsgood = false;
  if (a == NULL) ; // error already reported
  else if (a->type->type != Type_ARRAY) semanticError("symbol '%s' is not an array\n", var->name);
  else lhsgood = true;

  bool rhsgood = false;
  if (idx->type == NULL) ;
  else if (idx->type->type != Type_INT) semanticError("Array subscript is not an integer\n");
  else rhsgood = true;

  if (lhsgood && rhsgood) arr->type = createType(a->type->itemType->type);
}

void printCheck(struct Expr *expr) {
  if (expr->type == NULL) return;
  if (isScalarType(expr->type)) return;
  else if (expr->type->type == Type_ARRAY) semanticError("Array type cannot print\n");
  else if (expr->type->type == Type_VOID) semanticError("Void type cannot print\n");
}


void arithOpCheck(struct Expr *expr) 
{
  struct Expr *op1 = expr->args, *op2 = op1->next;
  if (op1->type == NULL || op2->type == NULL) return ;
  
  bool lhs = op1->type->type == Type_INT || op1->type->type == Type_REAL;
  bool rhs = op2->type->type == Type_INT || op2->type->type == Type_REAL;
  if (lhs && rhs) 
  {
    if (op1->type->type == Type_REAL || op2->type->type == Type_REAL)  expr->type = createType(Type_REAL);
    else expr->type = createType(Type_INT);
  }
  else binaryOpErr(op1, op2, expr->op);
}

void boolOpCheck(struct Expr *expr) 
{
  struct Expr *op1 = expr->args, *op2 = op1->next;
  if (op1->type == NULL || op2->type == NULL) return ;
  bool lhs = op1->type->type == Type_BOOL;
  bool rhs = op2->type->type == Type_BOOL;
  if (lhs && rhs) 
  { 
    expr->type = createType(Type_BOOL);
  }
  else 
  {
    binaryOpErr(op1, op2, expr->op);
  }
}

void relOpCheck(struct Expr *expr) 
{
  struct Expr *op1 = expr->args, *op2 = op1->next;
  if (op1->type == NULL || op2->type == NULL) return ;
  bool lhs = op1->type->type == Type_INT || op1->type->type == Type_REAL;
  bool rhs = op2->type->type == Type_INT || op2->type->type == Type_REAL;
  if (lhs && rhs) 
  { 
    expr->type = createType(Type_BOOL);
  }
  else 
  {
    binaryOpErr(op1, op2, expr->op);
  }
}

// unary ops: '-' and 'not'
void unaryOpCheck(struct Expr *expr) 
{
  struct Expr *op = expr->args;
  if (op->type == NULL) return ;
  bool good = false;
  if (expr->op == Op_UMINUS) 
  {
    if (op->type->type == Type_INT || op->type->type == Type_REAL) 
    {
      expr->type = copyType(op->type);
      good = true;
    }
    else {
      semanticError("invalid operand to unary minus, type = ");
    }
  }
  else if (expr->op == Op_NOT) {
    if (op->type->type == Type_BOOL) {
      expr->type = createType(Type_BOOL);
      good = true;
    }
    else {
      semanticError("invalid operand to unary not, type = ");
    }
  }
}

void functionCheck(struct Expr *expr) {
    struct Expr *nm = expr->args, *args = nm->next;
    struct SymTableEntry *a = getSymbol(nm->name);
    // find a function symbol
    if (a == NULL) 
    {
      semanticError("symbol '%s' is not defined\n", nm->name);
      return;
    }
    if (a->kind != SymbolKind_procedure) 
    {
      semanticError("symbol '%s' is not a procedure\n", nm->name);
      return ;
    }
    expr->type = copyType(a->type);
    
    struct Args* funArgs = a->attr.args;
    struct Expr *ptr = args;
    
    //no args
    if(funArgs == NULL &&  ptr == NULL) return;

    int i = 0;
    while(true)
    {
        if(funArgs == NULL)
        {
            if(ptr != NULL) semanticError("too many arguments to function '%s'\n", nm->name);
            return;
        }
        else if(ptr == NULL)
        {
            if(funArgs != NULL) semanticError("too few arguments to function '%s'\n", nm->name);
            return;
        }
        if(!isSameType(ptr->type, funArgs->type)) semanticError("Argument %d of '%s' type mismatch", i+1, nm->name);
        funArgs = funArgs->NEXT;
        ptr = ptr->next;
        i++;
    }
}



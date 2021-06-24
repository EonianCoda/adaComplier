%{
#include "symtable.h"
#include "semcheck.h"
#include "codeGen.h"
#include <stdio.h>
#include <stdlib.h>
extern int linenum;


#define Trace(t)  { if(DEBUG_FLAG){  if(ENABLE_BEFORE_LINENUMBER) {if(linenum >= DEBUG_BEFORE_LINENUMBER) printf(t);} else printf(t);} }
extern FILE *yyin;
extern int yylex(void);
struct SymTableEntry *curFunc = NULL;
bool decGlobalVar = true;
bool decProcPars = false;
bool procReturn = false;
bool decConstantExpr = false;
bool isCondition = false;
%}

%union
{
    bool flag;
    enum TypeEnum typeEnum;
    enum Operator oper;
    char *name;
    struct Constant literal;
    struct Type *type;
    struct Expr *expr;
    struct ExprList args;
    struct Args *funcArgs;
    struct statement stmt;
    struct LogicExpr logicExpr;
    int label;
}
%token BEGIN_
// Output keywords
%token PRINT PRINTLN
// Type keywords
%token BOOLEAN INTEGER FLOAT STRING CONSTANT
// Bool keywords
%token BOOL_TRUE BOOL_FALSE 
// Condition keywords
%token IF ELSE DO THEN WHILE BREAK CONTINUE FOR LOOP 

// Block keywords
%token PROGRAM PROCEDURE END DECLARE RETURN


//Other keywords
%token  OF  READ  CHARACTER EXIT CASE IN

//operation
%token ASSIGN
%left OR
%left AND
%right NOT
%left '<' LEEQ NOTEQ GREQ '>' '='
%left '+' '-'
%left '*' '/'


%token <name> ID

// literals
%token<literal> LIT_INT LIT_STR LIT_REAL


/* tokens */
%type<label> Label 
%type<typeEnum> type_keyword 
%type<type> type varAssignType procedureReturn
%type<literal> literalConstant
%type<oper> mul_op add_op rel_op
%type<expr> variable_reference function_invoc procedure_call
%type<logicExpr> prior_expr factor term expression relation_expr boolean_factor boolean_term boolean_expr
%type<logicExpr> condition
%type<stmt> statements statement compound_stmt conditional_stmt while_stmt for_stmt IfGoto
%type<stmt> block block_or_simple 
%type<args> arg_list arguments
%type<funcArgs> paraDeclars
%type<flag> print_keyword
%%

/***************************************************/
/********************Main Block*********************/
/***************************************************/

program:        PROGRAM ID 
                {
                    addVar($2, SymbolKind_program);
                    program_name = $2;
                    nextScope();
                    initProg(program_name);
                }
                programbody ';' END ID
                {
                    if(strcmp($2, $7)) semanticError("Program declaration and END should be same name, %s and %s\n", $2, $7);
                    Trace("Reducing to program\n");

                    //main and class's end parantheses
                    genFunDeclarEnd(); //main function is also a function
                    outTabs = 0;
                    genCode("\t\treturn\n\t}\n}");
                }
                ;

programbody: 
            declarations
                {
                    Trace("Reducing to declarations \n");
                    decGlobalVar = false;
                }
            procedureDeclars
                { 
                    Trace("Reducing to procedureDeclars \n");
                    genMain();
                    outTabs++;
                    curLocalVarId = 0;
                }
            compound_stmt
                {
                    backPath($5.path, genLabel());
                    Trace("Reducing to programbody\n");
                }
            ;
block: 
        {  
            nextScope(); 
        }
        Label declarations compound_stmt ';'
        {
            prevScope();
            //backPath($4.path, genLabel());
            $$.path = $4.path;
            Trace("Reducing to BLOCK\n"); 
        }
        ;

/***************************************************/
/****************Procedure Declare******************/
/***************************************************/
procedureDeclars:
         /* empty */ 
        | procedureDeclars procedureDeclar
        ;

procedureDeclar:
        PROCEDURE ID 
        {
            addVar($2, SymbolKind_procedure);
            curFunc = getSymbol($2);
            nextScope();
            curLocalVarId = 0;
            decProcPars = true;
        }
        paraDeclars
        {
            curFunc->attr.args = $4;
            decProcPars = false;
            Trace("End this procedure's parameter declaration!\n");
        }
        procedureReturn
        {
            curFunc->type = $6;
            procReturn = false;
            //the arg of the procedure has the same scope as the content 
            curScopeLevel--;
            genFunDeclar($2);
            outTabs++;
        }
        block END ID ';'
        {
            backPath($8.path, genLabel());
            if(strcmp($2,$10))
            {
                semanticError("Procedure declaration and END should be same name, %s and %s\n", $2, $10);
            }
            Trace("End this procedure declaration!\n");
            curFunc = NULL;

            genFunDeclarEnd();
            if(!procReturn) genCode("return\n");
            //end of function
            outTabs = 1;
            genCode("}\n");
        }
        ;

procedureReturn:
        /* Empty */ { $$ = createType(Type_VOID); }
        | RETURN type {$$ = $2;}
        ;
paraDeclars:
        /* Empty */ 
        { 
            $$ = NULL;
            Trace("No parameters!\n"); 
        }
        | '(' paraDeclar ')'
        {
            end_declar();
            $$ = getArgs();
        }
        ;
paraDeclar:
        /* Empty */   { Trace("No parameters!\n"); }
        | varAssignType 
        {
            Trace("add new parameter\n");
        }
        | paraDeclar ';' varAssignType 
        ;

/***************************************************/
/********************statement**********************/
/***************************************************/
compound_stmt:
        BEGIN_  statements END
        {
            $$.path = $2.path;
        }
        ;

statements:
        /* empty */ 
        {
            Trace("Empty statement\n");
            $$.path = NULL;
        }
        | statements Label statement
        {
            backPath($1.path, $2);
            $$.path = $3.path;
        }
        ;
statement:
        simple_stmt { $$.path = NULL; }
        | conditional_stmt { Trace("Reducing to conditional_stmt\n");  }
        | while_stmt  { Trace("Reducing to  while_stmt\n");  }
        | for_stmt  { Trace("Reducing to for_stmt \n");  }
        | return_stmt 
        {
            procReturn = true; 
            $$.path = NULL; 
        }
        ;

return_stmt: 
        RETURN boolean_expr ';'
        {
            returnCheck(LogicExprToExpr($2), curFunc->type);
            destroyExpr($2.expr);
            fgenCode("ireturn\n");
        }
        | RETURN ';'
        {
            //if(procReturn) semanticError("This procedure should have the vaild return statement");
            fgenCode("return\n");
        }
        ;
procedure_call: function_invoc ';' 
        {
            $$ = $1;
            //destroyExpr($1);
        }
        ;

function_invoc: 
        ID '(' arg_list ')'
        {
            Trace("Reducing to function_invoc \n");
            $$ = createFuncExpr($1, $3.first);
            genFunCallEnd($1);
            functionCheck($$);
        }
        ;

arg_list:
        /* no arguments */ { initExprList(&$$); }
        | arguments
        ;

arguments:
        boolean_expr
        {
            initExprList(&$$);
            addToExprList(&$$, LogicExprToExpr($1));
        }
        | arguments ',' boolean_expr
        {
            addToExprList(&$1, LogicExprToExpr($3)); 
            $$ = $1;
        }
        ;


while_stmt:
        WHILE Label condition 
        {
            conditionCheck($3.expr);
            destroyExpr($3.expr);
        }
        LOOP Label
        block_or_simple
        END LOOP ';'
        {
            Trace("End While Loop\n");
            genCode("goto ");
            int i = genLabel();
            struct PathList *tmp = mergePathList(createPathList(i), $7.path);
            backPath(tmp, $2);
            backPath($3.TList, $6);
            
            $$.path = $3.FList;
        }
        ;

for_stmt:
        FOR '(' variable_reference IN literalConstant 
        {
            if($5.type != Type_INT) semanticError("for loop range should be integer");
            genConstant($5);
            genStoreVar($3->name);
        }
        //$7(for loop start)
        Label '.' '.' literalConstant ')'
        {
            if($10.type != Type_INT) semanticError("for loop range should be integer");
            genLoadVar($3->name);
            genConstant($10);
            genOperand(Op_LEQUAL);
        }
        //$13 (TList)
        Label
        {
            genCode("goto ");
        }
        //$15 (FList)
        Label 
        LOOP Label
        block_or_simple END LOOP ';'
        {
            int increment_label = genLabel();
            genIncrement($3->name, 1);
            genCode("goto ");
            int i = genLabel();

            backPath($18.path, increment_label);
            backPath(createPathList(i), $7);

            // struct PathList *tmp = mergePathList(createPathList(i), $18.path);
            // backPath(tmp, $7);
            backPath(createPathList($13), $17);
            $$.path = createPathList($15);
            Trace("End For Loop\n");
            destroyExpr($3);
        }
        ;

block_or_simple:
        block 
        {
            $$.path = $1.path;
            Trace("Reducing to block_or_simple (block)\n"); 
        }
        | simple_stmt 
        {
            $$.path = NULL;
            Trace("Reducing to block_or_simple (simple)\n");
        }
        ;

IfGoto: {
  Trace("IfGoto\n");
  genCode("goto ");
  $$.path = createPathList(genLabel());
};

conditional_stmt:
        IF condition THEN Label
        block_or_simple IfGoto
        ELSE Label
        block_or_simple 
        END IF ';'
        {
            if (!$2.isLogicExpr) 
            {
                genCodeAt("ifeq ",$4);
                $2.TList = NULL;
                $2.FList = createPathList($4);
            }
            backPath($2.TList, $4);
            backPath($2.FList, $8);
            struct PathList *tmp = mergePathList($5.path, $6.path);
            $$.path = mergePathList(tmp, $9.path);
            destroyExpr($2.expr);
        }
        | IF condition THEN Label
        block_or_simple 
        END IF ';'
        {
            if (!$2.isLogicExpr) 
            {
                genCodeAt("ifeq ",$4);
                $2.TList = NULL; // fallthrough
                $2.FList = createPathList($4);
            }
            backPath($2.TList, $4);
            $$.path = mergePathList($2.FList, $5.path);
            destroyExpr($2.expr);
        }
        ;   

condition:
        {
            isCondition = true;
        }
        boolean_expr 
        {
            conditionCheck($2.expr);
            isCondition = false;
            $$ = $2;
        }
        ;

simple_stmt:
        variable_reference ASSIGN boolean_expr ';' 
        {
            assignCheck($1, $3.expr);
            genStoreVar($1->name);
            destroyExpr($1);
            destroyExpr($3.expr);
            Trace("Reducing to simple stmt (Assign statement)\n");
        }
        | print_keyword 
            {
                genPrintStart();
            }
            boolean_expr ';'
            {
                printCheck($3.expr);
                if($3.expr->type->type == Type_BOOL)
                {
                    genCode("iconst_1\n");
                    fgenCode("if_icmpeq BoolTrue%d\n", boolOperandLabel);
                    genCode("ldc \"false\"\n");
                    fgenCode("goto BoolPrint%d\n", boolOperandLabel);
                    fgenCode("BoolTrue%d:\n", boolOperandLabel);
                    genCode("ldc \"true\"\n");
                    fgenCode("BoolPrint%d:\n", boolOperandLabel);
                    boolOperandLabel++;
                    genPrintEnd($1, Type_STR);
                }
                else genPrintEnd($1, $3.expr->type->type);
                destroyExpr($3.expr);
                Trace("print statement\n"); 
            }
        | READ variable_reference ';'
        {
            destroyExpr($2);
        }
        | procedure_call
        {
            struct SymTableEntry * tmp = getSymbol($1->args->name);
            if(tmp->type->type != Type_VOID) genCode("pop\n");
            destroyExpr($1);
        }
        ;
print_keyword:
        PRINT {$$ = false;}
        | PRINTLN {$$ = true;}
        ;
/***************************************************/
/*******************Expression**********************/
/***************************************************/
variable_reference:
        ID 
        { 
            $$ = createVarExpr($1);
            varTypeCheck($$); 
        }
        ;
//The most Priority expression  
prior_expr:
        '(' boolean_expr ')' 
        { 
            $$ = $2; 
            Trace("Reducing to prior expression\n");
        }
        | variable_reference 
        {
            if(decConstantExpr) 
            {
                struct SymTableEntry* tmp = getSymbol($1->name);
                if(tmp->kind == SymbolKind_constant) $$ = ExprToLogicExpr(createLitExpr(tmp->attr.value));
                else semanticError("cannot use variable in constant expression!\n");
            }
            else
            {
                $$ = ExprToLogicExpr($1);
                genLoadVar($1->name);
                Trace("Reducing to prior expression by var ref\n");
            }
        }
        | function_invoc
        {
            $$ = ExprToLogicExpr($1);
        }
        ;

//Binary minus or liternal Constant          
factor:
        prior_expr { Trace("Reducing to factor\n"); }
        | literalConstant
        {
            $$ =  ExprToLogicExpr(createLitExpr($1));
            if(!decConstantExpr) genConstant($1);
        }
        | '-' prior_expr
        {
            if($2.expr->type->type != Type_INT) semanticError("invalid operand!\n");
            if(decConstantExpr)
            {
                $2.expr->lit.integer = -1 * $2.expr->lit.integer;
                $$ = $2;
            }
            else
            {
                $$ = ExprToLogicExpr(createExpr(Op_UMINUS, LogicExprToExpr($2), NULL));
                //-(neg)
                genOperand(Op_UMINUS);
                unaryOpCheck($$.expr);
                Trace("Unary minus expression\n");
            }
        }
        ;

// * or / expression
term:
        factor { Trace("Reducing to term\n"); }
        | term mul_op factor
        {
            if(decConstantExpr)
            {
                struct Constant tmpValue;
                tmpValue.type = Type_INT;
                if($1.expr->op != Op_LIT || $3.expr->op != Op_LIT) semanticError("constant value program error\n");
                if($1.expr->lit.type != Type_INT || $3.expr->lit.type != Type_INT) semanticError("invalid operand!\n");
                if($2 == Op_MULTIPLY) tmpValue.integer = $1.expr->lit.integer * $3.expr->lit.integer;
                else if($2 == Op_DIVIDE) tmpValue.integer = $1.expr->lit.integer / $3.expr->lit.integer;
                struct Expr* tmpExpr = createLitExpr(tmpValue);
                $$ = ExprToLogicExpr(tmpExpr);
                destroyExpr($1.expr);
                destroyExpr($3.expr);
            }
            else
            {
                $$ = createLogicExpr($2, $1, $3);
                arithOpCheck($$.expr);
                genOperand($2);
            }
        }
        ;
mul_op:
        '*' { Trace("Reducing to mul_op\n"); $$ = Op_MULTIPLY;}
        | '/' { Trace("Reducing to mul_op\n"); $$ = Op_DIVIDE;}
        ;
// + or - expression
expression:
        term { Trace("Reducing to expression\n"); }
        | expression add_op term
        {
            if(decConstantExpr)
            {
                struct Constant tmpValue;
                tmpValue.type = Type_INT;
                if($1.expr->op != Op_LIT || $3.expr->op != Op_LIT) semanticError("constant value program error\n");
                if($1.expr->lit.type != Type_INT || $3.expr->lit.type != Type_INT) semanticError("invalid operand!\n");
                if($2 == Op_PLUS) tmpValue.integer = $1.expr->lit.integer + $3.expr->lit.integer;
                else if($2 == Op_MINUS) tmpValue.integer = $1.expr->lit.integer - $3.expr->lit.integer;
                struct Expr* tmpExpr = createLitExpr(tmpValue);
                $$ = ExprToLogicExpr(tmpExpr);
                destroyExpr($1.expr);
                destroyExpr($3.expr);
            }
            else
            {
                $$ = createLogicExpr($2, $1, $3);
                arithOpCheck($$.expr);
                genOperand($2);
            }
            Trace("Reducing to expression by binary element\n");
        }
        ;
add_op:
        '+' { Trace("Reducing to add_op\n"); $$ = Op_PLUS; }
        | '-' { Trace("Reducing to add_op\n"); $$ = Op_MINUS; }
        ;
// relation operation
relation_expr:
        expression { Trace("Reducing to relation_expr\n"); }
        | relation_expr rel_op Label expression
        {
            if(decConstantExpr)
            {
                if($1.expr->op != Op_LIT || $4.expr->op != Op_LIT) semanticError("constant value program error!\n");
                if($1.expr->lit.type != Type_INT || $4.expr->lit.type != Type_INT) semanticError("invalid operand!\n");
                struct Constant tmpValue;
                tmpValue.type = Type_BOOL;
               
                int LValue = $1.expr->lit.integer;
                int RValue = $4.expr->lit.integer;
                switch ($2)
                {
                    case Op_LESS: tmpValue.boolean = (LValue < RValue); break;
                    case Op_LEQUAL: tmpValue.boolean = (LValue <= RValue); break;
                    case Op_EQUAL: tmpValue.boolean = (LValue == RValue); break;
                    case Op_GEQUAL: tmpValue.boolean = (LValue >= RValue); break;
                    case Op_GREATER: tmpValue.boolean = (LValue > RValue); break;
                    case Op_NOTEQUAL: tmpValue.boolean = (LValue != RValue); break;
                }
                struct Expr* tmpExpr = createLitExpr(tmpValue);
                $$ = ExprToLogicExpr(tmpExpr);
                destroyExpr($1.expr);
                destroyExpr($4.expr);
            }
            else 
            {
                $$ = createLogicExpr($2, $1, $4);
                relOpCheck($$.expr);
                genOperand($2);
                if(isCondition)
                {
                    $$.isLogicExpr = true;
                    $$.TList = createPathList(genLabel());
                    genCode("goto ");
                    $$.FList = createPathList(genLabel());
                }
                else
                {
                    $$.isLogicExpr = false;
                    fgenCode("BoolTrue%d\n", boolOperandLabel);
                    //false
                    genCode("iconst_0\n");
                    fgenCode("goto BoolOpEnd%d\n", boolOperandLabel);
                    fgenCode("BoolTrue%d:\n", boolOperandLabel);
                    genCode("iconst_1\n");
                    fgenCode("BoolOpEnd%d:\n", boolOperandLabel); 
                    boolOperandLabel++;
                }
            }
        }
        ;
rel_op:
        '<' { $$ = Op_LESS; }
        | LEEQ { $$ = Op_LEQUAL; }
        | '=' { $$ = Op_EQUAL; }
        | GREQ { $$ = Op_GEQUAL; }
        | '>' { $$ = Op_GREATER; }
        | NOTEQ { $$ = Op_NOTEQUAL; }
        ;

// not operation
boolean_factor:
        relation_expr { Trace("Reducing to boolean factor\n"); }
        | NOT boolean_factor
        {
            if(decConstantExpr)
            {
                if($2.expr->op != Op_LIT) semanticError("constant value program error\n");
                if($2.expr->lit.type != Type_BOOL) semanticError("invalid operand!\n");
                struct Constant tmpValue;
                tmpValue.type = Type_BOOL;
                tmpValue.boolean = !$2.expr->lit.boolean;
                struct Expr* tmpExpr = createLitExpr(tmpValue);
                $$ = ExprToLogicExpr(tmpExpr);
                destroyExpr($2.expr);
            }
            else
            {
                $$ = ExprToLogicExpr(createExpr(Op_NOT, $2.expr, NULL));
                unaryOpCheck($$.expr);
                if(isCondition)
                {
                    $$.isLogicExpr = $2.isLogicExpr;
                    if ($2.isLogicExpr) 
                    {
                        $$.TList = $2.FList;
                        $$.FList = $2.TList;
                    }
                }
                else
                {
                    genCode("iconst_1\n");
                    genOperand(Op_NOT);
                    $$.isLogicExpr = false;
                }
            }
        }
        ;
Label : {
    $$ = genLabel();
    Trace("New label\n");
};

// AND operation
boolean_term:
        boolean_factor { Trace("Reducing to boolean_term\n"); }
        | boolean_term AND Label boolean_factor
        {
            if(decConstantExpr)
            {
                if($1.expr->op != Op_LIT || $4.expr->op != Op_LIT) semanticError("constant value program error\n");
                if($1.expr->lit.type != Type_BOOL || $4.expr->lit.type != Type_BOOL) semanticError("invalid operand!\n");
                struct Constant tmpValue;
                tmpValue.type = Type_BOOL;
                tmpValue.boolean = $1.expr->lit.boolean && $4.expr->lit.boolean;
                struct Expr* tmpExpr = createLitExpr(tmpValue);
                $$ = ExprToLogicExpr(tmpExpr);
                destroyExpr($1.expr);
                destroyExpr($4.expr);
            }
            else 
            {
                $$ =  ExprToLogicExpr(createExpr(Op_AND, $1.expr, $4.expr));
                boolOpCheck($$.expr);

                if(isCondition)
                {
                    $$.isLogicExpr = true;
                    backPath($1.TList, $3);
                    $$.FList = mergePathList($1.FList, $4.FList);
                    $$.TList = $4.TList;
                }
                else
                {
                    $$.isLogicExpr = false;
                    genOperand(Op_AND);
                }
            }
        }
        ;

// Or operation
boolean_expr:
        boolean_term { Trace("Reducing to boolean_expr\n"); }
        | boolean_expr OR Label boolean_term
        {
            if(decConstantExpr)
            {
                if($1.expr->op != Op_LIT || $4.expr->op != Op_LIT) semanticError("constant value program error\n");
                if($1.expr->lit.type != Type_BOOL || $4.expr->lit.type != Type_BOOL) semanticError("invalid operand!\n");
                struct Constant tmpValue;
                tmpValue.type = Type_BOOL;
                tmpValue.boolean = $1.expr->lit.boolean || $4.expr->lit.boolean;
                struct Expr* tmpExpr = createLitExpr(tmpValue);
                $$ = ExprToLogicExpr(tmpExpr);
                destroyExpr($1.expr);
                destroyExpr($4.expr);
            }
            else 
            {
                $$ = ExprToLogicExpr(createExpr(Op_OR, $1.expr, $4.expr));
                boolOpCheck($$.expr);
                if(isCondition)
                {
                    $$.isLogicExpr = true;
                    backPath($1.FList, $3);
                    $$.TList = mergePathList($1.TList, $4.TList);
                    $$.FList = $4.FList;
                }
                else
                {
                    $$.isLogicExpr = false;
                    genOperand(Op_OR);
                }
            }
        }
        ;

/***************************************************/
/*******************Declaration*********************/
/***************************************************/

declarations:
        /* Empty */  { Trace("No declarations!\n"); }
        | DECLARE 
        {
            decConstantExpr = true;
        }
        declaration
        {
            decConstantExpr = false;
        }
        ;
declaration:
        /* Empty */
        | declaration varDeclar 
        | declaration constVarDeclar 
        ;

//Variable declaration
varDeclar:
        identifier_list ';'
        {
            struct Type * default_type = createType(Type_INT);
            assign_type(default_type, false);
            if(decGlobalVar) genGlobalVar(declaration, default_type, false, 0);
            else assign_localId(declaration);

            destroy_type(default_type);
            end_declar();
            Trace("Reducing to varAssignType\n");
        }
        | varAssignType ';' 
        {
            if(decGlobalVar) genGlobalVar(declaration, $1, false, 0);
            else assign_localId(declaration);
            destroy_type($1);
            Trace("Reducing to varDeclar\n");
            end_declar(); 
        }
        | identifier_list  ASSIGN  boolean_expr ';'  
        {
            if($3.expr->op != Op_LIT) semanticError("constVarDeclar program error\n");
            assign_type($3.expr->type, false);
            int initValue = 0;
            switch($3.expr->type->type)
            {
                case Type_STR: semanticError("The string variable cannot exist!\n"); break;
                case Type_BOOL: initValue = $3.expr->lit.boolean ? 1 : 0; break;
                case Type_INT: initValue = $3.expr->lit.integer; break;
            }
            // Global variable
            if(decGlobalVar) genGlobalVar(declaration, $3.expr->type, true, initValue);
            //Local variable
            else
            {
                assign_localId(declaration);
                genDeclarLocalVar(declaration, initValue);
            }
            Trace("Reducing to varDeclar\n");
            destroyExpr($3.expr);
            end_declar(); 
        }
        | varAssignType ASSIGN boolean_expr ';' 
        {
            if($3.expr->op != Op_LIT) semanticError("constVarDeclar program error\n");
            if($1->type != $3.expr->type->type)  semanticError("init error(left-side and right-side have different type)\n");

            assign_type($1, false);
            int initValue = 0;
            switch($3.expr->type->type)
            {
                case Type_STR: semanticError("The string variable cannot exist!\n"); break;
                case Type_BOOL: initValue = $3.expr->lit.boolean ? 1 : 0; break;
                case Type_INT: initValue = $3.expr->lit.integer; break;
            }
            // Globl Var
            if(decGlobalVar) genGlobalVar(declaration, $1, true, initValue);
            //Local var
            else
            {
                assign_localId(declaration);
                genDeclarLocalVar(declaration, initValue);
            }
            destroy_type($1);
            destroyExpr($3.expr);
            end_declar(); 
            Trace("Reducing to varDeclar\n");
        }
        ;

varAssignType:
        identifier_list ':' type
        {
            //declare global var
            assign_type($3, false);
            if(decProcPars) 
            {
                assign_localId(declaration);
                end_declar();
            }
            $$ = $3;
            
            Trace("Reducing to varAssignType\n");
        }
        ;

//Constant variable declaration
constVarDeclar:
        identifier_list  ':' CONSTANT ASSIGN boolean_expr ';' 
        {
            if($5.expr->op != Op_LIT) semanticError("constVarDeclar program error\n");
            //struct Type * tmp = createType($5.expr->type);
            assign_constant_value($5.expr->lit);
            assign_type($5.expr->type, true);
            //destroy_type(tmp);
            end_declar();
            destroyExpr($5.expr);
        }
        | identifier_list ':' CONSTANT ':' type ASSIGN boolean_expr ';' 
        { 
            if($7.expr->op != Op_LIT) semanticError("constVarDeclar program error\n");
            if($5->type != $7.expr->type->type) semanticError("init error(left-side and right-side have different type)\n");
            assign_type($5, true);
            destroy_type($5);
            assign_constant_value($7.expr->lit);
            Trace("Reducing to constVarDeclar\n");
            destroyExpr($7.expr);
            end_declar();
        }
        ;

// Multiple variable on same line
identifier_list:
         ID { addVar($1, SymbolKind_variable); }
         | identifier_list ',' ID { addVar($3, SymbolKind_variable); }
         ;

/***************************************************/
/****************Type And Constant******************/
/***************************************************/
type:
        type_keyword
        { 
            $$ = malloc(sizeof(struct Type));
            $$->type = $1;
            $$->itemType = NULL;
        }
        | type_keyword '[' literalConstant ']'
        {
            if ($3.type == Type_INT && $3.integer > 0)
            {
                $$ = malloc(sizeof(struct Type));
                $$->type = Type_ARRAY;
                $$->itemType = malloc(sizeof(struct ArrayItems));
                $$->itemType->type = $1;
                $$->itemType->size = $3.integer;
            }
            else
            {
                semanticError("Array should be defined by positive integer");
            }
        }
        ;

type_keyword:
             BOOLEAN  { $$ = Type_BOOL; }
             | INTEGER  { $$ = Type_INT; }
             | FLOAT  { $$ = Type_REAL; }
             | STRING  { $$ = Type_STR;}
             ;
literalConstant:
        LIT_INT { Trace("literal_integer \n");}
        | '-' LIT_INT 
        { 
            $$ = $2;
            $$.integer = -($$.integer);
            Trace("Minus integer\n");
        }

        | LIT_STR
        | LIT_REAL
        | '-' LIT_REAL 
        {
            $$ = $2;
            $$.real = -($$.real);
            Trace("Minus real\n");
        } 
        | BOOL_TRUE { $$.type = Type_BOOL; $$.boolean = true; }
        | BOOL_FALSE { $$.type = Type_BOOL; $$.boolean = false; }
        ;
%%


int yyerror(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

int main(int argc, char *argv[])
{
    /* open the source program file */
    if (argc != 2) {
        printf ("Usage: sc <filename> <outputName>\n");
        exit(1);
    }
    
    yyin = fopen(argv[1], "r");         /* open input file */
    if(!yyin)
    {
        printf("open file fail!\n");
        return 0;
    }

    
    initCodeGen(argv[1]);
    initSymbolTable();
    /* perform parsing */
    if (yyparse() == 1)                 /* parsing */
    {
        yyerror("Parsing error !");     /* syntax error */
    }
    printf("Success Parse File!\n");
    PrintSymbolTable();
    destroySymbolTable();
    EndCodeGen();
}


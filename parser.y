%{
#include "symtable.h"
#include "semcheck.h"
#include <stdio.h>
#include <stdlib.h>
extern int linenum;


#define Trace(t)  { if(DEBUG_FLAG){  if(ENABLE_BEFORE_LINENUMBER) {if(linenum >= DEBUG_BEFORE_LINENUMBER) printf(t);} else printf(t);} }
extern FILE *yyin;
extern int yylex(void);

struct SymTableEntry *curFunc = NULL;
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

%nonassoc LOWER_THEN_INDEX
%nonassoc '['




%token <name> ID

// literals
%token<literal> LIT_INT LIT_STR LIT_REAL


/* tokens */
%type<typeEnum> type_keyword 
%type<type> type varAssignType procedureReturn
%type<literal> literalConstant
%type<oper> mul_op add_op rel_op
%type<expr> variable_reference function_invoc
%type<expr> prior_expr factor term expression relation_expr boolean_factor boolean_term boolean_expr
%type<args> arg_list arguments
%type<funcArgs> paraDeclars
%%

/***************************************************/
/********************Main Block*********************/
/***************************************************/

program:        PROGRAM ID 
                {
                    addVar($2, SymbolKind_program);
                    nextScope();
                }
                programbody END ID
                {
                    Trace("Reducing to program\n");
                }
                ;

programbody: 
            declarations
                { 
                    Trace("Reducing to declarations \n");
                }
            procedureDeclars
                { 
                    Trace("Reducing to procedureDeclars \n");
                }
            compound_stmt
                {
                    Trace("Reducing to programbody\n");
                }
            
            ;
block: 
        {  
            nextScope(); 
        }
        declarations compound_stmt ';'
        {
            prevScope();
            Trace("Reducing to BLOCK\n"); 
        }
        ;

/***************************************************/
/****************Procedure Declare******************/
/***************************************************/
procedureDeclars:
        /* empty */ { Trace("No procedure!\n"); }
        | procedureDeclar 
        | procedureDeclars procedureDeclar
        ;

procedureDeclar:
        PROCEDURE ID 
        {
            addVar($2, SymbolKind_procedure);
            curFunc = getSymbol($2);
            nextScope();
        }
        paraDeclars
        {
            curFunc->args = $4;
            // struct Args* test = curFunc->args;
            // if(test == NULL) printf("No args!");
            // else
            // {
            //     while(test)
            //     {
            //         printf("%d, ",test->type->type);
            //         test = test->NEXT;
            //     }
            //     printf("\n");
            // }
            
            Trace("End this procedure's parameter declaration!\n");
        }
        procedureReturn
        {
            curFunc->type = $6;
        }
        {
            //the arg of the procedure has the same scope as the content 
            curScopeLevel--; 
        }
        block END ID ';'
        {
            Trace("End this procedure declaration!\n");
            curFunc = NULL;
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
            $$ = getArgs();
        }
        ;

paraDeclar:
        /* Empty */   { Trace("No parameters!\n"); }
        | varAssignType { Trace("add new parameter\n"); }
        | paraDeclar ';' varAssignType 
        ;

/***************************************************/
/********************statement**********************/
/***************************************************/
compound_stmt:
        BEGIN_  statements END
        ;

statements:
        /* empty */
        | statements statement
        ;
statement:
        simple_stmt
        | conditional_stmt { Trace("Reducing to conditional_stmt\n");  }
        | while_stmt  { Trace("Reducing to  while_stmt\n");  }
        | for_stmt  { Trace("Reducing to for_stmt \n");  }
        | procedure_call { Trace("Reducing to procedure_call \n");  }
        ;

procedure_call: function_invoc ';' 
        { 
            destroyExpr($1);
        }
        ;

function_invoc: 
        ID '(' arg_list ')'
        {
            Trace("Reducing to function_invoc \n");
            $$ = createFuncExpr($1, $3.first);
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
            addToExprList(&$$, $1);
        }
        | arguments ',' boolean_expr
        {
            addToExprList(&$1, $3); 
            $$ = $1;
        }
        ;

while_stmt:
        WHILE boolean_expr 
        {
            conditionCheck($2, "while");
            destroyExpr($2);
        }
        LOOP
        block_or_simple
        END LOOP ';'
        {
            Trace("End While Loop\n");
        }
        ;

for_stmt:
        FOR '(' variable_reference IN literalConstant '.' '.' literalConstant ')'
        {
            if($5.type != Type_INT || $8.type != Type_INT) semanticError("for loop range should be integer");
            //forCheck($5.integer, $8.integer); 
            destroyExpr($3);
        }
        LOOP block_or_simple END LOOP ';'
        {
           // if ($<boolVal>3) removeLoopVar(); 
            Trace("End For Loop\n");
        }
        ;

block_or_simple:
        block { Trace("Reducing to block_or_simple (block)\n"); }
        | simple_stmt { Trace("Reducing to block_or_simple (simple)\n"); }
        ;

conditional_stmt:
                IF condition THEN block_or_simple ELSE block_or_simple END IF ';'
                | IF condition THEN block_or_simple END IF ';'
                ;

condition:
        boolean_expr 
        {
            conditionCheck($1, "if");
            destroyExpr($1);
        }
        ;

simple_stmt:
        variable_reference ASSIGN boolean_expr ';' 
        { 
            assignCheck($1, $3);
            destroyExpr($3);
            Trace("Reducing to simple stmt (Assign statement)\n"); 
        }
        | print_keyword boolean_expr ';'
        { 
            printCheck($2);
            destroyExpr($2);
            Trace("print statement\n"); 
        }
        | READ variable_reference ';'
        {
            destroyExpr($2);
        }
        ;
print_keyword:
        PRINT
        | PRINTLN
        ;
/***************************************************/
/*******************Expression*********************/
/***************************************************/

variable_reference:
        ID %prec LOWER_THEN_INDEX
        { 
            $$ = createVarExpr($1);  
            varTypeCheck($$); 
        }
        | ID '[' boolean_expr ']'
        {
            $$ = createExpr(Op_INDEX, createVarExpr($1), $3);
            arrayTypeCheck($$);
            Trace("Reducing to a array element ref\n");

        }
        ;
        
prior_expr:
        '(' boolean_expr ')' 
        { 
            $$ = $2; 
            Trace("Reducing to prior expression\n");
        }
        | variable_reference { Trace("Reducing to prior expression by var ref\n"); }
        | function_invoc
        ;


factor:
        prior_expr { Trace("Reducing to factor\n"); }
        | literalConstant
        { 
            Trace("Reducing to factor by literalConstant\n");
            $$ = createLitExpr($1);
        }
        | '-' prior_expr
        {
            $$ = createExpr(Op_UMINUS, $2, NULL);
            unaryOpCheck($$);
            Trace("Unary minus expression\n");
        }
        ;

term:
        factor { Trace("Reducing to term\n"); }
        | term mul_op factor
        {
            $$ = createExpr($2, $1, $3);
            arithOpCheck($$);
        }
        ;
mul_op:
        '*' { Trace("Reducing to mul_op\n"); $$ = Op_MULTIPLY;}
        | '/' { Trace("Reducing to mul_op\n"); $$ = Op_DIVIDE;}
        ;
expression:
        term { Trace("Reducing to expression\n"); }
        | expression add_op term
        {
            Trace("Reducing to expression by binary element\n");
            $$ = createExpr($2, $1, $3);
            arithOpCheck($$);
        }
        ;
add_op:
        '+' { Trace("Reducing to add_op\n"); $$ = Op_PLUS; }
        | '-' { Trace("Reducing to add_op\n"); $$ = Op_MINUS; }
        ;

relation_expr:
        expression { Trace("Reducing to relation_expr\n"); }
        | relation_expr rel_op expression
        {
            $$ = createExpr($2, $1, $3);
            relOpCheck($$);
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

boolean_factor:
        relation_expr { Trace("Reducing to boolean factor\n"); }
        | NOT boolean_factor
        {
            $$ = createExpr(Op_NOT, $2, NULL);
            unaryOpCheck($$);
        }
        ;

boolean_term:
        boolean_factor { Trace("Reducing to boolean_term\n"); }
        | boolean_term AND boolean_factor
        {
            $$ = createExpr(Op_AND, $1, $3);
            boolOpCheck($$);
        }
        ;

boolean_expr:
        boolean_term { Trace("Reducing to boolean_expr\n"); }
        | boolean_expr OR boolean_term
        {  
            $$ = createExpr(Op_OR, $1, $3);
            boolOpCheck($$);
        }
        ;

/***************************************************/
/*******************Declaration*********************/
/***************************************************/

declarations:
        /* Empty */  { Trace("No declarations!\n"); }
        | DECLARE declaration
        ;
declaration:
        /* Empty */
        | declaration varDeclar 
        | declaration constVarDeclar { }
        ;


varDeclar:
        varAssignType ';' 
        { 
            destroy_type($1);
            Trace("Reducing to varDeclar\n");
        }
        | identifier_list  ASSIGN  boolean_expr ';'  
        { 
            if($3->type == NULL)
            {
                semanticError("init error(left-side and right-side have different type)");
                assign_type_byEnum(Type_VOID, false);
            }
            else
            {
                assign_type($3->type, false);
            }
            destroyExpr($3);
            Trace("Reducing to varDeclar\n");
        }
        | varAssignType ASSIGN boolean_expr ';' 
        {
            if($3->type == NULL || $1->type != $3->type->type)
            {
                semanticError("init error(left-side and right-side have different type)");
            }
            destroy_type($1);
            destroyExpr($3);
            Trace("Reducing to varDeclar\n");
        }
        ;

varAssignType:
        identifier_list ':' type
        {
            assign_type($3, false);
            $$ = $3;
            Trace("Reducing to varAssignType\n");
        }
        ;

constVarDeclar:
        identifier_list  ':' CONSTANT ASSIGN boolean_expr ';' 
        { 
            if($5->type == NULL)
            {
                semanticError("LSH is VOID type");
                assign_type_byEnum(Type_VOID, true);
            }
            assign_type($5->type, true);
        }
        | identifier_list ':' CONSTANT ':' type ASSIGN boolean_expr ';' 
        { 
            assign_type($5, true);
            if($7->type == NULL || $5->type != $7->type->type)
            {
                semanticError("init error(left-side and right-side have different type)");
            }
            destroy_type($5);
            destroyExpr($7);
            Trace("Reducing to constVarDeclar\n");
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
        type_keyword %prec LOWER_THEN_INDEX
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
            $$.integer = -($$.real);
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
    initSymbolTable();
    
    /* open the source program file */
    if (argc != 2) {
        printf ("Usage: sc filename\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");         /* open input file */
    if(yyin)
    {
        printf("open file success!\n");
    }
    else
    {
        printf("open file fail!\n");
        return 0;
    }
    /* perform parsing */
    if (yyparse() == 1)                 /* parsing */
    {
        yyerror("Parsing error !");     /* syntax error */
    }
    PrintSymbolTable();
    //clear
    destroySymbolTable();
}


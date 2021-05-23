%{
#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>
#define Trace(t)  { if(DEBUG_FLAG) printf(t); }
extern FILE *yyin;
%}

%union
{
    bool flag;
    enum TypeEnum typeEnum;
    char *name;
    struct Constant literal;
    struct Type type; 
}
%token BEGIN_
// Type keywords
%token BOOLEAN INTEGER FLOAT STRING CONSTANT
// Bool keywords
%token BOOL_TRUE BOOL_FALSE 
// Condition keywords
%token IF ELSE DO THEN WHILE BREAK CONTINUE FOR LOOP 
// Output keywords
%token PRINT PRINTLN
// Block keywords
%token PROGRAM PROCEDURE END DECLARE RETURN
// Logical Operation
%token OR NOT AND


//Other keywords
%token  OF  READ  CHARACTER EXIT CASE IN

//operation
%token ASSIGN

%token <name> ID

// literals
%token<literal> LIT_INT LIT_STR LIT_REAL


/* tokens */
%token SEMICOLON

%type<typeEnum> type_keyword procedureReturn
%type<type> type 
%type<literal> literalConstant
%%
program:        PROGRAM ID 
                {
                    addVar($2, SymbolKind_program);
                    clear_stack();
                }
                programbody END ID
                {

                    Trace("Reducing to program\n");
                }
                ;

programbody: 
            | declarations 
                { 
                    Trace("Reducing to declarations \n");
                }
            procedureDeclars
                { 
                    Trace("Reducing to procedureDeclars \n");
                }
            compound_stmt
                { 
                    Trace("Reducing to BLOCK\n");
                    Trace("Reducing to programbody\n");
                }
            
            ;

/***************************************************/
/********************Procedure**********************/
/***************************************************/
procedureDeclars :
        /* empty */ { Trace("No procedure!\n"); }
        | procedureDeclar 
        | procedureDeclars procedureDeclar
        ;

procedureDeclar:
        PROCEDURE ID 
        {
            addVar($2, SymbolKind_procedure);
            nextScope();
        }
        paraDeclars procedureReturn
        {
            assign_type($5, false);
            clear_stack();
        }
        declarations compound_stmt END ID ';'
        { 
            Trace("End this procedure declaration!\n");
            prevScope();
        }
        ;
compound_stmt:
        BEGIN_  END
        ;


procedureReturn:
        /* Empty */ {Trace("Return Type= Void!\n"); $$ = Type_VOID;}
        | RETURN type {$$ = $2.type;}
        ;
paraDeclars:
        /* Empty */ { Trace("No parameters!\n"); }
        | '(' paraDeclar ')'
        ;

paraDeclar:
        varDeclar
        | paraDeclar varDeclar
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
        | declaration varDeclar { }
        | declaration constVarDeclar { }
        ;

varDeclar:
        identifier_list ':' type ';' 
        { 
            if($3.type == Type_ARRAY)
            {
                assign_list_type($3);
            }
            else assign_type($3.type, false);
        }
        | identifier_list  ASSIGN  literalConstant ';'  
        { 
            /****This rule occur error in real ada****/
            assign_type($3.type, false);
        }
        | identifier_list ':' type ASSIGN literalConstant ';' 
        {
            if($3.type != $5.type) semanticError("init error(left-side and right-side have different type)");
            else
            {
                assign_type($3.type, false);
            }
        }
        ;
 
constVarDeclar:
        identifier_list  ':' CONSTANT ASSIGN literalConstant ';' 
        { 
            if($5.type == Type_ARRAY) semanticError("Array cannot define with keyword constant!");
            else assign_type($5.type, true);
        }
        | identifier_list ':' CONSTANT ':' type ASSIGN literalConstant ';' 
        { 
            if($5.type != $7.type) semanticError("init error(left-side and right-side have different type)");
            else assign_type($5.type, true);
        }
        ;

// Multiple variable on same line
identifier_list :
         ID { addVar($1, SymbolKind_variable); }
         | identifier_list ',' ID { addVar($3, SymbolKind_variable); }
         ;


type :
        type_keyword 
        { 
            Trace("Constant Type\n"); 
            $$.type = $1;
        }
        | type_keyword '[' literalConstant ']'
        {
            if ($3.type == Type_INT && $3.integer > 0)
            {
                Trace("Array Type\n");
                $$.type = Type_ARRAY;
                $$.itemType = $1;
                $$.size = $3.integer;
            }
            else
            {
                semanticError("Array can define by only positive integer!");
            }
        }
        ;

type_keyword :
             BOOLEAN  { $$ = Type_BOOL; }
             | INTEGER  { $$ = Type_INT; }
             | FLOAT  { $$ = Type_REAL; }
             | STRING  { $$ = Type_STR;}
             ;
literalConstant:
        LIT_INT { Trace("literal_integer \n");}
        | LIT_STR
        | LIT_REAL
        | BOOL_TRUE { $$.type = Type_BOOL; $$.boolean = true; }
        | BOOL_FALSE { $$.type = Type_BOOL; $$.boolean = false; }
        ;
%%


yyerror(msg)
char *msg;
{
    fprintf(stderr, "%s\n", msg);
}

main(int argc, char *argv[])
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
        return;
    }
    /* perform parsing */
    if (yyparse() == 1)                 /* parsing */
    {
        yyerror("Parsing error !");     /* syntax error */
    }
    PrintSymbolTable();
    //clear
    initSymbolTable();
}


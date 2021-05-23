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
/***********************************************/
/*TODO pushScope() implement in symtable.h/.c  */
/***********************************************/
programbody: 
            | DECLARE programDeclars                 
                { 
                    Trace("End program variable declaration!\n");
                }
            procedureDecls
                { 
                    nextScope();
                    Trace("Procedure Declaration\n");
                }
                { 
                    Trace("Reducing to DECLAREBODY\n");
                }
             ;

/***************************************************/
/********************Procedure**********************/
/***************************************************/
procedureDecls :
        /* empty */ { Trace("Empty procedure Declaration\n"); }
        | procedureDeclar
        | procedureDecls procedureDeclar
        ;
procedureDeclar:
        PROCEDURE ID parameters procedureReturn END ID ';'
        {
            addVar($2, SymbolKind_procedure);
            assign_type($4, false);
            clear_stack();
        }
        ;

procedureReturn:
        /* Empty */ {$$ = Type_VOID;}
        | RETURN type {$$ = $2.type;}
        ;
parameters:
        /* Empty */
        | '(' parameterDecalrs ')'
        ;

parameterDecalrs:
        varDeclar
        | parameterDecalrs varDeclar
        ;
/***************************************************/
/*******************Declaration*********************/
/***************************************************/
programDeclars:
        /* Empty */
        | programDeclars varDeclar { }
        | programDeclars constVarDeclar { }
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
semi:           SEMICOLON
                {
                    Trace("Reducing to semi\n");
                }
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


%{
#define Trace(t)        printf(t)
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
%}

%union
{
    enum TypeEnum typeEnum;
    char *name;
    struct Constant literal;
    struct Type *type;
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

%token <name> ID

// literals
%token<literal> LIT_INT LIT_STR LIT_REAL


/* tokens */
%token SEMICOLON

%type<type> type
%type<typeEnum> scalar_type
%type<literal> literalConstant
%type<name> identifier
%%
program:        PROGRAM ID programbody END ID
                { 
                     Trace("Reducing to program\n");
                }
                ;
/***********************************************/
/*TODO pushScope() implement in symtable.h/.c  */
/***********************************************/
programbody:    programDeclars
                ;

programDeclars:
          /*Empty*/
         | programDeclars varDeclar
         | programDeclars constVarDeclar
         ;

varDeclar:
         ID ":" type ";"
         | ID ":=" literalConstant ";" { }
         | ID ":" type ":=" literalConstant ";" {}
         ;
 
constVarDeclar:
         ID ":" CONSTANT ":=" literalConstant ";"
         | ID ":" CONSTANT ":" type ";"
         ;

type :
         scalar_type
         {
             $$ = malloc(sizeof(struct Type));
             $$->itemType = NULL;
             $$->type = $1;
         }
scalar_type :
             BOOLEAN  { $$ = Type_BOOL; }
             | INTEGER  { $$ = Type_INT; }
             | FLOAT  { $$ = Type_REAL; }
             | STRING  { $$ = Type_STR;}
             ;
literalConstant:
         LIT_INT
         | LIT_STR
         | LIT_REAL
         | BOOL_TRUE { $$.type = Type_BOOL; $$.boolean = true; }
         | BOOL_FALSE { $$.type = Type_BOOL; $$.boolean = false; }
         ;

identifier	: ID { $$ = $1; }
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
    /* open the source program file */
    if (argc != 2) {
        printf ("Usage: sc filename\n");
        exit(1);
    }
    printf("%s",argv[1]);
    yyin = fopen(argv[1], "r");         /* open input file */
    if(yyin)
    {
        printf("open success\n");
    }
    else
    {
        printf("open fail!\n");
        return;
    }
    
    /* perform parsing */
    if (yyparse() == 1)                 /* parsing */
        yyerror("Parsing error !");     /* syntax error */
}


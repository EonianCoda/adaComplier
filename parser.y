%{
#define Trace(t)        printf(t)
#include "symtable.h"



%}

%union
{
    char *name;
    struct Constant literal;
}


/* tokens */
%token SEMICOLON
%token 


%%
program:        PROGRAM ID programbody END ID
                { 
                     Trace("Reducing to program\n");
                }
                ;
programbody:    D

declar
semi:           SEMICOLON
                {
                    Trace("Reducing to semi\n");
                }
                ;
%%
#include "lex.yy.c"

yyerror(msg)
char *msg;
{
    fprintf(stderr, "%s\n", msg);
}

main()
{
    /* open the source program file */
    if (argc != 2) {
        printf ("Usage: sc filename\n");
        exit(1);
    }
    yyin = fopen(argv[1], "r");         /* open input file */

    /* perform parsing */
    if (yyparse() == 1)                 /* parsing */
        yyerror("Parsing error !");     /* syntax error */
}


%{
#include <stdio.h>
#include <stdlib.h>

#include "y.tab.h"
%}
%%
[0-9]+   {
             yylval = atoi(yytext);
             return NUMBER;
         }
\n           return 0;
[ \t]        ;
.            return yytext[0];

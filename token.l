%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structure.h"
#include "y.tab.h"

#define LIST				strcat(buf,yytext)
#define ADD_STRING(s)		strcat(stringTmp,s)
#define token(t) 			{LIST; return t;}
#define tokenInteger(i) 	{LIST; printf("<integer:%d>\n",i); yylval.literal.type = Type_INT; yylval.literal.integer = i; return LIT_INT;}
#define tokenString(s) 	{LIST; printf("<String:%s>\n",s);  yylval.literal.type = Type_STRING; yylval.literal.str = s; return LIT_STRING;}
#define tokenReal(r)        {LIST; printf("<real:%e>\n",r);  yylval.literal.type = Type_REAL; yylval.literal.real = r; return LIT_REAL;}
#define tokenBoolean(b)     {LIST; printf("<boolean:%s>\n",b);  yylval.literal.type = Type_BOOL; yylval.literal.boolean = b; return LIT_BOOL;}

#define MAX_LINE_LENG 256

int linenum = 1;
char buf[MAX_LINE_LENG];
char stringTmp[MAX_LINE_LENG];

%}

%x	blockComment
%x	inlineComment
%x	isString

%%
<*>\r                   ;
<*>[ \t]*  			    {LIST;}

<INITIAL>\n             {
                            LIST;
                            printf("%d: %s", linenum++, buf);
                            buf[0] = '\0';
                        }

--						{
                            LIST;
                            BEGIN inlineComment;
                        }
<inlineComment>.        {LIST;}

<inlineComment>\n       {
                            LIST;
                            printf("%d: %s", linenum++, buf);
                            buf[0] = '\0';
                            BEGIN INITIAL;
                        }

"{"                     {
                            LIST;
                            BEGIN blockComment;
						}

<blockComment>[^\n}]  {LIST;}

<blockComment>\n        {
                            LIST;
                            printf("%d: %s", linenum++, buf);
                            buf[0] = '\0';
                        }

<blockComment>"}"       {
                            LIST;
                            BEGIN INITIAL;
                        }

\"                      {
                            LIST;
                            BEGIN isString;
                        }

<isString>\"\"          {
                            LIST;
                            ADD_STRING("\"");
                        }

<isString>[^\n"]+      {
                            LIST;
                            ADD_STRING(yytext);
                        }

<isString>\n            {
                            LIST;
                            printf("%d:%s\n", linenum+1, buf);
                            printf("bad character:'%s'\n",yytext);
                            exit(-1);
                        }

<isString>\"            {
                            tokenString(stringTmp);
                            stringTmp[0] = '\0';
                            BEGIN INITIAL;
                        }

[+-]?[0-9]+     {tokenInteger(atoi(yytext));}

[+-]?[0-9]+\.[0-9]+([eE][-+]?[0-9]+)?	{tokenReal(atof(yytext));}

","					{token(",");}
":"					{token(":");}
"."					{token(".");}
";"					{token(";");}
"("					{token("(");}
")"					{token(")");}
"["					{token("[");}
"]"					{token("]");}
"+"					{token("+");}
"-"					{token("-");}
"*"					{token("*");}
"/"					{token("/");}
"%"					{token("%");}
"<"					{token("<");}
"<="				{token("<=");}
">="				{token(">=");}
">"					{token(">");}
"="					{token("=");}
"/="				{token("/=");}
":="				{token(":=");}


[bB][eE][gG][iI][nN]					{token("BEGIN");}
[bB][oO][oO][lL][eE][aA][nN]			{token("BOOLEAN");}
[bB][rR][eE][aA][kK]					{token("BREAK");}
[cC][hH][aA][rR][aA][cC][tT][eE][rR]	{token("CHARACTER");}
[cC][aA][sS][eE]						{token("CASE");}
[cC][oO][nN][tT][iI][nN][uU][eE]		{token("CONTINUE");}
[cC][oO][nN][sS][tT][aA][nN][tT]		{token("CONSTANT");}
[dD][eE][cC][lL][aA][rR][eE]			{token("DECLARE");}
[dD][oO]								{token("DO");}
[eE][lL][sS][eE]						{token("ELSE");}
[eE][nN][dD]							{token("END");}
[eE][xX][iI][tT]						{token("EXIT");}
[fF][lL][oO][aA][tT]					{token("FLOAT");}
[fF][oO][rR]							{token("FOR");}
[iI][fF]								{token("IF");}
[iI][nN]								{token("IN");}
[iI][nN][tT][eE][gG][eE][rR]			{token("INTEGER");}
[lL][oO][oO][pP]						{token("LOOP");}
[pP][rR][iI][nN][tT]					{token("PRINT");}
[pP][rR][iI][nN][tT][lL][nN]			{token("PRINTLN");}
[pP][rR][oO][cC][eE][dD][uU][rR][eE]	{token("PROCEDURE");}
[pP][rR][oO][gG][rR][aA][mM]			{token("PROGRAM");}
[rR][eE][tT][uU][rR][nN]				{token("RETURN");}
[sS][tT][rR][iI][nN][gG]				{token("STRING");}
[tT][hH][eE][nN]						{token("THEN");}
[wW][hH][iI][lL][eE]					{token("WHILE");}


[tT][rR][uU][eE]						{tokenBoolean("true");}
[fF][aA][lL][sS][eE]					{tokenBoolean("false");}
[aA][nN][dD]							{token(AND);}
[nN][oO][tT]							{token(NOT);}
[oO][rR]								{token(OR);}

[a-zA-Z][a-zA-Z0-9_]*   {	
                            yylval.name = yytext;
                            return ID;
                        }

<*>.                {
                        LIST;
                        printf("%d:%s\n", linenum+1, buf);
                        printf("bad character:'%s'\n",yytext);
                        exit(-1);
                    }

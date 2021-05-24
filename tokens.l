%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "y.tab.h"
#define LIST				strcat(buf,yytext)
#define ADD_STRING(s)		strcat(stringTmp,s)
#define token(t) 			{LIST; if (DEBUG_FLAG) printf("<token: %s>\n", t);}
#define symbolToken(t)      {LIST; if (DEBUG_FLAG) printf("<Symbol:'%c'>\n", t); return (t);}
#define tokenInteger(i) 	{LIST; if (DEBUG_FLAG) printf("<integer:%d>\n",i); yylval.literal.type = Type_INT; yylval.literal.integer = i; return (LIT_INT);}
#define tokenReal(r)        {LIST; if (DEBUG_FLAG) printf("<real:%e>\n",r);  yylval.literal.type = Type_REAL; yylval.literal.real = r; return (LIT_REAL);}

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
                            LIST;
                            printf("<String:%s>\n",stringTmp);
                            int n = strlen(stringTmp);
                            char *tmp = malloc(n + 1);
                            strncpy(tmp, stringTmp, n);
                            tmp[n] = '\0';
                            yylval.literal.type = Type_STR;
                            yylval.literal.str = tmp;
                            stringTmp[0] = '\0';
                            BEGIN INITIAL;
                            return (LIT_STR);
                        }

[0-9]+     {tokenInteger(atoi(yytext));}

[0-9]+\.[0-9]+([eE][-+]?[0-9]+)?	{tokenReal(atof(yytext));}

","					{symbolToken(',');}
":"					{symbolToken(':');}
"."					{symbolToken('.');}
";"					{symbolToken(';');}
"("  				{symbolToken('(');}
")"					{symbolToken(')');}
"["					{symbolToken('[');}
"]"					{symbolToken(']');}
"+"					{symbolToken('+');}
"-"					{symbolToken('-');}
"*"					{symbolToken('*');}
"/"					{symbolToken('/');}
"%"					{symbolToken('%');}
"<"					{symbolToken('<');}
">"					{symbolToken('>');}
"="					{symbolToken('=');}


"!="				{
                       LIST;
                       token("NOTEQ")
                       return NOTEQ;
                    }
"<="				{
                       LIST;
                       token("LEEQ")
                       return LEEQ;
                    }
">="				{
                       LIST;
                       token("GREQ")
                       return GREQ;
                    }
"/="				{
                       LIST;
                       token("DIVEQ")
                       return DIVEQ;
                    }
":="				{
                        LIST;
                        token("ASSIGN")
                        return ASSIGN;
                    }


[bB][eE][gG][iI][nN]					{
                                            token("BEGIN");
                                            return BEGIN_;
                                        }
[bB][oO][oO][lL][eE][aA][nN]			{
                                            token("BOOLEAN");
                                            return BOOLEAN;
                                        }
[bB][rR][eE][aA][kK]					{
                                            token("BREAK");
                                            return BREAK;
                                        }
[cC][hH][aA][rR][aA][cC][tT][eE][rR]	{
                                            token("CHARACTER");
                                            return CHARACTER;
                                        }
[cC][aA][sS][eE]						{
                                            token("CASE");
                                            return CASE;
                                        }
[cC][oO][nN][tT][iI][nN][uU][eE]		{
                                            token("CONTINUE");
                                            return CONTINUE;
                                        }
[cC][oO][nN][sS][tT][aA][nN][tT]		{
                                            token("CONSTANT");
                                            return CONSTANT;
                                        }
[dD][eE][cC][lL][aA][rR][eE]			{
                                            token("DECLARE");
                                            return DECLARE;
                                        }
[dD][oO]								{
                                            token("DO");
                                            return DO;
                                        }
[eE][lL][sS][eE]						{
                                            token("ELSE");
                                            return ELSE;
                                        }
[eE][nN][dD]							{
                                            token("END");
                                            return END;
                                        }
[eE][xX][iI][tT]						{
                                            token("EXIT");
                                            return EXIT;
                                        }
[fF][lL][oO][aA][tT]					{
                                            token("FLOAT");
                                            return FLOAT;
                                        }
[fF][oO][rR]							{
                                            token("FOR");
                                            return FOR;
                                        }
[iI][fF]								{
                                            token("IF");
                                            return IF;
                                        }
[iI][nN]								{
                                            token("IN");
                                            return IN;
                                        }
[iI][nN][tT][eE][gG][eE][rR]			{
                                            token("INTEGER");
                                            return INTEGER;
                                        }
[lL][oO][oO][pP]						{
                                            token("LOOP");
                                            return LOOP;
                                        }
[pP][rR][iI][nN][tT]					{
                                            token("PRINT");
                                            return PRINT;
                                        }
[pP][rR][iI][nN][tT][lL][nN]			{
                                            token("PRINTLN");
                                            return PRINTLN;
                                        }
[pP][rR][oO][cC][eE][dD][uU][rR][eE]	{
                                            token("PROCEDURE");
                                            return PROCEDURE;
                                        }
[pP][rR][oO][gG][rR][aA][mM]			{
                                            token("PROGRAM");
                                            return PROGRAM;
                                        }
[rR][eE][tT][uU][rR][nN]				{
                                            token("RETURN");
                                            return RETURN;
                                        }
[sS][tT][rR][iI][nN][gG]				{
                                            token("STRING");
                                            return STRING;
                                        }
[tT][hH][eE][nN]						{
                                            token("THEN");
                                            return THEN;
                                        }
[wW][hH][iI][lL][eE]					{
                                            token("WHILE");
                                            return WHILE;
                                        }

[tT][rR][uU][eE]						{
                                            token("BOOL_TRUE");
                                            return BOOL_TRUE;
                                        }
[fF][aA][lL][sS][eE]					{
                                            token("BOOL_FALSE");
                                            return BOOL_FALSE;
                                        }
[aA][nN][dD]							{
                                            token("AND");
                                            return AND;
                                        }
[nN][oO][tT]							{
                                            token("NOT");
                                            return NOT;
                                        }
[oO][rR]								{
                                            token("OR");
                                            return OR;
                                        }

[a-zA-Z][a-zA-Z0-9_]*   {	
                            LIST;
                            if (DEBUG_FLAG)
                            {
                                printf("<ID:%s>\n", yytext);
                            }
                            
                            size_t n = yyleng;
                            char *nstr = malloc(n + 1);
                            strncpy(nstr, yytext, n);
                            nstr[n] = '\0'; 
                            yylval.name = nstr;
                            return ID;
                        }

<*>.                {
                        LIST;
                        printf("%d:%s\n", linenum+1, buf);
                        printf("bad character:'%s'\n",yytext);
                        exit(-1);
                    }

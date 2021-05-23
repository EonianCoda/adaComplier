/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BEGIN_ = 258,
    BOOLEAN = 259,
    INTEGER = 260,
    FLOAT = 261,
    STRING = 262,
    CONSTANT = 263,
    BOOL_TRUE = 264,
    BOOL_FALSE = 265,
    IF = 266,
    ELSE = 267,
    DO = 268,
    THEN = 269,
    WHILE = 270,
    BREAK = 271,
    CONTINUE = 272,
    FOR = 273,
    LOOP = 274,
    PRINT = 275,
    PRINTLN = 276,
    PROGRAM = 277,
    PROCEDURE = 278,
    END = 279,
    DECLARE = 280,
    RETURN = 281,
    OR = 282,
    NOT = 283,
    AND = 284,
    OF = 285,
    READ = 286,
    CHARACTER = 287,
    EXIT = 288,
    CASE = 289,
    IN = 290,
    ASSIGN = 291,
    ID = 292,
    LIT_INT = 293,
    LIT_STR = 294,
    LIT_REAL = 295,
    SEMICOLON = 296
  };
#endif
/* Tokens.  */
#define BEGIN_ 258
#define BOOLEAN 259
#define INTEGER 260
#define FLOAT 261
#define STRING 262
#define CONSTANT 263
#define BOOL_TRUE 264
#define BOOL_FALSE 265
#define IF 266
#define ELSE 267
#define DO 268
#define THEN 269
#define WHILE 270
#define BREAK 271
#define CONTINUE 272
#define FOR 273
#define LOOP 274
#define PRINT 275
#define PRINTLN 276
#define PROGRAM 277
#define PROCEDURE 278
#define END 279
#define DECLARE 280
#define RETURN 281
#define OR 282
#define NOT 283
#define AND 284
#define OF 285
#define READ 286
#define CHARACTER 287
#define EXIT 288
#define CASE 289
#define IN 290
#define ASSIGN 291
#define ID 292
#define LIT_INT 293
#define LIT_STR 294
#define LIT_REAL 295
#define SEMICOLON 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 10 "parser.y" /* yacc.c:1909  */

    bool flag;
    enum TypeEnum typeEnum;
    char *name;
    struct Constant literal;
    struct Type type; 

#line 144 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

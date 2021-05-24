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
    PRINT = 259,
    PRINTLN = 260,
    BOOLEAN = 261,
    INTEGER = 262,
    FLOAT = 263,
    STRING = 264,
    CONSTANT = 265,
    BOOL_TRUE = 266,
    BOOL_FALSE = 267,
    IF = 268,
    ELSE = 269,
    DO = 270,
    THEN = 271,
    WHILE = 272,
    BREAK = 273,
    CONTINUE = 274,
    FOR = 275,
    LOOP = 276,
    PROGRAM = 277,
    PROCEDURE = 278,
    END = 279,
    DECLARE = 280,
    RETURN = 281,
    OF = 282,
    READ = 283,
    CHARACTER = 284,
    EXIT = 285,
    CASE = 286,
    IN = 287,
    ASSIGN = 288,
    OR = 289,
    AND = 290,
    NOT = 291,
    LEEQ = 292,
    NOTEQ = 293,
    GREQ = 294,
    DIVEQ = 295,
    LOWER_THEN_INDEX = 296,
    ID = 297,
    LIT_INT = 298,
    LIT_STR = 299,
    LIT_REAL = 300,
    SEMICOLON = 301
  };
#endif
/* Tokens.  */
#define BEGIN_ 258
#define PRINT 259
#define PRINTLN 260
#define BOOLEAN 261
#define INTEGER 262
#define FLOAT 263
#define STRING 264
#define CONSTANT 265
#define BOOL_TRUE 266
#define BOOL_FALSE 267
#define IF 268
#define ELSE 269
#define DO 270
#define THEN 271
#define WHILE 272
#define BREAK 273
#define CONTINUE 274
#define FOR 275
#define LOOP 276
#define PROGRAM 277
#define PROCEDURE 278
#define END 279
#define DECLARE 280
#define RETURN 281
#define OF 282
#define READ 283
#define CHARACTER 284
#define EXIT 285
#define CASE 286
#define IN 287
#define ASSIGN 288
#define OR 289
#define AND 290
#define NOT 291
#define LEEQ 292
#define NOTEQ 293
#define GREQ 294
#define DIVEQ 295
#define LOWER_THEN_INDEX 296
#define ID 297
#define LIT_INT 298
#define LIT_STR 299
#define LIT_REAL 300
#define SEMICOLON 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "parser.y" /* yacc.c:1909  */

    bool flag;
    enum TypeEnum typeEnum;
    enum Operator oper;
    char *name;
    struct Constant literal;
    struct Type *type;
    struct Expr *expr;

#line 156 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

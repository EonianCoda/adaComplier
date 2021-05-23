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
    BOOLEAN = 258,
    INTEGER = 259,
    FLOAT = 260,
    STRING = 261,
    CONSTANT = 262,
    BOOL_TRUE = 263,
    BOOL_FALSE = 264,
    IF = 265,
    ELSE = 266,
    DO = 267,
    THEN = 268,
    WHILE = 269,
    BREAK = 270,
    CONTINUE = 271,
    FOR = 272,
    LOOP = 273,
    PRINT = 274,
    PRINTLN = 275,
    PROGRAM = 276,
    PROCEDURE = 277,
    END = 278,
    DECLARE = 279,
    RETURN = 280,
    OR = 281,
    NOT = 282,
    AND = 283,
    OF = 284,
    READ = 285,
    CHARACTER = 286,
    EXIT = 287,
    CASE = 288,
    IN = 289,
    ID = 290,
    LIT_INT = 291,
    LIT_STR = 292,
    LIT_REAL = 293,
    SEMICOLON = 294
  };
#endif
/* Tokens.  */
#define BOOLEAN 258
#define INTEGER 259
#define FLOAT 260
#define STRING 261
#define CONSTANT 262
#define BOOL_TRUE 263
#define BOOL_FALSE 264
#define IF 265
#define ELSE 266
#define DO 267
#define THEN 268
#define WHILE 269
#define BREAK 270
#define CONTINUE 271
#define FOR 272
#define LOOP 273
#define PRINT 274
#define PRINTLN 275
#define PROGRAM 276
#define PROCEDURE 277
#define END 278
#define DECLARE 279
#define RETURN 280
#define OR 281
#define NOT 282
#define AND 283
#define OF 284
#define READ 285
#define CHARACTER 286
#define EXIT 287
#define CASE 288
#define IN 289
#define ID 290
#define LIT_INT 291
#define LIT_STR 292
#define LIT_REAL 293
#define SEMICOLON 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 11 "parser.y" /* yacc.c:1909  */

    enum TypeEnum typeEnum;
    char *name;
    struct Constant literal;
    struct Type *type;

#line 139 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

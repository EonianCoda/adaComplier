/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include "symtable.h"
#include "semcheck.h"
#include <stdio.h>
#include <stdlib.h>
extern int linenum;


#define Trace(t)  { if(DEBUG_FLAG){  if(ENABLE_BEFORE_LINENUMBER) {if(linenum >= DEBUG_BEFORE_LINENUMBER) printf(t);} else printf(t);} }
extern FILE *yyin;
extern int yylex(void);


#line 80 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
    LIT_REAL = 300
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "parser.y" /* yacc.c:355  */

    bool flag;
    enum TypeEnum typeEnum;
    enum Operator oper;
    char *name;
    struct Constant literal;
    struct Type *type;
    struct Expr *expr;
    struct ExprList args;

#line 221 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 238 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   176

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  183

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      55,    56,    46,    44,    60,    45,    57,    47,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    59,    54,
      37,    42,    41,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    58,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    38,    39,    40,    43,    48,    50,    51,    52,
      53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    74,    74,    73,    87,    91,    86,   101,   107,   108,
     109,   114,   119,   123,   113,   135,   136,   139,   140,   144,
     145,   146,   153,   156,   158,   161,   162,   163,   164,   169,
     168,   183,   182,   196,   197,   201,   202,   206,   214,   220,
     224,   231,   232,   239,   244,   254,   259,   263,   264,   269,
     278,   279,   286,   287,   290,   291,   299,   300,   304,   305,
     319,   320,   321,   322,   323,   324,   325,   329,   330,   338,
     339,   347,   348,   360,   361,   363,   365,   366,   371,   376,
     390,   403,   412,   421,   436,   437,   442,   449,   468,   469,
     470,   471,   474,   475,   482,   483,   484,   490,   491
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BEGIN_", "PRINT", "PRINTLN", "BOOLEAN",
  "INTEGER", "FLOAT", "STRING", "CONSTANT", "BOOL_TRUE", "BOOL_FALSE",
  "IF", "ELSE", "DO", "THEN", "WHILE", "BREAK", "CONTINUE", "FOR", "LOOP",
  "PROGRAM", "PROCEDURE", "END", "DECLARE", "RETURN", "OF", "READ",
  "CHARACTER", "EXIT", "CASE", "IN", "ASSIGN", "OR", "AND", "NOT", "'<'",
  "LEEQ", "NOTEQ", "GREQ", "'>'", "'='", "DIVEQ", "'+'", "'-'", "'*'",
  "'/'", "LOWER_THEN_INDEX", "'['", "ID", "LIT_INT", "LIT_STR", "LIT_REAL",
  "';'", "'('", "')'", "'.'", "']'", "':'", "','", "$accept", "program",
  "$@1", "programbody", "$@2", "$@3", "block", "procedureDeclars",
  "procedureDeclar", "$@4", "$@5", "$@6", "procedureReturn", "paraDeclars",
  "paraDeclar", "compound_stmt", "statements", "statement", "while_stmt",
  "$@7", "for_stmt", "$@8", "block_or_simple", "conditional_stmt",
  "condition", "simple_stmt", "print_stmt", "variable_reference",
  "prior_expr", "factor", "term", "mul_op", "expression", "add_op",
  "relation_expr", "rel_op", "boolean_factor", "boolean_term",
  "boolean_expr", "declarations", "declaration", "varDeclar",
  "varAssignType", "constVarDeclar", "identifier_list", "type",
  "type_keyword", "literalConstant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,    60,   292,   293,
     294,    62,    61,   295,    43,    45,    42,    47,   296,    91,
     297,   298,   299,   300,    59,    40,    41,    46,    93,    58,
      44
};
# endif

#define YYPACT_NINF -133

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-133)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       3,   -40,    48,  -133,  -133,    28,  -133,    33,  -133,    12,
      37,    53,  -133,  -133,   -17,  -133,   -24,  -133,    42,    53,
    -133,    22,  -133,    22,    97,    50,  -133,    75,  -133,  -133,
    -133,    22,    70,    62,  -133,  -133,  -133,    22,  -133,  -133,
    -133,   -15,    86,    76,  -133,    99,   -12,  -133,     9,  -133,
    -133,  -133,  -133,   -21,  -133,    87,  -133,    80,  -133,  -133,
    -133,  -133,  -133,  -133,    22,   -16,  -133,  -133,    44,  -133,
    -133,    44,  -133,  -133,  -133,  -133,  -133,  -133,  -133,    44,
      22,    22,  -133,  -133,    22,   120,    57,    12,  -133,     0,
     -19,  -133,  -133,   -15,    86,  -133,    99,    10,   104,    40,
      81,    68,  -133,    73,   112,    22,    22,    22,    22,    85,
    -133,    91,  -133,  -133,  -133,  -133,  -133,  -133,   109,  -133,
    -133,    22,  -133,    12,  -133,   120,   120,  -133,    25,    26,
     127,   110,   110,    91,    92,    22,    32,  -133,  -133,    28,
    -133,  -133,     2,   124,   115,  -133,    47,  -133,   125,    75,
    -133,     5,  -133,     2,    57,  -133,    98,  -133,     2,   137,
     128,    94,   100,   129,   101,   135,   102,  -133,   144,  -133,
     106,    57,   107,  -133,   108,  -133,  -133,   141,     2,   134,
     142,   111,  -133
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,    73,    75,     0,     4,    74,
       0,     8,    84,    76,     0,    77,     0,     3,     0,     5,
       9,     0,    78,     0,     0,     0,    11,     0,    10,    97,
      98,     0,     0,    43,    92,    94,    95,     0,    46,    47,
      50,    54,    58,    67,    69,    71,     0,    48,     0,    88,
      89,    90,    91,     0,    81,    86,    85,    17,    23,     6,
      68,    93,    96,    49,     0,     0,    52,    53,     0,    56,
      57,     0,    60,    61,    65,    63,    64,    62,    66,     0,
       0,     0,    80,    79,     0,     0,     0,    19,    12,     0,
       0,    45,    51,    55,    59,    70,    72,     0,     0,     0,
       0,     0,    20,     0,    15,     0,     0,     0,     0,     0,
      22,     0,    24,    27,    28,    26,    25,    39,     0,    44,
      82,     0,    87,     0,    18,     0,     0,    13,     0,     0,
       0,    37,    29,     0,     0,     0,     0,    21,    16,    73,
      41,    42,    73,     0,     0,    40,     0,    83,     0,     0,
      33,     0,    34,    73,     0,    38,     0,     7,    73,     0,
       0,     0,     0,     0,     0,     0,     0,    14,     0,    36,
       0,     0,     0,    30,     0,    35,    31,     0,    73,     0,
       0,     0,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -133,  -133,  -133,  -133,  -133,  -133,    27,  -133,   148,  -133,
    -133,  -133,  -133,  -133,  -133,    19,  -133,  -133,  -133,  -133,
    -133,  -133,  -132,  -133,  -133,    82,  -133,   -88,   138,   105,
     103,  -133,    90,  -133,  -133,  -133,   -29,    95,   -23,   167,
    -133,  -133,   -76,  -133,   166,   -77,  -133,   -83
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,     7,    11,    27,   150,    19,    20,    57,
     104,   139,   127,    88,   101,    59,    89,   112,   113,   143,
     114,   177,   151,   115,   130,   152,   117,    38,    39,    40,
      41,    68,    42,    71,    43,    79,    44,    45,    46,   149,
       9,    13,    14,    15,   103,    54,    55,    47
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      48,   118,    60,   100,   105,   106,   105,   106,    98,    23,
       3,   102,    84,   107,    65,    81,    21,   108,    81,   158,
     109,   160,    81,   134,   110,     1,   163,     6,   111,   159,
     111,    66,    67,    29,    30,    24,    25,    22,    85,   119,
      91,    90,    82,    81,    81,   144,   179,   137,     4,   138,
      33,    95,    33,     6,   118,    29,    30,    10,    31,    81,
      81,    97,    12,    83,   120,   118,    81,    32,    29,    30,
     118,   161,    33,    34,    35,    36,    18,    37,    58,   140,
     141,    81,   128,   129,   131,   132,   147,    17,   174,    32,
     118,    61,    26,    62,    33,    34,    35,    36,   136,    37,
      56,   155,    99,    49,    50,    51,    52,    53,    34,    35,
      36,    64,   146,    72,    73,    74,    75,    76,    77,    78,
      33,    61,   123,    62,   124,    37,    49,    50,    51,    52,
      69,    70,   125,    25,    80,    87,    86,   121,   126,   122,
     133,    33,   135,   142,    81,   153,   145,   154,   162,   156,
     164,   166,   165,   168,   167,   169,   170,   172,   180,   171,
     173,   175,   178,   181,   176,   182,   148,    28,   157,    94,
      63,   116,     8,    92,    93,    16,    96
};

static const yytype_uint8 yycheck[] =
{
      23,    89,    31,    86,     4,     5,     4,     5,    85,    33,
      50,    87,    33,    13,    37,    34,    33,    17,    34,    14,
      20,   153,    34,   111,    24,    22,   158,    25,    28,    24,
      28,    46,    47,    11,    12,    59,    60,    54,    59,    58,
      56,    64,    54,    34,    34,   133,   178,   123,     0,   126,
      50,    80,    50,    25,   142,    11,    12,    24,    36,    34,
      34,    84,    50,    54,    54,   153,    34,    45,    11,    12,
     158,   154,    50,    51,    52,    53,    23,    55,     3,    54,
      54,    34,   105,   106,   107,   108,    54,    50,   171,    45,
     178,    51,    50,    53,    50,    51,    52,    53,   121,    55,
      50,    54,    45,     6,     7,     8,     9,    10,    51,    52,
      53,    49,   135,    37,    38,    39,    40,    41,    42,    43,
      50,    51,    54,    53,    56,    55,     6,     7,     8,     9,
      44,    45,    59,    60,    35,    55,    49,    33,    26,    58,
      55,    50,    33,    16,    34,    21,    54,    32,    50,    24,
      13,    57,    24,    24,    54,    54,    21,    13,    24,    57,
      54,    54,    21,    21,    56,    54,   139,    19,   149,    79,
      32,    89,     5,    68,    71,     9,    81
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    22,    62,    50,     0,    63,    25,    64,   100,   101,
      24,    65,    50,   102,   103,   104,   105,    50,    23,    68,
      69,    33,    54,    33,    59,    60,    50,    66,    69,    11,
      12,    36,    45,    50,    51,    52,    53,    55,    88,    89,
      90,    91,    93,    95,    97,    98,    99,   108,    99,     6,
       7,     8,     9,    10,   106,   107,    50,    70,     3,    76,
      97,    51,    53,    89,    49,    99,    46,    47,    92,    44,
      45,    94,    37,    38,    39,    40,    41,    42,    43,    96,
      35,    34,    54,    54,    33,    59,    49,    55,    74,    77,
      99,    56,    90,    91,    93,    97,    98,    99,   106,    45,
     108,    75,   103,   105,    71,     4,     5,    13,    17,    20,
      24,    28,    78,    79,    81,    84,    86,    87,    88,    58,
      54,    33,    58,    54,    56,    59,    26,    73,    99,    99,
      85,    99,    99,    55,    88,    33,    99,   103,   106,    72,
      54,    54,    16,    80,    88,    54,    99,    54,    67,   100,
      67,    83,    86,    21,    32,    54,    24,    76,    14,    24,
      83,   108,    50,    83,    13,    24,    57,    54,    24,    54,
      21,    57,    13,    54,   108,    54,    56,    82,    21,    83,
      24,    21,    54
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    63,    62,    65,    66,    64,    67,    68,    68,
      68,    70,    71,    72,    69,    73,    73,    74,    74,    75,
      75,    75,    76,    77,    77,    78,    78,    78,    78,    80,
      79,    82,    81,    83,    83,    84,    84,    85,    86,    86,
      86,    87,    87,    88,    88,    89,    89,    90,    90,    90,
      91,    91,    92,    92,    93,    93,    94,    94,    95,    95,
      96,    96,    96,    96,    96,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   101,   101,   101,   102,   102,
     102,   103,   104,   104,   105,   105,   106,   106,   107,   107,
     107,   107,   108,   108,   108,   108,   108,   108,   108
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     6,     0,     0,     5,     2,     0,     1,
       2,     0,     0,     0,    11,     0,     2,     0,     3,     0,
       1,     3,     3,     0,     2,     1,     1,     1,     1,     0,
       8,     0,    15,     1,     1,     9,     7,     1,     4,     1,
       3,     3,     3,     1,     4,     3,     1,     1,     1,     2,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       3,     1,     3,     0,     2,     0,     2,     2,     2,     4,
       4,     3,     6,     8,     1,     3,     1,     4,     1,     1,
       1,     1,     1,     2,     1,     1,     2,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 74 "parser.y" /* yacc.c:1646  */
    {
                    addVar((yyvsp[0].name), SymbolKind_program);
                    clear_stack();
                }
#line 1456 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 79 "parser.y" /* yacc.c:1646  */
    {

                    Trace("Reducing to program\n");
                }
#line 1465 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 87 "parser.y" /* yacc.c:1646  */
    { 
                    Trace("Reducing to declarations \n");
                }
#line 1473 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 91 "parser.y" /* yacc.c:1646  */
    { 
                    Trace("Reducing to procedureDeclars \n");
                }
#line 1481 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 95 "parser.y" /* yacc.c:1646  */
    {
                    Trace("Reducing to programbody\n");
                }
#line 1489 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 101 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to BLOCK\n"); }
#line 1495 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 107 "parser.y" /* yacc.c:1646  */
    { Trace("No procedure!\n"); }
#line 1501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 114 "parser.y" /* yacc.c:1646  */
    {
            addVar((yyvsp[0].name), SymbolKind_procedure);
            nextScope();
        }
#line 1510 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 119 "parser.y" /* yacc.c:1646  */
    {
            Trace("End this procedure's parameter declaration!\n");
        }
#line 1518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 123 "parser.y" /* yacc.c:1646  */
    {
            assign_type_byEnum((yyvsp[0].typeEnum), false);
            clear_stack();
        }
#line 1527 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 128 "parser.y" /* yacc.c:1646  */
    { 
            Trace("End this procedure declaration!\n");
            prevScope();
        }
#line 1536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 135 "parser.y" /* yacc.c:1646  */
    {Trace("Return Type= Void!\n"); (yyval.typeEnum) = Type_VOID;}
#line 1542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 136 "parser.y" /* yacc.c:1646  */
    {(yyval.typeEnum) = (yyvsp[0].type)->type;}
#line 1548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 139 "parser.y" /* yacc.c:1646  */
    { Trace("No parameters!\n"); }
#line 1554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 144 "parser.y" /* yacc.c:1646  */
    { Trace("No parameters!\n"); }
#line 1560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 145 "parser.y" /* yacc.c:1646  */
    { Trace("add new parameter\n"); }
#line 1566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 162 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to conditional_stmt\n");  }
#line 1572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 163 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to  while_stmt\n");  }
#line 1578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 164 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to for_stmt \n");  }
#line 1584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 169 "parser.y" /* yacc.c:1646  */
    {
            conditionCheck((yyvsp[0].expr), "while");
            destroyExpr((yyvsp[0].expr));
        }
#line 1593 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 176 "parser.y" /* yacc.c:1646  */
    {
            Trace("End While Loop\n");
        }
#line 1601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 183 "parser.y" /* yacc.c:1646  */
    {
            if((yyvsp[-4].literal).type != Type_INT || (yyvsp[-1].literal).type != Type_INT) semanticError("for loop range should be integer");
            //forCheck($5.integer, $8.integer); 
            destroyExpr((yyvsp[-6].expr));
        }
#line 1611 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 189 "parser.y" /* yacc.c:1646  */
    {
           // if ($<boolVal>3) removeLoopVar(); 
            Trace("End For Loop\n");
        }
#line 1620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 196 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to block_or_simple (block)\n"); }
#line 1626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 197 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to block_or_simple (simple)\n"); }
#line 1632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 207 "parser.y" /* yacc.c:1646  */
    {
            conditionCheck((yyvsp[0].expr), "if");
            destroyExpr((yyvsp[0].expr));
        }
#line 1641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 215 "parser.y" /* yacc.c:1646  */
    { 
            assignCheck((yyvsp[-3].expr), (yyvsp[-1].expr));
            destroyExpr((yyvsp[-1].expr));
            Trace("Reducing to simple stmt (Assign statement)\n"); 
        }
#line 1651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 221 "parser.y" /* yacc.c:1646  */
    { 
            Trace("print statement\n"); 
        }
#line 1659 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 225 "parser.y" /* yacc.c:1646  */
    {
            destroyExpr((yyvsp[-1].expr));
        }
#line 1667 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 240 "parser.y" /* yacc.c:1646  */
    { 
            (yyval.expr) = createVarExpr((yyvsp[0].name));  
            varTypeCheck((yyval.expr)); 
        }
#line 1676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 245 "parser.y" /* yacc.c:1646  */
    {
            (yyval.expr) = createExpr(Op_INDEX, createVarExpr((yyvsp[-3].name)), (yyvsp[-1].expr));
            arrayTypeCheck((yyval.expr));
            Trace("Reducing to a array element ref\n");

        }
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 255 "parser.y" /* yacc.c:1646  */
    { 
            (yyval.expr) = (yyvsp[-1].expr); 
            Trace("Reducing to prior expression\n");
        }
#line 1696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 259 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to prior expression by var ref\n"); }
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 263 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to factor\n"); }
#line 1708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 265 "parser.y" /* yacc.c:1646  */
    { 
            Trace("Reducing to factor by literalConstant\n");
            (yyval.expr) = createLitExpr((yyvsp[0].literal));
        }
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 270 "parser.y" /* yacc.c:1646  */
    {
            (yyval.expr) = createExpr(Op_UMINUS, (yyvsp[0].expr), NULL);
            unaryOpCheck((yyval.expr));
            Trace("Unary minus expression\n");
        }
#line 1727 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 278 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to term\n"); }
#line 1733 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 280 "parser.y" /* yacc.c:1646  */
    {
            (yyval.expr) = createExpr((yyvsp[-1].oper), (yyvsp[-2].expr), (yyvsp[0].expr));
            arithOpCheck((yyval.expr));
        }
#line 1742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 286 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to mul_op\n"); (yyval.oper) = Op_MULTIPLY;}
#line 1748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 287 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to mul_op\n"); (yyval.oper) = Op_DIVIDE;}
#line 1754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 290 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to expression\n"); }
#line 1760 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 292 "parser.y" /* yacc.c:1646  */
    {
            Trace("Reducing to expression by binary element\n");
            (yyval.expr) = createExpr((yyvsp[-1].oper), (yyvsp[-2].expr), (yyvsp[0].expr));
            arithOpCheck((yyval.expr));
        }
#line 1770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 299 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to add_op\n"); (yyval.oper) = Op_PLUS; }
#line 1776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 300 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to add_op\n"); (yyval.oper) = Op_MINUS; }
#line 1782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 304 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to relation_expr\n"); }
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 306 "parser.y" /* yacc.c:1646  */
    {
            if( (yyvsp[-1].oper) == Op_DIVIDEEQ)
            {
                Trace("/= TODO");
            }
            else
            {
                (yyval.expr) = createExpr((yyvsp[-1].oper), (yyvsp[-2].expr), (yyvsp[0].expr));
                relOpCheck((yyval.expr));
            }
        }
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 319 "parser.y" /* yacc.c:1646  */
    { (yyval.oper) = Op_LESS; }
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 320 "parser.y" /* yacc.c:1646  */
    { (yyval.oper) = Op_LEQUAL; }
#line 1816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 321 "parser.y" /* yacc.c:1646  */
    { (yyval.oper) = Op_EQUAL; }
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 322 "parser.y" /* yacc.c:1646  */
    { (yyval.oper) = Op_GEQUAL; }
#line 1828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 323 "parser.y" /* yacc.c:1646  */
    { (yyval.oper) = Op_GREATER; }
#line 1834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 324 "parser.y" /* yacc.c:1646  */
    { (yyval.oper) = Op_NOTEQUAL; }
#line 1840 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 325 "parser.y" /* yacc.c:1646  */
    { (yyval.oper) = Op_DIVIDEEQ; }
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 329 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to boolean factor\n"); }
#line 1852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 331 "parser.y" /* yacc.c:1646  */
    {
            (yyval.expr) = createExpr(Op_NOT, (yyvsp[0].expr), NULL);
            unaryOpCheck((yyval.expr));
        }
#line 1861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 338 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to boolean_term\n"); }
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 340 "parser.y" /* yacc.c:1646  */
    {
            (yyval.expr) = createExpr(Op_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
            boolOpCheck((yyval.expr));
        }
#line 1876 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 347 "parser.y" /* yacc.c:1646  */
    { Trace("Reducing to boolean_expr\n"); }
#line 1882 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 349 "parser.y" /* yacc.c:1646  */
    {  
            (yyval.expr) = createExpr(Op_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
            boolOpCheck((yyval.expr));
        }
#line 1891 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 360 "parser.y" /* yacc.c:1646  */
    { Trace("No declarations!\n"); }
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 365 "parser.y" /* yacc.c:1646  */
    { }
#line 1903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 366 "parser.y" /* yacc.c:1646  */
    { }
#line 1909 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 372 "parser.y" /* yacc.c:1646  */
    { 
            destroy_type((yyvsp[-1].type));
            Trace("Reducing to varDeclar\n");
        }
#line 1918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 377 "parser.y" /* yacc.c:1646  */
    { 
            if((yyvsp[-1].expr)->type == NULL)
            {
                semanticError("init error(left-side and right-side have different type)");
                assign_type_byEnum(Type_VOID, false);
            }
            else
            {
                assign_type((yyvsp[-1].expr)->type, false);
            }
            destroyExpr((yyvsp[-1].expr));
            Trace("Reducing to varDeclar\n");
        }
#line 1936 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 391 "parser.y" /* yacc.c:1646  */
    {
            if((yyvsp[-1].expr)->type == NULL || (yyvsp[-3].type)->type != (yyvsp[-1].expr)->type->type)
            {
                semanticError("init error(left-side and right-side have different type)");
            }
            destroy_type((yyvsp[-3].type));
            destroyExpr((yyvsp[-1].expr));
            Trace("Reducing to varDeclar\n");
        }
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 404 "parser.y" /* yacc.c:1646  */
    {
            assign_type((yyvsp[0].type), false);
            (yyval.type) = (yyvsp[0].type);
            Trace("Reducing to varAssignType\n");
        }
#line 1960 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 413 "parser.y" /* yacc.c:1646  */
    { 
            if((yyvsp[-1].expr)->type == NULL)
            {
                semanticError("LSH is VOID type");
                assign_type_byEnum(Type_VOID, true);
            }
            assign_type((yyvsp[-1].expr)->type, true);
        }
#line 1973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 422 "parser.y" /* yacc.c:1646  */
    { 
            assign_type((yyvsp[-3].type), true);
            if((yyvsp[-1].expr)->type == NULL || (yyvsp[-3].type)->type != (yyvsp[-1].expr)->type->type)
            {
                semanticError("init error(left-side and right-side have different type)");
            }
            destroy_type((yyvsp[-3].type));
            destroyExpr((yyvsp[-1].expr));
            Trace("Reducing to constVarDeclar\n");
        }
#line 1988 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 436 "parser.y" /* yacc.c:1646  */
    { addVar((yyvsp[0].name), SymbolKind_variable); }
#line 1994 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 437 "parser.y" /* yacc.c:1646  */
    { addVar((yyvsp[0].name), SymbolKind_variable); }
#line 2000 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 443 "parser.y" /* yacc.c:1646  */
    { 
            Trace("Constant Type\n"); 
            (yyval.type) = malloc(sizeof(struct Type));
            (yyval.type)->type = (yyvsp[0].typeEnum);
            (yyval.type)->itemType = NULL;
        }
#line 2011 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 450 "parser.y" /* yacc.c:1646  */
    {
            if ((yyvsp[-1].literal).type == Type_INT && (yyvsp[-1].literal).integer > 0)
            {
                Trace("Array Type!\n");
                (yyval.type) = malloc(sizeof(struct Type));
                (yyval.type)->type = Type_ARRAY;
                (yyval.type)->itemType = malloc(sizeof(struct ArrayItems));
                (yyval.type)->itemType->type = (yyvsp[-3].typeEnum);
                (yyval.type)->itemType->size = (yyvsp[-1].literal).integer;
            }
            else
            {
                semanticError("Array can define by only positive integer!");
            }
        }
#line 2031 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 468 "parser.y" /* yacc.c:1646  */
    { (yyval.typeEnum) = Type_BOOL; }
#line 2037 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 469 "parser.y" /* yacc.c:1646  */
    { (yyval.typeEnum) = Type_INT; }
#line 2043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 470 "parser.y" /* yacc.c:1646  */
    { (yyval.typeEnum) = Type_REAL; }
#line 2049 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 471 "parser.y" /* yacc.c:1646  */
    { (yyval.typeEnum) = Type_STR;}
#line 2055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 474 "parser.y" /* yacc.c:1646  */
    { Trace("literal_integer \n");}
#line 2061 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 476 "parser.y" /* yacc.c:1646  */
    { 
            (yyval.literal) = (yyvsp[0].literal);
            (yyval.literal).integer = -((yyval.literal).real);
            Trace("Minus integer\n");
        }
#line 2071 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 485 "parser.y" /* yacc.c:1646  */
    {
            (yyval.literal) = (yyvsp[0].literal);
            (yyval.literal).real = -((yyval.literal).real);
            Trace("Minus real\n");
        }
#line 2081 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 490 "parser.y" /* yacc.c:1646  */
    { (yyval.literal).type = Type_BOOL; (yyval.literal).boolean = true; }
#line 2087 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 491 "parser.y" /* yacc.c:1646  */
    { (yyval.literal).type = Type_BOOL; (yyval.literal).boolean = false; }
#line 2093 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2097 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 493 "parser.y" /* yacc.c:1906  */



int yyerror(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

int main(int argc, char *argv[])
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
        return 0;
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


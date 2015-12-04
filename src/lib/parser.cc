/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "parser.yy"

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Copyright 2005-2011 Google, Inc.
// All Rights Reserved.
//
// Author: wojciech@google.com (Wojciech Skut)
//         ttai@google.com (Terry Tai)
//         rws@google.com (Richard Sproat)
//
// Bison parser for FST generation.

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <thrax/compat/utils.h>
#include <thrax/collection-node.h>
#include <thrax/fst-node.h>
#include <thrax/function-node.h>
#include <thrax/grammar-node.h>
#include <thrax/identifier-node.h>
#include <thrax/import-node.h>
#include <thrax/node.h>
#include <thrax/return-node.h>
#include <thrax/rule-node.h>
#include <thrax/statement-node.h>
#include <thrax/string-node.h>
#include <thrax/grm-compiler.h>
#include <thrax/lexer.h>

DECLARE_bool(always_export);

using namespace thrax;

#define YYPARSE_PARAM parm
#define YYLEX_PARAM parm
#define CTRL (static_cast<GrmCompilerParserInterface*>(parm))

class FuncOrStmt {
public:
  CollectionNode *funcs_;
  CollectionNode *stmts_;
};

namespace thrax_rewriter {
  int yylex(void *, void *parm);
  int yyerror(const char *);


/* Line 268 of yacc.c  */
#line 130 "parser.cc"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     tDESCR = 258,
     tDQSTRING = 259,
     tQSTRING = 260,
     tINTEGER = 261,
     tFLOAT = 262,
     tLPAREN = 263,
     tRPAREN = 264,
     tLBRACE = 265,
     tRBRACE = 266,
     tPIPE = 267,
     tSTAR = 268,
     tPLUS = 269,
     tQMARK = 270,
     tDOT = 271,
     tCOMMA = 272,
     tAT = 273,
     tCOLON = 274,
     tSEMICOLON = 275,
     tEQUALS = 276,
     tCONCAT = 277,
     tUNARY = 278,
     tDOLLAR = 279,
     tLBRACKET = 280,
     tRBRACKET = 281,
     tANGLE_STRING = 282,
     tSLASH = 283,
     tUNDERSCORE = 284,
     tMINUS = 285,
     tREAD_STRINGS = 286,
     tREAD_WEIGHTED_STRINGS = 287,
     tCASE_INSENSITIVE = 288,
     tKEYWORD_EXPORT = 289,
     tKEYWORD_FUNC = 290,
     tKEYWORD_RETURN = 291,
     tKEYWORD_BYTE = 292,
     tKEYWORD_UTF8 = 293,
     tKEYWORD_AS = 294,
     tKEYWORD_IMPORT = 295
   };
#endif
/* Tokens.  */
#define tDESCR 258
#define tDQSTRING 259
#define tQSTRING 260
#define tINTEGER 261
#define tFLOAT 262
#define tLPAREN 263
#define tRPAREN 264
#define tLBRACE 265
#define tRBRACE 266
#define tPIPE 267
#define tSTAR 268
#define tPLUS 269
#define tQMARK 270
#define tDOT 271
#define tCOMMA 272
#define tAT 273
#define tCOLON 274
#define tSEMICOLON 275
#define tEQUALS 276
#define tCONCAT 277
#define tUNARY 278
#define tDOLLAR 279
#define tLBRACKET 280
#define tRBRACKET 281
#define tANGLE_STRING 282
#define tSLASH 283
#define tUNDERSCORE 284
#define tMINUS 285
#define tREAD_STRINGS 286
#define tREAD_WEIGHTED_STRINGS 287
#define tCASE_INSENSITIVE 288
#define tKEYWORD_EXPORT 289
#define tKEYWORD_FUNC 290
#define tKEYWORD_RETURN 291
#define tKEYWORD_BYTE 292
#define tKEYWORD_UTF8 293
#define tKEYWORD_AS 294
#define tKEYWORD_IMPORT 295




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 61 "parser.yy"

  int                        int_type;
  FunctionNode*              function_node_type;
  ImportNode*                import_node_type;
  ReturnNode*                return_node_type;
  RuleNode*                  rule_node_type;
  IdentifierNode*            identifier_node_type;
  CollectionNode*            collection_node_type;
  StatementNode*             statement_node_type;
  FstNode*                   fst_node_type;
  StringNode*                string_node_type;
  GrammarNode*               grammar_node_type;
  Node*                      node_type;
  FuncOrStmt*                function_or_statement_node_type;



/* Line 293 of yacc.c  */
#line 264 "parser.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 276 "parser.cc"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   126

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNRULES -- Number of states.  */
#define YYNSTATES  116

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     8,     9,    12,    13,    16,    19,
      20,    23,    25,    27,    29,    32,    36,    41,    47,    49,
      51,    53,    55,    57,    59,    61,    63,    66,    68,    72,
      74,    78,    80,    84,    87,    90,    94,    96,   100,   102,
     106,   108,   112,   115,   118,   121,   128,   133,   135,   139,
     141,   143,   145,   149,   153,   157,   161,   165,   167,   170,
     172,   174,   176,   178,   180,   186,   189,   194,   197,   200,
     204,   206,   210
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      42,     0,    -1,    43,    44,    -1,     1,    -1,    -1,    70,
      43,    -1,    -1,    46,    44,    -1,    71,    44,    -1,    -1,
      46,    45,    -1,    48,    -1,    47,    -1,    70,    -1,     1,
      20,    -1,    36,    52,    20,    -1,    50,    21,    49,    20,
      -1,    34,    50,    21,    49,    20,    -1,    52,    -1,     3,
      -1,    68,    -1,    63,    -1,    62,    -1,    57,    -1,    56,
      -1,    65,    -1,    60,    53,    -1,    60,    -1,    61,    12,
      54,    -1,    61,    -1,    55,    30,    53,    -1,    53,    -1,
       8,    52,     9,    -1,    50,    58,    -1,    25,    26,    -1,
      25,    59,    26,    -1,    52,    -1,    52,    17,    59,    -1,
      37,    -1,    37,    17,    59,    -1,    38,    -1,    38,    17,
      59,    -1,    51,    13,    -1,    51,    14,    -1,    51,    15,
      -1,    51,    10,    66,    17,    66,    11,    -1,    51,    10,
      66,    11,    -1,    51,    -1,    61,    18,    55,    -1,    55,
      -1,    50,    -1,    67,    -1,    67,    16,    37,    -1,    67,
      16,    38,    -1,    67,    16,    62,    -1,    67,    16,    57,
      -1,    54,    19,    54,    -1,    54,    -1,    64,    69,    -1,
      64,    -1,     6,    -1,     4,    -1,     5,    -1,    27,    -1,
      40,    68,    39,    50,    20,    -1,     1,    20,    -1,    35,
      50,    72,    74,    -1,     1,    11,    -1,    25,    26,    -1,
      25,    73,    26,    -1,    50,    -1,    50,    17,    73,    -1,
      10,    45,    11,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   134,   134,   139,   146,   147,   154,   158,   161,   168,
     169,   175,   180,   185,   188,   194,   200,   206,   212,   217,
     227,   228,   229,   230,   231,   235,   240,   246,   252,   258,
     264,   270,   276,   282,   290,   292,   297,   301,   306,   311,
     315,   320,   328,   332,   336,   340,   351,   358,   364,   370,
     375,   383,   388,   393,   398,   404,   413,   419,   424,   430,
     437,   442,   449,   456,   463,   467,   473,   477,   483,   485,
     490,   494,   500
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tDESCR", "tDQSTRING", "tQSTRING",
  "tINTEGER", "tFLOAT", "tLPAREN", "tRPAREN", "tLBRACE", "tRBRACE",
  "tPIPE", "tSTAR", "tPLUS", "tQMARK", "tDOT", "tCOMMA", "tAT", "tCOLON",
  "tSEMICOLON", "tEQUALS", "tCONCAT", "tUNARY", "tDOLLAR", "tLBRACKET",
  "tRBRACKET", "tANGLE_STRING", "tSLASH", "tUNDERSCORE", "tMINUS",
  "tREAD_STRINGS", "tREAD_WEIGHTED_STRINGS", "tCASE_INSENSITIVE",
  "tKEYWORD_EXPORT", "tKEYWORD_FUNC", "tKEYWORD_RETURN", "tKEYWORD_BYTE",
  "tKEYWORD_UTF8", "tKEYWORD_AS", "tKEYWORD_IMPORT", "$accept", "grammar",
  "import_list", "func_or_stmt_list", "stmt_list", "stmt", "return_stmt",
  "rule_stmt", "rule_body", "descriptor", "atomic_obj", "obj",
  "concat_fst", "union_fst", "difference_fst", "grouped_obj",
  "funccall_obj", "funccall_arglist", "funccall_arguments",
  "repetition_fst", "composition_fst", "identifier_obj", "string_fst",
  "fst_with_output", "fst_with_weight", "number", "quoted_fst_string",
  "quoted_string", "weight", "import_request", "func_decl", "func_arglist",
  "func_arguments", "func_body", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    42,    43,    43,    44,    44,    44,    45,
      45,    46,    46,    46,    46,    47,    48,    48,    49,    50,
      51,    51,    51,    51,    51,    52,    53,    53,    54,    54,
      55,    55,    56,    57,    58,    58,    59,    59,    59,    59,
      59,    59,    60,    60,    60,    60,    60,    60,    61,    61,
      62,    63,    63,    63,    63,    63,    64,    64,    65,    65,
      66,    67,    68,    69,    70,    70,    71,    71,    72,    72,
      73,    73,    74
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     2,     0,     2,     2,     0,
       2,     1,     1,     1,     2,     3,     4,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     3,     1,
       3,     1,     3,     2,     2,     3,     1,     3,     1,     3,
       1,     3,     2,     2,     2,     6,     4,     1,     3,     1,
       1,     1,     3,     3,     3,     3,     3,     1,     2,     1,
       1,     1,     1,     1,     5,     2,     4,     2,     2,     3,
       1,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     0,     0,     0,    65,    62,     0,     1,
       0,    19,     0,     0,     0,     2,     0,    12,    11,     0,
      13,     0,     0,     5,     0,    67,    14,     0,     0,    61,
       0,    50,    47,     0,    31,    57,    49,    24,    23,    27,
      29,    22,    21,    59,    25,    51,    20,     7,     0,     8,
       0,     0,     0,     0,     0,     0,    33,     0,    42,    43,
      44,    15,     0,     0,    26,     0,     0,    63,    58,     0,
       0,    18,    64,     0,    68,    70,     0,     0,    66,    32,
      34,    38,    40,    36,     0,    60,     0,    56,    30,    28,
      48,    52,    53,    55,    54,    16,    17,     0,    69,     0,
       0,     0,     0,     0,     0,    35,    46,     0,    71,    72,
      10,    39,    41,    37,     0,    45
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,    15,   100,    16,    17,    18,    70,    31,
      32,    83,    34,    35,    36,    37,    38,    56,    84,    39,
      40,    41,    42,    43,    44,    86,    45,    46,    68,    20,
      21,    53,    76,    78
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -75
static const yytype_int8 yypact[] =
{
       1,   -13,    11,    15,    10,    18,   -75,   -75,     8,   -75,
       3,   -75,    59,    59,    73,   -75,    10,   -75,   -75,    46,
     -75,    10,   -13,   -75,    59,   -75,   -75,    47,    49,   -75,
      73,    55,    69,    65,   -75,    72,    56,   -75,   -75,    73,
      13,   -75,   -75,    68,   -75,    76,   -75,   -75,    73,   -75,
      74,    73,    25,    86,    91,    61,   -75,    95,   -75,   -75,
     -75,   -75,    73,    73,   -75,    73,    73,   -75,   -75,     2,
      82,   -75,   -75,    83,   -75,    89,    81,    21,   -75,   -75,
     -75,    92,    93,    94,    87,   -75,    32,   -75,   -75,   -75,
      56,   -75,   -75,   -75,   -75,   -75,   -75,    59,   -75,    88,
     101,    21,    67,    67,    67,   -75,   -75,    95,   -75,   -75,
     -75,   -75,   -75,   -75,   103,   -75
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -75,   -75,   110,    17,    16,   -74,   -75,   -75,    70,    -4,
     -75,    12,   -33,    -6,    50,   -75,    51,   -75,   -14,   -75,
     -75,    53,   -75,   -75,   -75,    19,   -75,   116,   -75,    29,
     -75,   -75,    22,   -75
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -10
static const yytype_int8 yytable[] =
{
      19,    -4,     1,   101,    -4,    11,    64,     6,    27,    28,
      -6,    10,    19,    11,    25,     9,     7,    19,    -4,    22,
      50,    -4,    99,    26,    11,    65,    33,   101,    11,     5,
      88,    66,    -9,    47,     5,    -4,    -4,    -4,    49,    91,
      92,     2,    54,   106,    12,    13,    14,    24,    75,   107,
       2,    74,    -4,    -4,    -4,    12,    87,    14,     2,    89,
      71,     2,    11,    71,    11,    29,     7,    48,    51,    30,
      11,    29,     7,    19,    52,    30,    11,    29,     7,    57,
      55,    30,    58,    59,    60,    61,    63,    80,   111,   112,
     113,    62,    69,    75,    72,    67,    77,    19,    81,    82,
      79,    85,    95,    96,    81,    82,    97,    98,    26,   102,
     103,   104,   109,   105,   115,    23,    90,   110,     8,   108,
      93,    73,    94,     0,     0,     0,   114
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-75))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       4,     0,     1,    77,     3,     3,    39,    20,    12,    13,
       0,     1,    16,     3,    11,     0,     5,    21,     0,     1,
      24,     3,     1,    20,     3,    12,    14,   101,     3,     0,
      63,    18,    11,    16,     5,    34,    35,    36,    21,    37,
      38,    40,    30,    11,    34,    35,    36,    39,    52,    17,
      40,    26,    34,    35,    36,    34,    62,    36,    40,    65,
      48,    40,     3,    51,     3,     4,     5,    21,    21,     8,
       3,     4,     5,    77,    25,     8,     3,     4,     5,    10,
      25,     8,    13,    14,    15,    20,    30,    26,   102,   103,
     104,    19,    16,    97,    20,    27,    10,   101,    37,    38,
       9,     6,    20,    20,    37,    38,    17,    26,    20,    17,
      17,    17,    11,    26,    11,     5,    66,   101,     2,    97,
      69,    51,    69,    -1,    -1,    -1,   107
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    40,    42,    43,    70,    20,     5,    68,     0,
       1,     3,    34,    35,    36,    44,    46,    47,    48,    50,
      70,    71,     1,    43,    39,    11,    20,    50,    50,     4,
       8,    50,    51,    52,    53,    54,    55,    56,    57,    60,
      61,    62,    63,    64,    65,    67,    68,    44,    21,    44,
      50,    21,    25,    72,    52,    25,    58,    10,    13,    14,
      15,    20,    19,    30,    53,    12,    18,    27,    69,    16,
      49,    52,    20,    49,    26,    50,    73,    10,    74,     9,
      26,    37,    38,    52,    59,     6,    66,    54,    53,    54,
      55,    37,    38,    57,    62,    20,    20,    17,    26,     1,
      45,    46,    17,    17,    17,    26,    11,    17,    73,    11,
      45,    59,    59,    59,    66,    11
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1806 of yacc.c  */
#line 135 "parser.yy"
    { GrammarNode* node = new GrammarNode((yyvsp[(1) - (2)].collection_node_type), (yyvsp[(2) - (2)].function_or_statement_node_type)->funcs_, (yyvsp[(2) - (2)].function_or_statement_node_type)->stmts_);
      delete (yyvsp[(2) - (2)].function_or_statement_node_type);
      (yyval.grammar_node_type) = node;
      CTRL->SetAst(static_cast<Node*>((yyval.grammar_node_type))); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 140 "parser.yy"
    { CTRL->Error("Generic parsing error.");
      (yyval.grammar_node_type) = NULL; }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 146 "parser.yy"
    { (yyval.collection_node_type) = new CollectionNode(); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 148 "parser.yy"
    { (yyvsp[(2) - (2)].collection_node_type)->AddFront((yyvsp[(1) - (2)].import_node_type));
      (yyval.collection_node_type) = (yyvsp[(2) - (2)].collection_node_type); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 154 "parser.yy"
    { (yyval.function_or_statement_node_type) = new FuncOrStmt();
      (yyval.function_or_statement_node_type)->funcs_ = new CollectionNode();
      (yyval.function_or_statement_node_type)->stmts_ = new CollectionNode();
    }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 159 "parser.yy"
    { (yyvsp[(2) - (2)].function_or_statement_node_type)->stmts_->AddFront((yyvsp[(1) - (2)].statement_node_type));
      (yyval.function_or_statement_node_type) = (yyvsp[(2) - (2)].function_or_statement_node_type); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 162 "parser.yy"
    { (yyvsp[(2) - (2)].function_or_statement_node_type)->funcs_->AddFront((yyvsp[(1) - (2)].function_node_type));
      (yyval.function_or_statement_node_type) = (yyvsp[(2) - (2)].function_or_statement_node_type); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 168 "parser.yy"
    { (yyval.collection_node_type) = new CollectionNode(); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 170 "parser.yy"
    { (yyvsp[(2) - (2)].collection_node_type)->AddFront((yyvsp[(1) - (2)].statement_node_type));
      (yyval.collection_node_type) = (yyvsp[(2) - (2)].collection_node_type); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 176 "parser.yy"
    { StatementNode* node = new StatementNode(StatementNode::RULE_STATEMENTNODE);
      node->SetLine(CTRL->GetLexer()->line_number());
      node->Set((yyvsp[(1) - (1)].rule_node_type));
      (yyval.statement_node_type) = node; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 181 "parser.yy"
    { StatementNode* node = new StatementNode(StatementNode::RETURN_STATEMENTNODE);
      node->SetLine(CTRL->GetLexer()->line_number());
      node->Set((yyvsp[(1) - (1)].return_node_type));
      (yyval.statement_node_type) = node; }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 186 "parser.yy"
    { CTRL->Error("import statements must occur in the first block of the grammar.");
      (yyval.statement_node_type) = NULL; }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 189 "parser.yy"
    { CTRL->Error("Invalid statement (or previous statement).");
      (yyval.statement_node_type) = NULL; }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 195 "parser.yy"
    { ReturnNode* node = new ReturnNode((yyvsp[(2) - (3)].node_type));
      (yyval.return_node_type) = node; }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 201 "parser.yy"
    { RuleNode* node = new RuleNode((yyvsp[(1) - (4)].identifier_node_type), (yyvsp[(3) - (4)].node_type),
                                    FLAGS_always_export ?
                                    RuleNode::EXPORT :
                                    RuleNode::DO_NOT_EXPORT);
      (yyval.rule_node_type) = node; }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 207 "parser.yy"
    { RuleNode* node = new RuleNode((yyvsp[(2) - (5)].identifier_node_type), (yyvsp[(4) - (5)].node_type), RuleNode::EXPORT);
      (yyval.rule_node_type) = node; }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 213 "parser.yy"
    { (yyval.node_type) = (yyvsp[(1) - (1)].node_type); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 218 "parser.yy"
    { const string& name = CTRL->GetLexer()->YYString();
      IdentifierNode* node = new IdentifierNode(name);
      node->SetLine(CTRL->GetLexer()->line_number());
      if (!node->IsValid())
        CTRL->Error(StringPrintf("Illegal identifier: %s", name.c_str()));
      (yyval.identifier_node_type) = node; }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 227 "parser.yy"
    { (yyval.node_type) = (yyvsp[(1) - (1)].string_node_type); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 228 "parser.yy"
    { (yyval.node_type) = (yyvsp[(1) - (1)].node_type); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 229 "parser.yy"
    { (yyval.node_type) = (yyvsp[(1) - (1)].node_type); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 230 "parser.yy"
    { (yyval.node_type) = (yyvsp[(1) - (1)].node_type); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 231 "parser.yy"
    { (yyval.node_type) = (yyvsp[(1) - (1)].node_type); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 235 "parser.yy"
    { (yyval.node_type) = (yyvsp[(1) - (1)].node_type); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 241 "parser.yy"
    { FstNode* node = new FstNode(FstNode::CONCAT_FSTNODE);
      node->SetLine(CTRL->GetLexer()->line_number());
      node->AddArgument((yyvsp[(1) - (2)].node_type));
      node->AddArgument((yyvsp[(2) - (2)].node_type));
      (yyval.node_type) = node; }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 247 "parser.yy"
    { (yyval.node_type) = (yyvsp[(1) - (1)].node_type); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 253 "parser.yy"
    { FstNode* node = new FstNode(FstNode::UNION_FSTNODE);
      node->SetLine(CTRL->GetLexer()->line_number());
      node->AddArgument((yyvsp[(1) - (3)].node_type));
      node->AddArgument((yyvsp[(3) - (3)].node_type));
      (yyval.node_type) = node; }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 259 "parser.yy"
    { (yyval.node_type) = (yyvsp[(1) - (1)].node_type); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 265 "parser.yy"
    { FstNode* node = new FstNode(FstNode::DIFFERENCE_FSTNODE);
      node->SetLine(CTRL->GetLexer()->line_number());
      node->AddArgument((yyvsp[(1) - (3)].node_type));
      node->AddArgument((yyvsp[(3) - (3)].node_type));
      (yyval.node_type) = node; }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 271 "parser.yy"
    { (yyval.node_type) = (yyvsp[(1) - (1)].node_type); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 277 "parser.yy"
    { (yyval.node_type) = (yyvsp[(2) - (3)].node_type); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 283 "parser.yy"
    { FstNode* node = new FstNode(FstNode::FUNCTION_FSTNODE);
      node->SetLine(CTRL->GetLexer()->line_number());
      node->AddArgument((yyvsp[(1) - (2)].identifier_node_type));
      node->AddArgument((yyvsp[(2) - (2)].collection_node_type));
      (yyval.node_type) = node; }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 291 "parser.yy"
    { (yyval.collection_node_type) = new CollectionNode(); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 293 "parser.yy"
    { (yyval.collection_node_type) = (yyvsp[(2) - (3)].collection_node_type); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 298 "parser.yy"
    { CollectionNode* node = new CollectionNode();
      node->AddFront((yyvsp[(1) - (1)].node_type));
      (yyval.collection_node_type) = node; }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 302 "parser.yy"
    { (yyvsp[(3) - (3)].collection_node_type)->AddFront((yyvsp[(1) - (3)].node_type));
      (yyval.collection_node_type) = (yyvsp[(3) - (3)].collection_node_type); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 307 "parser.yy"
    { CollectionNode* node = new CollectionNode();
      StringNode* nnode = new StringNode("byte");
      node->AddFront(nnode);
      (yyval.collection_node_type) = node; }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 312 "parser.yy"
    { StringNode* nnode = new StringNode("byte");
      (yyvsp[(3) - (3)].collection_node_type)->AddFront(nnode);
      (yyval.collection_node_type) = (yyvsp[(3) - (3)].collection_node_type); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 316 "parser.yy"
    { CollectionNode* node = new CollectionNode();
      StringNode* nnode = new StringNode("utf8");
      node->AddFront(nnode);
      (yyval.collection_node_type) = node; }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 321 "parser.yy"
    { StringNode* nnode = new StringNode("utf8");
      (yyvsp[(3) - (3)].collection_node_type)->AddFront(nnode);
      (yyval.collection_node_type) = (yyvsp[(3) - (3)].collection_node_type); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 329 "parser.yy"
    { RepetitionFstNode* node = new RepetitionFstNode(RepetitionFstNode::STAR);
      node->AddArgument((yyvsp[(1) - (2)].node_type));
      (yyval.node_type) = node; }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 333 "parser.yy"
    { RepetitionFstNode* node = new RepetitionFstNode(RepetitionFstNode::PLUS);
      node->AddArgument((yyvsp[(1) - (2)].node_type));
      (yyval.node_type) = node; }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 337 "parser.yy"
    { RepetitionFstNode* node = new RepetitionFstNode(RepetitionFstNode::QUESTION);
      node->AddArgument((yyvsp[(1) - (2)].node_type));
      (yyval.node_type) = node; }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 341 "parser.yy"
    { if ((yyvsp[(3) - (6)].int_type) > (yyvsp[(5) - (6)].int_type))
        CTRL->Error(StringPrintf("Reversed repetition bounds: %d > %d", (yyvsp[(3) - (6)].int_type), (yyvsp[(5) - (6)].int_type)));
      if ((yyvsp[(3) - (6)].int_type) < 0)
        CTRL->Error(StringPrintf("Start bound must be non-negative: %d", (yyvsp[(3) - (6)].int_type)));
      if ((yyvsp[(5) - (6)].int_type) < 0)
        CTRL->Error(StringPrintf("End bound must be non-negative: %d", (yyvsp[(5) - (6)].int_type)));
      RepetitionFstNode* node = new RepetitionFstNode(RepetitionFstNode::RANGE);
      node->AddArgument((yyvsp[(1) - (6)].node_type));
      node->SetRange((yyvsp[(3) - (6)].int_type), (yyvsp[(5) - (6)].int_type));
      (yyval.node_type) = node; }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 352 "parser.yy"
    { if ((yyvsp[(3) - (4)].int_type) < 0)
        CTRL->Error(StringPrintf("Repetition count should be non-negative: %d", (yyvsp[(3) - (4)].int_type)));
      RepetitionFstNode* node = new RepetitionFstNode(RepetitionFstNode::RANGE);
      node->AddArgument((yyvsp[(1) - (4)].node_type));
      node->SetRange((yyvsp[(3) - (4)].int_type), (yyvsp[(3) - (4)].int_type));
      (yyval.node_type) = node; }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 359 "parser.yy"
    { (yyval.node_type) = (yyvsp[(1) - (1)].node_type); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 365 "parser.yy"
    { FstNode* node = new FstNode(FstNode::COMPOSITION_FSTNODE);
      node->SetLine(CTRL->GetLexer()->line_number());
      node->AddArgument((yyvsp[(1) - (3)].node_type));
      node->AddArgument((yyvsp[(3) - (3)].node_type));
      (yyval.node_type) = node; }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 371 "parser.yy"
    { (yyval.node_type) = (yyvsp[(1) - (1)].node_type); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 376 "parser.yy"
    { FstNode* node = new FstNode(FstNode::IDENTIFIER_FSTNODE);
      node->SetLine(CTRL->GetLexer()->line_number());
      node->AddArgument((yyvsp[(1) - (1)].identifier_node_type));
      (yyval.node_type) = node; }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 384 "parser.yy"
    { StringFstNode* node = new StringFstNode(StringFstNode::BYTE);
      node->AddArgument((yyvsp[(1) - (1)].string_node_type));
      node->SetLine((yyvsp[(1) - (1)].string_node_type)->getline());  // Get the line from the actual text line.
      (yyval.node_type) = node; }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 389 "parser.yy"
    { StringFstNode* node = new StringFstNode(StringFstNode::BYTE);
      node->AddArgument((yyvsp[(1) - (3)].string_node_type));
      node->SetLine((yyvsp[(1) - (3)].string_node_type)->getline());
      (yyval.node_type) = node; }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 394 "parser.yy"
    { StringFstNode* node = new StringFstNode(StringFstNode::UTF8);
      node->AddArgument((yyvsp[(1) - (3)].string_node_type));
      node->SetLine((yyvsp[(1) - (3)].string_node_type)->getline());
      (yyval.node_type) = node; }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 399 "parser.yy"
    { StringFstNode* node = new StringFstNode(StringFstNode::SYMBOL_TABLE);
      node->AddArgument((yyvsp[(1) - (3)].string_node_type));
      node->AddArgument((yyvsp[(3) - (3)].node_type));
      node->SetLine((yyvsp[(1) - (3)].string_node_type)->getline());
      (yyval.node_type) = node; }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 405 "parser.yy"
    { StringFstNode* node = new StringFstNode(StringFstNode::SYMBOL_TABLE);
      node->AddArgument((yyvsp[(1) - (3)].string_node_type));
      node->AddArgument((yyvsp[(3) - (3)].node_type));
      node->SetLine((yyvsp[(1) - (3)].string_node_type)->getline());
      (yyval.node_type) = node; }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 414 "parser.yy"
    { FstNode* node = new FstNode(FstNode::REWRITE_FSTNODE);
      node->SetLine(CTRL->GetLexer()->line_number());
      node->AddArgument((yyvsp[(1) - (3)].node_type));
      node->AddArgument((yyvsp[(3) - (3)].node_type));
      (yyval.node_type) = node; }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 420 "parser.yy"
    { (yyval.node_type) = (yyvsp[(1) - (1)].node_type); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 427 "parser.yy"
    { if (!static_cast<FstNode*>((yyvsp[(1) - (2)].node_type))->SetWeight((yyvsp[(2) - (2)].string_node_type)))
        CTRL->Error("Rules may have only one weight.");
      (yyval.node_type) = (yyvsp[(1) - (2)].node_type); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 431 "parser.yy"
    { (yyval.node_type) = (yyvsp[(1) - (1)].node_type); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 438 "parser.yy"
    { (yyval.int_type) = atoi(CTRL->GetLexer()->YYString().c_str()); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 443 "parser.yy"
    { StringNode* node = new StringNode(CTRL->GetLexer()->YYString());
      node->SetLine(CTRL->GetLexer()->line_number());
      (yyval.string_node_type) = node; }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 450 "parser.yy"
    { StringNode* node = new StringNode(CTRL->GetLexer()->YYString());
      node->SetLine(CTRL->GetLexer()->line_number());
      (yyval.string_node_type) = node; }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 457 "parser.yy"
    { StringNode* node = new StringNode(CTRL->GetLexer()->YYString());
      node->SetLine(CTRL->GetLexer()->line_number());
      (yyval.string_node_type) = node; }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 464 "parser.yy"
    { ImportNode* node = new ImportNode((yyvsp[(2) - (5)].string_node_type), (yyvsp[(4) - (5)].identifier_node_type));
      node->SetLine(CTRL->GetLexer()->line_number());
      (yyval.import_node_type) = node; }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 468 "parser.yy"
    { CTRL->Error("Invalid import statement.");
      (yyval.import_node_type) = NULL; }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 474 "parser.yy"
    { FunctionNode* node = new FunctionNode((yyvsp[(2) - (4)].identifier_node_type), (yyvsp[(3) - (4)].collection_node_type), (yyvsp[(4) - (4)].collection_node_type));
      node->SetLine(node->GetName()->getline());  // Use the identifier's location.
      (yyval.function_node_type) = node; }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 478 "parser.yy"
    { CTRL->Error("Invalid function declaration.");
      (yyval.function_node_type) = NULL; }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 484 "parser.yy"
    { (yyval.collection_node_type) = new CollectionNode(); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 486 "parser.yy"
    { (yyval.collection_node_type) = (yyvsp[(2) - (3)].collection_node_type); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 491 "parser.yy"
    { CollectionNode* node = new CollectionNode();
      node->AddFront((yyvsp[(1) - (1)].identifier_node_type));
      (yyval.collection_node_type) = node; }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 495 "parser.yy"
    { (yyvsp[(3) - (3)].collection_node_type)->AddFront((yyvsp[(1) - (3)].identifier_node_type));
      (yyval.collection_node_type) = (yyvsp[(3) - (3)].collection_node_type); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 501 "parser.yy"
    { (yyval.collection_node_type) = (yyvsp[(2) - (3)].collection_node_type); }
    break;



/* Line 1806 of yacc.c  */
#line 2239 "parser.cc"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 504 "parser.yy"


// Local definitions, definitions that need the semantics of the
// token/type defines.

// yylex() calls Lexer::YYLex()
int yylex(void *, void *parm) {
  switch(CTRL->GetLexer()->YYLex()) {
    case Lexer::EOS:
      return 0;
    case Lexer::QUOTED_STRING:
      return tQSTRING;
    case Lexer::DOUBLE_QUOTED_STRING:
      return tDQSTRING;
    case Lexer::DESCRIPTOR:
      return tDESCR;
    case Lexer::INTEGER:
      return tINTEGER;
    case Lexer::FLOAT:
      return tFLOAT;
    case Lexer::ANGLE_STRING:
      return tANGLE_STRING;
    case Lexer::CONNECTOR: {
      string connector = CTRL->GetLexer()->YYString();
      if (connector.length() != 1) {
        CTRL->Error(StringPrintf("Parse error - unknown connector: %s", connector.c_str()));
        return 0;
      }
      switch (CTRL->GetLexer()->YYString()[0]) {
        case '$': return tDOLLAR;
        case '(': return tLPAREN;
        case ')': return tRPAREN;
        case '*': return tSTAR;
        case '+': return tPLUS;
        case ',': return tCOMMA;
        case '-': return tMINUS;
        case '.': return tDOT;
        case '/': return tSLASH;
        case ':': return tCOLON;
        case ';': return tSEMICOLON;
        case '=': return tEQUALS;
        case '?': return tQMARK;
        case '@': return tAT;
        case '[': return tLBRACKET;
        case ']': return tRBRACKET;
        case '_': return tUNDERSCORE;
        case '{': return tLBRACE;
        case '}': return tRBRACE;
        case '|': return tPIPE;
        default:  CTRL->Error(StringPrintf("Parse error - unknown connector: %s", connector.c_str()));
                  return 0;
      }
    }
    case Lexer::KEYWORD: {
      string keyword = CTRL->GetLexer()->YYString();
      if (keyword == "export") {
        return tKEYWORD_EXPORT;
      } else if (keyword == "as") {
        return tKEYWORD_AS;
      } else if (keyword == "func") {
        return tKEYWORD_FUNC;
      } else if (keyword == "import") {
        return tKEYWORD_IMPORT;
      } else if (keyword == "return") {
        return tKEYWORD_RETURN;
      } else if (keyword == "byte") {
        return tKEYWORD_BYTE;
      } else if (keyword == "utf8") {
        return tKEYWORD_UTF8;
      } else {
        CTRL->Error(StringPrintf("Parse error - unknown keyword: %s", keyword.c_str()));
        return 0;
      }
    }
  }
  return 0;
}

int yyerror(const char *s) {
  cout << "Parse Failed: " << s << endl;
  return 0;
}

} // namespace thrax_rewriter

namespace thrax {

int CallParser(GrmCompilerParserInterface* compiler) {
  return thrax_rewriter::yyparse(compiler);
}

}  // namespace thrax


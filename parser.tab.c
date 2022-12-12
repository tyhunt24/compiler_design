/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "symbolTable.h"
#include "symtab.h"
#include "AST.h"
#include "IrCode.h"
#include "Assembly.h"

extern int yylex();
extern int yyparse();

extern FILE* yyin;

void yyerror(const char* s);
char currentScope[50] = "global";
char label[50] = "IfStmt";
char otherScope[50];
char returnName[50];

int inreturn = 0;

int is_else = 0;

int in_true = 0;

int in_loop = 0;

char *returnType;

int semanticChecks = 1;

//$$ parses the tree back together
//parser: reads right to left
//find the first argument and second argument in this statement

clock_t t;


/*
  1. Try to get a really simple function running in MIPS. 

 */


#line 119 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TYPE = 258,
    ID = 259,
    IF = 260,
    ELSE = 261,
    WHILE = 262,
    SEMICOLON = 263,
    COMMA = 264,
    EQ = 265,
    OPAREN = 266,
    CPAREN = 267,
    OBRACK = 268,
    CBRACK = 269,
    OCBRACE = 270,
    CCBRACE = 271,
    PLUS = 272,
    MINUS = 273,
    MULTIPLY = 274,
    DIVIDE = 275,
    NUMBER = 276,
    LT = 277,
    GT = 278,
    GTE = 279,
    LTE = 280,
    EQEQ = 281,
    NOTEQ = 282,
    AND = 283,
    OR = 284,
    WRITE = 285,
    WRITEln = 286,
    RETURN = 287
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 50 "parser.y"

    int number;
    char character;
    char* string;
    struct AST* ast;

#line 211 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  31
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   123

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  105

#define YYUNDEFTOK  2
#define YYMAXUTOK   287


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    98,    98,   108,   111,   114,   115,   116,   119,   120,
     123,   135,   139,   139,   157,   158,   161,   162,   165,   173,
     177,   178,   181,   182,   183,   186,   190,   221,   240,   270,
     272,   298,   324,   328,   341,   351,   351,   366,   366,   376,
     385,   386,   393,   403,   505,   594,   671,   753,   756,   761,
     769,   782,   795,   810,   824,   833
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "ID", "IF", "ELSE", "WHILE",
  "SEMICOLON", "COMMA", "EQ", "OPAREN", "CPAREN", "OBRACK", "CBRACK",
  "OCBRACE", "CCBRACE", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "NUMBER",
  "LT", "GT", "GTE", "LTE", "EQEQ", "NOTEQ", "AND", "OR", "WRITE",
  "WRITEln", "RETURN", "$accept", "Program", "DeclList", "Decl",
  "VarDeclList", "VarDecl", "FunDecl", "$@1", "ParamDecList",
  "ParamDecListTail", "ParamDecl", "StmtList", "Stmt", "Expr", "IfExpr",
  "$@2", "WhileStmt", "$@3", "Block", "CallList", "Math", "RelOps", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287
};
# endif

#define YYPACT_NINF (-58)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-36)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       6,     1,    -6,    -3,   -58,    42,   -58,    22,   -58,    39,
      47,   -58,     6,   -58,    48,   -58,   -58,    18,    44,   -58,
     -58,    77,    57,    58,    10,    42,    56,   -58,    81,   -58,
     -58,   -58,   -58,    62,   -58,   -58,   -58,    42,    42,    42,
      42,   -58,   -58,    59,    94,    -2,    77,    64,    65,    69,
      42,   -58,    11,    -4,    -4,   -58,   -58,    73,    89,    42,
      96,    42,    42,    42,    42,    42,    42,    92,    97,   100,
      98,   -58,   102,   104,   101,    55,    10,    77,    77,    77,
      77,    77,    77,    48,   108,    92,   103,    92,    73,   -58,
     -58,    42,   -58,    18,   109,   -58,   105,   -58,   -58,   -58,
     106,    92,   -58,   -58,   -58
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       8,     0,    48,     0,    37,     0,    49,     0,    32,     0,
       0,     2,     4,     6,     8,     5,     7,    20,     0,    23,
      24,    25,     0,     0,     0,     0,     0,    48,     0,    31,
      33,     1,     3,     0,     9,    21,    22,     0,     0,     0,
       0,    10,    12,     0,    48,    49,    30,     0,     0,     0,
       0,    47,     0,    43,    44,    45,    46,    14,     0,    40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    15,    16,     0,     0,    41,     0,    53,    52,    50,
      51,    54,    55,     8,    34,     0,    18,     0,     0,    11,
      28,    40,    29,     0,     0,    38,     0,    13,    17,    42,
       0,     0,    19,    39,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -58,   -58,   111,   -58,   -12,   -58,   -58,   -58,   -58,    29,
     -58,   -16,   -58,   -21,   -58,   -58,   -58,   -58,   -57,    27,
      -5,    70
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    14,    15,    57,    70,    71,
      72,    16,    17,    18,    19,    94,    20,    26,    84,    74,
      21,    49
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      28,    35,    34,    47,    23,    22,   -27,    24,    25,     1,
       2,     3,   -27,     4,     2,    39,    40,     5,    46,    41,
      48,     5,     2,     3,    43,     4,    29,     6,    95,     5,
      97,     6,    53,    54,    55,    56,     7,     8,     9,     6,
       7,     8,     9,    30,   104,    48,    27,    31,     7,     8,
       9,    33,    36,     5,    75,    92,    77,    78,    79,    80,
      81,    82,    44,     6,    91,    41,    52,    50,    42,     5,
      43,    93,    37,    38,    39,    40,    69,   100,    60,    45,
      58,    67,    37,    38,    39,    40,    75,    61,    62,    63,
      64,    65,    66,    51,    37,    38,    39,    40,    37,    38,
      39,    40,   -26,    73,    86,    59,    76,    83,   -26,    85,
      87,    88,    89,    90,   -35,   101,    96,    98,    99,   102,
      68,     0,   103,    32
};

static const yytype_int8 yycheck[] =
{
       5,    17,    14,    24,    10,     4,     8,    13,    11,     3,
       4,     5,    14,     7,     4,    19,    20,    11,    23,     8,
      25,    11,     4,     5,    13,     7,     4,    21,    85,    11,
      87,    21,    37,    38,    39,    40,    30,    31,    32,    21,
      30,    31,    32,     4,   101,    50,     4,     0,    30,    31,
      32,     3,     8,    11,    59,    76,    61,    62,    63,    64,
      65,    66,     4,    21,     9,     8,     4,    11,    11,    11,
      13,    83,    17,    18,    19,    20,     3,    93,    14,    21,
      21,    12,    17,    18,    19,    20,    91,    22,    23,    24,
      25,    26,    27,    12,    17,    18,    19,    20,    17,    18,
      19,    20,     8,    14,     4,    11,    10,    15,    14,    12,
      12,     9,     8,    12,     6,     6,    13,    88,    91,    14,
      50,    -1,    16,    12
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     7,    11,    21,    30,    31,    32,
      34,    35,    36,    37,    38,    39,    44,    45,    46,    47,
      49,    53,     4,    10,    13,    11,    50,     4,    53,     4,
       4,     0,    35,     3,    37,    44,     8,    17,    18,    19,
      20,     8,    11,    13,     4,    21,    53,    46,    53,    54,
      11,    12,     4,    53,    53,    53,    53,    40,    21,    11,
      14,    22,    23,    24,    25,    26,    27,    12,    54,     3,
      41,    42,    43,    14,    52,    53,    10,    53,    53,    53,
      53,    53,    53,    15,    51,    12,     4,    12,     9,     8,
      12,     9,    46,    37,    48,    51,    13,    51,    42,    52,
      44,     6,    14,    16,    51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    36,    37,    37,
      38,    38,    40,    39,    41,    41,    42,    42,    43,    43,
      44,    44,    45,    45,    45,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    47,    48,    47,    50,    49,    51,
      52,    52,    52,    53,    53,    53,    53,    53,    53,    53,
      54,    54,    54,    54,    54,    54
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     0,     2,
       3,     6,     0,     7,     0,     1,     1,     3,     2,     4,
       1,     2,     2,     1,     1,     1,     3,     3,     6,     6,
       3,     2,     1,     2,     5,     0,     8,     0,     6,     4,
       0,     1,     3,     3,     3,     3,     3,     3,     1,     1,
       3,     3,     3,     3,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
    case 4: /* ID  */
#line 88 "parser.y"
         { fprintf(yyoutput, "%s", ((*yyvaluep).string)); }
#line 852 "parser.tab.c"
        break;

    case 21: /* NUMBER  */
#line 89 "parser.y"
         { fprintf(yyoutput, "%d", ((*yyvaluep).number)); }
#line 858 "parser.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 98 "parser.y"
                   {(yyval.ast) = (yyvsp[0].ast);
                    endMipsFile();
                    t = clock() - t;
                    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
                    printf("Program took %f seconds to execute \n", time_taken);
                    }
#line 1480 "parser.tab.c"
    break;

  case 3:
#line 108 "parser.y"
                            {(yyvsp[-1].ast)->left = (yyvsp[0].ast);
                             (yyval.ast) = (yyvsp[-1].ast);
                            }
#line 1488 "parser.tab.c"
    break;

  case 4:
#line 111 "parser.y"
            { (yyval.ast) = (yyvsp[0].ast); }
#line 1494 "parser.tab.c"
    break;

  case 8:
#line 119 "parser.y"
             {(yyval.ast) = NULL;}
#line 1500 "parser.tab.c"
    break;

  case 10:
#line 123 "parser.y"
                              {printf("\n RECOGNIZED RULE: VARIABLE DECLERATION\n");
                                // ----- Semantic Checks ----- //
                                if (found((yyvsp[-2].string), currentScope) == 0) {
                                    
                                    // ----- Symbol Table ----- //
                                    addItem((yyvsp[-1].string), "var", (yyvsp[-2].string), currentScope);
                                }
                                // ----- AST Tree ----- //
                                (yyval.ast) = AST_assignment("Type", (yyvsp[-2].string), (yyvsp[-1].string));

                                printTable();
                            }
#line 1517 "parser.tab.c"
    break;

  case 11:
#line 135 "parser.y"
                                                   {printf("\n Array Decleration\n");}
#line 1523 "parser.tab.c"
    break;

  case 12:
#line 139 "parser.y"
                        {
                            // ----- Symbol Table ----- //
                           // addItem($2, "func", $1, currentScope);

                            // copy function name to currentscope
                            strcpy(currentScope, (yyvsp[-1].string));
                            strcpy(label, (yyvsp[-1].string));
                         }
#line 1536 "parser.tab.c"
    break;

  case 13:
#line 147 "parser.y"
                           {printf("\nFunction\n");
                            // ----- AST Tree ----- //
                            (yyval.ast) = ast_func("func", (yyvsp[-5].string), (yyvsp[0].ast));

                            // ----- IR code ----- //
                            labelFunction((yyvsp[-5].string));
                            MipsCreateFunction((yyvsp[-5].string));
                         }
#line 1549 "parser.tab.c"
    break;

  case 14:
#line 157 "parser.y"
              {(yyval.ast) = NULL;}
#line 1555 "parser.tab.c"
    break;

  case 18:
#line 165 "parser.y"
                   {printf("\nEncountered Parameter\n");
                        // ----- Symbol Table ----- //
                        addItem((yyvsp[0].string), "param", (yyvsp[-1].string), currentScope);

                        // ----- AST Actions ----- //
                        (yyval.ast) = AST_assignment("Type", (yyvsp[-1].string), (yyvsp[0].string));
                    }
#line 1567 "parser.tab.c"
    break;

  case 19:
#line 173 "parser.y"
                          {printf("\nParameter Array\n");}
#line 1573 "parser.tab.c"
    break;

  case 22:
#line 181 "parser.y"
                     {(yyval.ast) = (yyvsp[-1].ast);}
#line 1579 "parser.tab.c"
    break;

  case 23:
#line 182 "parser.y"
          {(yyval.ast) = (yyvsp[0].ast);}
#line 1585 "parser.tab.c"
    break;

  case 24:
#line 183 "parser.y"
             {(yyval.ast) = (yyvsp[0].ast);}
#line 1591 "parser.tab.c"
    break;

  case 25:
#line 186 "parser.y"
             {printf("\nRECOGNIZED RULE: Primary Statement\n");
                    (yyval.ast) = (yyvsp[0].ast);

                }
#line 1600 "parser.tab.c"
    break;

  case 26:
#line 190 "parser.y"
                 {printf("\nRECONGINZED RULE: Assignment statement\n");
                    // ----- Semantic Checks ----- //
                    if(found((yyvsp[-2].string), currentScope)  == 0) {
                        printf("Semantic Error: %s is not intialized\n", (yyvsp[-2].string));
                        semanticChecks = 0;
                    }

                    if(found((yyvsp[0].string), currentScope)  == 0) {
                        printf("Semantic Error: %s is not intialized\n", (yyvsp[0].string));
                        semanticChecks = 0;
                    }

                    // Get Variable Types
                    char *varType1 = getVariableType((yyvsp[-2].string), currentScope);
                    char *varType2 = getVariableType((yyvsp[0].string), currentScope);

                    // Check Variable Types
                    if(strcmp(varType1, varType2) != 0) {
                        printf("\nSemantic Error: variables Type mistmatch\n");
                        semanticChecks = 0;
                    }

                    // ----- Symbol Table ----- //
                    updateValue((yyvsp[-2].string), currentScope, getValue((yyvsp[0].string), currentScope));

                    // ----- AST Tree ----- //
                    (yyval.ast) = AST_assignment("=", (yyvsp[-2].string), (yyvsp[0].string));

                    // ----- IR code ----- //
                }
#line 1635 "parser.tab.c"
    break;

  case 27:
#line 221 "parser.y"
                     {printf("\n RECONGIZED RULE: Number Decleration\n");
                        // ----- Semantic Checks ----- //
                        if(found((yyvsp[-2].string), currentScope) == 0) {
                            printf("Semantic Error: ID has not been declared");
                        }

                        // ----- Symbol Table ----- //
                        char str[50];
                        sprintf(str, "%d", (yyvsp[0].number));
                        updateValue((yyvsp[-2].string), currentScope, str);

                        // ----- AST Tree ----- //
                        (yyval.ast) = AST_assignment("=", (yyvsp[-2].string), str);

                        // ----- IR Code ----- //
                        loadValueInts((yyvsp[-2].string), currentScope, str);

                        }
#line 1658 "parser.tab.c"
    break;

  case 28:
#line 240 "parser.y"
                                      {printf("\nCall Function: In ID\n");
                                        // ----- Semantic Checks ----- //
                                        if(found((yyvsp[-5].string), currentScope)  == 0) {
                                            printf("Semantic Error: %s is not intialized\n", (yyvsp[-5].string));
                                            semanticChecks = 0;
                                        }

                                        if(found((yyvsp[-3].string), currentScope)  == 0) {
                                            printf("Semantic Error: %s is not intialized\n", (yyvsp[-3].string));
                                            semanticChecks = 0;
                                        }

                                        // Get Variable Types
                                        char *varType1 = getVariableType((yyvsp[-5].string), currentScope);
                                        char *varType2 = getVariableType((yyvsp[-3].string), currentScope);

                                        // Check Variable Types
                                        if(strcmp(varType1, varType2) != 0) {
                                            printf("\nSemantic Error: variables Type mistmatch\n");
                                            semanticChecks = 0;
                                    }

                                      // ----- AST Tree ----- //
                                      // ! Not quite sure what this should look like yet.

                                      // ----- IR Code ----- //
                                      mipsJumpFunction(label);
                        }
#line 1691 "parser.tab.c"
    break;

  case 29:
#line 270 "parser.y"
                                    {printf("\n Recongized Rule: Array Expression\n");}
#line 1697 "parser.tab.c"
    break;

  case 30:
#line 272 "parser.y"
                 {printf("\nRecongized Rule: Math Expression\n");
                    // ----- Semantic Checks ----- //
                    if(found((yyvsp[-2].string), currentScope) == 0) {
                        printf("Error: Variable is not found");
                        semanticChecks = 0;
                    }
                    // put the value here
                    if((yyvsp[0].ast)->isNumber == 1) {
                        updateValue((yyvsp[-2].string), currentScope, (yyvsp[0].ast)->nodeType);

                        printf("\n\n\n\n%s\n\n\n\n", (yyvsp[0].ast)->nodeType);
                
                        // ----- IR code ----- //
                      //  loadAddition($1, currentScope);

                    } else {
                        // ----- IR code ----- //
                        printf("Not a number");
                    }

                    // ----- AST Tree ----- //
                    (yyval.ast) = idMathexp("=", (yyvsp[-2].string), (yyvsp[0].ast));
                
                }
#line 1726 "parser.tab.c"
    break;

  case 31:
#line 298 "parser.y"
                 {printf("\nRECONGIZED RULE: Print Statement\n");
                    // ----- AST Actions ----- //
                     (yyval.ast) = AST_Write("Write", (yyvsp[0].string), "");

                     // ----- IR Code ----- //
                     if (inreturn == 1) {
                     moveFunction((yyvsp[0].string), currentScope);
                     writeValue((yyvsp[0].string), currentScope);
                     } else {
                     
                     if(in_true == 1) {
                        jumpExit();
                     }
                     
                     if (in_loop == 1) {
                        writeValueInWhile((yyvsp[0].string), currentScope);
                     } else {
                        writeValue((yyvsp[0].string), currentScope);
                     }
                     
                     
                     }


                }
#line 1756 "parser.tab.c"
    break;

  case 32:
#line 324 "parser.y"
                        {printf("\nRECONGIZED RULE: write ln Statement\n");
                    writeNewLine();
                }
#line 1764 "parser.tab.c"
    break;

  case 33:
#line 328 "parser.y"
                  {printf("\nFunction Found: Return ID\n");
                    // ----- AST actions ----- //
                    (yyval.ast) = AST_Write("return", (yyvsp[0].string), "");

                    // ----- No IR code Here I think
                    strcpy(returnName, (yyvsp[0].string));
                    strcpy(otherScope, currentScope);

                    inreturn = 1;
                    }
#line 1779 "parser.tab.c"
    break;

  case 34:
#line 341 "parser.y"
                                      {printf("Entering if statement");
                                        in_true = 1;
                                        // ----- Generate IR Code -----//
                                         // ! Need to Create a label statement here //
                                        MipsCreateLabel(label);

                                        // ----- AST ACTIONS ----- //
                                        (yyval.ast) = add_tree((yyvsp[-4].string), (yyvsp[-2].ast), (yyvsp[0].ast));
}
#line 1793 "parser.tab.c"
    break;

  case 35:
#line 351 "parser.y"
                                  {printf("Entering in First if statement");
                                    in_true = 1;

                                    // --- Create Mips Label --- //
                                     MipsCreateLabel(label);
    }
#line 1804 "parser.tab.c"
    break;

  case 36:
#line 357 "parser.y"
               { printf("Entering into an else statement");
                        // --- Create Mips Label --- //
                        MipsCreateLabel("ElseStmt");
                        jumpLabel("ElseStmt");

                        // ! --- Create the AST Tree --- //
}
#line 1816 "parser.tab.c"
    break;

  case 37:
#line 366 "parser.y"
                  {strcpy(label, "WhileStmt"); whileMipsCreateLabel(label); in_loop = 1;}
#line 1822 "parser.tab.c"
    break;

  case 38:
#line 366 "parser.y"
                                                                                                                     {printf("\nRecongized Rule: While Statement\n");  
                                        // --- Generate IR Code --- //
                                       // jumpLabel(label);

                                        // --- AST Tree --- //
                                        (yyval.ast) = add_tree((yyvsp[-5].string), (yyvsp[-2].ast), (yyvsp[0].ast));
                                        }
#line 1834 "parser.tab.c"
    break;

  case 39:
#line 376 "parser.y"
                                             {printf("\nBlock Statement\n");
                                                // ----- AST Actions ----- //
                                                (yyval.ast) = add_tree("block", (yyvsp[-2].ast), (yyvsp[-1].ast));

                                                //currentScope -> Global
                                                strcpy(currentScope, "global");                                                
                                            }
#line 1846 "parser.tab.c"
    break;

  case 40:
#line 385 "parser.y"
          {(yyval.ast) = NULL;}
#line 1852 "parser.tab.c"
    break;

  case 41:
#line 386 "parser.y"
               {
            // ----- IR Code ----- //
            paramMips((yyvsp[0].ast)->nodeType); // Gives us the value in here

            // ----- AST Tree -----//
            (yyval.ast) = add_tree("Call", (yyvsp[0].ast), NULL);
        }
#line 1864 "parser.tab.c"
    break;

  case 42:
#line 393 "parser.y"
                              {
           
            // ----- IR Code ----- //
            paramMips((yyvsp[-2].ast)->nodeType);

            // ----- AST Tree ----- //
            (yyval.ast) = add_tree("Call", (yyvsp[-2].ast), (yyvsp[0].ast));
        }
#line 1877 "parser.tab.c"
    break;

  case 43:
#line 403 "parser.y"
                     {printf("\nReconiged Rule: Addition Expression\n");
                                
                            //intialize a number to 0
                             int num = 0;

                            //IF $1 and $3 are both numbers
                            if((yyvsp[-2].ast)->isNumber == 1 && (yyvsp[0].ast)->isNumber == 1) {
                                
                                //change from characters to numbers
                                //And Add them
                                int num1 = atoi((yyvsp[-2].ast)->nodeType);
                                int num3 = atoi((yyvsp[0].ast)->nodeType);
                                
                                //add the numbers and add it to first variable
                                int number = num1 + num3;
                                num += number;
                                
                                // ----- AST Tree ----- //
                                char str[50];
                                sprintf(str, "%d", num);
                                (yyval.ast) = addTree(str, 1);
                            }

                            //If the $1 is a number but the $3 is a variable
                            else if((yyvsp[-2].ast)->isNumber == 1) {
                                
                                //convert the number from Char to Num
                                //Get the value of the variable from the symbol table
                                //convert it from Char to num
                                int num1 = atoi((yyvsp[-2].ast)->nodeType);
                                char *val1 = getValue((yyvsp[0].ast)->nodeType, currentScope);
                                int num3 = atoi(val1);

                                //add the numbers and add it to first variable
                                int number = num1 + num3;
                                num += number;

                                // ----- AST Tree ----- //
                                char str[50];
                                sprintf(str, "%d", num);
                                (yyval.ast) = addTree(str, 1);
                            } 

                            //Now $1 is variable and $3 is number
                            else if((yyvsp[0].ast)->isNumber == 1) {
                                
                                //do the same as the steps before
                                char *val1 = getValue((yyvsp[-2].ast)->nodeType, currentScope);
                                int num1 = atoi(val1);
                                int num3 = atoi((yyvsp[0].ast)->nodeType);

                                if (in_loop == 1) {
                                    increment((yyvsp[-2].ast)->nodeType, (yyvsp[0].ast)->nodeType, currentScope); // loop through the statement
                                    jumpLabel(label);
                                }
                                    

                                //add the numbers and add it to first variable
                                int number = num1 + num3;
                                num += number;

                                // ----- AST Tree ----- //
                                char str[50];
                                sprintf(str, "%d", num);
                                (yyval.ast) = addTree(str, 1);
                            }
                            
                            else {
                                    
                                char *val1 = getValue((yyvsp[-2].ast)->nodeType, currentScope);
                                char *val2 = getValue((yyvsp[0].ast)->nodeType, currentScope);

                                if(strcmp(val1, "NULL") != 0 && strcmp(val2, "NULL") != 0) {
                                    
                                    //Gets the numbers from inside of the values
                                    int num1 = atoi(val1);
                                    int num2 = atoi(val2);

                                    int number;
                                    
                                    //add the numbers
                                    number = num1 + num2;
                                    num += number;
                                    char str[50];
                                    sprintf(str, "%d", num);

                                    // ----- AST TREE ----- //
                                    (yyval.ast) = addTree(str, 1);
                                } else {
                                    mipsInside();

                                    // ---- IR CODE -----//
                                    addMips();

                                    // ----- AST TREE -----//
                                    (yyval.ast) = add_tree("+", (yyvsp[-2].ast), (yyvsp[0].ast));
                                }



                            }
                    }
#line 1984 "parser.tab.c"
    break;

  case 44:
#line 505 "parser.y"
                          {printf("\nReconiged Rule: Subtraction Expression Expression\n");
                            //intialize a number to 0
                            int num = 0;

                            //IF $1 and $3 are both numbers
                            if((yyvsp[-2].ast)->isNumber && (yyvsp[0].ast)->isNumber == 1) {
                                
                                //change from characters to numbers
                                //And Add them
                                int num1 = atoi((yyvsp[-2].ast)->nodeType);
                                int num3 = atoi((yyvsp[0].ast)->nodeType);
                                
                                //add the numbers and add it to first variable
                                int number = num1 - num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            }

                            //If the $1 is a number but the $3 is a variable
                            else if((yyvsp[-2].ast)->isNumber == 1) {
                                
                                //convert the number from Char to Num
                                //Get the value of the variable from the symbol table
                                //convert it from Char to num
                                int num1 = atoi((yyvsp[-2].ast)->nodeType);
                                char *val1 = getValue((yyvsp[0].ast)->nodeType, currentScope);
                                int num3 = atoi(val1);

                                //add the numbers and add it to first variable
                                int number = num1 - num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            } 

                            //Now $1 is variable and $3 is number
                            else if((yyvsp[0].ast)->isNumber == 1) {
                                
                                //do the same as the steps before
                                char *val1 = getValue((yyvsp[-2].ast)->nodeType, currentScope);
                                int num1 = atoi(val1);
                                int num3 = atoi((yyvsp[0].ast)->nodeType);

                                //add the numbers and add it to first variable
                                int number = num1 - num3;
                                num += number;

                                //decrement inside of the loop
                                if (in_loop == 1) {
                                    decrement((yyvsp[-2].ast)->nodeType, (yyvsp[0].ast)->nodeType, currentScope); // loop through the statement
                                    jumpLabel(label);
                                }

                                //printf("%d\n\n\n", num);
                            }

                            //if we are adding both variables and no numbers
                            else { 
                                char *val1 = getValue((yyvsp[-2].ast)->nodeType, currentScope); 
                                char *val2 = getValue((yyvsp[0].ast)->nodeType, currentScope);

                                // check in the Symbol tables are NULL or not.
                                if(strcmp(val1, "NULL") != 0 && strcmp(val2, "NULL") != 0) {
                                
                                    // get the values
                                    int num1 = atoi(val1);
                                    int num2 = atoi(val2);

                                    int number;

                                    number = num1 - num2;
                                    num += number;
                                    char str[50];
                                    sprintf(str, "%d", num);

                                    // ----- AST Tree ----- //
                                    (yyval.ast) = addTree(str, 1);
                                } else {
                                    mipsInside();
                                    subMips();

                                    // ----- AST Tree ----- //
                                    (yyval.ast) = add_tree("+", (yyvsp[-2].ast), (yyvsp[0].ast));
                                }
                            }

                            }
#line 2077 "parser.tab.c"
    break;

  case 45:
#line 594 "parser.y"
                             {printf("\nReconiged Rule: Addition Expression\n");
                            //intialize a number to 0
                            int num = 0;

                            //IF $1 and $3 are both numbers
                            if((yyvsp[-2].ast)->isNumber && (yyvsp[0].ast)->isNumber == 1) {
                                
                                //change from characters to numbers
                                //And Add them
                                int num1 = atoi((yyvsp[-2].ast)->nodeType);
                                int num3 = atoi((yyvsp[0].ast)->nodeType);
                                
                                //add the numbers and add it to first variable
                                int number = num1 * num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            }

                            //If the $1 is a number but the $3 is a variable
                            else if((yyvsp[-2].ast)->isNumber == 1) {
                                
                                //convert the number from Char to Num
                                //Get the value of the variable from the symbol table
                                //convert it from Char to num
                                int num1 = atoi((yyvsp[-2].ast)->nodeType);
                                char *val1 = getValue((yyvsp[0].ast)->nodeType, currentScope);
                                int num3 = atoi(val1);

                                //add the numbers and add it to first variable
                                int number = num1 * num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            } 

                            //Now $1 is variable and $3 is number
                            else if((yyvsp[0].ast)->isNumber == 1) {
                                
                                //do the same as the steps before
                                char *val1 = getValue((yyvsp[-2].ast)->nodeType, currentScope);
                                int num1 = atoi(val1);
                                int num3 = atoi((yyvsp[0].ast)->nodeType);

                                //add the numbers and add it to first variable
                                int number = num1 * num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            }

                            //if we are adding both variables and no numbers
                            else { 
                                // 
                                char *val1 = getValue((yyvsp[-2].ast)->nodeType, currentScope); 
                                char *val2 = getValue((yyvsp[0].ast)->nodeType, currentScope);

                                if(strcmp(val1, "NULL") != 0 && strcmp(val2, "NULL") != 0) {
                            
                                    int num1 = atoi(val1);
                                    int num2 = atoi(val2);

                                    int number;

                                    number = num1 * num2;
                                    num += number;
                                    char str[50];
                                    sprintf(str, "%d", num);
                                (yyval.ast) = addTree(str, 1);
                                } else {
                                    mipsInside();
                                    multiMips();
                                    (yyval.ast) = add_tree("+", (yyvsp[-2].ast), (yyvsp[0].ast));
                                }
                            }
                            }
#line 2158 "parser.tab.c"
    break;

  case 46:
#line 671 "parser.y"
                           {printf("\nReconiged Rule: Addition Expression\n");
                            //intialize a number to 0
                            int num = 0;

                            //IF $1 and $3 are both numbers
                            if((yyvsp[-2].ast)->isNumber == 1 && (yyvsp[0].ast)->isNumber == 1) {
                                
                                //change from characters to numbers
                                //And Add them
                                int num1 = atoi((yyvsp[-2].ast)->nodeType);
                                int num3 = atoi((yyvsp[0].ast)->nodeType);
                                
                                //add the numbers and add it to first variable
                                int number = num1 / num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            }

                            //If the $1 is a number but the $3 is a variable
                            else if((yyvsp[-2].ast)->isNumber == 1) {
                                
                                //convert the number from Char to Num
                                //Get the value of the variable from the symbol table
                                //convert it from Char to num
                                int num1 = atoi((yyvsp[-2].ast)->nodeType);
                                char *val1 = getValue((yyvsp[0].ast)->nodeType, currentScope);
                                int num3 = atoi(val1);

                                //add the numbers and add it to first variable
                                int number = num1 / num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            } 

                            //Now $1 is variable and $3 is number
                            else if((yyvsp[0].ast)->isNumber == 1) {
                                
                                //do the same as the steps before
                                char *val1 = getValue((yyvsp[-2].ast)->nodeType, currentScope);
                                int num1 = atoi(val1);
                                int num3 = atoi((yyvsp[0].ast)->nodeType);

                                //add the numbers and add it to first variable
                                int number = num1 / num3;
                                num += number;

                                //printf("%d\n\n\n", num);
                            }

                            //if we are adding both variables and no numbers
                            else { 
                                char *val1 = getValue((yyvsp[-2].ast)->nodeType, currentScope); 
                                char *val2 = getValue((yyvsp[0].ast)->nodeType, currentScope);

                                if(strcmp(val1, "NULL") != 0 && strcmp(val2, "NULL") != 0) {
                                
                                    int num1 = atoi(val1);
                                    int num2 = atoi(val2);

                                    int number;

                                    number = num1 / num2;
                                    num += number;
                                    char str[50];
                                    sprintf(str, "%d", num);

                                 // ----- AST Tree ----- //
                                (yyval.ast) = addTree(str, 1);
                                } else {
                                    mipsInside();

                                    // ----- IR Code -----//
                                    divideMips();

                                    // ----- AST Tree ----- //
                                    (yyval.ast) = add_tree("+", (yyvsp[-2].ast), (yyvsp[0].ast));
                                }
                            }
                            }
#line 2244 "parser.tab.c"
    break;

  case 47:
#line 753 "parser.y"
                             {
            (yyval.ast) = (yyvsp[-1].ast);
        }
#line 2252 "parser.tab.c"
    break;

  case 48:
#line 756 "parser.y"
             {printf("\n ID\n");
                printf("\n\n\n\n%s\n\n\n\n", (yyvsp[0].string));
                (yyval.ast) = addTree((yyvsp[0].string), 0);
            }
#line 2261 "parser.tab.c"
    break;

  case 49:
#line 761 "parser.y"
                 {printf("\n In Number\n");
                    char str[50];
                    sprintf(str, "%d", (yyvsp[0].number));
                    (yyval.ast) =addTree(str, 1);
                    }
#line 2271 "parser.tab.c"
    break;

  case 50:
#line 769 "parser.y"
                      {printf("\nGreater Than\n");
                        // --- Generate IR code --- //
                        if (in_loop == 1) {
                            bleMips((yyvsp[-2].ast)->nodeType, (yyvsp[0].ast)->nodeType, currentScope, "Exit");
                        } else {
                            bgeMips((yyvsp[-2].ast)->nodeType, (yyvsp[0].ast)->nodeType, currentScope, label);
                        }
                        

                        // --- AST Actions --- //
                        (yyval.ast) = add_tree((yyvsp[-1].string), (yyvsp[-2].ast), (yyvsp[0].ast));
                        }
#line 2288 "parser.tab.c"
    break;

  case 51:
#line 782 "parser.y"
                        {printf("\nGreater Than\n");
                        // --- Generate IR code --- //
                        if(in_loop == 1) {
                            bgeMips((yyvsp[-2].ast)->nodeType, (yyvsp[0].ast)->nodeType, currentScope, "Exit");
                        } else {
                              bleMips((yyvsp[-2].ast)->nodeType, (yyvsp[0].ast)->nodeType, currentScope, label);
                        }
                       
                       
                        // --- AST Actions --- //
                        (yyval.ast) = add_tree((yyvsp[-1].string), (yyvsp[-2].ast), (yyvsp[0].ast));
                        }
#line 2305 "parser.tab.c"
    break;

  case 52:
#line 795 "parser.y"
                       {printf("\nGreater Than\n");
                        // --- Generate IR code --- //
                        if(in_loop == 1) {
                            bltMips((yyvsp[-2].ast)->nodeType, currentScope, (yyvsp[0].ast)->nodeType, "Exit");
                            printf("\n\n\n\n\n%s\n\n\n\n\n", (yyvsp[-2].ast)->nodeType);
                            
                        } else {
                            bgtMips((yyvsp[-2].ast)->nodeType, (yyvsp[0].ast)->nodeType, currentScope, label);
                        }
                        
                       
                        // --- AST Actions --- //
                        (yyval.ast) = add_tree((yyvsp[-1].string), (yyvsp[-2].ast), (yyvsp[0].ast));
                        }
#line 2324 "parser.tab.c"
    break;

  case 53:
#line 810 "parser.y"
                       {printf("\nGreater Than\n");
                        // --- Generate IR code --- //
                        if(in_loop == 1) {
                            bgtMips((yyvsp[-2].ast)->nodeType, (yyvsp[0].ast)->nodeType, currentScope, "Exit");
                            printf("this is what the value is\n\n\n%s\n\n\n\n", (yyvsp[-2].ast)->nodeType);
                        }else {
                            bltMips((yyvsp[-2].ast)->nodeType, currentScope, (yyvsp[0].ast)->nodeType, label);
                        }


                        // --- AST Actions --- //
                        (yyval.ast) = add_tree((yyvsp[-1].string), (yyvsp[-2].ast), (yyvsp[0].ast));
                        }
#line 2342 "parser.tab.c"
    break;

  case 54:
#line 824 "parser.y"
                         {printf("\nGreater Than\n");
                        // --- Generate IR code --- //
                        beqMips((yyvsp[-2].ast)->nodeType, currentScope, (yyvsp[0].ast)->nodeType, label);
                        

                       // --- AST Actions --- //
                       (yyval.ast) = add_tree((yyvsp[-1].string), (yyvsp[-2].ast), (yyvsp[0].ast));
                        }
#line 2355 "parser.tab.c"
    break;

  case 55:
#line 833 "parser.y"
                          {printf("\nGreater Than\n");
                        // --- Generate IR code --- //
                        bneMips((yyvsp[-2].ast)->nodeType, currentScope, (yyvsp[0].ast)->nodeType, label);


                        // --- AST Actions --- //
                        (yyval.ast) = add_tree((yyvsp[-1].string), (yyvsp[-2].ast), (yyvsp[0].ast));
                        }
#line 2368 "parser.tab.c"
    break;


#line 2372 "parser.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 844 "parser.y"


int main(int argc, char**argv)
{
	// #ifdef YYDEBUG
	// 	yydebug = 1;
	// #endif

    t = clock();


	printf("\n\n##### COMPILER STARTED #####\n\n");
    initIRcodeFile();
    initMipsFile();
	
	if (argc > 1){
	  if(!(yyin = fopen(argv[1], "r")))
          {
		perror(argv[1]);
		return(1);
	  }
	}

	yyparse();

}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

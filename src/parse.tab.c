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
#line 1 "src/parse.y"

#define YYPARSER // Diferenciar inclusão do definitions.h
#include "definitions.h"
#define YYSTYPE NoArvore *
//#define YYDEBUG 1
static char * nomeSalvo; // para uso geral em IDs
static char * nomeVarSalvo; // para uso em atribuições
static char * nomeFuncDecl; // para uso em declaracao de funções
static Pilha nomeFunc; // para uso em funções
static bool pilha_ja_inicializada = false; // já inicializada pilha
static int numLinhaSalva;
static int numLinhaSalvaF;
static NoArvore* arvoreSalva; /* armazena árvore para retornar depois */
static int yylex();
int yyerror(char *message);

#line 87 "parse.tab.c"

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
#ifndef YY_YY_PARSE_TAB_H_INCLUDED
# define YY_YY_PARSE_TAB_H_INCLUDED
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
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    RETURN = 261,
    INT = 262,
    VOID = 263,
    ID = 264,
    NUM = 265,
    IGUAL = 266,
    IGUALIGUAL = 267,
    DIF = 268,
    MENOR = 269,
    MAIOR = 270,
    MENIGUAL = 271,
    MAIIGUAL = 272,
    MAIS = 273,
    MENOS = 274,
    VEZES = 275,
    DIV = 276,
    ABREPAR = 277,
    FECHAPAR = 278,
    PVIRG = 279,
    VIRG = 280,
    ABRECOL = 281,
    FECHACOL = 282,
    ABRECH = 283,
    FECHACH = 284,
    COMENT = 285,
    ENTER = 286,
    ERRO = 287,
    FIMARQ = 288,
    ESPACO = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSE_TAB_H_INCLUDED  */



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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   107

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  109

#define YYUNDEFTOK  2
#define YYMAXUTOK   289


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    24,    24,    27,    40,    42,    43,    45,    45,    56,
      56,    76,    79,    83,    83,   100,   103,   105,   117,   119,
     130,   130,   147,   161,   173,   179,   191,   197,   198,   199,
     200,   201,   203,   204,   210,   215,   222,   228,   231,   235,
     242,   245,   252,   252,   264,   270,   272,   273,   274,   275,
     276,   277,   279,   285,   287,   288,   291,   297,   299,   300,
     302,   303,   304,   305,   310,   310,   325,   326,   332,   344,
     345
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "RETURN", "INT",
  "VOID", "ID", "NUM", "IGUAL", "IGUALIGUAL", "DIF", "MENOR", "MAIOR",
  "MENIGUAL", "MAIIGUAL", "MAIS", "MENOS", "VEZES", "DIV", "ABREPAR",
  "FECHAPAR", "PVIRG", "VIRG", "ABRECOL", "FECHACOL", "ABRECH", "FECHACH",
  "COMENT", "ENTER", "ERRO", "FIMARQ", "ESPACO", "$accept", "programa",
  "decl_lista", "decl", "var_decl", "$@1", "$@2", "tipo_esp", "fun_decl",
  "$@3", "params", "param_lista", "param", "$@4", "bloco_decl",
  "local_decl", "stmt_lista", "stmt", "exp_decl", "sel_decl", "iter_decl",
  "ret_decl", "exp", "var", "$@5", "simples_exp", "relacional", "soma_exp",
  "soma", "termo", "mult", "fator", "ativacao", "$@6", "args", "arg_lista", YY_NULLPTR
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
     285,   286,   287,   288,   289
};
# endif

#define YYPACT_NINF (-84)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-65)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      39,   -84,   -84,    24,    39,   -84,   -84,    22,   -84,   -84,
     -84,     3,    16,    27,    26,   -84,    45,    44,    48,    36,
      67,    54,    56,   -84,    58,    52,    51,    39,   -84,    57,
     -84,   -84,   -84,    59,    39,   -84,   -84,    71,     4,    61,
      62,    63,    40,    17,   -84,    12,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,    64,    78,   -84,    53,    37,   -84,
     -84,    12,    12,   -84,    66,    65,    70,    72,   -84,    12,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,    12,    12,
     -84,   -84,    12,    73,    74,   -84,    12,     8,   -84,   -84,
     -84,    55,    37,   -84,    32,    32,    75,   -84,   -84,    76,
      68,    90,   -84,   -84,   -84,    12,    32,   -84,   -84
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    11,    12,     0,     2,     4,     5,     0,     6,     1,
       3,     7,     0,     0,     0,     8,     0,     0,     0,    12,
       0,     0,    15,    18,     0,    19,     0,     0,    10,     0,
      24,    14,    17,     0,    26,    21,    23,     0,     0,     7,
       0,     0,     0,    41,    63,     0,    33,    22,    28,    25,
      27,    29,    30,    31,     0,    61,    40,    45,    53,    57,
      62,     0,     0,    37,     0,     0,     0,     0,    32,     0,
      50,    51,    47,    48,    46,    49,    54,    55,     0,     0,
      58,    59,     0,     0,     0,    38,     0,    67,    60,    39,
      61,    44,    52,    56,     0,     0,     0,    69,    70,     0,
      66,    34,    36,    43,    65,     0,     0,    68,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -84,   -84,   -84,    94,    69,   -84,   -84,     2,   -84,   -84,
     -84,   -84,   -26,   -84,    79,   -84,   -84,   -83,   -84,   -84,
     -84,   -84,   -42,   -74,   -84,   -84,   -84,    23,   -84,    21,
     -84,    25,   -84,   -84,   -84,   -84
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    12,    13,    20,     8,    14,
      21,    22,    23,    29,    48,    34,    38,    49,    50,    51,
      52,    53,    54,    55,    65,    56,    78,    57,    79,    58,
      82,    59,    60,    66,    99,   100
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      64,    32,     7,    67,    90,    90,     7,    40,    90,    41,
      42,   101,   102,    43,    44,     1,     2,    43,    44,    83,
      84,    43,    44,   108,     9,   -13,    45,    89,    46,    -9,
      45,    11,    30,    47,    45,    40,    37,    41,    42,   -64,
      15,    43,    44,   -42,    96,    98,     1,     2,    17,    43,
      44,     1,    19,    16,    45,    18,    46,    80,    81,   -16,
      30,    97,    45,   107,    63,    70,    71,    72,    73,    74,
      75,    76,    77,    76,    77,    24,    25,    26,   -20,    30,
      39,    27,    28,    33,    61,    62,    35,    -9,    68,    69,
      85,    86,    87,   105,   106,    88,    94,    95,    10,   104,
      92,    91,   103,    36,     0,    31,     0,    93
};

static const yytype_int8 yycheck[] =
{
      42,    27,     0,    45,    78,    79,     4,     3,    82,     5,
       6,    94,    95,     9,    10,     7,     8,     9,    10,    61,
      62,     9,    10,   106,     0,    22,    22,    69,    24,    26,
      22,     9,    28,    29,    22,     3,    34,     5,     6,    22,
      24,     9,    10,    26,    86,    87,     7,     8,    22,     9,
      10,     7,     8,    26,    22,    10,    24,    20,    21,    23,
      28,    87,    22,   105,    24,    12,    13,    14,    15,    16,
      17,    18,    19,    18,    19,    27,     9,    23,    26,    28,
       9,    25,    24,    26,    22,    22,    27,    26,    24,    11,
      24,    26,    22,    25,     4,    23,    23,    23,     4,    23,
      79,    78,    27,    34,    -1,    26,    -1,    82
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,    36,    37,    38,    39,    42,    43,     0,
      38,     9,    40,    41,    44,    24,    26,    22,    10,     8,
      42,    45,    46,    47,    27,     9,    23,    25,    24,    48,
      28,    49,    47,    26,    50,    27,    39,    42,    51,     9,
       3,     5,     6,     9,    10,    22,    24,    29,    49,    52,
      53,    54,    55,    56,    57,    58,    60,    62,    64,    66,
      67,    22,    22,    24,    57,    59,    68,    57,    24,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    61,    63,
      20,    21,    65,    57,    57,    24,    26,    22,    23,    57,
      58,    62,    64,    66,    23,    23,    57,    47,    57,    69,
      70,    52,    52,    27,    23,    25,     4,    57,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    40,    39,    41,
      39,    42,    42,    44,    43,    45,    45,    46,    46,    47,
      48,    47,    49,    50,    50,    51,    51,    52,    52,    52,
      52,    52,    53,    53,    54,    54,    55,    56,    56,    57,
      57,    58,    59,    58,    60,    60,    61,    61,    61,    61,
      61,    61,    62,    62,    63,    63,    64,    64,    65,    65,
      66,    66,    66,    66,    68,    67,    69,    69,    70,    70,
      70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     0,     4,     0,
       7,     1,     1,     0,     7,     1,     1,     3,     1,     2,
       0,     5,     4,     2,     0,     2,     0,     1,     1,     1,
       1,     1,     2,     1,     5,     7,     5,     2,     3,     3,
       1,     1,     0,     5,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     1,     1,     0,     5,     1,     0,     3,     1,
       1
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
  YYUSE (yytype);
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
#line 25 "src/parse.y"
                { arvoreSalva = yyvsp[0];}
#line 1422 "parse.tab.c"
    break;

  case 3:
#line 28 "src/parse.y"
                { YYSTYPE temp = yyvsp[-1];
                // adiciona os nós como irmãos
                // pela recursividade a esquerda
                  if(temp != NULL){
                    while(temp->filho[0]->irmao != NULL)
                        temp = temp->filho[0]->irmao;
                    temp->filho[0]->irmao = yyvsp[0];
                    yyval = yyvsp[-1];
                  }else{
                    yyval = yyvsp[0];
                  }
                }
#line 1439 "parse.tab.c"
    break;

  case 4:
#line 40 "src/parse.y"
                   {yyval = yyvsp[0];}
#line 1445 "parse.tab.c"
    break;

  case 5:
#line 42 "src/parse.y"
                       {yyval = yyvsp[0];}
#line 1451 "parse.tab.c"
    break;

  case 6:
#line 43 "src/parse.y"
                       {yyval = yyvsp[0];}
#line 1457 "parse.tab.c"
    break;

  case 7:
#line 45 "src/parse.y"
                          { nomeSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                 }
#line 1465 "parse.tab.c"
    break;

  case 8:
#line 48 "src/parse.y"
                    {   yyval = yyvsp[-3];
                        YYSTYPE vd;
                        vd = novoNoDecl(D_var);
                        vd->atrib.nome = nomeSalvo;
                        vd->numlinha = numLinhaSalva;
                        vd->tipo_c = yyvsp[-3]->tipo_c;
                        yyval->filho[0] = vd;
                    }
#line 1478 "parse.tab.c"
    break;

  case 9:
#line 56 "src/parse.y"
                          { nomeSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                 }
#line 1486 "parse.tab.c"
    break;

  case 10:
#line 60 "src/parse.y"
                            { yyval = yyvsp[-6];
                              YYSTYPE indice = novoNoExp(E_Num);
                              indice->atrib.val = atoi(NUM_val);
                              indice->tipo_c = Integer;
                              YYSTYPE vd;
                              vd = novoNoDecl(D_var);
                              vd->atrib.nome = nomeSalvo;
                              vd->numlinha = numLinhaSalva;
                              vd->filho[0] = indice;
                              if(yyvsp[-6]->tipo_c == Integer)
                                vd->tipo_c = Array;
                              else
                                vd->tipo_c = Void;
                              yyval->filho[0] = vd; //nó de tipo fica como pai da declaracao
                            }
#line 1506 "parse.tab.c"
    break;

  case 11:
#line 76 "src/parse.y"
                  { yyval = novoNoDecl(D_Tipo); // cria o nó para o tipo
                    yyval->tipo_c = Integer; 
                  }
#line 1514 "parse.tab.c"
    break;

  case 12:
#line 79 "src/parse.y"
                   { yyval = novoNoDecl(D_Tipo); // cria o nó para o tipo
                    yyval->tipo_c = Void; 
                   }
#line 1522 "parse.tab.c"
    break;

  case 13:
#line 83 "src/parse.y"
                          {
                    nomeFuncDecl = copiaString(ID_nome);
                    numLinhaSalvaF = numlinha;
                 }
#line 1531 "parse.tab.c"
    break;

  case 14:
#line 88 "src/parse.y"
              {
                yyval = yyvsp[-6];
                YYSTYPE fun;
                fun = novoNoDecl(D_func);
                fun->filho[0] = yyvsp[-2];
                fun->filho[1] = yyvsp[0];
                fun->atrib.nome = nomeFuncDecl;
                fun->numlinha = numLinhaSalvaF;
                fun->tipo_c = yyvsp[-6]->tipo_c;
                yyval->filho[0] = fun;
              }
#line 1547 "parse.tab.c"
    break;

  case 15:
#line 100 "src/parse.y"
                          { yyval = yyvsp[0];
                            //$$->filho[0] = $1;
                          }
#line 1555 "parse.tab.c"
    break;

  case 16:
#line 103 "src/parse.y"
                   { yyval = novoNoExp(E_Id); yyval->atrib.nome = "void"; yyval->tipo_c = Void;}
#line 1561 "parse.tab.c"
    break;

  case 17:
#line 105 "src/parse.y"
                                     {  YYSTYPE temp = yyvsp[-2];
                                        // adiciona os nós como irmãos
                                        if(temp != NULL){
                                            while(temp->irmao != NULL){
                                                temp = temp->irmao;
                                            }
                                            temp-> irmao = yyvsp[0];
                                            yyval = yyvsp[-2];
                                        }else{
                                            yyval = yyvsp[0];
                                        }
                                     }
#line 1578 "parse.tab.c"
    break;

  case 18:
#line 117 "src/parse.y"
                    {yyval = yyvsp[0];}
#line 1584 "parse.tab.c"
    break;

  case 19:
#line 119 "src/parse.y"
                          { 
                   yyval = yyvsp[-1];
                   nomeSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                   YYSTYPE par;
                   par = novoNoDecl(D_var); // cuidado com isso
                   par-> atrib.nome = nomeSalvo;
                   par-> numlinha = numLinhaSalva;
                   par-> tipo_c = yyvsp[-1]->tipo_c;
                   yyval->filho[0] = par;
                 }
#line 1600 "parse.tab.c"
    break;

  case 20:
#line 130 "src/parse.y"
                          {nomeSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                 }
#line 1608 "parse.tab.c"
    break;

  case 21:
#line 134 "src/parse.y"
              {    yyval = yyvsp[-4];
                   YYSTYPE par;
                   par = novoNoDecl(D_var);
                   par-> atrib.nome = nomeSalvo;
                   par-> numlinha = numLinhaSalva;
                   if(yyvsp[-4]->tipo_c == Integer){
                      par-> tipo_c = Array;
                   }else{
                      par->tipo_c = yyvsp[-4]->tipo_c;
                   }
                   yyval->filho[0] = par;
              }
#line 1625 "parse.tab.c"
    break;

  case 22:
#line 147 "src/parse.y"
                                                   { { YYSTYPE temp = yyvsp[-2];
                                                    // adiciona os nós como irmãos
                                                      if(temp != NULL){
                                                        while(temp->irmao != NULL){
                                                            temp = temp->irmao;
                                                        }
                                                        temp-> irmao = yyvsp[-1];
                                                        yyval = yyvsp[-2];
                                                      }else{
                                                        yyval = yyvsp[-1];
                                                      }
                                                    }      
                                                   }
#line 1643 "parse.tab.c"
    break;

  case 23:
#line 161 "src/parse.y"
                                   { YYSTYPE temp = yyvsp[-1];
                                    // adiciona os nós como irmãos
                                      if(temp != NULL && temp->atrib.nome != "sem_local_decl" ){
                                        while(temp->irmao != NULL){
                                            temp = temp->irmao;
                                        }
                                        temp-> irmao = yyvsp[0];
                                        yyval = yyvsp[-1];
                                      }else{
                                        yyval = yyvsp[0];
                                      }
                                    }
#line 1660 "parse.tab.c"
    break;

  case 24:
#line 173 "src/parse.y"
                      { 
                        //$$ = novoNoExp(E_Id);
                        //$$-> atrib.nome = "sem_local_decl";
                        yyval = NULL;
                    }
#line 1670 "parse.tab.c"
    break;

  case 25:
#line 179 "src/parse.y"
                              { YYSTYPE temp = yyvsp[-1];
                                    // adiciona os nós como irmãos
                                      if(temp != NULL){
                                        while(temp->irmao != NULL){
                                            temp = temp->irmao;
                                        }
                                        temp-> irmao = yyvsp[0];
                                        yyval = yyvsp[-1];
                                      }else{
                                        yyval = yyvsp[0];
                                      }
                                    }
#line 1687 "parse.tab.c"
    break;

  case 26:
#line 191 "src/parse.y"
                      { 
                        //$$ = novoNoExp(E_Id);
                        //$$-> atrib.nome = "sem_stmt_lista";
                        yyval = NULL;
                    }
#line 1697 "parse.tab.c"
    break;

  case 27:
#line 197 "src/parse.y"
                       {yyval = yyvsp[0];}
#line 1703 "parse.tab.c"
    break;

  case 28:
#line 198 "src/parse.y"
                         {yyval = yyvsp[0];}
#line 1709 "parse.tab.c"
    break;

  case 29:
#line 199 "src/parse.y"
                       {yyval = yyvsp[0];}
#line 1715 "parse.tab.c"
    break;

  case 30:
#line 200 "src/parse.y"
                        {yyval = yyvsp[0];}
#line 1721 "parse.tab.c"
    break;

  case 31:
#line 201 "src/parse.y"
                       {yyval = yyvsp[0];}
#line 1727 "parse.tab.c"
    break;

  case 32:
#line 203 "src/parse.y"
                        {yyval = yyvsp[-1];}
#line 1733 "parse.tab.c"
    break;

  case 33:
#line 204 "src/parse.y"
                    { 
                        //$$ = novoNoExp(E_Id);
                        //$$->atrib.nome = "expr_vazia";
                        yyval = NULL;
                    }
#line 1743 "parse.tab.c"
    break;

  case 34:
#line 211 "src/parse.y"
                { yyval = novoNoStmt(S_If);
                  yyval->filho[0] = yyvsp[-2];
                  yyval->filho[1] = yyvsp[0];
                }
#line 1752 "parse.tab.c"
    break;

  case 35:
#line 216 "src/parse.y"
                { yyval = novoNoStmt(S_If);
                  yyval->filho[0] = yyvsp[-4];
                  yyval->filho[1] = yyvsp[-2];
                  yyval->filho[2] = yyvsp[0];
                }
#line 1762 "parse.tab.c"
    break;

  case 36:
#line 223 "src/parse.y"
                { yyval = novoNoStmt(S_While);
                  yyval->filho[0] = yyvsp[-2];
                  yyval->filho[1] = yyvsp[0];
                }
#line 1771 "parse.tab.c"
    break;

  case 37:
#line 228 "src/parse.y"
                           { 
                        yyval = novoNoStmt(S_Retorno);
                    }
#line 1779 "parse.tab.c"
    break;

  case 38:
#line 231 "src/parse.y"
                               {yyval = novoNoStmt(S_Retorno);
                                yyval->filho[0] = yyvsp[-1];
                                }
#line 1787 "parse.tab.c"
    break;

  case 39:
#line 236 "src/parse.y"
                { yyval = novoNoStmt(S_Atrib);
                  yyval->filho[0] = yyvsp[-2];
                  yyval->filho[1] = yyvsp[0];
                  yyval->tipo_c = Integer;
                  yyval->atrib.op = IGUAL; //IGUAL
                }
#line 1798 "parse.tab.c"
    break;

  case 40:
#line 242 "src/parse.y"
                          {yyval = yyvsp[0];}
#line 1804 "parse.tab.c"
    break;

  case 41:
#line 245 "src/parse.y"
                 { nomeSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                   yyval = novoNoExp(E_Id);
                   yyval->atrib.nome = nomeSalvo;
                   yyval->numlinha = numLinhaSalva;
                   yyval->tipo_c = Void;// precisa buscar na TS
                 }
#line 1816 "parse.tab.c"
    break;

  case 42:
#line 252 "src/parse.y"
                 { nomeVarSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                 }
#line 1824 "parse.tab.c"
    break;

  case 43:
#line 256 "src/parse.y"
                 {
                   yyval = novoNoExp(E_Id);
                   yyval->atrib.nome = nomeVarSalvo;
                   yyval->numlinha = numLinhaSalva;
                   yyval->filho[0] = yyvsp[-1];
                   yyval->tipo_c = Integer; //certeza. v[indice] é inteiro
                 }
#line 1836 "parse.tab.c"
    break;

  case 44:
#line 265 "src/parse.y"
                { yyval = novoNoExp(E_Op);
                  yyval->filho[0] = yyvsp[-2];
                  yyval->filho[1] = yyvsp[0];
                  yyval->atrib.op = yyvsp[-1]->atrib.op; // Token recebido pelo relacional
                }
#line 1846 "parse.tab.c"
    break;

  case 45:
#line 270 "src/parse.y"
                       {yyval = yyvsp[0];}
#line 1852 "parse.tab.c"
    break;

  case 46:
#line 272 "src/parse.y"
                      {yyval = novoNoExp(E_Id); yyval->atrib.op = MENIGUAL;}
#line 1858 "parse.tab.c"
    break;

  case 47:
#line 273 "src/parse.y"
                   {yyval = novoNoExp(E_Id); yyval->atrib.op = MENOR;}
#line 1864 "parse.tab.c"
    break;

  case 48:
#line 274 "src/parse.y"
                   {yyval = novoNoExp(E_Id); yyval->atrib.op = MAIOR;}
#line 1870 "parse.tab.c"
    break;

  case 49:
#line 275 "src/parse.y"
                      {yyval = novoNoExp(E_Id); yyval->atrib.op = MAIIGUAL;}
#line 1876 "parse.tab.c"
    break;

  case 50:
#line 276 "src/parse.y"
                        {yyval = novoNoExp(E_Id); yyval->atrib.op = IGUALIGUAL;}
#line 1882 "parse.tab.c"
    break;

  case 51:
#line 277 "src/parse.y"
                 {yyval = novoNoExp(E_Id); yyval->atrib.op = DIF;}
#line 1888 "parse.tab.c"
    break;

  case 52:
#line 280 "src/parse.y"
                { yyval = novoNoExp(E_Op);
                  yyval->filho[0] = yyvsp[-2];
                  yyval->filho[1] = yyvsp[0];
                  yyval->atrib.op = yyvsp[-1]->atrib.op; // Token recebido pelo "soma"
                }
#line 1898 "parse.tab.c"
    break;

  case 53:
#line 285 "src/parse.y"
                    {yyval = yyvsp[0];}
#line 1904 "parse.tab.c"
    break;

  case 54:
#line 287 "src/parse.y"
                   {yyval = novoNoExp(E_Id); yyval->atrib.op = MAIS;}
#line 1910 "parse.tab.c"
    break;

  case 55:
#line 288 "src/parse.y"
                    {yyval = novoNoExp(E_Id); yyval->atrib.op = MENOS;}
#line 1916 "parse.tab.c"
    break;

  case 56:
#line 292 "src/parse.y"
                { yyval = novoNoExp(E_Op);
                  yyval->filho[0] = yyvsp[-2];
                  yyval->filho[1] = yyvsp[0];
                  yyval->atrib.op = yyvsp[-1]->atrib.op; // Token recebido pelo "mult"
                }
#line 1926 "parse.tab.c"
    break;

  case 57:
#line 297 "src/parse.y"
                    {yyval = yyvsp[0];}
#line 1932 "parse.tab.c"
    break;

  case 58:
#line 299 "src/parse.y"
                    {yyval = novoNoExp(E_Id); yyval->atrib.op = VEZES;}
#line 1938 "parse.tab.c"
    break;

  case 59:
#line 300 "src/parse.y"
                  {yyval = novoNoExp(E_Id); yyval->atrib.op = DIV;}
#line 1944 "parse.tab.c"
    break;

  case 60:
#line 302 "src/parse.y"
                                   {yyval = yyvsp[-2];}
#line 1950 "parse.tab.c"
    break;

  case 61:
#line 303 "src/parse.y"
                  {yyval = yyvsp[0];}
#line 1956 "parse.tab.c"
    break;

  case 62:
#line 304 "src/parse.y"
                       {yyval = yyvsp[0];}
#line 1962 "parse.tab.c"
    break;

  case 63:
#line 305 "src/parse.y"
                  { yyval = novoNoExp(E_Num);
                    yyval->atrib.val = atoi(NUM_val);
                    yyval->tipo_c = Integer;
                  }
#line 1971 "parse.tab.c"
    break;

  case 64:
#line 310 "src/parse.y"
                 { 
                   if(pilha_ja_inicializada == false){
                      inicializaPilha(&nomeFunc);
                      pilha_ja_inicializada = true;
                   }
                   push(&nomeFunc,copiaString(ID_nome));
                   numLinhaSalva = numlinha;
                                                       }
#line 1984 "parse.tab.c"
    break;

  case 65:
#line 319 "src/parse.y"
                 { yyval = novoNoStmt(S_Chamada);
                   yyval->filho[1] = yyvsp[-1]; // filho direito
                   yyval->atrib.nome = pop(&nomeFunc);
                   yyval->numlinha = numLinhaSalva;
                 }
#line 1994 "parse.tab.c"
    break;

  case 66:
#line 325 "src/parse.y"
                        {yyval = yyvsp[0];}
#line 2000 "parse.tab.c"
    break;

  case 67:
#line 326 "src/parse.y"
                      { 
                        //$$ = novoNoExp(E_Id);
                        //$$-> atrib.nome = "sem_args";
                        yyval = NULL;
                    }
#line 2010 "parse.tab.c"
    break;

  case 68:
#line 332 "src/parse.y"
                                 {  YYSTYPE temp = yyvsp[-2];
                                    // adiciona os nós como irmãos
                                    if(temp != NULL){
                                        while(temp->irmao != NULL){
                                            temp = temp->irmao;
                                        }
                                        temp-> irmao = yyvsp[0];
                                        yyval = yyvsp[-2];
                                    }else{
                                        yyval = yyvsp[0];
                                    }
                                 }
#line 2027 "parse.tab.c"
    break;

  case 69:
#line 344 "src/parse.y"
                    {yyval = yyvsp[0];}
#line 2033 "parse.tab.c"
    break;

  case 70:
#line 345 "src/parse.y"
                  {yyval = yyvsp[0];}
#line 2039 "parse.tab.c"
    break;


#line 2043 "parse.tab.c"

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
#line 347 "src/parse.y"


int yyerror(char * message){
    char* nt = nome_token(yychar);
    if(yychar == ID || yychar == NUM){
        fprintf(stdout,"Erro Sintático %s  na linha: %d\n", nt, numlinha);
    }else{
        fprintf(stdout,"Erro Sintático %s (%s)  na linha: %d\n", nt, yytext, numlinha);
    }
    Erro = true;
    free(nt);
    return 0;
}

// Informa ao Yacc a função reponsável pela análise léxica 
static int yylex(void)
{ return retornaToken(); }

// Função principal do analisador sintático
NoArvore * parse(void){
//  extern int yydebug;
//  yydebug = 1;
  yyparse();
  return arvoreSalva;
}

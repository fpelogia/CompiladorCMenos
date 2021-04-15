/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parse.y"

#define YYPARSER // Diferenciar inclusão do definitions.h
#include "definitions.h"
#define YYSTYPE NoArvore *
//#define YYDEBUG 1
static char * nomeSalvo; // para uso geral em IDs
static char * nomeVarSalvo; // para uso em atribuições
static char * nomeFuncDecl; // para uso em declaracao de funções
static char * nomeFunc; // para uso em funções
static int numLinhaSalva;
static int numLinhaSalvaF;
static NoArvore* arvoreSalva; /* armazena árvore para retornar depois */
static int yylex();
int yyerror(char *message);


#line 88 "parse.tab.c"

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

#include "parse.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_WHILE = 5,                      /* WHILE  */
  YYSYMBOL_RETURN = 6,                     /* RETURN  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_VOID = 8,                       /* VOID  */
  YYSYMBOL_ID = 9,                         /* ID  */
  YYSYMBOL_NUM = 10,                       /* NUM  */
  YYSYMBOL_IGUAL = 11,                     /* IGUAL  */
  YYSYMBOL_IGUALIGUAL = 12,                /* IGUALIGUAL  */
  YYSYMBOL_DIF = 13,                       /* DIF  */
  YYSYMBOL_MENOR = 14,                     /* MENOR  */
  YYSYMBOL_MAIOR = 15,                     /* MAIOR  */
  YYSYMBOL_MENIGUAL = 16,                  /* MENIGUAL  */
  YYSYMBOL_MAIIGUAL = 17,                  /* MAIIGUAL  */
  YYSYMBOL_MAIS = 18,                      /* MAIS  */
  YYSYMBOL_MENOS = 19,                     /* MENOS  */
  YYSYMBOL_VEZES = 20,                     /* VEZES  */
  YYSYMBOL_DIV = 21,                       /* DIV  */
  YYSYMBOL_ABREPAR = 22,                   /* ABREPAR  */
  YYSYMBOL_FECHAPAR = 23,                  /* FECHAPAR  */
  YYSYMBOL_PVIRG = 24,                     /* PVIRG  */
  YYSYMBOL_VIRG = 25,                      /* VIRG  */
  YYSYMBOL_ABRECOL = 26,                   /* ABRECOL  */
  YYSYMBOL_FECHACOL = 27,                  /* FECHACOL  */
  YYSYMBOL_ABRECH = 28,                    /* ABRECH  */
  YYSYMBOL_FECHACH = 29,                   /* FECHACH  */
  YYSYMBOL_COMENT = 30,                    /* COMENT  */
  YYSYMBOL_ENTER = 31,                     /* ENTER  */
  YYSYMBOL_ERRO = 32,                      /* ERRO  */
  YYSYMBOL_FIMARQ = 33,                    /* FIMARQ  */
  YYSYMBOL_ESPACO = 34,                    /* ESPACO  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_programa = 36,                  /* programa  */
  YYSYMBOL_decl_lista = 37,                /* decl_lista  */
  YYSYMBOL_decl = 38,                      /* decl  */
  YYSYMBOL_var_decl = 39,                  /* var_decl  */
  YYSYMBOL_40_1 = 40,                      /* $@1  */
  YYSYMBOL_41_2 = 41,                      /* $@2  */
  YYSYMBOL_tipo_esp = 42,                  /* tipo_esp  */
  YYSYMBOL_fun_decl = 43,                  /* fun_decl  */
  YYSYMBOL_44_3 = 44,                      /* $@3  */
  YYSYMBOL_params = 45,                    /* params  */
  YYSYMBOL_param_lista = 46,               /* param_lista  */
  YYSYMBOL_param = 47,                     /* param  */
  YYSYMBOL_48_4 = 48,                      /* $@4  */
  YYSYMBOL_bloco_decl = 49,                /* bloco_decl  */
  YYSYMBOL_local_decl = 50,                /* local_decl  */
  YYSYMBOL_stmt_lista = 51,                /* stmt_lista  */
  YYSYMBOL_stmt = 52,                      /* stmt  */
  YYSYMBOL_exp_decl = 53,                  /* exp_decl  */
  YYSYMBOL_sel_decl = 54,                  /* sel_decl  */
  YYSYMBOL_iter_decl = 55,                 /* iter_decl  */
  YYSYMBOL_ret_decl = 56,                  /* ret_decl  */
  YYSYMBOL_exp = 57,                       /* exp  */
  YYSYMBOL_var = 58,                       /* var  */
  YYSYMBOL_59_5 = 59,                      /* $@5  */
  YYSYMBOL_simples_exp = 60,               /* simples_exp  */
  YYSYMBOL_relacional = 61,                /* relacional  */
  YYSYMBOL_soma_exp = 62,                  /* soma_exp  */
  YYSYMBOL_soma = 63,                      /* soma  */
  YYSYMBOL_termo = 64,                     /* termo  */
  YYSYMBOL_mult = 65,                      /* mult  */
  YYSYMBOL_fator = 66,                     /* fator  */
  YYSYMBOL_ativacao = 67,                  /* ativacao  */
  YYSYMBOL_68_6 = 68,                      /* $@6  */
  YYSYMBOL_args = 69,                      /* args  */
  YYSYMBOL_arg_lista = 70                  /* arg_lista  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
     241,   244,   251,   251,   263,   269,   271,   272,   273,   274,
     275,   276,   278,   284,   286,   287,   290,   296,   298,   299,
     301,   302,   303,   304,   309,   309,   319,   320,   326,   338,
     339
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "WHILE",
  "RETURN", "INT", "VOID", "ID", "NUM", "IGUAL", "IGUALIGUAL", "DIF",
  "MENOR", "MAIOR", "MENIGUAL", "MAIIGUAL", "MAIS", "MENOS", "VEZES",
  "DIV", "ABREPAR", "FECHAPAR", "PVIRG", "VIRG", "ABRECOL", "FECHACOL",
  "ABRECH", "FECHACH", "COMENT", "ENTER", "ERRO", "FIMARQ", "ESPACO",
  "$accept", "programa", "decl_lista", "decl", "var_decl", "$@1", "$@2",
  "tipo_esp", "fun_decl", "$@3", "params", "param_lista", "param", "$@4",
  "bloco_decl", "local_decl", "stmt_lista", "stmt", "exp_decl", "sel_decl",
  "iter_decl", "ret_decl", "exp", "var", "$@5", "simples_exp",
  "relacional", "soma_exp", "soma", "termo", "mult", "fator", "ativacao",
  "$@6", "args", "arg_lista", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289
};
#endif

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
       0,     3,     4,     5,     6,    12,    13,    20,     8,    14,
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


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

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
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* programa: decl_lista  */
#line 25 "parse.y"
                { arvoreSalva = yyvsp[0];}
#line 1230 "parse.tab.c"
    break;

  case 3: /* decl_lista: decl_lista decl  */
#line 28 "parse.y"
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
#line 1247 "parse.tab.c"
    break;

  case 4: /* decl_lista: decl  */
#line 40 "parse.y"
                   {yyval = yyvsp[0];}
#line 1253 "parse.tab.c"
    break;

  case 5: /* decl: var_decl  */
#line 42 "parse.y"
                       {yyval = yyvsp[0];}
#line 1259 "parse.tab.c"
    break;

  case 6: /* decl: fun_decl  */
#line 43 "parse.y"
                       {yyval = yyvsp[0];}
#line 1265 "parse.tab.c"
    break;

  case 7: /* $@1: %empty  */
#line 45 "parse.y"
                          { nomeSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                 }
#line 1273 "parse.tab.c"
    break;

  case 8: /* var_decl: tipo_esp ID $@1 PVIRG  */
#line 48 "parse.y"
                    {   yyval = yyvsp[-3];
                        YYSTYPE vd;
                        vd = novoNoDecl(D_var);
                        vd->atrib.nome = nomeSalvo;
                        vd->numlinha = numLinhaSalva;
                        vd->tipo_c = yyvsp[-3]->tipo_c;
                        yyval->filho[0] = vd;
                    }
#line 1286 "parse.tab.c"
    break;

  case 9: /* $@2: %empty  */
#line 56 "parse.y"
                          { nomeSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                 }
#line 1294 "parse.tab.c"
    break;

  case 10: /* var_decl: tipo_esp ID $@2 ABRECOL NUM FECHACOL PVIRG  */
#line 60 "parse.y"
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
#line 1314 "parse.tab.c"
    break;

  case 11: /* tipo_esp: INT  */
#line 76 "parse.y"
                  { yyval = novoNoDecl(D_Tipo); // cria o nó para o tipo
                    yyval->tipo_c = Integer; 
                  }
#line 1322 "parse.tab.c"
    break;

  case 12: /* tipo_esp: VOID  */
#line 79 "parse.y"
                   { yyval = novoNoDecl(D_Tipo); // cria o nó para o tipo
                    yyval->tipo_c = Void; 
                   }
#line 1330 "parse.tab.c"
    break;

  case 13: /* $@3: %empty  */
#line 83 "parse.y"
                          {
                    nomeFuncDecl = copiaString(ID_nome);
                    numLinhaSalvaF = numlinha;
                 }
#line 1339 "parse.tab.c"
    break;

  case 14: /* fun_decl: tipo_esp ID $@3 ABREPAR params FECHAPAR bloco_decl  */
#line 88 "parse.y"
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
#line 1355 "parse.tab.c"
    break;

  case 15: /* params: param_lista  */
#line 100 "parse.y"
                          { yyval = yyvsp[0];
                            //$$->filho[0] = $1;
                          }
#line 1363 "parse.tab.c"
    break;

  case 16: /* params: VOID  */
#line 103 "parse.y"
                   { yyval = novoNoExp(E_Id); yyval->atrib.nome = "void"; yyval->tipo_c = Void;}
#line 1369 "parse.tab.c"
    break;

  case 17: /* param_lista: param_lista VIRG param  */
#line 105 "parse.y"
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
#line 1386 "parse.tab.c"
    break;

  case 18: /* param_lista: param  */
#line 117 "parse.y"
                    {yyval = yyvsp[0];}
#line 1392 "parse.tab.c"
    break;

  case 19: /* param: tipo_esp ID  */
#line 119 "parse.y"
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
#line 1408 "parse.tab.c"
    break;

  case 20: /* $@4: %empty  */
#line 130 "parse.y"
                          {nomeSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                 }
#line 1416 "parse.tab.c"
    break;

  case 21: /* param: tipo_esp ID $@4 ABRECOL FECHACOL  */
#line 134 "parse.y"
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
#line 1433 "parse.tab.c"
    break;

  case 22: /* bloco_decl: ABRECH local_decl stmt_lista FECHACH  */
#line 147 "parse.y"
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
#line 1451 "parse.tab.c"
    break;

  case 23: /* local_decl: local_decl var_decl  */
#line 161 "parse.y"
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
#line 1468 "parse.tab.c"
    break;

  case 24: /* local_decl: %empty  */
#line 173 "parse.y"
                      { 
                        //$$ = novoNoExp(E_Id);
                        //$$-> atrib.nome = "sem_local_decl";
                        yyval = NULL;
                    }
#line 1478 "parse.tab.c"
    break;

  case 25: /* stmt_lista: stmt_lista stmt  */
#line 179 "parse.y"
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
#line 1495 "parse.tab.c"
    break;

  case 26: /* stmt_lista: %empty  */
#line 191 "parse.y"
                      { 
                        //$$ = novoNoExp(E_Id);
                        //$$-> atrib.nome = "sem_stmt_lista";
                        yyval = NULL;
                    }
#line 1505 "parse.tab.c"
    break;

  case 27: /* stmt: exp_decl  */
#line 197 "parse.y"
                       {yyval = yyvsp[0];}
#line 1511 "parse.tab.c"
    break;

  case 28: /* stmt: bloco_decl  */
#line 198 "parse.y"
                         {yyval = yyvsp[0];}
#line 1517 "parse.tab.c"
    break;

  case 29: /* stmt: sel_decl  */
#line 199 "parse.y"
                       {yyval = yyvsp[0];}
#line 1523 "parse.tab.c"
    break;

  case 30: /* stmt: iter_decl  */
#line 200 "parse.y"
                        {yyval = yyvsp[0];}
#line 1529 "parse.tab.c"
    break;

  case 31: /* stmt: ret_decl  */
#line 201 "parse.y"
                       {yyval = yyvsp[0];}
#line 1535 "parse.tab.c"
    break;

  case 32: /* exp_decl: exp PVIRG  */
#line 203 "parse.y"
                        {yyval = yyvsp[-1];}
#line 1541 "parse.tab.c"
    break;

  case 33: /* exp_decl: PVIRG  */
#line 204 "parse.y"
                    { 
                        //$$ = novoNoExp(E_Id);
                        //$$->atrib.nome = "expr_vazia";
                        yyval = NULL;
                    }
#line 1551 "parse.tab.c"
    break;

  case 34: /* sel_decl: IF ABREPAR exp FECHAPAR stmt  */
#line 211 "parse.y"
                { yyval = novoNoStmt(S_If);
                  yyval->filho[0] = yyvsp[-2];
                  yyval->filho[1] = yyvsp[0];
                }
#line 1560 "parse.tab.c"
    break;

  case 35: /* sel_decl: IF ABREPAR exp FECHAPAR stmt ELSE stmt  */
#line 216 "parse.y"
                { yyval = novoNoStmt(S_If);
                  yyval->filho[0] = yyvsp[-4];
                  yyval->filho[1] = yyvsp[-2];
                  yyval->filho[2] = yyvsp[0];
                }
#line 1570 "parse.tab.c"
    break;

  case 36: /* iter_decl: WHILE ABREPAR exp FECHAPAR stmt  */
#line 223 "parse.y"
                { yyval = novoNoStmt(S_While);
                  yyval->filho[0] = yyvsp[-2];
                  yyval->filho[1] = yyvsp[0];
                }
#line 1579 "parse.tab.c"
    break;

  case 37: /* ret_decl: RETURN PVIRG  */
#line 228 "parse.y"
                           { 
                        yyval = novoNoStmt(S_Retorno);
                    }
#line 1587 "parse.tab.c"
    break;

  case 38: /* ret_decl: RETURN exp PVIRG  */
#line 231 "parse.y"
                               {yyval = novoNoStmt(S_Retorno);
                                yyval->filho[0] = yyvsp[-1];
                                }
#line 1595 "parse.tab.c"
    break;

  case 39: /* exp: var IGUAL exp  */
#line 236 "parse.y"
                { yyval = novoNoStmt(S_Atrib);
                  yyval->filho[0] = yyvsp[-2];
                  yyval->filho[1] = yyvsp[0];
                  yyval->atrib.op = IGUAL; //IGUAL
                }
#line 1605 "parse.tab.c"
    break;

  case 40: /* exp: simples_exp  */
#line 241 "parse.y"
                          {yyval = yyvsp[0];}
#line 1611 "parse.tab.c"
    break;

  case 41: /* var: ID  */
#line 244 "parse.y"
                 { nomeSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                   yyval = novoNoExp(E_Id);
                   yyval->atrib.nome = nomeSalvo;
                   yyval->numlinha = numLinhaSalva;
                   yyval->tipo_c = Void;// precisa buscar na TS
                 }
#line 1623 "parse.tab.c"
    break;

  case 42: /* $@5: %empty  */
#line 251 "parse.y"
                 { nomeVarSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                 }
#line 1631 "parse.tab.c"
    break;

  case 43: /* var: ID $@5 ABRECOL exp FECHACOL  */
#line 255 "parse.y"
                 {
                   yyval = novoNoExp(E_Id);
                   yyval->atrib.nome = nomeVarSalvo;
                   yyval->numlinha = numLinhaSalva;
                   yyval->filho[0] = yyvsp[-1];
                   yyval->tipo_c = Integer; //certeza. v[indice] é inteiro
                 }
#line 1643 "parse.tab.c"
    break;

  case 44: /* simples_exp: soma_exp relacional soma_exp  */
#line 264 "parse.y"
                { yyval = novoNoExp(E_Op);
                  yyval->filho[0] = yyvsp[-2];
                  yyval->filho[1] = yyvsp[0];
                  yyval->atrib.op = yyvsp[-1]->atrib.op; // Token recebido pelo relacional
                }
#line 1653 "parse.tab.c"
    break;

  case 45: /* simples_exp: soma_exp  */
#line 269 "parse.y"
                       {yyval = yyvsp[0];}
#line 1659 "parse.tab.c"
    break;

  case 46: /* relacional: MENIGUAL  */
#line 271 "parse.y"
                      {yyval = novoNoExp(E_Id); yyval->atrib.op = MENIGUAL;}
#line 1665 "parse.tab.c"
    break;

  case 47: /* relacional: MENOR  */
#line 272 "parse.y"
                   {yyval = novoNoExp(E_Id); yyval->atrib.op = MENOR;}
#line 1671 "parse.tab.c"
    break;

  case 48: /* relacional: MAIOR  */
#line 273 "parse.y"
                   {yyval = novoNoExp(E_Id); yyval->atrib.op = MAIOR;}
#line 1677 "parse.tab.c"
    break;

  case 49: /* relacional: MAIIGUAL  */
#line 274 "parse.y"
                      {yyval = novoNoExp(E_Id); yyval->atrib.op = MAIIGUAL;}
#line 1683 "parse.tab.c"
    break;

  case 50: /* relacional: IGUALIGUAL  */
#line 275 "parse.y"
                        {yyval = novoNoExp(E_Id); yyval->atrib.op = IGUALIGUAL;}
#line 1689 "parse.tab.c"
    break;

  case 51: /* relacional: DIF  */
#line 276 "parse.y"
                 {yyval = novoNoExp(E_Id); yyval->atrib.op = DIF;}
#line 1695 "parse.tab.c"
    break;

  case 52: /* soma_exp: soma_exp soma termo  */
#line 279 "parse.y"
                { yyval = novoNoExp(E_Op);
                  yyval->filho[0] = yyvsp[-2];
                  yyval->filho[1] = yyvsp[0];
                  yyval->atrib.op = yyvsp[-1]->atrib.op; // Token recebido pelo "soma"
                }
#line 1705 "parse.tab.c"
    break;

  case 53: /* soma_exp: termo  */
#line 284 "parse.y"
                    {yyval = yyvsp[0];}
#line 1711 "parse.tab.c"
    break;

  case 54: /* soma: MAIS  */
#line 286 "parse.y"
                   {yyval = novoNoExp(E_Id); yyval->atrib.op = MAIS;}
#line 1717 "parse.tab.c"
    break;

  case 55: /* soma: MENOS  */
#line 287 "parse.y"
                    {yyval = novoNoExp(E_Id); yyval->atrib.op = MENOS;}
#line 1723 "parse.tab.c"
    break;

  case 56: /* termo: termo mult fator  */
#line 291 "parse.y"
                { yyval = novoNoExp(E_Op);
                  yyval->filho[0] = yyvsp[-2];
                  yyval->filho[1] = yyvsp[0];
                  yyval->atrib.op = yyvsp[-1]->atrib.op; // Token recebido pelo "mult"
                }
#line 1733 "parse.tab.c"
    break;

  case 57: /* termo: fator  */
#line 296 "parse.y"
                    {yyval = yyvsp[0];}
#line 1739 "parse.tab.c"
    break;

  case 58: /* mult: VEZES  */
#line 298 "parse.y"
                    {yyval = novoNoExp(E_Id); yyval->atrib.op = VEZES;}
#line 1745 "parse.tab.c"
    break;

  case 59: /* mult: DIV  */
#line 299 "parse.y"
                  {yyval = novoNoExp(E_Id); yyval->atrib.op = DIV;}
#line 1751 "parse.tab.c"
    break;

  case 60: /* fator: ABREPAR exp FECHAPAR  */
#line 301 "parse.y"
                                   {yyval = yyvsp[-2];}
#line 1757 "parse.tab.c"
    break;

  case 61: /* fator: var  */
#line 302 "parse.y"
                  {yyval = yyvsp[0];}
#line 1763 "parse.tab.c"
    break;

  case 62: /* fator: ativacao  */
#line 303 "parse.y"
                       {yyval = yyvsp[0];}
#line 1769 "parse.tab.c"
    break;

  case 63: /* fator: NUM  */
#line 304 "parse.y"
                  { yyval = novoNoExp(E_Num);
                    yyval->atrib.val = atoi(NUM_val);
                    yyval->tipo_c = Integer;
                  }
#line 1778 "parse.tab.c"
    break;

  case 64: /* $@6: %empty  */
#line 309 "parse.y"
                 { nomeFunc = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                 }
#line 1786 "parse.tab.c"
    break;

  case 65: /* ativacao: ID $@6 ABREPAR args FECHAPAR  */
#line 313 "parse.y"
                 { yyval = novoNoStmt(S_Chamada);
                   yyval->filho[1] = yyvsp[-1]; // filho direito
                   yyval->atrib.nome = nomeFunc;
                   yyval->numlinha = numLinhaSalva;
                 }
#line 1796 "parse.tab.c"
    break;

  case 66: /* args: arg_lista  */
#line 319 "parse.y"
                        {yyval = yyvsp[0];}
#line 1802 "parse.tab.c"
    break;

  case 67: /* args: %empty  */
#line 320 "parse.y"
                      { 
                        //$$ = novoNoExp(E_Id);
                        //$$-> atrib.nome = "sem_args";
                        yyval = NULL;
                    }
#line 1812 "parse.tab.c"
    break;

  case 68: /* arg_lista: arg_lista VIRG exp  */
#line 326 "parse.y"
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
#line 1829 "parse.tab.c"
    break;

  case 69: /* arg_lista: param  */
#line 338 "parse.y"
                    {yyval = yyvsp[0];}
#line 1835 "parse.tab.c"
    break;

  case 70: /* arg_lista: exp  */
#line 339 "parse.y"
                  {yyval = yyvsp[0];}
#line 1841 "parse.tab.c"
    break;


#line 1845 "parse.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 341 "parse.y"


int yyerror(char * message){
    if(yychar == ID || yychar == NUM){
        fprintf(stdout,"Erro Sintático %s  na linha: %d\n", nome_token(yychar), numlinha);
    }else{
        fprintf(stdout,"Erro Sintático %s (%s)  na linha: %d\n", nome_token(yychar), yytext, numlinha);
    }
    Erro = true;
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

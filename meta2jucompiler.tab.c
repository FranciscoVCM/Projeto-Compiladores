/* A Bison parser, made by GNU Bison 3.8.2.  */

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
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "meta2jucompiler.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex();
extern int line, column;
extern int token_line, token_column;
extern char token_text[];
extern int last_lex_error_line;
extern int print_tokens;
extern int yychar;

void yyerror(char *s);

struct node *ast = NULL;

int print_tree = 0;
int only_errors = 0;
int syntax_errors = 0;
int syntax_error_count = 0;

int last_syntax_error_line = 0;
int last_syntax_error_col = 0;
char last_syntax_error_text[10000] = "";

static struct node *make_list(void) {
    return newnode(Program, NULL);
}

static void append_children(struct node *dst, struct node *src) {
    if (!dst || !src || !src->children)
        return;

    struct node_list *child = src->children->next;
    while (child) {
        addchild(dst, child->node);
        child = child->next;
    }

    src->children->next = NULL;
}

static void free_list_only(struct node *n) {
    if (!n)
        return;

    if (n->children)
        free(n->children);

    if (n->token)
        free(n->token);

    free(n);
}

static struct node *clone_type(struct node *n) {
    if (!n)
        return NULL;

    return newnode(n->category, n->token);
}

static int child_count(struct node *n) {
    int count = 0;

    if (!n || !n->children)
        return 0;

    struct node_list *child = n->children->next;
    while (child) {
        count++;
        child = child->next;
    }

    return count;
}

static int is_empty_block(struct node *n) {
    return n && n->category == Block && child_count(n) == 0;
}

static int meaningful_count(struct node *list) {
    int count = 0;

    if (!list || !list->children)
        return 0;

    struct node_list *child = list->children->next;
    while (child) {
        if (!is_empty_block(child->node))
            count++;
        child = child->next;
    }

    return count;
}

static struct node *first_meaningful(struct node *list) {
    if (!list || !list->children)
        return NULL;

    struct node_list *child = list->children->next;
    while (child) {
        if (!is_empty_block(child->node))
            return child->node;
        child = child->next;
    }

    return NULL;
}

static struct node *build_block(struct node *list) {
    int n = meaningful_count(list);

    if (n == 0) {
        free_list_only(list);
        return newnode(Block, NULL);
    }

    if (n == 1) {
        struct node *single = first_meaningful(list);
        list->children->next = NULL;
        free_list_only(list);
        return single;
    }

    struct node *block = newnode(Block, NULL);

    struct node_list *child = list->children->next;
    while (child) {
        if (!is_empty_block(child->node))
            addchild(block, child->node);
        child = child->next;
    }

    list->children->next = NULL;
    free_list_only(list);
    return block;
}

void yyerror(char *s) {
    int err_line = token_line;
    int err_col = token_column;
    const char *err_text = token_text;

    syntax_errors = 1;

    if (token_line == last_lex_error_line)
        return;

    if (yychar == 0) {
        err_line = line;
        err_col = column;
        err_text = "";

        if (syntax_error_count > 0)
            return;
    }

    if (err_line == last_syntax_error_line &&
        err_col == last_syntax_error_col &&
        strcmp(err_text, last_syntax_error_text) == 0) {
        return;
    }

    printf("Line %d, col %d: syntax error: %s\n", err_line, err_col, err_text);
    syntax_error_count++;

    last_syntax_error_line = err_line;
    last_syntax_error_col = err_col;
    strncpy(last_syntax_error_text, err_text, sizeof(last_syntax_error_text) - 1);
    last_syntax_error_text[sizeof(last_syntax_error_text) - 1] = '\0';
}


#line 249 "meta2jucompiler.tab.c"

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

#include "meta2jucompiler.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_NATURAL = 4,                    /* NATURAL  */
  YYSYMBOL_DECIMAL = 5,                    /* DECIMAL  */
  YYSYMBOL_STRLIT = 6,                     /* STRLIT  */
  YYSYMBOL_BOOLLIT = 7,                    /* BOOLLIT  */
  YYSYMBOL_CLASS = 8,                      /* CLASS  */
  YYSYMBOL_PUBLIC = 9,                     /* PUBLIC  */
  YYSYMBOL_STATIC = 10,                    /* STATIC  */
  YYSYMBOL_RESERVED = 11,                  /* RESERVED  */
  YYSYMBOL_BOOL = 12,                      /* BOOL  */
  YYSYMBOL_INT = 13,                       /* INT  */
  YYSYMBOL_DOUBLE = 14,                    /* DOUBLE  */
  YYSYMBOL_VOID = 15,                      /* VOID  */
  YYSYMBOL_STRING = 16,                    /* STRING  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_ELSE = 18,                      /* ELSE  */
  YYSYMBOL_WHILE = 19,                     /* WHILE  */
  YYSYMBOL_RETURN = 20,                    /* RETURN  */
  YYSYMBOL_PRINT = 21,                     /* PRINT  */
  YYSYMBOL_PARSEINT = 22,                  /* PARSEINT  */
  YYSYMBOL_DOTLENGTH = 23,                 /* DOTLENGTH  */
  YYSYMBOL_INC = 24,                       /* INC  */
  YYSYMBOL_DEC = 25,                       /* DEC  */
  YYSYMBOL_ARROW = 26,                     /* ARROW  */
  YYSYMBOL_ASSIGN = 27,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 28,                      /* PLUS  */
  YYSYMBOL_MINUS = 29,                     /* MINUS  */
  YYSYMBOL_STAR = 30,                      /* STAR  */
  YYSYMBOL_DIV = 31,                       /* DIV  */
  YYSYMBOL_MOD = 32,                       /* MOD  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_OR = 34,                        /* OR  */
  YYSYMBOL_XOR = 35,                       /* XOR  */
  YYSYMBOL_LSHIFT = 36,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 37,                    /* RSHIFT  */
  YYSYMBOL_EQ = 38,                        /* EQ  */
  YYSYMBOL_NE = 39,                        /* NE  */
  YYSYMBOL_LT = 40,                        /* LT  */
  YYSYMBOL_GT = 41,                        /* GT  */
  YYSYMBOL_LE = 42,                        /* LE  */
  YYSYMBOL_GE = 43,                        /* GE  */
  YYSYMBOL_NOT = 44,                       /* NOT  */
  YYSYMBOL_LPAR = 45,                      /* LPAR  */
  YYSYMBOL_RPAR = 46,                      /* RPAR  */
  YYSYMBOL_LBRACE = 47,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 48,                    /* RBRACE  */
  YYSYMBOL_LSQ = 49,                       /* LSQ  */
  YYSYMBOL_RSQ = 50,                       /* RSQ  */
  YYSYMBOL_SEMICOLON = 51,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 52,                     /* COMMA  */
  YYSYMBOL_UPLUS = 53,                     /* UPLUS  */
  YYSYMBOL_UMINUS = 54,                    /* UMINUS  */
  YYSYMBOL_LOWER_THAN_ELSE = 55,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_program = 57,                   /* program  */
  YYSYMBOL_class_body = 58,                /* class_body  */
  YYSYMBOL_class_member = 59,              /* class_member  */
  YYSYMBOL_field_decl = 60,                /* field_decl  */
  YYSYMBOL_field_ids = 61,                 /* field_ids  */
  YYSYMBOL_method_decl = 62,               /* method_decl  */
  YYSYMBOL_method_header = 63,             /* method_header  */
  YYSYMBOL_formal_params = 64,             /* formal_params  */
  YYSYMBOL_formal_param = 65,              /* formal_param  */
  YYSYMBOL_method_body = 66,               /* method_body  */
  YYSYMBOL_method_body_items = 67,         /* method_body_items  */
  YYSYMBOL_var_decl = 68,                  /* var_decl  */
  YYSYMBOL_var_ids = 69,                   /* var_ids  */
  YYSYMBOL_stmt = 70,                      /* stmt  */
  YYSYMBOL_stmt_list = 71,                 /* stmt_list  */
  YYSYMBOL_expr = 72,                      /* expr  */
  YYSYMBOL_assignment_expr = 73,           /* assignment_expr  */
  YYSYMBOL_or_expr = 74,                   /* or_expr  */
  YYSYMBOL_and_expr = 75,                  /* and_expr  */
  YYSYMBOL_xor_expr = 76,                  /* xor_expr  */
  YYSYMBOL_equality_expr = 77,             /* equality_expr  */
  YYSYMBOL_relational_expr = 78,           /* relational_expr  */
  YYSYMBOL_shift_expr = 79,                /* shift_expr  */
  YYSYMBOL_additive_expr = 80,             /* additive_expr  */
  YYSYMBOL_multiplicative_expr = 81,       /* multiplicative_expr  */
  YYSYMBOL_unary_expr = 82,                /* unary_expr  */
  YYSYMBOL_primary_expr = 83,              /* primary_expr  */
  YYSYMBOL_method_invocation = 84,         /* method_invocation  */
  YYSYMBOL_args_opt = 85,                  /* args_opt  */
  YYSYMBOL_expr_list = 86,                 /* expr_list  */
  YYSYMBOL_parse_args = 87,                /* parse_args  */
  YYSYMBOL_type = 88                       /* type  */
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
typedef yytype_uint8 yy_state_t;

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

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   351

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  214

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   310


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   225,   225,   235,   238,   252,   255,   258,   261,   268,
     283,   290,   294,   301,   306,   315,   321,   327,   333,   342,
     346,   355,   364,   371,   379,   387,   390,   395,   403,   418,
     422,   429,   433,   440,   443,   449,   455,   462,   469,   476,
     483,   488,   494,   500,   504,   507,   511,   514,   519,   524,
     528,   531,   535,   539,   543,   547,   550,   557,   560,   568,
     574,   579,   585,   590,   596,   601,   607,   612,   618,   623,
     628,   634,   639,   644,   649,   654,   660,   665,   670,   676,
     681,   686,   692,   697,   702,   707,   713,   717,   721,   725,
     731,   734,   738,   741,   744,   747,   750,   753,   756,   763,
     769,   777,   780,   786,   790,   794,   801,   806,   813,   816,
     819
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
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "NATURAL", "DECIMAL", "STRLIT", "BOOLLIT", "CLASS", "PUBLIC", "STATIC",
  "RESERVED", "BOOL", "INT", "DOUBLE", "VOID", "STRING", "IF", "ELSE",
  "WHILE", "RETURN", "PRINT", "PARSEINT", "DOTLENGTH", "INC", "DEC",
  "ARROW", "ASSIGN", "PLUS", "MINUS", "STAR", "DIV", "MOD", "AND", "OR",
  "XOR", "LSHIFT", "RSHIFT", "EQ", "NE", "LT", "GT", "LE", "GE", "NOT",
  "LPAR", "RPAR", "LBRACE", "RBRACE", "LSQ", "RSQ", "SEMICOLON", "COMMA",
  "UPLUS", "UMINUS", "LOWER_THAN_ELSE", "$accept", "program", "class_body",
  "class_member", "field_decl", "field_ids", "method_decl",
  "method_header", "formal_params", "formal_param", "method_body",
  "method_body_items", "var_decl", "var_ids", "stmt", "stmt_list", "expr",
  "assignment_expr", "or_expr", "and_expr", "xor_expr", "equality_expr",
  "relational_expr", "shift_expr", "additive_expr", "multiplicative_expr",
  "unary_expr", "primary_expr", "method_invocation", "args_opt",
  "expr_list", "parse_args", "type", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-90)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-102)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      28,    77,    52,    12,   -90,   -90,     9,    44,    93,   -90,
     -90,   -90,   -90,   -90,   -90,    86,    54,   -90,   -90,   -90,
     104,     8,   109,   -90,    76,    98,   -90,   -90,   108,    39,
      80,   -90,    20,    97,   -90,   156,   118,   -90,    33,   -90,
     168,   122,     0,   178,   144,   151,    21,   157,   158,   -90,
     -90,   -90,   -90,   -90,     7,   153,    45,   -90,    56,   -90,
      34,   -90,    49,   -90,   -90,   214,   165,   154,   223,   228,
     155,    24,   -90,   -90,   -90,   286,   286,   286,   259,   -90,
     161,   -90,   173,   175,   179,   -19,   105,    79,   100,   125,
     -90,   -90,   -90,   -90,   194,    85,   103,   -90,   -90,   -90,
     162,   -90,     2,   -90,   170,   222,   -90,   183,   186,   195,
     -90,   198,   188,   -90,   200,    10,   201,    43,   -90,   -90,
     306,   -10,   -90,   -90,   -90,   202,   203,   -90,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   207,   208,   209,   215,   216,   -90,
     -90,   -90,   -90,   -90,   266,   267,   -90,   -90,   -90,   -90,
     -90,   273,   141,   141,   141,   141,   141,   141,   -90,   -90,
     -90,   175,   179,   -19,   105,   105,    79,    79,    79,    79,
     100,   100,   125,   125,   -90,   -90,   -90,   220,   224,   231,
     -90,   306,   -90,   -90,   -90,   -90,   261,   265,   268,   -90,
     -90,   -90,   -90,   -90,   -90,   234,   141,   141,   141,   239,
     -90,   -90,   -90,   -90
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     0,     0,     2,
       7,     4,     5,     6,     8,     0,     0,   108,   109,   110,
       0,     0,     0,    10,     0,     0,    25,    13,    11,     0,
       0,    14,     0,     0,     9,     0,     0,    17,     0,    19,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    57,
      24,    55,    26,    27,     0,     0,     0,    15,     0,    12,
       0,    18,     0,    23,    56,     0,     0,     0,     0,     0,
       0,    90,    92,    93,    94,     0,     0,     0,     0,    44,
       0,    59,    61,    63,    65,    67,    70,    75,    78,    81,
      85,    89,    95,    96,     0,     0,     0,    47,    46,    50,
       0,    31,     0,    16,     0,     0,    22,     0,     0,     0,
     103,     0,   102,    54,     0,     0,     0,     0,    45,    91,
       0,    90,    88,    87,    86,     0,     0,    43,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
      58,    30,    29,    28,     0,     0,    20,    49,    48,   100,
      99,     0,     0,     0,     0,     0,     0,     0,    60,    98,
      97,    62,    64,    66,    68,    69,    71,    72,    73,    74,
      76,    77,    79,    80,    82,    83,    84,     0,     0,     0,
     107,     0,    32,    21,   105,   104,    36,    38,    34,    41,
      42,    40,    53,    52,    51,     0,     0,     0,     0,     0,
      37,    39,    35,   106
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   263,   230,
     -90,   -90,   -90,   -90,   -89,   -90,   -64,   174,   -90,   169,
     171,   176,    46,    50,    27,    51,   -60,   -90,   -32,   -90,
     -90,   -26,    -3
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     6,    11,    12,    29,    13,    21,    38,    39,
      27,    32,    52,   102,    53,    96,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,   111,
     112,    93,    40
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      54,   108,   110,   152,   115,   117,    55,   150,    97,    25,
       7,   163,    22,   119,   126,   122,   123,   124,     8,   131,
     132,    41,    70,    42,    71,    72,    73,    65,    74,    56,
     146,    43,    17,    18,    19,    66,     1,    44,   104,    45,
      46,    47,    48,    48,   166,    66,   100,   119,   101,    75,
      76,   120,     4,   153,   154,    26,   164,     9,    98,     5,
      10,    17,    18,    19,    54,    77,    78,    49,    50,    66,
      55,    51,    79,   196,   197,   198,   199,   200,   201,    61,
       3,   184,   185,   186,   105,    62,   147,    16,   148,   167,
      34,    35,    17,    18,    19,    14,    36,   195,    17,    18,
      19,    20,   103,    15,    41,    23,    42,    24,    62,    17,
      18,    19,    28,    36,    43,   137,   138,   210,   211,   212,
      44,    30,    45,    46,    47,    48,    37,   205,   139,   140,
      54,    54,    54,    54,    54,    54,    55,    55,    55,    55,
      55,    55,    41,    57,    42,   133,   134,   135,   136,    31,
      49,   149,    43,    33,    51,   141,   142,   143,    44,    59,
      45,    46,    47,    48,   180,   181,   109,    60,    71,    72,
      73,    63,    74,    64,    54,    54,    54,   174,   175,    67,
      55,    55,    55,   176,   177,   178,   179,    48,    49,    68,
     182,   183,    51,    75,    76,   144,    69,    71,    72,    73,
     145,    74,    94,    95,    99,   113,   118,   128,   129,    77,
      78,  -101,   127,   151,   130,   107,    48,    71,    72,    73,
     155,    74,    75,    76,   114,   156,    71,    72,    73,   116,
      74,    71,    72,    73,   157,    74,    48,   158,    77,    78,
     161,   159,    75,    76,   160,    48,   162,   165,   169,   170,
      48,    75,    76,   187,   188,   189,    75,    76,    77,    78,
     125,   190,    71,    72,    73,   191,    74,    77,    78,   192,
     193,   202,    77,    78,   194,   203,    71,    72,    73,   206,
      74,    48,   204,   207,   209,   213,   208,    75,    76,   121,
      72,    73,   106,    74,   168,    48,    58,   171,     0,     0,
     172,    75,    76,    77,    78,     0,   173,     0,    48,    71,
      72,    73,     0,    74,    75,    76,     0,    77,    78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,     0,
      77,    78,     0,     0,    75,    76,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      77,    78
};

static const yytype_int16 yycheck[] =
{
      32,    65,    66,     1,    68,    69,    32,    96,     1,     1,
       1,     1,    15,    23,    78,    75,    76,    77,     9,    38,
      39,     1,     1,     3,     3,     4,     5,    27,     7,    32,
      94,    11,    12,    13,    14,    45,     8,    17,     4,    19,
      20,    21,    22,    22,     1,    45,     1,    23,     3,    28,
      29,    27,     0,    51,    52,    47,    46,    48,    51,    47,
      51,    12,    13,    14,    96,    44,    45,    47,    48,    45,
      96,    51,    51,   162,   163,   164,   165,   166,   167,    46,
       3,   141,   142,   143,    50,    52,     1,     1,     3,    46,
      51,    52,    12,    13,    14,    51,    16,   161,    12,    13,
      14,    15,    46,    10,     1,    51,     3,     3,    52,    12,
      13,    14,     3,    16,    11,    36,    37,   206,   207,   208,
      17,    45,    19,    20,    21,    22,    46,   191,    28,    29,
     162,   163,   164,   165,   166,   167,   162,   163,   164,   165,
     166,   167,     1,    46,     3,    40,    41,    42,    43,    51,
      47,    48,    11,    45,    51,    30,    31,    32,    17,     3,
      19,    20,    21,    22,   137,   138,     1,    49,     3,     4,
       5,     3,     7,    51,   206,   207,   208,   131,   132,     1,
     206,   207,   208,   133,   134,   135,   136,    22,    47,    45,
     139,   140,    51,    28,    29,     1,    45,     3,     4,     5,
       6,     7,    45,    45,    51,    51,    51,    34,    33,    44,
      45,    46,    51,    51,    35,     1,    22,     3,     4,     5,
      50,     7,    28,    29,     1,     3,     3,     4,     5,     1,
       7,     3,     4,     5,    51,     7,    22,    51,    44,    45,
      52,    46,    28,    29,    46,    22,    46,    46,    46,    46,
      22,    28,    29,    46,    46,    46,    28,    29,    44,    45,
       1,    46,     3,     4,     5,    49,     7,    44,    45,     3,
       3,    51,    44,    45,     1,    51,     3,     4,     5,    18,
       7,    22,    51,    18,    50,    46,    18,    28,    29,     3,
       4,     5,    62,     7,   120,    22,    33,   128,    -1,    -1,
     129,    28,    29,    44,    45,    -1,   130,    -1,    22,     3,
       4,     5,    -1,     7,    28,    29,    -1,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    -1,
      44,    45,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    57,     3,     0,    47,    58,     1,     9,    48,
      51,    59,    60,    62,    51,    10,     1,    12,    13,    14,
      15,    63,    88,    51,     3,     1,    47,    66,     3,    61,
      45,    51,    67,    45,    51,    52,    16,    46,    64,    65,
      88,     1,     3,    11,    17,    19,    20,    21,    22,    47,
      48,    51,    68,    70,    84,    87,    88,    46,    64,     3,
      49,    46,    52,     3,    51,    27,    45,     1,    45,    45,
       1,     3,     4,     5,     7,    28,    29,    44,    45,    51,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    87,    45,    45,    71,     1,    51,    51,
       1,     3,    69,    46,     4,    50,    65,     1,    72,     1,
      72,    85,    86,    51,     1,    72,     1,    72,    51,    23,
      27,     3,    82,    82,    82,     1,    72,    51,    34,    33,
      35,    38,    39,    40,    41,    42,    43,    36,    37,    28,
      29,    30,    31,    32,     1,     6,    72,     1,     3,    48,
      70,    51,     1,    51,    52,    50,     3,    51,    51,    46,
      46,    52,    46,     1,    46,    46,     1,    46,    73,    46,
      46,    75,    76,    77,    78,    78,    79,    79,    79,    79,
      80,    80,    81,    81,    82,    82,    82,    46,    46,    46,
      46,    49,     3,     3,     1,    72,    70,    70,    70,    70,
      70,    70,    51,    51,    51,    72,    18,    18,    18,    50,
      70,    70,    70,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    59,    59,    60,
      60,    61,    61,    62,    62,    63,    63,    63,    63,    64,
      64,    64,    64,    65,    66,    67,    67,    67,    68,    68,
      68,    69,    69,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    71,    71,    72,
      73,    73,    74,    74,    75,    75,    76,    76,    77,    77,
      77,    78,    78,    78,    78,    78,    79,    79,    79,    80,
      80,    80,    81,    81,    81,    81,    82,    82,    82,    82,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    84,
      84,    85,    85,    86,    86,    86,    87,    87,    88,    88,
      88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     0,     2,     1,     1,     1,     2,     5,
       4,     1,     3,     4,     5,     4,     5,     4,     5,     1,
       4,     5,     3,     2,     3,     0,     2,     2,     3,     3,
       3,     1,     3,     3,     5,     7,     5,     7,     5,     7,
       5,     5,     5,     3,     2,     3,     2,     2,     4,     4,
       2,     5,     5,     5,     3,     1,     2,     0,     2,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     2,     2,     2,     1,
       1,     2,     1,     1,     1,     1,     1,     3,     3,     4,
       4,     0,     1,     1,     3,     3,     7,     4,     1,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
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
  case 2: /* program: CLASS IDENTIFIER LBRACE class_body RBRACE  */
#line 225 "meta2jucompiler.y"
                                              {
        (yyval.node) = newnode(Program, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        append_children((yyval.node), (yyvsp[-1].node));
        free_list_only((yyvsp[-1].node));
        ast = (yyval.node);
    }
#line 1507 "meta2jucompiler.tab.c"
    break;

  case 3: /* class_body: %empty  */
#line 235 "meta2jucompiler.y"
    {
        (yyval.node) = make_list();
    }
#line 1515 "meta2jucompiler.tab.c"
    break;

  case 4: /* class_body: class_body class_member  */
#line 238 "meta2jucompiler.y"
                            {
        if ((yyvsp[0].node)) {
            if ((yyvsp[0].node)->category == Program) {
                append_children((yyvsp[-1].node), (yyvsp[0].node));
                free_list_only((yyvsp[0].node));
            } else {
                addchild((yyvsp[-1].node), (yyvsp[0].node));
            }
        }
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1531 "meta2jucompiler.tab.c"
    break;

  case 5: /* class_member: field_decl  */
#line 252 "meta2jucompiler.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1539 "meta2jucompiler.tab.c"
    break;

  case 6: /* class_member: method_decl  */
#line 255 "meta2jucompiler.y"
                {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1547 "meta2jucompiler.tab.c"
    break;

  case 7: /* class_member: SEMICOLON  */
#line 258 "meta2jucompiler.y"
              {
        (yyval.node) = NULL;
    }
#line 1555 "meta2jucompiler.tab.c"
    break;

  case 8: /* class_member: error SEMICOLON  */
#line 261 "meta2jucompiler.y"
                    {
        yyerrok;
        (yyval.node) = NULL;
    }
#line 1564 "meta2jucompiler.tab.c"
    break;

  case 9: /* field_decl: PUBLIC STATIC type field_ids SEMICOLON  */
#line 268 "meta2jucompiler.y"
                                           {
        (yyval.node) = make_list();

        struct node_list *child = (yyvsp[-1].node)->children->next;
        while (child) {
            struct node *decl = newnode(FieldDecl, NULL);
            addchild(decl, clone_type((yyvsp[-2].node)));
            addchild(decl, newnode(Identifier, child->node->token));
            addchild((yyval.node), decl);
            child = child->next;
        }

        free_ast((yyvsp[-2].node));
        free_ast((yyvsp[-1].node));
    }
#line 1584 "meta2jucompiler.tab.c"
    break;

  case 10: /* field_decl: PUBLIC STATIC error SEMICOLON  */
#line 283 "meta2jucompiler.y"
                                  {
        yyerrok;
        (yyval.node) = make_list();
    }
#line 1593 "meta2jucompiler.tab.c"
    break;

  case 11: /* field_ids: IDENTIFIER  */
#line 290 "meta2jucompiler.y"
               {
        (yyval.node) = make_list();
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1602 "meta2jucompiler.tab.c"
    break;

  case 12: /* field_ids: field_ids COMMA IDENTIFIER  */
#line 294 "meta2jucompiler.y"
                               {
        addchild((yyvsp[-2].node), newnode(Identifier, (yyvsp[0].lexeme)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1611 "meta2jucompiler.tab.c"
    break;

  case 13: /* method_decl: PUBLIC STATIC method_header method_body  */
#line 301 "meta2jucompiler.y"
                                            {
        (yyval.node) = newnode(MethodDecl, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1621 "meta2jucompiler.tab.c"
    break;

  case 14: /* method_decl: PUBLIC STATIC method_header error SEMICOLON  */
#line 306 "meta2jucompiler.y"
                                                {
        yyerrok;
        (yyval.node) = newnode(MethodDecl, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), newnode(MethodBody, NULL));
    }
#line 1632 "meta2jucompiler.tab.c"
    break;

  case 15: /* method_header: type IDENTIFIER LPAR RPAR  */
#line 315 "meta2jucompiler.y"
                              {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), (yyvsp[-3].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), newnode(MethodParams, NULL));
    }
#line 1643 "meta2jucompiler.tab.c"
    break;

  case 16: /* method_header: type IDENTIFIER LPAR formal_params RPAR  */
#line 321 "meta2jucompiler.y"
                                            {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1654 "meta2jucompiler.tab.c"
    break;

  case 17: /* method_header: VOID IDENTIFIER LPAR RPAR  */
#line 327 "meta2jucompiler.y"
                              {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), newnode(Void, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), newnode(MethodParams, NULL));
    }
#line 1665 "meta2jucompiler.tab.c"
    break;

  case 18: /* method_header: VOID IDENTIFIER LPAR formal_params RPAR  */
#line 333 "meta2jucompiler.y"
                                            {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), newnode(Void, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1676 "meta2jucompiler.tab.c"
    break;

  case 19: /* formal_params: formal_param  */
#line 342 "meta2jucompiler.y"
                 {
        (yyval.node) = newnode(MethodParams, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1685 "meta2jucompiler.tab.c"
    break;

  case 20: /* formal_params: STRING LSQ RSQ IDENTIFIER  */
#line 346 "meta2jucompiler.y"
                              {
        (yyval.node) = newnode(MethodParams, NULL);

        struct node *param = newnode(ParamDecl, NULL);
        addchild(param, newnode(StringArray, NULL));
        addchild(param, newnode(Identifier, (yyvsp[0].lexeme)));

        addchild((yyval.node), param);
    }
#line 1699 "meta2jucompiler.tab.c"
    break;

  case 21: /* formal_params: STRING LSQ NATURAL RSQ IDENTIFIER  */
#line 355 "meta2jucompiler.y"
                                      {
        (yyval.node) = newnode(MethodParams, NULL);

        struct node *param = newnode(ParamDecl, NULL);
        addchild(param, newnode(StringArray, NULL));
        addchild(param, newnode(Identifier, (yyvsp[0].lexeme)));

        addchild((yyval.node), param);
    }
#line 1713 "meta2jucompiler.tab.c"
    break;

  case 22: /* formal_params: formal_params COMMA formal_param  */
#line 364 "meta2jucompiler.y"
                                     {
        addchild((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1722 "meta2jucompiler.tab.c"
    break;

  case 23: /* formal_param: type IDENTIFIER  */
#line 371 "meta2jucompiler.y"
                    {
        (yyval.node) = newnode(ParamDecl, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1732 "meta2jucompiler.tab.c"
    break;

  case 24: /* method_body: LBRACE method_body_items RBRACE  */
#line 379 "meta2jucompiler.y"
                                    {
        (yyval.node) = newnode(MethodBody, NULL);
        append_children((yyval.node), (yyvsp[-1].node));
        free_list_only((yyvsp[-1].node));
    }
#line 1742 "meta2jucompiler.tab.c"
    break;

  case 25: /* method_body_items: %empty  */
#line 387 "meta2jucompiler.y"
    {
        (yyval.node) = make_list();
    }
#line 1750 "meta2jucompiler.tab.c"
    break;

  case 26: /* method_body_items: method_body_items var_decl  */
#line 390 "meta2jucompiler.y"
                               {
        append_children((yyvsp[-1].node), (yyvsp[0].node));
        free_list_only((yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1760 "meta2jucompiler.tab.c"
    break;

  case 27: /* method_body_items: method_body_items stmt  */
#line 395 "meta2jucompiler.y"
                           {
        if (!is_empty_block((yyvsp[0].node)))
            addchild((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1770 "meta2jucompiler.tab.c"
    break;

  case 28: /* var_decl: type var_ids SEMICOLON  */
#line 403 "meta2jucompiler.y"
                           {
        (yyval.node) = make_list();

        struct node_list *child = (yyvsp[-1].node)->children->next;
        while (child) {
            struct node *decl = newnode(VarDecl, NULL);
            addchild(decl, clone_type((yyvsp[-2].node)));
            addchild(decl, newnode(Identifier, child->node->token));
            addchild((yyval.node), decl);
            child = child->next;
        }

        free_ast((yyvsp[-2].node));
        free_ast((yyvsp[-1].node));
    }
#line 1790 "meta2jucompiler.tab.c"
    break;

  case 29: /* var_decl: type var_ids error  */
#line 418 "meta2jucompiler.y"
                       {
        yyerrok;
        (yyval.node) = make_list();
    }
#line 1799 "meta2jucompiler.tab.c"
    break;

  case 30: /* var_decl: type error SEMICOLON  */
#line 422 "meta2jucompiler.y"
                         {
        yyerrok;
        (yyval.node) = make_list();
    }
#line 1808 "meta2jucompiler.tab.c"
    break;

  case 31: /* var_ids: IDENTIFIER  */
#line 429 "meta2jucompiler.y"
               {
        (yyval.node) = make_list();
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1817 "meta2jucompiler.tab.c"
    break;

  case 32: /* var_ids: var_ids COMMA IDENTIFIER  */
#line 433 "meta2jucompiler.y"
                             {
        addchild((yyvsp[-2].node), newnode(Identifier, (yyvsp[0].lexeme)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1826 "meta2jucompiler.tab.c"
    break;

  case 33: /* stmt: LBRACE stmt_list RBRACE  */
#line 440 "meta2jucompiler.y"
                            {
        (yyval.node) = build_block((yyvsp[-1].node));
    }
#line 1834 "meta2jucompiler.tab.c"
    break;

  case 34: /* stmt: IF LPAR expr RPAR stmt  */
#line 443 "meta2jucompiler.y"
                                                 {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 1845 "meta2jucompiler.tab.c"
    break;

  case 35: /* stmt: IF LPAR expr RPAR stmt ELSE stmt  */
#line 449 "meta2jucompiler.y"
                                     {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1856 "meta2jucompiler.tab.c"
    break;

  case 36: /* stmt: IF LPAR error RPAR stmt  */
#line 455 "meta2jucompiler.y"
                                                  {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 1868 "meta2jucompiler.tab.c"
    break;

  case 37: /* stmt: IF LPAR error RPAR stmt ELSE stmt  */
#line 462 "meta2jucompiler.y"
                                      {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1880 "meta2jucompiler.tab.c"
    break;

  case 38: /* stmt: IF LPAR expr error stmt  */
#line 469 "meta2jucompiler.y"
                                                  {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 1892 "meta2jucompiler.tab.c"
    break;

  case 39: /* stmt: IF LPAR expr error stmt ELSE stmt  */
#line 476 "meta2jucompiler.y"
                                      {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1904 "meta2jucompiler.tab.c"
    break;

  case 40: /* stmt: WHILE LPAR expr RPAR stmt  */
#line 483 "meta2jucompiler.y"
                              {
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1914 "meta2jucompiler.tab.c"
    break;

  case 41: /* stmt: WHILE LPAR error RPAR stmt  */
#line 488 "meta2jucompiler.y"
                               {
        yyerrok;
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1925 "meta2jucompiler.tab.c"
    break;

  case 42: /* stmt: WHILE LPAR expr error stmt  */
#line 494 "meta2jucompiler.y"
                               {
        yyerrok;
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1936 "meta2jucompiler.tab.c"
    break;

  case 43: /* stmt: RETURN expr SEMICOLON  */
#line 500 "meta2jucompiler.y"
                          {
        (yyval.node) = newnode(Return, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1945 "meta2jucompiler.tab.c"
    break;

  case 44: /* stmt: RETURN SEMICOLON  */
#line 504 "meta2jucompiler.y"
                     {
        (yyval.node) = newnode(Return, NULL);
    }
#line 1953 "meta2jucompiler.tab.c"
    break;

  case 45: /* stmt: RETURN error SEMICOLON  */
#line 507 "meta2jucompiler.y"
                           {
        yyerrok;
        (yyval.node) = newnode(Return, NULL);
    }
#line 1962 "meta2jucompiler.tab.c"
    break;

  case 46: /* stmt: method_invocation SEMICOLON  */
#line 511 "meta2jucompiler.y"
                                {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1970 "meta2jucompiler.tab.c"
    break;

  case 47: /* stmt: method_invocation error  */
#line 514 "meta2jucompiler.y"
                            {
        yyerror("syntax error");
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 1980 "meta2jucompiler.tab.c"
    break;

  case 48: /* stmt: IDENTIFIER ASSIGN expr SEMICOLON  */
#line 519 "meta2jucompiler.y"
                                     {
        (yyval.node) = newnode(Assign, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1990 "meta2jucompiler.tab.c"
    break;

  case 49: /* stmt: IDENTIFIER ASSIGN error SEMICOLON  */
#line 524 "meta2jucompiler.y"
                                      {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 1999 "meta2jucompiler.tab.c"
    break;

  case 50: /* stmt: parse_args SEMICOLON  */
#line 528 "meta2jucompiler.y"
                         {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2007 "meta2jucompiler.tab.c"
    break;

  case 51: /* stmt: PRINT LPAR expr RPAR SEMICOLON  */
#line 531 "meta2jucompiler.y"
                                   {
        (yyval.node) = newnode(Print, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 2016 "meta2jucompiler.tab.c"
    break;

  case 52: /* stmt: PRINT LPAR STRLIT RPAR SEMICOLON  */
#line 535 "meta2jucompiler.y"
                                     {
        (yyval.node) = newnode(Print, NULL);
        addchild((yyval.node), newnode(StrLit, (yyvsp[-2].lexeme)));
    }
#line 2025 "meta2jucompiler.tab.c"
    break;

  case 53: /* stmt: PRINT LPAR error RPAR SEMICOLON  */
#line 539 "meta2jucompiler.y"
                                    {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2034 "meta2jucompiler.tab.c"
    break;

  case 54: /* stmt: RESERVED error SEMICOLON  */
#line 543 "meta2jucompiler.y"
                             {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2043 "meta2jucompiler.tab.c"
    break;

  case 55: /* stmt: SEMICOLON  */
#line 547 "meta2jucompiler.y"
              {
        (yyval.node) = newnode(Block, NULL);
    }
#line 2051 "meta2jucompiler.tab.c"
    break;

  case 56: /* stmt: error SEMICOLON  */
#line 550 "meta2jucompiler.y"
                    {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2060 "meta2jucompiler.tab.c"
    break;

  case 57: /* stmt_list: %empty  */
#line 557 "meta2jucompiler.y"
    {
        (yyval.node) = make_list();
    }
#line 2068 "meta2jucompiler.tab.c"
    break;

  case 58: /* stmt_list: stmt_list stmt  */
#line 560 "meta2jucompiler.y"
                   {
        if (!is_empty_block((yyvsp[0].node)))
            addchild((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2078 "meta2jucompiler.tab.c"
    break;

  case 59: /* expr: assignment_expr  */
#line 568 "meta2jucompiler.y"
                    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2086 "meta2jucompiler.tab.c"
    break;

  case 60: /* assignment_expr: IDENTIFIER ASSIGN assignment_expr  */
#line 574 "meta2jucompiler.y"
                                      {
        (yyval.node) = newnode(Assign, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2096 "meta2jucompiler.tab.c"
    break;

  case 61: /* assignment_expr: or_expr  */
#line 579 "meta2jucompiler.y"
            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2104 "meta2jucompiler.tab.c"
    break;

  case 62: /* or_expr: or_expr OR and_expr  */
#line 585 "meta2jucompiler.y"
                        {
        (yyval.node) = newnode(Or, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2114 "meta2jucompiler.tab.c"
    break;

  case 63: /* or_expr: and_expr  */
#line 590 "meta2jucompiler.y"
             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2122 "meta2jucompiler.tab.c"
    break;

  case 64: /* and_expr: and_expr AND xor_expr  */
#line 596 "meta2jucompiler.y"
                          {
        (yyval.node) = newnode(And, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2132 "meta2jucompiler.tab.c"
    break;

  case 65: /* and_expr: xor_expr  */
#line 601 "meta2jucompiler.y"
             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2140 "meta2jucompiler.tab.c"
    break;

  case 66: /* xor_expr: xor_expr XOR equality_expr  */
#line 607 "meta2jucompiler.y"
                               {
        (yyval.node) = newnode(Xor, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2150 "meta2jucompiler.tab.c"
    break;

  case 67: /* xor_expr: equality_expr  */
#line 612 "meta2jucompiler.y"
                  {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2158 "meta2jucompiler.tab.c"
    break;

  case 68: /* equality_expr: equality_expr EQ relational_expr  */
#line 618 "meta2jucompiler.y"
                                     {
        (yyval.node) = newnode(Eq, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2168 "meta2jucompiler.tab.c"
    break;

  case 69: /* equality_expr: equality_expr NE relational_expr  */
#line 623 "meta2jucompiler.y"
                                     {
        (yyval.node) = newnode(Ne, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2178 "meta2jucompiler.tab.c"
    break;

  case 70: /* equality_expr: relational_expr  */
#line 628 "meta2jucompiler.y"
                    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2186 "meta2jucompiler.tab.c"
    break;

  case 71: /* relational_expr: relational_expr LT shift_expr  */
#line 634 "meta2jucompiler.y"
                                  {
        (yyval.node) = newnode(Lt, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2196 "meta2jucompiler.tab.c"
    break;

  case 72: /* relational_expr: relational_expr GT shift_expr  */
#line 639 "meta2jucompiler.y"
                                  {
        (yyval.node) = newnode(Gt, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2206 "meta2jucompiler.tab.c"
    break;

  case 73: /* relational_expr: relational_expr LE shift_expr  */
#line 644 "meta2jucompiler.y"
                                  {
        (yyval.node) = newnode(Le, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2216 "meta2jucompiler.tab.c"
    break;

  case 74: /* relational_expr: relational_expr GE shift_expr  */
#line 649 "meta2jucompiler.y"
                                  {
        (yyval.node) = newnode(Ge, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2226 "meta2jucompiler.tab.c"
    break;

  case 75: /* relational_expr: shift_expr  */
#line 654 "meta2jucompiler.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2234 "meta2jucompiler.tab.c"
    break;

  case 76: /* shift_expr: shift_expr LSHIFT additive_expr  */
#line 660 "meta2jucompiler.y"
                                    {
        (yyval.node) = newnode(Lshift, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2244 "meta2jucompiler.tab.c"
    break;

  case 77: /* shift_expr: shift_expr RSHIFT additive_expr  */
#line 665 "meta2jucompiler.y"
                                    {
        (yyval.node) = newnode(Rshift, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2254 "meta2jucompiler.tab.c"
    break;

  case 78: /* shift_expr: additive_expr  */
#line 670 "meta2jucompiler.y"
                  {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2262 "meta2jucompiler.tab.c"
    break;

  case 79: /* additive_expr: additive_expr PLUS multiplicative_expr  */
#line 676 "meta2jucompiler.y"
                                           {
        (yyval.node) = newnode(Add, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2272 "meta2jucompiler.tab.c"
    break;

  case 80: /* additive_expr: additive_expr MINUS multiplicative_expr  */
#line 681 "meta2jucompiler.y"
                                            {
        (yyval.node) = newnode(Sub, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2282 "meta2jucompiler.tab.c"
    break;

  case 81: /* additive_expr: multiplicative_expr  */
#line 686 "meta2jucompiler.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2290 "meta2jucompiler.tab.c"
    break;

  case 82: /* multiplicative_expr: multiplicative_expr STAR unary_expr  */
#line 692 "meta2jucompiler.y"
                                        {
        (yyval.node) = newnode(Mul, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2300 "meta2jucompiler.tab.c"
    break;

  case 83: /* multiplicative_expr: multiplicative_expr DIV unary_expr  */
#line 697 "meta2jucompiler.y"
                                       {
        (yyval.node) = newnode(Div, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2310 "meta2jucompiler.tab.c"
    break;

  case 84: /* multiplicative_expr: multiplicative_expr MOD unary_expr  */
#line 702 "meta2jucompiler.y"
                                       {
        (yyval.node) = newnode(Mod, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2320 "meta2jucompiler.tab.c"
    break;

  case 85: /* multiplicative_expr: unary_expr  */
#line 707 "meta2jucompiler.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2328 "meta2jucompiler.tab.c"
    break;

  case 86: /* unary_expr: NOT unary_expr  */
#line 713 "meta2jucompiler.y"
                   {
        (yyval.node) = newnode(Not, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2337 "meta2jucompiler.tab.c"
    break;

  case 87: /* unary_expr: MINUS unary_expr  */
#line 717 "meta2jucompiler.y"
                                  {
        (yyval.node) = newnode(Minus, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2346 "meta2jucompiler.tab.c"
    break;

  case 88: /* unary_expr: PLUS unary_expr  */
#line 721 "meta2jucompiler.y"
                                {
        (yyval.node) = newnode(Plus, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2355 "meta2jucompiler.tab.c"
    break;

  case 89: /* unary_expr: primary_expr  */
#line 725 "meta2jucompiler.y"
                 {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2363 "meta2jucompiler.tab.c"
    break;

  case 90: /* primary_expr: IDENTIFIER  */
#line 731 "meta2jucompiler.y"
               {
        (yyval.node) = newnode(Identifier, (yyvsp[0].lexeme));
    }
#line 2371 "meta2jucompiler.tab.c"
    break;

  case 91: /* primary_expr: IDENTIFIER DOTLENGTH  */
#line 734 "meta2jucompiler.y"
                         {
        (yyval.node) = newnode(Length, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-1].lexeme)));
    }
#line 2380 "meta2jucompiler.tab.c"
    break;

  case 92: /* primary_expr: NATURAL  */
#line 738 "meta2jucompiler.y"
            {
        (yyval.node) = newnode(Natural, (yyvsp[0].lexeme));
    }
#line 2388 "meta2jucompiler.tab.c"
    break;

  case 93: /* primary_expr: DECIMAL  */
#line 741 "meta2jucompiler.y"
            {
        (yyval.node) = newnode(Decimal, (yyvsp[0].lexeme));
    }
#line 2396 "meta2jucompiler.tab.c"
    break;

  case 94: /* primary_expr: BOOLLIT  */
#line 744 "meta2jucompiler.y"
            {
        (yyval.node) = newnode(BoolLit, (yyvsp[0].lexeme));
    }
#line 2404 "meta2jucompiler.tab.c"
    break;

  case 95: /* primary_expr: method_invocation  */
#line 747 "meta2jucompiler.y"
                      {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2412 "meta2jucompiler.tab.c"
    break;

  case 96: /* primary_expr: parse_args  */
#line 750 "meta2jucompiler.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2420 "meta2jucompiler.tab.c"
    break;

  case 97: /* primary_expr: LPAR expr RPAR  */
#line 753 "meta2jucompiler.y"
                   {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2428 "meta2jucompiler.tab.c"
    break;

  case 98: /* primary_expr: LPAR error RPAR  */
#line 756 "meta2jucompiler.y"
                    {
        yyerrok;
        (yyval.node) = newnode(Natural, "0");
    }
#line 2437 "meta2jucompiler.tab.c"
    break;

  case 99: /* method_invocation: IDENTIFIER LPAR args_opt RPAR  */
#line 763 "meta2jucompiler.y"
                                  {
        (yyval.node) = newnode(Call, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        append_children((yyval.node), (yyvsp[-1].node));
        free_list_only((yyvsp[-1].node));
    }
#line 2448 "meta2jucompiler.tab.c"
    break;

  case 100: /* method_invocation: IDENTIFIER LPAR error RPAR  */
#line 769 "meta2jucompiler.y"
                               {
        yyerrok;
        (yyval.node) = newnode(Call, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
    }
#line 2458 "meta2jucompiler.tab.c"
    break;

  case 101: /* args_opt: %empty  */
#line 777 "meta2jucompiler.y"
    {
        (yyval.node) = make_list();
    }
#line 2466 "meta2jucompiler.tab.c"
    break;

  case 102: /* args_opt: expr_list  */
#line 780 "meta2jucompiler.y"
              {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2474 "meta2jucompiler.tab.c"
    break;

  case 103: /* expr_list: expr  */
#line 786 "meta2jucompiler.y"
         {
        (yyval.node) = make_list();
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2483 "meta2jucompiler.tab.c"
    break;

  case 104: /* expr_list: expr_list COMMA expr  */
#line 790 "meta2jucompiler.y"
                         {
        addchild((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2492 "meta2jucompiler.tab.c"
    break;

  case 105: /* expr_list: expr_list COMMA error  */
#line 794 "meta2jucompiler.y"
                          {
        yyerrok;
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2501 "meta2jucompiler.tab.c"
    break;

  case 106: /* parse_args: PARSEINT LPAR IDENTIFIER LSQ expr RSQ RPAR  */
#line 801 "meta2jucompiler.y"
                                               {
        (yyval.node) = newnode(ParseArgs, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-4].lexeme)));
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 2511 "meta2jucompiler.tab.c"
    break;

  case 107: /* parse_args: PARSEINT LPAR error RPAR  */
#line 806 "meta2jucompiler.y"
                             {
        yyerrok;
        (yyval.node) = newnode(ParseArgs, NULL);
    }
#line 2520 "meta2jucompiler.tab.c"
    break;

  case 108: /* type: BOOL  */
#line 813 "meta2jucompiler.y"
         {
        (yyval.node) = newnode(Bool, NULL);
    }
#line 2528 "meta2jucompiler.tab.c"
    break;

  case 109: /* type: INT  */
#line 816 "meta2jucompiler.y"
        {
        (yyval.node) = newnode(Int, NULL);
    }
#line 2536 "meta2jucompiler.tab.c"
    break;

  case 110: /* type: DOUBLE  */
#line 819 "meta2jucompiler.y"
           {
        (yyval.node) = newnode(Double, NULL);
    }
#line 2544 "meta2jucompiler.tab.c"
    break;


#line 2548 "meta2jucompiler.tab.c"

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
  ++yynerrs;

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
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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

#line 824 "meta2jucompiler.y"


int main(int argc, char **argv) {
    int lex_only = 0;

    if (argc > 1) {
        if (strcmp(argv[1], "-l") == 0) {
            lex_only = 1;
            print_tokens = 1;
        } else if (strcmp(argv[1], "-e1") == 0) {
            lex_only = 1;
        } else if (strcmp(argv[1], "-t") == 0) {
            print_tree = 1;
        } else if (strcmp(argv[1], "-e2") == 0) {
            only_errors = 1;
        }
    }

    if (lex_only) {
        while (yylex())
            ;
        return 0;
    }

    yyparse();

    if (!syntax_errors && print_tree && ast)
        print_ast(ast, 0);

    if (ast)
        free_ast(ast);

    return 0;
}

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
#line 1 "claudecompiler.y"

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


#line 249 "claudecompiler.tab.c"

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

#include "claudecompiler.tab.h"
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
#define YYLAST   303

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  205

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
     425,   429,   436,   439,   445,   451,   458,   465,   472,   479,
     484,   490,   494,   497,   501,   504,   509,   512,   516,   520,
     524,   527,   534,   537,   545,   551,   556,   562,   567,   573,
     578,   584,   589,   595,   600,   605,   611,   616,   621,   626,
     631,   637,   642,   647,   653,   658,   663,   669,   674,   679,
     684,   690,   694,   698,   702,   708,   711,   715,   718,   721,
     724,   727,   730,   733,   740,   746,   754,   757,   763,   767,
     771,   778,   783,   790,   793,   796
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

#define YYPACT_NINF (-88)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-97)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      32,    51,    65,    28,   -88,   -88,    34,    33,    76,   -88,
     -88,   -88,   -88,   -88,   -88,   181,    37,   -88,   -88,   -88,
      87,     8,    89,   -88,    53,    58,   -88,   -88,    59,   -40,
      47,   -88,     5,   173,   -88,   111,    92,   -88,    -5,   -88,
     132,    68,   -17,   104,   110,    29,   123,   133,   -88,   -88,
     -88,   -88,   -88,    95,   137,    36,   -88,    -2,   -88,    16,
     -88,    82,   -88,   -88,   253,   135,   155,   200,   139,    19,
     -88,   -88,   -88,   258,   258,   258,   205,   -88,   151,   -88,
     127,   185,   195,    10,   183,    85,   116,    70,   -88,   -88,
     -88,   -88,   147,    80,    86,   -88,   -88,   165,   -88,   122,
     -88,   187,   228,   -88,   196,   202,   -88,   206,   194,   207,
      30,   213,   218,   -88,   -88,   253,     0,   -88,   -88,   -88,
     220,   221,   -88,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   222,
     223,   224,   225,   227,   -88,   -88,   -88,   -88,   248,   269,
     -88,   -88,   -88,   -88,   210,    96,    96,    96,    96,    96,
     -88,   -88,   -88,   185,   195,    10,   183,   183,    85,    85,
      85,    85,   116,   116,    70,    70,   -88,   -88,   -88,   226,
     232,   233,   -88,   253,   -88,   -88,   -88,   -88,   255,   256,
     260,   -88,   -88,   -88,   -88,   -88,   229,    96,    96,    96,
     239,   -88,   -88,   -88,   -88
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     0,     0,     2,
       7,     4,     5,     6,     8,     0,     0,   103,   104,   105,
       0,     0,     0,    10,     0,     0,    25,    13,    11,     0,
       0,    14,     0,     0,     9,     0,     0,    17,     0,    19,
       0,     0,     0,     0,     0,     0,     0,     0,    52,    24,
      50,    26,    27,     0,     0,     0,    15,     0,    12,     0,
      18,     0,    23,    51,     0,     0,     0,     0,     0,    85,
      87,    88,    89,     0,     0,     0,     0,    42,     0,    54,
      56,    58,    60,    62,    65,    70,    73,    76,    80,    84,
      90,    91,     0,     0,     0,    44,    46,     0,    30,     0,
      16,     0,     0,    22,     0,     0,    98,     0,    97,     0,
       0,     0,     0,    43,    86,     0,    85,    83,    82,    81,
       0,     0,    41,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    32,    53,    29,    28,     0,     0,
      20,    45,    95,    94,     0,     0,     0,     0,     0,     0,
      55,    93,    92,    57,    59,    61,    63,    64,    66,    67,
      68,    69,    71,    72,    74,    75,    77,    78,    79,     0,
       0,     0,   102,     0,    31,    21,   100,    99,    35,    37,
      33,    40,    39,    49,    48,    47,     0,     0,     0,     0,
       0,    36,    38,    34,   101
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   257,   230,
     -88,   -88,   -88,   -88,   -87,   -88,   -63,   174,   -88,   169,
     164,   168,    71,   112,    88,   101,   -59,   -88,   -32,   -88,
     -88,   -27,     6
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     6,    11,    12,    29,    13,    21,    38,    39,
      27,    32,    51,    99,    52,    94,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,   107,
     108,    91,    40
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,   104,   106,   110,   112,    54,    41,   145,    42,    25,
      64,    34,    35,   121,   117,   118,   119,    17,    18,    19,
     101,    22,    43,   114,    44,    45,    46,    47,    65,   141,
      68,   156,    69,    70,    71,     7,    72,    97,    55,    98,
       1,    60,   114,     8,   100,    65,   115,    61,   126,   127,
      61,    47,    48,    49,     3,    26,    50,    73,    74,    17,
      18,    19,    53,    36,    65,     4,   102,    54,   188,   189,
     190,   191,   192,    75,    76,     5,   157,   176,   177,   178,
      77,   142,     9,   143,    14,    10,    15,    41,    23,    42,
      24,   187,    28,    37,    17,    18,    19,    41,    30,    42,
     136,   137,   138,    43,    33,    44,    45,    46,    47,    31,
     201,   202,   203,    43,    58,    44,    45,    46,    47,    63,
     196,   132,   133,    53,    53,    53,    53,    53,    54,    54,
      54,    54,    54,    48,   144,    62,   105,    50,    69,    70,
      71,    59,    72,    48,   134,   135,    95,    50,   139,    66,
      69,    70,    71,   140,    72,    67,   109,    47,    69,    70,
      71,   123,    72,    73,    74,    53,    53,    53,    92,    47,
      54,    54,    54,   147,   148,    73,    74,    47,    93,    75,
      76,   -96,    16,    73,    74,    17,    18,    19,    96,    36,
     113,    75,    76,    17,    18,    19,    20,   166,   167,    75,
      76,   111,   122,    69,    70,    71,   120,    72,    69,    70,
      71,   186,    72,    69,    70,    71,   146,    72,   124,    56,
     172,   173,    47,   128,   129,   130,   131,    47,    73,    74,
     125,   150,    47,    73,    74,   174,   175,   149,    73,    74,
     168,   169,   170,   171,    75,    76,   154,   151,   152,    75,
      76,   184,   153,   155,    75,    76,    69,    70,    71,   158,
      72,   116,    70,    71,   159,    72,   161,   162,   179,   180,
     181,   182,   185,   197,   198,    47,   183,   193,   199,   200,
      47,    73,    74,   194,   195,   204,    73,    74,   164,   160,
      57,   103,   163,   165,     0,     0,     0,    75,    76,     0,
       0,     0,    75,    76
};

static const yytype_int16 yycheck[] =
{
      32,    64,    65,    66,    67,    32,     1,    94,     3,     1,
      27,    51,    52,    76,    73,    74,    75,    12,    13,    14,
       4,    15,    17,    23,    19,    20,    21,    22,    45,    92,
       1,     1,     3,     4,     5,     1,     7,     1,    32,     3,
       8,    46,    23,     9,    46,    45,    27,    52,    38,    39,
      52,    22,    47,    48,     3,    47,    51,    28,    29,    12,
      13,    14,    94,    16,    45,     0,    50,    94,   155,   156,
     157,   158,   159,    44,    45,    47,    46,   136,   137,   138,
      51,     1,    48,     3,    51,    51,    10,     1,    51,     3,
       3,   154,     3,    46,    12,    13,    14,     1,    45,     3,
      30,    31,    32,    17,    45,    19,    20,    21,    22,    51,
     197,   198,   199,    17,     3,    19,    20,    21,    22,    51,
     183,    36,    37,   155,   156,   157,   158,   159,   155,   156,
     157,   158,   159,    47,    48,     3,     1,    51,     3,     4,
       5,    49,     7,    47,    28,    29,    51,    51,     1,    45,
       3,     4,     5,     6,     7,    45,     1,    22,     3,     4,
       5,    34,     7,    28,    29,   197,   198,   199,    45,    22,
     197,   198,   199,    51,    52,    28,    29,    22,    45,    44,
      45,    46,     1,    28,    29,    12,    13,    14,    51,    16,
      51,    44,    45,    12,    13,    14,    15,   126,   127,    44,
      45,     1,    51,     3,     4,     5,     1,     7,     3,     4,
       5,     1,     7,     3,     4,     5,    51,     7,    33,    46,
     132,   133,    22,    40,    41,    42,    43,    22,    28,    29,
      35,     3,    22,    28,    29,   134,   135,    50,    28,    29,
     128,   129,   130,   131,    44,    45,    52,    51,    46,    44,
      45,     3,    46,    46,    44,    45,     3,     4,     5,    46,
       7,     3,     4,     5,    46,     7,    46,    46,    46,    46,
      46,    46,     3,    18,    18,    22,    49,    51,    18,    50,
      22,    28,    29,    51,    51,    46,    28,    29,   124,   115,
      33,    61,   123,   125,    -1,    -1,    -1,    44,    45,    -1,
      -1,    -1,    44,    45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    57,     3,     0,    47,    58,     1,     9,    48,
      51,    59,    60,    62,    51,    10,     1,    12,    13,    14,
      15,    63,    88,    51,     3,     1,    47,    66,     3,    61,
      45,    51,    67,    45,    51,    52,    16,    46,    64,    65,
      88,     1,     3,    17,    19,    20,    21,    22,    47,    48,
      51,    68,    70,    84,    87,    88,    46,    64,     3,    49,
      46,    52,     3,    51,    27,    45,    45,    45,     1,     3,
       4,     5,     7,    28,    29,    44,    45,    51,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    87,    45,    45,    71,    51,    51,     1,     3,    69,
      46,     4,    50,    65,    72,     1,    72,    85,    86,     1,
      72,     1,    72,    51,    23,    27,     3,    82,    82,    82,
       1,    72,    51,    34,    33,    35,    38,    39,    40,    41,
      42,    43,    36,    37,    28,    29,    30,    31,    32,     1,
       6,    72,     1,     3,    48,    70,    51,    51,    52,    50,
       3,    51,    46,    46,    52,    46,     1,    46,    46,    46,
      73,    46,    46,    75,    76,    77,    78,    78,    79,    79,
      79,    79,    80,    80,    81,    81,    82,    82,    82,    46,
      46,    46,    46,    49,     3,     3,     1,    72,    70,    70,
      70,    70,    70,    51,    51,    51,    72,    18,    18,    18,
      50,    70,    70,    70,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    59,    59,    60,
      60,    61,    61,    62,    62,    63,    63,    63,    63,    64,
      64,    64,    64,    65,    66,    67,    67,    67,    68,    68,
      69,    69,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    71,    71,    72,    73,    73,    74,    74,    75,
      75,    76,    76,    77,    77,    77,    78,    78,    78,    78,
      78,    79,    79,    79,    80,    80,    80,    81,    81,    81,
      81,    82,    82,    82,    82,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    84,    84,    85,    85,    86,    86,
      86,    87,    87,    88,    88,    88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     0,     2,     1,     1,     1,     2,     5,
       4,     1,     3,     4,     5,     4,     5,     4,     5,     1,
       4,     5,     3,     2,     3,     0,     2,     2,     3,     3,
       1,     3,     3,     5,     7,     5,     7,     5,     7,     5,
       5,     3,     2,     3,     2,     4,     2,     5,     5,     5,
       1,     2,     0,     2,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     2,     2,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     3,     3,     4,     4,     0,     1,     1,     3,
       3,     7,     4,     1,     1,     1
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
#line 225 "claudecompiler.y"
                                              {
        (yyval.node) = newnode(Program, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        append_children((yyval.node), (yyvsp[-1].node));
        free_list_only((yyvsp[-1].node));
        ast = (yyval.node);
    }
#line 1491 "claudecompiler.tab.c"
    break;

  case 3: /* class_body: %empty  */
#line 235 "claudecompiler.y"
    {
        (yyval.node) = make_list();
    }
#line 1499 "claudecompiler.tab.c"
    break;

  case 4: /* class_body: class_body class_member  */
#line 238 "claudecompiler.y"
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
#line 1515 "claudecompiler.tab.c"
    break;

  case 5: /* class_member: field_decl  */
#line 252 "claudecompiler.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1523 "claudecompiler.tab.c"
    break;

  case 6: /* class_member: method_decl  */
#line 255 "claudecompiler.y"
                {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1531 "claudecompiler.tab.c"
    break;

  case 7: /* class_member: SEMICOLON  */
#line 258 "claudecompiler.y"
              {
        (yyval.node) = NULL;
    }
#line 1539 "claudecompiler.tab.c"
    break;

  case 8: /* class_member: error SEMICOLON  */
#line 261 "claudecompiler.y"
                    {
        yyerrok;
        (yyval.node) = NULL;
    }
#line 1548 "claudecompiler.tab.c"
    break;

  case 9: /* field_decl: PUBLIC STATIC type field_ids SEMICOLON  */
#line 268 "claudecompiler.y"
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
#line 1568 "claudecompiler.tab.c"
    break;

  case 10: /* field_decl: PUBLIC STATIC error SEMICOLON  */
#line 283 "claudecompiler.y"
                                  {
        yyerrok;
        (yyval.node) = make_list();
    }
#line 1577 "claudecompiler.tab.c"
    break;

  case 11: /* field_ids: IDENTIFIER  */
#line 290 "claudecompiler.y"
               {
        (yyval.node) = make_list();
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1586 "claudecompiler.tab.c"
    break;

  case 12: /* field_ids: field_ids COMMA IDENTIFIER  */
#line 294 "claudecompiler.y"
                               {
        addchild((yyvsp[-2].node), newnode(Identifier, (yyvsp[0].lexeme)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1595 "claudecompiler.tab.c"
    break;

  case 13: /* method_decl: PUBLIC STATIC method_header method_body  */
#line 301 "claudecompiler.y"
                                            {
        (yyval.node) = newnode(MethodDecl, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1605 "claudecompiler.tab.c"
    break;

  case 14: /* method_decl: PUBLIC STATIC method_header error SEMICOLON  */
#line 306 "claudecompiler.y"
                                                {
        yyerrok;
        (yyval.node) = newnode(MethodDecl, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), newnode(MethodBody, NULL));
    }
#line 1616 "claudecompiler.tab.c"
    break;

  case 15: /* method_header: type IDENTIFIER LPAR RPAR  */
#line 315 "claudecompiler.y"
                              {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), (yyvsp[-3].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), newnode(MethodParams, NULL));
    }
#line 1627 "claudecompiler.tab.c"
    break;

  case 16: /* method_header: type IDENTIFIER LPAR formal_params RPAR  */
#line 321 "claudecompiler.y"
                                            {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1638 "claudecompiler.tab.c"
    break;

  case 17: /* method_header: VOID IDENTIFIER LPAR RPAR  */
#line 327 "claudecompiler.y"
                              {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), newnode(Void, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), newnode(MethodParams, NULL));
    }
#line 1649 "claudecompiler.tab.c"
    break;

  case 18: /* method_header: VOID IDENTIFIER LPAR formal_params RPAR  */
#line 333 "claudecompiler.y"
                                            {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), newnode(Void, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1660 "claudecompiler.tab.c"
    break;

  case 19: /* formal_params: formal_param  */
#line 342 "claudecompiler.y"
                 {
        (yyval.node) = newnode(MethodParams, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1669 "claudecompiler.tab.c"
    break;

  case 20: /* formal_params: STRING LSQ RSQ IDENTIFIER  */
#line 346 "claudecompiler.y"
                              {
        (yyval.node) = newnode(MethodParams, NULL);

        struct node *param = newnode(ParamDecl, NULL);
        addchild(param, newnode(StringArray, NULL));
        addchild(param, newnode(Identifier, (yyvsp[0].lexeme)));

        addchild((yyval.node), param);
    }
#line 1683 "claudecompiler.tab.c"
    break;

  case 21: /* formal_params: STRING LSQ NATURAL RSQ IDENTIFIER  */
#line 355 "claudecompiler.y"
                                      {
        (yyval.node) = newnode(MethodParams, NULL);

        struct node *param = newnode(ParamDecl, NULL);
        addchild(param, newnode(StringArray, NULL));
        addchild(param, newnode(Identifier, (yyvsp[0].lexeme)));

        addchild((yyval.node), param);
    }
#line 1697 "claudecompiler.tab.c"
    break;

  case 22: /* formal_params: formal_params COMMA formal_param  */
#line 364 "claudecompiler.y"
                                     {
        addchild((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1706 "claudecompiler.tab.c"
    break;

  case 23: /* formal_param: type IDENTIFIER  */
#line 371 "claudecompiler.y"
                    {
        (yyval.node) = newnode(ParamDecl, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1716 "claudecompiler.tab.c"
    break;

  case 24: /* method_body: LBRACE method_body_items RBRACE  */
#line 379 "claudecompiler.y"
                                    {
        (yyval.node) = newnode(MethodBody, NULL);
        append_children((yyval.node), (yyvsp[-1].node));
        free_list_only((yyvsp[-1].node));
    }
#line 1726 "claudecompiler.tab.c"
    break;

  case 25: /* method_body_items: %empty  */
#line 387 "claudecompiler.y"
    {
        (yyval.node) = make_list();
    }
#line 1734 "claudecompiler.tab.c"
    break;

  case 26: /* method_body_items: method_body_items var_decl  */
#line 390 "claudecompiler.y"
                               {
        append_children((yyvsp[-1].node), (yyvsp[0].node));
        free_list_only((yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1744 "claudecompiler.tab.c"
    break;

  case 27: /* method_body_items: method_body_items stmt  */
#line 395 "claudecompiler.y"
                           {
        if (!is_empty_block((yyvsp[0].node)))
            addchild((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1754 "claudecompiler.tab.c"
    break;

  case 28: /* var_decl: type var_ids SEMICOLON  */
#line 403 "claudecompiler.y"
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
#line 1774 "claudecompiler.tab.c"
    break;

  case 29: /* var_decl: type error SEMICOLON  */
#line 418 "claudecompiler.y"
                         {
        yyerrok;
        (yyval.node) = make_list();
    }
#line 1783 "claudecompiler.tab.c"
    break;

  case 30: /* var_ids: IDENTIFIER  */
#line 425 "claudecompiler.y"
               {
        (yyval.node) = make_list();
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1792 "claudecompiler.tab.c"
    break;

  case 31: /* var_ids: var_ids COMMA IDENTIFIER  */
#line 429 "claudecompiler.y"
                             {
        addchild((yyvsp[-2].node), newnode(Identifier, (yyvsp[0].lexeme)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1801 "claudecompiler.tab.c"
    break;

  case 32: /* stmt: LBRACE stmt_list RBRACE  */
#line 436 "claudecompiler.y"
                            {
        (yyval.node) = build_block((yyvsp[-1].node));
    }
#line 1809 "claudecompiler.tab.c"
    break;

  case 33: /* stmt: IF LPAR expr RPAR stmt  */
#line 439 "claudecompiler.y"
                                                 {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 1820 "claudecompiler.tab.c"
    break;

  case 34: /* stmt: IF LPAR expr RPAR stmt ELSE stmt  */
#line 445 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1831 "claudecompiler.tab.c"
    break;

  case 35: /* stmt: IF LPAR error RPAR stmt  */
#line 451 "claudecompiler.y"
                                                  {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 1843 "claudecompiler.tab.c"
    break;

  case 36: /* stmt: IF LPAR error RPAR stmt ELSE stmt  */
#line 458 "claudecompiler.y"
                                      {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1855 "claudecompiler.tab.c"
    break;

  case 37: /* stmt: IF LPAR expr error stmt  */
#line 465 "claudecompiler.y"
                                                  {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 1867 "claudecompiler.tab.c"
    break;

  case 38: /* stmt: IF LPAR expr error stmt ELSE stmt  */
#line 472 "claudecompiler.y"
                                      {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1879 "claudecompiler.tab.c"
    break;

  case 39: /* stmt: WHILE LPAR expr RPAR stmt  */
#line 479 "claudecompiler.y"
                              {
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1889 "claudecompiler.tab.c"
    break;

  case 40: /* stmt: WHILE LPAR error RPAR stmt  */
#line 484 "claudecompiler.y"
                               {
        yyerrok;
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1900 "claudecompiler.tab.c"
    break;

  case 41: /* stmt: RETURN expr SEMICOLON  */
#line 490 "claudecompiler.y"
                          {
        (yyval.node) = newnode(Return, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1909 "claudecompiler.tab.c"
    break;

  case 42: /* stmt: RETURN SEMICOLON  */
#line 494 "claudecompiler.y"
                     {
        (yyval.node) = newnode(Return, NULL);
    }
#line 1917 "claudecompiler.tab.c"
    break;

  case 43: /* stmt: RETURN error SEMICOLON  */
#line 497 "claudecompiler.y"
                           {
        yyerrok;
        (yyval.node) = newnode(Return, NULL);
    }
#line 1926 "claudecompiler.tab.c"
    break;

  case 44: /* stmt: method_invocation SEMICOLON  */
#line 501 "claudecompiler.y"
                                {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1934 "claudecompiler.tab.c"
    break;

  case 45: /* stmt: IDENTIFIER ASSIGN expr SEMICOLON  */
#line 504 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(Assign, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1944 "claudecompiler.tab.c"
    break;

  case 46: /* stmt: parse_args SEMICOLON  */
#line 509 "claudecompiler.y"
                         {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1952 "claudecompiler.tab.c"
    break;

  case 47: /* stmt: PRINT LPAR expr RPAR SEMICOLON  */
#line 512 "claudecompiler.y"
                                   {
        (yyval.node) = newnode(Print, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 1961 "claudecompiler.tab.c"
    break;

  case 48: /* stmt: PRINT LPAR STRLIT RPAR SEMICOLON  */
#line 516 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(Print, NULL);
        addchild((yyval.node), newnode(StrLit, (yyvsp[-2].lexeme)));
    }
#line 1970 "claudecompiler.tab.c"
    break;

  case 49: /* stmt: PRINT LPAR error RPAR SEMICOLON  */
#line 520 "claudecompiler.y"
                                    {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 1979 "claudecompiler.tab.c"
    break;

  case 50: /* stmt: SEMICOLON  */
#line 524 "claudecompiler.y"
              {
        (yyval.node) = newnode(Block, NULL);
    }
#line 1987 "claudecompiler.tab.c"
    break;

  case 51: /* stmt: error SEMICOLON  */
#line 527 "claudecompiler.y"
                    {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 1996 "claudecompiler.tab.c"
    break;

  case 52: /* stmt_list: %empty  */
#line 534 "claudecompiler.y"
    {
        (yyval.node) = make_list();
    }
#line 2004 "claudecompiler.tab.c"
    break;

  case 53: /* stmt_list: stmt_list stmt  */
#line 537 "claudecompiler.y"
                   {
        if (!is_empty_block((yyvsp[0].node)))
            addchild((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2014 "claudecompiler.tab.c"
    break;

  case 54: /* expr: assignment_expr  */
#line 545 "claudecompiler.y"
                    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2022 "claudecompiler.tab.c"
    break;

  case 55: /* assignment_expr: IDENTIFIER ASSIGN assignment_expr  */
#line 551 "claudecompiler.y"
                                      {
        (yyval.node) = newnode(Assign, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2032 "claudecompiler.tab.c"
    break;

  case 56: /* assignment_expr: or_expr  */
#line 556 "claudecompiler.y"
            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2040 "claudecompiler.tab.c"
    break;

  case 57: /* or_expr: or_expr OR and_expr  */
#line 562 "claudecompiler.y"
                        {
        (yyval.node) = newnode(Or, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2050 "claudecompiler.tab.c"
    break;

  case 58: /* or_expr: and_expr  */
#line 567 "claudecompiler.y"
             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2058 "claudecompiler.tab.c"
    break;

  case 59: /* and_expr: and_expr AND xor_expr  */
#line 573 "claudecompiler.y"
                          {
        (yyval.node) = newnode(And, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2068 "claudecompiler.tab.c"
    break;

  case 60: /* and_expr: xor_expr  */
#line 578 "claudecompiler.y"
             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2076 "claudecompiler.tab.c"
    break;

  case 61: /* xor_expr: xor_expr XOR equality_expr  */
#line 584 "claudecompiler.y"
                               {
        (yyval.node) = newnode(Xor, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2086 "claudecompiler.tab.c"
    break;

  case 62: /* xor_expr: equality_expr  */
#line 589 "claudecompiler.y"
                  {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2094 "claudecompiler.tab.c"
    break;

  case 63: /* equality_expr: equality_expr EQ relational_expr  */
#line 595 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(Eq, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2104 "claudecompiler.tab.c"
    break;

  case 64: /* equality_expr: equality_expr NE relational_expr  */
#line 600 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(Ne, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2114 "claudecompiler.tab.c"
    break;

  case 65: /* equality_expr: relational_expr  */
#line 605 "claudecompiler.y"
                    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2122 "claudecompiler.tab.c"
    break;

  case 66: /* relational_expr: relational_expr LT shift_expr  */
#line 611 "claudecompiler.y"
                                  {
        (yyval.node) = newnode(Lt, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2132 "claudecompiler.tab.c"
    break;

  case 67: /* relational_expr: relational_expr GT shift_expr  */
#line 616 "claudecompiler.y"
                                  {
        (yyval.node) = newnode(Gt, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2142 "claudecompiler.tab.c"
    break;

  case 68: /* relational_expr: relational_expr LE shift_expr  */
#line 621 "claudecompiler.y"
                                  {
        (yyval.node) = newnode(Le, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2152 "claudecompiler.tab.c"
    break;

  case 69: /* relational_expr: relational_expr GE shift_expr  */
#line 626 "claudecompiler.y"
                                  {
        (yyval.node) = newnode(Ge, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2162 "claudecompiler.tab.c"
    break;

  case 70: /* relational_expr: shift_expr  */
#line 631 "claudecompiler.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2170 "claudecompiler.tab.c"
    break;

  case 71: /* shift_expr: shift_expr LSHIFT additive_expr  */
#line 637 "claudecompiler.y"
                                    {
        (yyval.node) = newnode(Lshift, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2180 "claudecompiler.tab.c"
    break;

  case 72: /* shift_expr: shift_expr RSHIFT additive_expr  */
#line 642 "claudecompiler.y"
                                    {
        (yyval.node) = newnode(Rshift, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2190 "claudecompiler.tab.c"
    break;

  case 73: /* shift_expr: additive_expr  */
#line 647 "claudecompiler.y"
                  {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2198 "claudecompiler.tab.c"
    break;

  case 74: /* additive_expr: additive_expr PLUS multiplicative_expr  */
#line 653 "claudecompiler.y"
                                           {
        (yyval.node) = newnode(Add, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2208 "claudecompiler.tab.c"
    break;

  case 75: /* additive_expr: additive_expr MINUS multiplicative_expr  */
#line 658 "claudecompiler.y"
                                            {
        (yyval.node) = newnode(Sub, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2218 "claudecompiler.tab.c"
    break;

  case 76: /* additive_expr: multiplicative_expr  */
#line 663 "claudecompiler.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2226 "claudecompiler.tab.c"
    break;

  case 77: /* multiplicative_expr: multiplicative_expr STAR unary_expr  */
#line 669 "claudecompiler.y"
                                        {
        (yyval.node) = newnode(Mul, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2236 "claudecompiler.tab.c"
    break;

  case 78: /* multiplicative_expr: multiplicative_expr DIV unary_expr  */
#line 674 "claudecompiler.y"
                                       {
        (yyval.node) = newnode(Div, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2246 "claudecompiler.tab.c"
    break;

  case 79: /* multiplicative_expr: multiplicative_expr MOD unary_expr  */
#line 679 "claudecompiler.y"
                                       {
        (yyval.node) = newnode(Mod, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2256 "claudecompiler.tab.c"
    break;

  case 80: /* multiplicative_expr: unary_expr  */
#line 684 "claudecompiler.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2264 "claudecompiler.tab.c"
    break;

  case 81: /* unary_expr: NOT unary_expr  */
#line 690 "claudecompiler.y"
                   {
        (yyval.node) = newnode(Not, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2273 "claudecompiler.tab.c"
    break;

  case 82: /* unary_expr: MINUS unary_expr  */
#line 694 "claudecompiler.y"
                                  {
        (yyval.node) = newnode(Minus, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2282 "claudecompiler.tab.c"
    break;

  case 83: /* unary_expr: PLUS unary_expr  */
#line 698 "claudecompiler.y"
                                {
        (yyval.node) = newnode(Plus, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2291 "claudecompiler.tab.c"
    break;

  case 84: /* unary_expr: primary_expr  */
#line 702 "claudecompiler.y"
                 {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2299 "claudecompiler.tab.c"
    break;

  case 85: /* primary_expr: IDENTIFIER  */
#line 708 "claudecompiler.y"
               {
        (yyval.node) = newnode(Identifier, (yyvsp[0].lexeme));
    }
#line 2307 "claudecompiler.tab.c"
    break;

  case 86: /* primary_expr: IDENTIFIER DOTLENGTH  */
#line 711 "claudecompiler.y"
                         {
        (yyval.node) = newnode(Length, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-1].lexeme)));
    }
#line 2316 "claudecompiler.tab.c"
    break;

  case 87: /* primary_expr: NATURAL  */
#line 715 "claudecompiler.y"
            {
        (yyval.node) = newnode(Natural, (yyvsp[0].lexeme));
    }
#line 2324 "claudecompiler.tab.c"
    break;

  case 88: /* primary_expr: DECIMAL  */
#line 718 "claudecompiler.y"
            {
        (yyval.node) = newnode(Decimal, (yyvsp[0].lexeme));
    }
#line 2332 "claudecompiler.tab.c"
    break;

  case 89: /* primary_expr: BOOLLIT  */
#line 721 "claudecompiler.y"
            {
        (yyval.node) = newnode(BoolLit, (yyvsp[0].lexeme));
    }
#line 2340 "claudecompiler.tab.c"
    break;

  case 90: /* primary_expr: method_invocation  */
#line 724 "claudecompiler.y"
                      {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2348 "claudecompiler.tab.c"
    break;

  case 91: /* primary_expr: parse_args  */
#line 727 "claudecompiler.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2356 "claudecompiler.tab.c"
    break;

  case 92: /* primary_expr: LPAR expr RPAR  */
#line 730 "claudecompiler.y"
                   {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2364 "claudecompiler.tab.c"
    break;

  case 93: /* primary_expr: LPAR error RPAR  */
#line 733 "claudecompiler.y"
                    {
        yyerrok;
        (yyval.node) = newnode(Natural, "0");
    }
#line 2373 "claudecompiler.tab.c"
    break;

  case 94: /* method_invocation: IDENTIFIER LPAR args_opt RPAR  */
#line 740 "claudecompiler.y"
                                  {
        (yyval.node) = newnode(Call, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        append_children((yyval.node), (yyvsp[-1].node));
        free_list_only((yyvsp[-1].node));
    }
#line 2384 "claudecompiler.tab.c"
    break;

  case 95: /* method_invocation: IDENTIFIER LPAR error RPAR  */
#line 746 "claudecompiler.y"
                               {
        yyerrok;
        (yyval.node) = newnode(Call, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
    }
#line 2394 "claudecompiler.tab.c"
    break;

  case 96: /* args_opt: %empty  */
#line 754 "claudecompiler.y"
    {
        (yyval.node) = make_list();
    }
#line 2402 "claudecompiler.tab.c"
    break;

  case 97: /* args_opt: expr_list  */
#line 757 "claudecompiler.y"
              {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2410 "claudecompiler.tab.c"
    break;

  case 98: /* expr_list: expr  */
#line 763 "claudecompiler.y"
         {
        (yyval.node) = make_list();
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2419 "claudecompiler.tab.c"
    break;

  case 99: /* expr_list: expr_list COMMA expr  */
#line 767 "claudecompiler.y"
                         {
        addchild((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2428 "claudecompiler.tab.c"
    break;

  case 100: /* expr_list: expr_list COMMA error  */
#line 771 "claudecompiler.y"
                          {
        yyerrok;
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2437 "claudecompiler.tab.c"
    break;

  case 101: /* parse_args: PARSEINT LPAR IDENTIFIER LSQ expr RSQ RPAR  */
#line 778 "claudecompiler.y"
                                               {
        (yyval.node) = newnode(ParseArgs, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-4].lexeme)));
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 2447 "claudecompiler.tab.c"
    break;

  case 102: /* parse_args: PARSEINT LPAR error RPAR  */
#line 783 "claudecompiler.y"
                             {
        yyerrok;
        (yyval.node) = newnode(ParseArgs, NULL);
    }
#line 2456 "claudecompiler.tab.c"
    break;

  case 103: /* type: BOOL  */
#line 790 "claudecompiler.y"
         {
        (yyval.node) = newnode(Bool, NULL);
    }
#line 2464 "claudecompiler.tab.c"
    break;

  case 104: /* type: INT  */
#line 793 "claudecompiler.y"
        {
        (yyval.node) = newnode(Int, NULL);
    }
#line 2472 "claudecompiler.tab.c"
    break;

  case 105: /* type: DOUBLE  */
#line 796 "claudecompiler.y"
           {
        (yyval.node) = newnode(Double, NULL);
    }
#line 2480 "claudecompiler.tab.c"
    break;


#line 2484 "claudecompiler.tab.c"

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

#line 801 "claudecompiler.y"


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

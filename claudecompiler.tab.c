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
extern int line, column, token_line, token_column, print_tokens;
extern char *yytext, token_text[];
extern int last_lex_error_line, yychar;

struct node *ast = NULL;
int print_tree = 0, only_errors = 0, syntax_errors = 0, syntax_error_count = 0;
int pending_error_after_block = 0;
int last_syntax_error_line = 0;
int saved_public_line = 0;
int saved_error_line = 0;
int saved_error_col = 0;
int last_syntax_error_col = 0;
char last_syntax_error_text[10000] = "";

static struct node *clone_type_node(struct node *n) { if (!n) return NULL; return newnode(n->category, n->token); }
static struct node *make_holder() { return newnode(Program, NULL); }

static void append_holder(struct node *dst, struct node *src) {
    struct node_list *child;
    if (!dst || !src || !src->children) return;
    child = src->children->next;
    while (child) { addchild(dst, child->node); child = child->next; }
    src->children->next = NULL;
}

static int child_count(struct node *n) {
    int count = 0;
    struct node_list *c;
    if (!n || !n->children) return 0;
    c = n->children->next;
    while (c) { count++; c = c->next; }
    return count;
}

static int is_empty_block(struct node *n) { return n && n->category == Block && child_count(n) == 0; }

static int meaningful_child_count(struct node *h) {
    int count = 0;
    struct node_list *c;
    if (!h || !h->children) return 0;
    c = h->children->next;
    while (c) { if (!is_empty_block(c->node)) count++; c = c->next; }
    return count;
}

static struct node *first_meaningful_child(struct node *h) {
    struct node_list *c;
    if (!h || !h->children) return NULL;
    c = h->children->next;
    while (c) { if (!is_empty_block(c->node)) return c->node; c = c->next; }
    return NULL;
}

static void append_meaningful_children(struct node *dst, struct node *src) {
    struct node_list *c;
    if (!dst || !src || !src->children) return;
    c = src->children->next;
    while (c) { if (!is_empty_block(c->node)) addchild(dst, c->node); c = c->next; }
}

static void free_holder_only(struct node *n) {
    if (!n) return;
    if (n->children) free(n->children);
    free(n);
}

static struct node *build_block_from_holder(struct node *holder) {
    int meaningful = meaningful_child_count(holder);
    struct node *result;
    if (meaningful == 0) {
        result = newnode(Block, NULL);
        free_holder_only(holder);
        return result;
    }
    if (meaningful == 1) {
        result = first_meaningful_child(holder);
        holder->children->next = NULL;
        free_holder_only(holder);
        return result;
    }
    result = newnode(Block, NULL);
    append_meaningful_children(result, holder);
    free_holder_only(holder);
    return result;
}

void yyerror(char *s) {
    int err_line = token_line;
    int err_col = token_column;
    const char *err_text = token_text;
    syntax_errors = 1;

    if (token_line == last_lex_error_line) return;
    if (yychar == 0) {
        err_line = line;
        err_col = column;
        err_text = "";
        if (syntax_error_count > 0) return;
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


#line 195 "claudecompiler.tab.c"

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
  YYSYMBOL_STATIC = 9,                     /* STATIC  */
  YYSYMBOL_RESERVED = 10,                  /* RESERVED  */
  YYSYMBOL_BOOL = 11,                      /* BOOL  */
  YYSYMBOL_INT = 12,                       /* INT  */
  YYSYMBOL_DOUBLE = 13,                    /* DOUBLE  */
  YYSYMBOL_VOID = 14,                      /* VOID  */
  YYSYMBOL_STRING = 15,                    /* STRING  */
  YYSYMBOL_IF = 16,                        /* IF  */
  YYSYMBOL_ELSE = 17,                      /* ELSE  */
  YYSYMBOL_WHILE = 18,                     /* WHILE  */
  YYSYMBOL_RETURN = 19,                    /* RETURN  */
  YYSYMBOL_PRINT = 20,                     /* PRINT  */
  YYSYMBOL_PARSEINT = 21,                  /* PARSEINT  */
  YYSYMBOL_DOTLENGTH = 22,                 /* DOTLENGTH  */
  YYSYMBOL_INC = 23,                       /* INC  */
  YYSYMBOL_DEC = 24,                       /* DEC  */
  YYSYMBOL_ARROW = 25,                     /* ARROW  */
  YYSYMBOL_ASSIGN = 26,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 27,                      /* PLUS  */
  YYSYMBOL_MINUS = 28,                     /* MINUS  */
  YYSYMBOL_STAR = 29,                      /* STAR  */
  YYSYMBOL_DIV = 30,                       /* DIV  */
  YYSYMBOL_MOD = 31,                       /* MOD  */
  YYSYMBOL_AND = 32,                       /* AND  */
  YYSYMBOL_OR = 33,                        /* OR  */
  YYSYMBOL_XOR = 34,                       /* XOR  */
  YYSYMBOL_LSHIFT = 35,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 36,                    /* RSHIFT  */
  YYSYMBOL_EQ = 37,                        /* EQ  */
  YYSYMBOL_NE = 38,                        /* NE  */
  YYSYMBOL_LT = 39,                        /* LT  */
  YYSYMBOL_GT = 40,                        /* GT  */
  YYSYMBOL_LE = 41,                        /* LE  */
  YYSYMBOL_GE = 42,                        /* GE  */
  YYSYMBOL_NOT = 43,                       /* NOT  */
  YYSYMBOL_LPAR = 44,                      /* LPAR  */
  YYSYMBOL_RPAR = 45,                      /* RPAR  */
  YYSYMBOL_LBRACE = 46,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 47,                    /* RBRACE  */
  YYSYMBOL_LSQ = 48,                       /* LSQ  */
  YYSYMBOL_RSQ = 49,                       /* RSQ  */
  YYSYMBOL_COMMA = 50,                     /* COMMA  */
  YYSYMBOL_TAIL_DONE = 51,                 /* TAIL_DONE  */
  YYSYMBOL_SEMICOLON = 52,                 /* SEMICOLON  */
  YYSYMBOL_PUBLIC = 53,                    /* PUBLIC  */
  YYSYMBOL_LOWER_THAN_ELSE = 54,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 55,                  /* $accept  */
  YYSYMBOL_program = 56,                   /* program  */
  YYSYMBOL_class_body = 57,                /* class_body  */
  YYSYMBOL_field_decl = 58,                /* field_decl  */
  YYSYMBOL_field_ids = 59,                 /* field_ids  */
  YYSYMBOL_method_decl = 60,               /* method_decl  */
  YYSYMBOL_61_1 = 61,                      /* $@1  */
  YYSYMBOL_62_2 = 62,                      /* $@2  */
  YYSYMBOL_63_3 = 63,                      /* $@3  */
  YYSYMBOL_method_header = 64,             /* method_header  */
  YYSYMBOL_param_list = 65,                /* param_list  */
  YYSYMBOL_param_decl = 66,                /* param_decl  */
  YYSYMBOL_method_body = 67,               /* method_body  */
  YYSYMBOL_invalid_method_body = 68,       /* invalid_method_body  */
  YYSYMBOL_invalid_body_items = 69,        /* invalid_body_items  */
  YYSYMBOL_invalid_body_item = 70,         /* invalid_body_item  */
  YYSYMBOL_method_body_items = 71,         /* method_body_items  */
  YYSYMBOL_bad_string_start = 72,          /* bad_string_start  */
  YYSYMBOL_bad_string_tail = 73,           /* bad_string_tail  */
  YYSYMBOL_bad_string_items = 74,          /* bad_string_items  */
  YYSYMBOL_bad_string_item = 75,           /* bad_string_item  */
  YYSYMBOL_invalid_public_decl = 76,       /* invalid_public_decl  */
  YYSYMBOL_77_4 = 77,                      /* $@4  */
  YYSYMBOL_invalid_public_tail = 78,       /* invalid_public_tail  */
  YYSYMBOL_invalid_id_list = 79,           /* invalid_id_list  */
  YYSYMBOL_semis = 80,                     /* semis  */
  YYSYMBOL_assign_save = 81,               /* assign_save  */
  YYSYMBOL_var_decl = 82,                  /* var_decl  */
  YYSYMBOL_var_ids = 83,                   /* var_ids  */
  YYSYMBOL_stmt = 84,                      /* stmt  */
  YYSYMBOL_stmt_entry = 85,                /* stmt_entry  */
  YYSYMBOL_stmt_core = 86,                 /* stmt_core  */
  YYSYMBOL_stmt_list = 87,                 /* stmt_list  */
  YYSYMBOL_expr = 88,                      /* expr  */
  YYSYMBOL_assign_expr = 89,               /* assign_expr  */
  YYSYMBOL_or_expr = 90,                   /* or_expr  */
  YYSYMBOL_and_expr = 91,                  /* and_expr  */
  YYSYMBOL_xor_expr = 92,                  /* xor_expr  */
  YYSYMBOL_eq_expr = 93,                   /* eq_expr  */
  YYSYMBOL_rel_expr = 94,                  /* rel_expr  */
  YYSYMBOL_shift_expr = 95,                /* shift_expr  */
  YYSYMBOL_add_expr = 96,                  /* add_expr  */
  YYSYMBOL_mul_expr = 97,                  /* mul_expr  */
  YYSYMBOL_unary_expr = 98,                /* unary_expr  */
  YYSYMBOL_primary_expr = 99,              /* primary_expr  */
  YYSYMBOL_method_invocation = 100,        /* method_invocation  */
  YYSYMBOL_args_opt = 101,                 /* args_opt  */
  YYSYMBOL_expr_list = 102,                /* expr_list  */
  YYSYMBOL_parse_args = 103,               /* parse_args  */
  YYSYMBOL_type = 104                      /* type  */
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
typedef yytype_int16 yy_state_t;

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
#define YYLAST   578

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  241
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  403

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   309


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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   163,   163,   173,   174,   179,   183,   187,   201,   205,
     209,   216,   220,   227,   233,   233,   249,   249,   260,   260,
     274,   280,   286,   292,   301,   305,   312,   317,   322,   330,
     339,   344,   345,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   401,   402,   405,   410,   415,   424,   435,   438,
     439,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     495,   495,   506,   507,   508,   509,   510,   513,   519,   520,
     524,   525,   529,   536,   550,   553,   559,   563,   570,   574,
     581,   585,   604,   607,   613,   619,   626,   633,   641,   649,
     654,   660,   667,   671,   674,   678,   681,   684,   689,   693,
     696,   700,   704,   708,   709,   713,   714,   717,   724,   725,
     734,   738,   743,   747,   752,   756,   761,   765,   770,   774,
     779,   784,   788,   793,   798,   803,   808,   812,   817,   822,
     826,   831,   836,   840,   845,   850,   855,   859,   863,   867,
     871,   875,   878,   882,   885,   888,   891,   892,   893,   894,
     901,   907,   915,   916,   920,   924,   928,   935,   940,   947,
     948,   949
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
  "NATURAL", "DECIMAL", "STRLIT", "BOOLLIT", "CLASS", "STATIC", "RESERVED",
  "BOOL", "INT", "DOUBLE", "VOID", "STRING", "IF", "ELSE", "WHILE",
  "RETURN", "PRINT", "PARSEINT", "DOTLENGTH", "INC", "DEC", "ARROW",
  "ASSIGN", "PLUS", "MINUS", "STAR", "DIV", "MOD", "AND", "OR", "XOR",
  "LSHIFT", "RSHIFT", "EQ", "NE", "LT", "GT", "LE", "GE", "NOT", "LPAR",
  "RPAR", "LBRACE", "RBRACE", "LSQ", "RSQ", "COMMA", "TAIL_DONE",
  "SEMICOLON", "PUBLIC", "LOWER_THAN_ELSE", "$accept", "program",
  "class_body", "field_decl", "field_ids", "method_decl", "$@1", "$@2",
  "$@3", "method_header", "param_list", "param_decl", "method_body",
  "invalid_method_body", "invalid_body_items", "invalid_body_item",
  "method_body_items", "bad_string_start", "bad_string_tail",
  "bad_string_items", "bad_string_item", "invalid_public_decl", "$@4",
  "invalid_public_tail", "invalid_id_list", "semis", "assign_save",
  "var_decl", "var_ids", "stmt", "stmt_entry", "stmt_core", "stmt_list",
  "expr", "assign_expr", "or_expr", "and_expr", "xor_expr", "eq_expr",
  "rel_expr", "shift_expr", "add_expr", "mul_expr", "unary_expr",
  "primary_expr", "method_invocation", "args_opt", "expr_list",
  "parse_args", "type", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-307)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-233)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      16,    25,    20,   -15,  -307,  -307,    10,    22,  -307,  -307,
      78,  -307,  -307,  -307,   144,    51,  -307,  -307,  -307,    45,
      74,    31,  -307,   167,  -307,  -307,   162,   223,    82,    64,
      39,  -307,    69,   149,  -307,   273,   324,  -307,  -307,    46,
    -307,   373,  -307,  -307,  -307,  -307,  -307,  -307,  -307,    26,
     118,   348,  -307,    72,  -307,  -307,    19,   349,  -307,   138,
    -307,   104,  -307,   160,   352,     9,   369,   372,    12,   377,
     389,  -307,  -307,  -307,   395,   402,   403,    23,    17,  -307,
    -307,   410,   411,   458,   450,  -307,   414,   127,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,   457,   374,   103,   387,   431,   418,    -1,  -307,  -307,
    -307,   427,   490,   490,   490,   436,  -307,   420,  -307,   440,
     444,   443,    56,   370,   100,   116,    30,  -307,  -307,  -307,
    -307,   379,   386,   434,  -307,  -307,  -307,  -307,   495,   495,
    -307,   475,  -307,   410,  -307,  -307,   479,  -307,   484,  -307,
     439,   493,   498,    74,   500,   216,   478,   453,   463,   505,
     462,   464,  -307,   465,   469,   470,    21,   476,    40,  -307,
    -307,   495,   396,    14,  -307,  -307,  -307,   480,   481,  -307,
     490,   490,   490,   490,   490,   490,   490,   490,   490,   490,
     490,   490,   490,   490,   490,   490,   482,   486,   487,   491,
     472,  -307,  -307,   488,   483,  -307,  -307,   267,  -307,   496,
    -307,   499,   353,   504,  -307,   501,  -307,   495,  -307,   441,
     502,  -307,  -307,  -307,   485,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,   497,  -307,  -307,   444,   443,    56,   370,   370,
     100,   100,   100,   100,   116,   116,    30,    30,  -307,  -307,
    -307,   492,   503,   506,   507,   495,   508,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,    74,
     114,   521,  -307,   509,   534,   438,   510,    89,   511,   495,
    -307,  -307,   530,   531,   532,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,   512,   514,  -307,   321,  -307,  -307,  -307,   513,
    -307,   515,   523,  -307,  -307,  -307,  -307,   524,  -307,   108,
    -307,   518,  -307,  -307,  -307,  -307,   541,  -307,   537,   550,
    -307,   353,   509
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     0,     2,     6,
       0,     4,     5,    10,     0,     0,   241,   239,   240,     0,
       0,     0,     8,     0,    82,    13,     0,    11,     0,     0,
     161,     9,     0,     0,     7,     0,     0,    22,    14,     0,
      24,     0,    87,    29,   140,    89,    83,    84,    86,     0,
       0,     0,    20,     0,    12,    18,     0,     0,    23,     0,
      26,     0,    85,     0,     0,     0,     0,     0,     0,     0,
       0,   188,   186,   160,     0,     0,     0,   158,     0,    16,
      21,     0,     0,     0,     0,    25,     0,     0,   141,    91,
      92,    93,    94,    95,    96,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,    89,    88,   136,   137,   139,   138,    97,    90,
     187,     0,     0,     0,     0,     0,     0,   221,   223,   224,
     225,     0,     0,     0,     0,     0,   173,     0,   190,   192,
     194,   196,   198,   201,   206,   209,   212,   216,   220,   226,
     227,     0,     0,   161,   183,   185,   157,   152,     0,     0,
     156,     0,   153,     0,    31,    19,     0,    27,     0,   147,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   234,     0,   233,     0,     0,     0,     0,   174,
     222,     0,     0,   221,   219,   218,   217,     0,     0,   172,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   162,   189,     0,     0,   159,    17,     0,    28,     0,
     146,   148,     0,     0,   145,     0,   135,     0,   178,     0,
       0,   177,   231,   230,     0,   161,   161,   161,   161,   161,
     161,   191,     0,   229,   228,   193,   195,   197,   199,   200,
     202,   203,   204,   205,   207,   208,   210,   211,   213,   214,
     215,     0,     0,     0,   238,     0,     0,   155,    34,    35,
      36,    37,    38,    39,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    31,    30,    78,    79,    81,    80,    40,    32,     0,
       0,     0,   150,   144,     0,     0,     0,   221,     0,     0,
     236,   235,   165,   167,   163,   170,   171,   169,   238,   182,
     181,   180,     0,     0,   154,     0,    15,   149,   151,     0,
     175,     0,     0,   161,   161,   161,   184,     0,    33,   143,
     176,     0,   166,   168,   164,   237,     0,   179,     0,     0,
     148,     0,   142
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,   467,
     -32,   516,  -187,   376,   225,  -307,  -307,  -307,  -307,   425,
    -307,  -307,  -307,  -307,   172,  -306,  -307,  -307,  -307,  -168,
    -307,  -307,  -307,  -141,   361,  -307,   354,   355,   351,    98,
     199,   190,   197,  -145,  -307,   528,  -307,  -307,   529,    -4
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     6,    11,    28,    12,    57,   183,    81,    20,
      39,    40,    25,   185,   247,   348,    30,    45,    62,    63,
     139,    46,    61,    88,   252,   353,   179,    47,    78,    48,
      49,    73,   173,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   203,   204,   170,    41
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,   200,   202,   206,   208,   242,   254,   214,   215,   216,
      21,     7,   141,   146,   218,   147,   148,   149,   180,   150,
       4,   210,   266,    82,     1,   211,    50,    64,     3,    65,
     238,     5,    26,   151,    27,   142,   210,   243,   244,   152,
     153,   269,    66,   143,    67,    68,    69,    70,    23,   177,
      16,    17,    18,   143,    42,   154,   155,     8,   143,   233,
     234,   235,     9,    10,   156,    35,   267,   181,    83,   182,
      51,   178,    71,   389,    13,    16,    17,    18,    72,    36,
      16,    17,    18,   194,    36,   270,    43,    14,   288,   289,
     290,    58,    44,   223,   224,   402,    59,   362,   363,   364,
     365,   366,   367,    22,   201,    86,   147,   148,   149,    37,
     150,   210,    38,    87,    52,   211,   356,    80,   358,    76,
      24,    77,    59,   361,   151,    16,    17,    18,   190,    36,
     152,   153,    33,   143,    34,   229,   230,   295,    16,    17,
      18,   191,   192,   231,   232,    15,   154,   155,  -232,    16,
      17,    18,    54,    36,   373,    16,    17,    18,    19,    37,
     378,   396,   376,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,    29,   137,   138,    31,   392,   393,   394,   382,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   256,   134,   135,   136,    32,   137,   138,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,    55,   346,
     347,   278,   279,    53,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   388,   343,
     344,   345,    56,   346,   347,   197,    60,   147,   148,   149,
     236,   150,   147,   148,   149,   237,   150,   239,   205,   240,
     147,   148,   149,    79,   150,   198,   199,   272,    84,   240,
     151,   152,   153,   351,   140,   352,   152,   153,   151,   225,
     226,   227,   228,   144,   152,   153,   145,   154,   155,   284,
     285,   171,   154,   155,   280,   281,   282,   283,   286,   287,
     154,   155,   207,   172,   147,   148,   149,   217,   150,   147,
     148,   149,   272,   150,   357,   148,   149,   174,   150,    16,
      17,    18,   151,    36,   175,   176,   184,   151,   152,   153,
     186,   187,   151,   152,   153,   188,   189,   196,   152,   153,
     209,   212,   219,   220,   154,   155,   221,   222,   245,   154,
     155,   241,   248,    52,   154,   155,   360,   249,   147,   148,
     149,   250,   150,   213,   148,   149,   251,   150,   147,   148,
     149,   253,   150,   255,   257,   258,   151,   259,   260,   262,
     263,   151,   152,   153,   261,   265,   151,   152,   153,   264,
     295,   268,   152,   153,   377,   273,   274,   291,   154,   155,
     354,   292,   293,   154,   155,   297,   294,   296,   154,   155,
     379,   349,   368,   350,   369,   355,   359,   383,   384,   385,
     398,   399,   372,   400,   193,   370,   381,   195,   371,   246,
     374,   378,   380,   387,   386,   352,   375,   390,   391,   395,
     397,   401,   271,   277,   275,    85,   276,    74,    75
};

static const yytype_int16 yycheck[] =
{
      32,   142,   143,   144,   145,   173,   193,   152,   153,   154,
      14,     1,     3,     1,   155,     3,     4,     5,     1,     7,
       0,    22,     1,     4,     8,    26,    30,     1,     3,     3,
     171,    46,     1,    21,     3,    26,    22,   178,   179,    27,
      28,     1,    16,    44,    18,    19,    20,    21,     3,    26,
      11,    12,    13,    44,    15,    43,    44,    47,    44,    29,
      30,    31,    52,    53,    52,     1,    45,    50,    49,    52,
       1,    48,    46,   379,    52,    11,    12,    13,    52,    15,
      11,    12,    13,    87,    15,    45,    47,     9,   233,   234,
     235,    45,    53,    37,    38,   401,    50,   265,   266,   267,
     268,   269,   270,    52,     1,     1,     3,     4,     5,    45,
       7,    22,    48,     9,    45,    26,   257,    45,   259,     1,
      46,     3,    50,   264,    21,    11,    12,    13,     1,    15,
      27,    28,    50,    44,    52,    35,    36,    48,    11,    12,
      13,    14,    15,    27,    28,     1,    43,    44,    45,    11,
      12,    13,     3,    15,   295,    11,    12,    13,    14,    45,
      52,    53,   349,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    44,    52,    53,    52,   383,   384,   385,   359,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    44,    52,    53,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    45,    52,
      53,   223,   224,   355,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    48,    52,    53,     1,     3,     3,     4,     5,
       1,     7,     3,     4,     5,     6,     7,     1,     1,     3,
       3,     4,     5,    45,     7,    21,    22,     1,    49,     3,
      21,    27,    28,    50,    52,    52,    27,    28,    21,    39,
      40,    41,    42,    44,    27,    28,    44,    43,    44,   229,
     230,    44,    43,    44,   225,   226,   227,   228,   231,   232,
      43,    44,     1,    44,     3,     4,     5,     1,     7,     3,
       4,     5,     1,     7,     3,     4,     5,    52,     7,    11,
      12,    13,    21,    15,    52,    52,    46,    21,    27,    28,
      49,     3,    21,    27,    28,    15,    52,    10,    27,    28,
      52,    44,    52,    33,    43,    44,    32,    34,     3,    43,
      44,    47,     3,    45,    43,    44,     1,     3,     3,     4,
       5,    52,     7,     3,     4,     5,     3,     7,     3,     4,
       5,     3,     7,     3,    26,    52,    21,    44,     3,    45,
      45,    21,    27,    28,    52,    45,    21,    27,    28,    50,
      48,    45,    27,    28,     3,    45,    45,    45,    43,    44,
      26,    45,    45,    43,    44,    52,    45,    49,    43,    44,
       6,    45,    45,    44,    52,    44,    44,    17,    17,    17,
       9,    14,    45,     3,    87,    52,    45,   132,    52,   183,
      52,    52,    52,    49,    52,    52,   341,    52,    45,    45,
      52,   399,   211,   222,   220,    59,   221,    49,    49
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    56,     3,     0,    46,    57,     1,    47,    52,
      53,    58,    60,    52,     9,     1,    11,    12,    13,    14,
      64,   104,    52,     3,    46,    67,     1,     3,    59,    44,
      71,    52,    44,    50,    52,     1,    15,    45,    48,    65,
      66,   104,    15,    47,    53,    72,    76,    82,    84,    85,
     104,     1,    45,    65,     3,    45,    48,    61,    45,    50,
       3,    77,    73,    74,     1,     3,    16,    18,    19,    20,
      21,    46,    52,    86,   100,   103,     1,     3,    83,    45,
      45,    63,     4,    49,    49,    66,     1,     9,    78,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    52,    53,    75,
      52,     3,    26,    44,    44,    44,     1,     3,     4,     5,
       7,    21,    27,    28,    43,    44,    52,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     103,    44,    44,    87,    52,    52,    52,    26,    48,    81,
       1,    50,    52,    62,    46,    68,    49,     3,    15,    52,
       1,    14,    15,    64,   104,    74,    10,     1,    21,    22,
      88,     1,    88,   101,   102,     1,    88,     1,    88,    52,
      22,    26,    44,     3,    98,    98,    98,     1,    88,    52,
      33,    32,    34,    37,    38,    39,    40,    41,    42,    35,
      36,    27,    28,    29,    30,    31,     1,     6,    88,     1,
       3,    47,    84,    88,    88,     3,    68,    69,     3,     3,
      52,     3,    79,     3,    67,     3,    47,    26,    52,    44,
       3,    52,    45,    45,    50,    45,     1,    45,    45,     1,
      45,    89,     1,    45,    45,    91,    92,    93,    94,    94,
      95,    95,    95,    95,    96,    96,    97,    97,    98,    98,
      98,    45,    45,    45,    45,    48,    49,    52,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    52,    53,    70,    45,
      44,    50,    52,    80,    26,    44,    88,     3,    88,    44,
       1,    88,    84,    84,    84,    84,    84,    84,    45,    52,
      52,    52,    45,    88,    52,    69,    67,     3,    52,     6,
      52,    45,    88,    17,    17,    17,    52,    49,    47,    80,
      52,    45,    84,    84,    84,    45,    53,    52,     9,    14,
       3,    79,    80
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    57,    57,    57,    57,    58,    58,    58,
      58,    59,    59,    60,    61,    60,    62,    60,    63,    60,
      64,    64,    64,    64,    65,    65,    66,    66,    66,    67,
      68,    69,    69,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    71,    71,    71,    71,    71,    72,    73,    74,
      74,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      77,    76,    78,    78,    78,    78,    78,    78,    79,    79,
      80,    80,    81,    82,    82,    82,    82,    82,    83,    83,
      84,    85,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    87,    87,
      88,    89,    89,    90,    90,    91,    91,    92,    92,    93,
      93,    93,    94,    94,    94,    94,    94,    95,    95,    95,
      96,    96,    96,    97,    97,    97,    97,    98,    98,    98,
      98,    99,    99,    99,    99,    99,    99,    99,    99,    99,
     100,   100,   101,   101,   102,   102,   102,   103,   103,   104,
     104,   104
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     0,     2,     2,     2,     5,     4,     5,
       2,     1,     3,     4,     0,    12,     0,     9,     0,     9,
       4,     5,     4,     5,     1,     3,     2,     4,     5,     3,
       3,     0,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     2,     2,     3,     2,     1,     2,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       0,     3,    11,     6,     4,     3,     3,     2,     1,     3,
       1,     2,     1,     3,     6,     5,     3,     3,     1,     3,
       2,     0,     3,     5,     7,     5,     7,     5,     7,     5,
       5,     5,     3,     2,     3,     6,     7,     4,     4,     8,
       5,     5,     5,     2,     6,     2,     1,     2,     0,     2,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     2,
       1,     1,     2,     1,     1,     1,     1,     1,     3,     3,
       4,     4,     0,     1,     1,     3,     3,     7,     4,     1,
       1,     1
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
#line 163 "claudecompiler.y"
                                              {
        (yyval.node) = newnode(Program, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        append_holder((yyval.node), (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));
        ast = (yyval.node);
    }
#line 1614 "claudecompiler.tab.c"
    break;

  case 3: /* class_body: %empty  */
#line 173 "claudecompiler.y"
    { (yyval.node) = make_holder(); }
#line 1620 "claudecompiler.tab.c"
    break;

  case 4: /* class_body: class_body field_decl  */
#line 174 "claudecompiler.y"
                          {
        append_holder((yyvsp[-1].node), (yyvsp[0].node));
        free_holder_only((yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1630 "claudecompiler.tab.c"
    break;

  case 5: /* class_body: class_body method_decl  */
#line 179 "claudecompiler.y"
                           {
        addchild((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1639 "claudecompiler.tab.c"
    break;

  case 6: /* class_body: class_body SEMICOLON  */
#line 183 "claudecompiler.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 1645 "claudecompiler.tab.c"
    break;

  case 7: /* field_decl: PUBLIC STATIC type field_ids SEMICOLON  */
#line 187 "claudecompiler.y"
                                           {
        struct node_list *child;
        (yyval.node) = make_holder();
        child = (yyvsp[-1].node)->children->next;
        while (child) {
            struct node *decl = newnode(FieldDecl, NULL);
            addchild(decl, clone_type_node((yyvsp[-2].node)));
            addchild(decl, newnode(Identifier, child->node->token));
            addchild((yyval.node), decl);
            child = child->next;
        }
        free_ast((yyvsp[-2].node));
        free_ast((yyvsp[-1].node));
    }
#line 1664 "claudecompiler.tab.c"
    break;

  case 8: /* field_decl: PUBLIC STATIC error SEMICOLON  */
#line 201 "claudecompiler.y"
                                  {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 1673 "claudecompiler.tab.c"
    break;

  case 9: /* field_decl: PUBLIC STATIC type error SEMICOLON  */
#line 205 "claudecompiler.y"
                                       {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 1682 "claudecompiler.tab.c"
    break;

  case 10: /* field_decl: error SEMICOLON  */
#line 209 "claudecompiler.y"
                    {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 1691 "claudecompiler.tab.c"
    break;

  case 11: /* field_ids: IDENTIFIER  */
#line 216 "claudecompiler.y"
               {
        (yyval.node) = make_holder();
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1700 "claudecompiler.tab.c"
    break;

  case 12: /* field_ids: field_ids COMMA IDENTIFIER  */
#line 220 "claudecompiler.y"
                               {
        addchild((yyvsp[-2].node), newnode(Identifier, (yyvsp[0].lexeme)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1709 "claudecompiler.tab.c"
    break;

  case 13: /* method_decl: PUBLIC STATIC method_header method_body  */
#line 227 "claudecompiler.y"
                                            {
        (yyval.node) = newnode(MethodDecl, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), (yyvsp[0].node));
        pending_error_after_block = 0;
    }
#line 1720 "claudecompiler.tab.c"
    break;

  case 14: /* $@1: %empty  */
#line 233 "claudecompiler.y"
                                           {
        saved_error_line = token_line;
        saved_error_col = token_column;
    }
#line 1729 "claudecompiler.tab.c"
    break;

  case 15: /* method_decl: PUBLIC STATIC VOID IDENTIFIER LPAR LSQ $@1 RSQ STRING IDENTIFIER RPAR method_body  */
#line 236 "claudecompiler.y"
                                             {
        syntax_errors = 1;
        printf("Line %d, col %d: syntax error: [\n", saved_error_line, saved_error_col);
        syntax_error_count++;

        (yyval.node) = newnode(MethodDecl, NULL);
        struct node *header = newnode(MethodHeader, NULL);
        addchild(header, newnode(Void, NULL));
        addchild(header, newnode(Identifier, (yyvsp[-8].lexeme)));
        addchild(header, newnode(MethodParams, NULL));
        addchild((yyval.node), header);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1747 "claudecompiler.tab.c"
    break;

  case 16: /* $@2: %empty  */
#line 249 "claudecompiler.y"
                                                  {
        yyerrok;
    }
#line 1755 "claudecompiler.tab.c"
    break;

  case 17: /* method_decl: PUBLIC STATIC type IDENTIFIER LPAR error RPAR $@2 invalid_method_body  */
#line 251 "claudecompiler.y"
                          {
        (yyval.node) = newnode(MethodDecl, NULL);
        struct node *header = newnode(MethodHeader, NULL);
        addchild(header, (yyvsp[-6].node));
        addchild(header, newnode(Identifier, (yyvsp[-5].lexeme)));
        addchild(header, newnode(MethodParams, NULL));
        addchild((yyval.node), header);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1769 "claudecompiler.tab.c"
    break;

  case 18: /* $@3: %empty  */
#line 260 "claudecompiler.y"
                                                  {
        yyerrok;
    }
#line 1777 "claudecompiler.tab.c"
    break;

  case 19: /* method_decl: PUBLIC STATIC VOID IDENTIFIER LPAR error RPAR $@3 invalid_method_body  */
#line 262 "claudecompiler.y"
                          {
        (yyval.node) = newnode(MethodDecl, NULL);
        struct node *header = newnode(MethodHeader, NULL);
        addchild(header, newnode(Void, NULL));
        addchild(header, newnode(Identifier, (yyvsp[-5].lexeme)));
        addchild(header, newnode(MethodParams, NULL));
        addchild((yyval.node), header);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1791 "claudecompiler.tab.c"
    break;

  case 20: /* method_header: type IDENTIFIER LPAR RPAR  */
#line 274 "claudecompiler.y"
                              {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), (yyvsp[-3].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), newnode(MethodParams, NULL));
    }
#line 1802 "claudecompiler.tab.c"
    break;

  case 21: /* method_header: type IDENTIFIER LPAR param_list RPAR  */
#line 280 "claudecompiler.y"
                                         {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1813 "claudecompiler.tab.c"
    break;

  case 22: /* method_header: VOID IDENTIFIER LPAR RPAR  */
#line 286 "claudecompiler.y"
                              {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), newnode(Void, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), newnode(MethodParams, NULL));
    }
#line 1824 "claudecompiler.tab.c"
    break;

  case 23: /* method_header: VOID IDENTIFIER LPAR param_list RPAR  */
#line 292 "claudecompiler.y"
                                         {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), newnode(Void, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1835 "claudecompiler.tab.c"
    break;

  case 24: /* param_list: param_decl  */
#line 301 "claudecompiler.y"
               {
        (yyval.node) = newnode(MethodParams, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1844 "claudecompiler.tab.c"
    break;

  case 25: /* param_list: param_list COMMA param_decl  */
#line 305 "claudecompiler.y"
                                {
        addchild((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1853 "claudecompiler.tab.c"
    break;

  case 26: /* param_decl: type IDENTIFIER  */
#line 312 "claudecompiler.y"
                    {
        (yyval.node) = newnode(ParamDecl, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1863 "claudecompiler.tab.c"
    break;

  case 27: /* param_decl: STRING LSQ RSQ IDENTIFIER  */
#line 317 "claudecompiler.y"
                              {
        (yyval.node) = newnode(ParamDecl, NULL);
        addchild((yyval.node), newnode(StringArray, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1873 "claudecompiler.tab.c"
    break;

  case 28: /* param_decl: STRING LSQ NATURAL RSQ IDENTIFIER  */
#line 322 "claudecompiler.y"
                                      {
    (yyval.node) = newnode(ParamDecl, NULL);
    addchild((yyval.node), newnode(StringArray, NULL));
    addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
}
#line 1883 "claudecompiler.tab.c"
    break;

  case 29: /* method_body: LBRACE method_body_items RBRACE  */
#line 330 "claudecompiler.y"
                                    {
        (yyval.node) = newnode(MethodBody, NULL);
        append_holder((yyval.node), (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));
        pending_error_after_block = 0;
    }
#line 1894 "claudecompiler.tab.c"
    break;

  case 30: /* invalid_method_body: LBRACE invalid_body_items RBRACE  */
#line 339 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(MethodBody, NULL);
    }
#line 1902 "claudecompiler.tab.c"
    break;

  case 33: /* invalid_body_item: LBRACE invalid_body_items RBRACE  */
#line 349 "claudecompiler.y"
                                     { }
#line 1908 "claudecompiler.tab.c"
    break;

  case 34: /* invalid_body_item: IDENTIFIER  */
#line 350 "claudecompiler.y"
               { }
#line 1914 "claudecompiler.tab.c"
    break;

  case 35: /* invalid_body_item: NATURAL  */
#line 351 "claudecompiler.y"
            { }
#line 1920 "claudecompiler.tab.c"
    break;

  case 36: /* invalid_body_item: DECIMAL  */
#line 352 "claudecompiler.y"
            { }
#line 1926 "claudecompiler.tab.c"
    break;

  case 37: /* invalid_body_item: STRLIT  */
#line 353 "claudecompiler.y"
           { }
#line 1932 "claudecompiler.tab.c"
    break;

  case 38: /* invalid_body_item: BOOLLIT  */
#line 354 "claudecompiler.y"
            { }
#line 1938 "claudecompiler.tab.c"
    break;

  case 39: /* invalid_body_item: CLASS  */
#line 355 "claudecompiler.y"
          { }
#line 1944 "claudecompiler.tab.c"
    break;

  case 40: /* invalid_body_item: PUBLIC  */
#line 356 "claudecompiler.y"
           { }
#line 1950 "claudecompiler.tab.c"
    break;

  case 41: /* invalid_body_item: STATIC  */
#line 357 "claudecompiler.y"
           { }
#line 1956 "claudecompiler.tab.c"
    break;

  case 42: /* invalid_body_item: RESERVED  */
#line 358 "claudecompiler.y"
             { }
#line 1962 "claudecompiler.tab.c"
    break;

  case 43: /* invalid_body_item: BOOL  */
#line 359 "claudecompiler.y"
         { }
#line 1968 "claudecompiler.tab.c"
    break;

  case 44: /* invalid_body_item: INT  */
#line 360 "claudecompiler.y"
        { }
#line 1974 "claudecompiler.tab.c"
    break;

  case 45: /* invalid_body_item: DOUBLE  */
#line 361 "claudecompiler.y"
           { }
#line 1980 "claudecompiler.tab.c"
    break;

  case 46: /* invalid_body_item: VOID  */
#line 362 "claudecompiler.y"
         { }
#line 1986 "claudecompiler.tab.c"
    break;

  case 47: /* invalid_body_item: STRING  */
#line 363 "claudecompiler.y"
           { }
#line 1992 "claudecompiler.tab.c"
    break;

  case 48: /* invalid_body_item: IF  */
#line 364 "claudecompiler.y"
       { }
#line 1998 "claudecompiler.tab.c"
    break;

  case 49: /* invalid_body_item: ELSE  */
#line 365 "claudecompiler.y"
         { }
#line 2004 "claudecompiler.tab.c"
    break;

  case 50: /* invalid_body_item: WHILE  */
#line 366 "claudecompiler.y"
          { }
#line 2010 "claudecompiler.tab.c"
    break;

  case 51: /* invalid_body_item: RETURN  */
#line 367 "claudecompiler.y"
           { }
#line 2016 "claudecompiler.tab.c"
    break;

  case 52: /* invalid_body_item: PRINT  */
#line 368 "claudecompiler.y"
          { }
#line 2022 "claudecompiler.tab.c"
    break;

  case 53: /* invalid_body_item: PARSEINT  */
#line 369 "claudecompiler.y"
             { }
#line 2028 "claudecompiler.tab.c"
    break;

  case 54: /* invalid_body_item: DOTLENGTH  */
#line 370 "claudecompiler.y"
              { }
#line 2034 "claudecompiler.tab.c"
    break;

  case 55: /* invalid_body_item: INC  */
#line 371 "claudecompiler.y"
        { }
#line 2040 "claudecompiler.tab.c"
    break;

  case 56: /* invalid_body_item: DEC  */
#line 372 "claudecompiler.y"
        { }
#line 2046 "claudecompiler.tab.c"
    break;

  case 57: /* invalid_body_item: ARROW  */
#line 373 "claudecompiler.y"
          { }
#line 2052 "claudecompiler.tab.c"
    break;

  case 58: /* invalid_body_item: ASSIGN  */
#line 374 "claudecompiler.y"
           { }
#line 2058 "claudecompiler.tab.c"
    break;

  case 59: /* invalid_body_item: PLUS  */
#line 375 "claudecompiler.y"
         { }
#line 2064 "claudecompiler.tab.c"
    break;

  case 60: /* invalid_body_item: MINUS  */
#line 376 "claudecompiler.y"
          { }
#line 2070 "claudecompiler.tab.c"
    break;

  case 61: /* invalid_body_item: STAR  */
#line 377 "claudecompiler.y"
         { }
#line 2076 "claudecompiler.tab.c"
    break;

  case 62: /* invalid_body_item: DIV  */
#line 378 "claudecompiler.y"
        { }
#line 2082 "claudecompiler.tab.c"
    break;

  case 63: /* invalid_body_item: MOD  */
#line 379 "claudecompiler.y"
        { }
#line 2088 "claudecompiler.tab.c"
    break;

  case 64: /* invalid_body_item: AND  */
#line 380 "claudecompiler.y"
        { }
#line 2094 "claudecompiler.tab.c"
    break;

  case 65: /* invalid_body_item: OR  */
#line 381 "claudecompiler.y"
       { }
#line 2100 "claudecompiler.tab.c"
    break;

  case 66: /* invalid_body_item: XOR  */
#line 382 "claudecompiler.y"
        { }
#line 2106 "claudecompiler.tab.c"
    break;

  case 67: /* invalid_body_item: LSHIFT  */
#line 383 "claudecompiler.y"
           { }
#line 2112 "claudecompiler.tab.c"
    break;

  case 68: /* invalid_body_item: RSHIFT  */
#line 384 "claudecompiler.y"
           { }
#line 2118 "claudecompiler.tab.c"
    break;

  case 69: /* invalid_body_item: EQ  */
#line 385 "claudecompiler.y"
       { }
#line 2124 "claudecompiler.tab.c"
    break;

  case 70: /* invalid_body_item: NE  */
#line 386 "claudecompiler.y"
       { }
#line 2130 "claudecompiler.tab.c"
    break;

  case 71: /* invalid_body_item: LT  */
#line 387 "claudecompiler.y"
       { }
#line 2136 "claudecompiler.tab.c"
    break;

  case 72: /* invalid_body_item: GT  */
#line 388 "claudecompiler.y"
       { }
#line 2142 "claudecompiler.tab.c"
    break;

  case 73: /* invalid_body_item: LE  */
#line 389 "claudecompiler.y"
       { }
#line 2148 "claudecompiler.tab.c"
    break;

  case 74: /* invalid_body_item: GE  */
#line 390 "claudecompiler.y"
       { }
#line 2154 "claudecompiler.tab.c"
    break;

  case 75: /* invalid_body_item: NOT  */
#line 391 "claudecompiler.y"
        { }
#line 2160 "claudecompiler.tab.c"
    break;

  case 76: /* invalid_body_item: LPAR  */
#line 392 "claudecompiler.y"
         { }
#line 2166 "claudecompiler.tab.c"
    break;

  case 77: /* invalid_body_item: RPAR  */
#line 393 "claudecompiler.y"
         { }
#line 2172 "claudecompiler.tab.c"
    break;

  case 78: /* invalid_body_item: LSQ  */
#line 394 "claudecompiler.y"
        { }
#line 2178 "claudecompiler.tab.c"
    break;

  case 79: /* invalid_body_item: RSQ  */
#line 395 "claudecompiler.y"
        { }
#line 2184 "claudecompiler.tab.c"
    break;

  case 80: /* invalid_body_item: SEMICOLON  */
#line 396 "claudecompiler.y"
              { }
#line 2190 "claudecompiler.tab.c"
    break;

  case 81: /* invalid_body_item: COMMA  */
#line 397 "claudecompiler.y"
          { }
#line 2196 "claudecompiler.tab.c"
    break;

  case 82: /* method_body_items: %empty  */
#line 401 "claudecompiler.y"
    { (yyval.node) = make_holder(); }
#line 2202 "claudecompiler.tab.c"
    break;

  case 83: /* method_body_items: method_body_items invalid_public_decl  */
#line 402 "claudecompiler.y"
                                          {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2210 "claudecompiler.tab.c"
    break;

  case 84: /* method_body_items: method_body_items var_decl  */
#line 405 "claudecompiler.y"
                               {
        append_holder((yyvsp[-1].node), (yyvsp[0].node));
        free_holder_only((yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2220 "claudecompiler.tab.c"
    break;

  case 85: /* method_body_items: method_body_items bad_string_start bad_string_tail  */
#line 410 "claudecompiler.y"
                                                       {
        yyerrok;
        pending_error_after_block = 0;
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2230 "claudecompiler.tab.c"
    break;

  case 86: /* method_body_items: method_body_items stmt  */
#line 415 "claudecompiler.y"
                           {
        if (!is_empty_block((yyvsp[0].node)))
            addchild((yyvsp[-1].node), (yyvsp[0].node));

        (yyval.node) = (yyvsp[-1].node);
    }
#line 2241 "claudecompiler.tab.c"
    break;

  case 87: /* bad_string_start: STRING  */
#line 424 "claudecompiler.y"
           {
        if (token_line != last_lex_error_line) {
            syntax_errors = 1;
            printf("Line %d, col %d: syntax error: String\n", token_line, token_column);
            syntax_error_count++;
        }
        (yyval.node) = NULL;
    }
#line 2254 "claudecompiler.tab.c"
    break;

  case 140: /* $@4: %empty  */
#line 495 "claudecompiler.y"
           {
        saved_public_line = token_line;
        syntax_errors = 1;
        printf("Line %d, col 5: syntax error: public\n", saved_public_line);
        syntax_error_count++;
    }
#line 2265 "claudecompiler.tab.c"
    break;

  case 141: /* invalid_public_decl: PUBLIC $@4 invalid_public_tail  */
#line 500 "claudecompiler.y"
                          {
        pending_error_after_block = 0;
    }
#line 2273 "claudecompiler.tab.c"
    break;

  case 146: /* invalid_public_tail: STATIC error SEMICOLON  */
#line 510 "claudecompiler.y"
                           {
        yyerrok;
    }
#line 2281 "claudecompiler.tab.c"
    break;

  case 147: /* invalid_public_tail: error SEMICOLON  */
#line 513 "claudecompiler.y"
                    {
        yyerrok;
    }
#line 2289 "claudecompiler.tab.c"
    break;

  case 152: /* assign_save: ASSIGN  */
#line 529 "claudecompiler.y"
           {
        saved_error_line = token_line;
        saved_error_col = token_column;
    }
#line 2298 "claudecompiler.tab.c"
    break;

  case 153: /* var_decl: type var_ids SEMICOLON  */
#line 536 "claudecompiler.y"
                           {
        struct node_list *child;
        (yyval.node) = make_holder();
        child = (yyvsp[-1].node)->children->next;
        while (child) {
            struct node *decl = newnode(VarDecl, NULL);
            addchild(decl, clone_type_node((yyvsp[-2].node)));
            addchild(decl, newnode(Identifier, child->node->token));
            addchild((yyval.node), decl);
            child = child->next;
        }
        free_ast((yyvsp[-2].node));
        free_ast((yyvsp[-1].node));
    }
#line 2317 "claudecompiler.tab.c"
    break;

  case 154: /* var_decl: type IDENTIFIER LSQ expr RSQ SEMICOLON  */
#line 550 "claudecompiler.y"
                                           {
      (yyval.node) = make_holder();
  }
#line 2325 "claudecompiler.tab.c"
    break;

  case 155: /* var_decl: type IDENTIFIER assign_save expr SEMICOLON  */
#line 553 "claudecompiler.y"
                                                 {
      syntax_errors = 1;
      printf("Line %d, col %d: syntax error: =\n", saved_error_line, saved_error_col);
      syntax_error_count++;
      (yyval.node) = make_holder();
  }
#line 2336 "claudecompiler.tab.c"
    break;

  case 156: /* var_decl: type var_ids error  */
#line 559 "claudecompiler.y"
                       {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 2345 "claudecompiler.tab.c"
    break;

  case 157: /* var_decl: type error SEMICOLON  */
#line 563 "claudecompiler.y"
                         {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 2354 "claudecompiler.tab.c"
    break;

  case 158: /* var_ids: IDENTIFIER  */
#line 570 "claudecompiler.y"
               {
        (yyval.node) = make_holder();
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 2363 "claudecompiler.tab.c"
    break;

  case 159: /* var_ids: var_ids COMMA IDENTIFIER  */
#line 574 "claudecompiler.y"
                             {
        addchild((yyvsp[-2].node), newnode(Identifier, (yyvsp[0].lexeme)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2372 "claudecompiler.tab.c"
    break;

  case 160: /* stmt: stmt_entry stmt_core  */
#line 581 "claudecompiler.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2378 "claudecompiler.tab.c"
    break;

  case 161: /* stmt_entry: %empty  */
#line 585 "claudecompiler.y"
    {
        if (pending_error_after_block) {
            pending_error_after_block = 0;

            if (yychar != RBRACE &&
                yychar != IF &&
                yychar != WHILE &&
                yychar != RETURN &&
                yychar != PRINT &&
                yychar != SEMICOLON) {
                yyerror("syntax error");
            }
        }

        (yyval.node) = NULL;
    }
#line 2399 "claudecompiler.tab.c"
    break;

  case 162: /* stmt_core: LBRACE stmt_list RBRACE  */
#line 604 "claudecompiler.y"
                            {
    (yyval.node) = build_block_from_holder((yyvsp[-1].node));
}
#line 2407 "claudecompiler.tab.c"
    break;

  case 163: /* stmt_core: IF LPAR expr RPAR stmt  */
#line 607 "claudecompiler.y"
                                                 {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 2418 "claudecompiler.tab.c"
    break;

  case 164: /* stmt_core: IF LPAR expr RPAR stmt ELSE stmt  */
#line 613 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2429 "claudecompiler.tab.c"
    break;

  case 165: /* stmt_core: IF LPAR error RPAR stmt  */
#line 619 "claudecompiler.y"
                                                  {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 2441 "claudecompiler.tab.c"
    break;

  case 166: /* stmt_core: IF LPAR error RPAR stmt ELSE stmt  */
#line 626 "claudecompiler.y"
                                      {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2453 "claudecompiler.tab.c"
    break;

  case 167: /* stmt_core: IF LPAR expr error stmt  */
#line 633 "claudecompiler.y"
                                                  {
        yyerrok;
        pending_error_after_block = 1;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 2466 "claudecompiler.tab.c"
    break;

  case 168: /* stmt_core: IF LPAR expr error stmt ELSE stmt  */
#line 641 "claudecompiler.y"
                                      {
        yyerrok;
        pending_error_after_block = 1;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2479 "claudecompiler.tab.c"
    break;

  case 169: /* stmt_core: WHILE LPAR expr RPAR stmt  */
#line 649 "claudecompiler.y"
                              {
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2489 "claudecompiler.tab.c"
    break;

  case 170: /* stmt_core: WHILE LPAR error RPAR stmt  */
#line 654 "claudecompiler.y"
                               {
        yyerrok;
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2500 "claudecompiler.tab.c"
    break;

  case 171: /* stmt_core: WHILE LPAR expr error stmt  */
#line 660 "claudecompiler.y"
                               {
        yyerrok;
        pending_error_after_block = 1;
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2512 "claudecompiler.tab.c"
    break;

  case 172: /* stmt_core: RETURN expr SEMICOLON  */
#line 667 "claudecompiler.y"
                          {
        (yyval.node) = newnode(Return, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 2521 "claudecompiler.tab.c"
    break;

  case 173: /* stmt_core: RETURN SEMICOLON  */
#line 671 "claudecompiler.y"
                     {
        (yyval.node) = newnode(Return, NULL);
    }
#line 2529 "claudecompiler.tab.c"
    break;

  case 174: /* stmt_core: RETURN error SEMICOLON  */
#line 674 "claudecompiler.y"
                           {
        yyerrok;
        (yyval.node) = newnode(Return, NULL);
    }
#line 2538 "claudecompiler.tab.c"
    break;

  case 175: /* stmt_core: IDENTIFIER IDENTIFIER RESERVED ASSIGN expr SEMICOLON  */
#line 678 "claudecompiler.y"
                                                         {
        (yyval.node) = newnode(Block, NULL);
    }
#line 2546 "claudecompiler.tab.c"
    break;

  case 176: /* stmt_core: IDENTIFIER ASSIGN PARSEINT LPAR expr RPAR SEMICOLON  */
#line 681 "claudecompiler.y"
                                                          {
      (yyval.node) = newnode(Block, NULL);
  }
#line 2554 "claudecompiler.tab.c"
    break;

  case 177: /* stmt_core: IDENTIFIER ASSIGN expr SEMICOLON  */
#line 684 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(Assign, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 2564 "claudecompiler.tab.c"
    break;

  case 178: /* stmt_core: IDENTIFIER ASSIGN error SEMICOLON  */
#line 689 "claudecompiler.y"
                                      {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2573 "claudecompiler.tab.c"
    break;

  case 179: /* stmt_core: IDENTIFIER ASSIGN DOTLENGTH IDENTIFIER LPAR expr RPAR SEMICOLON  */
#line 693 "claudecompiler.y"
                                                                    {
        (yyval.node) = newnode(Block, NULL);
    }
#line 2581 "claudecompiler.tab.c"
    break;

  case 180: /* stmt_core: PRINT LPAR expr RPAR SEMICOLON  */
#line 696 "claudecompiler.y"
                                   {
        (yyval.node) = newnode(Print, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 2590 "claudecompiler.tab.c"
    break;

  case 181: /* stmt_core: PRINT LPAR STRLIT RPAR SEMICOLON  */
#line 700 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(Print, NULL);
        addchild((yyval.node), newnode(StrLit, (yyvsp[-2].lexeme)));
    }
#line 2599 "claudecompiler.tab.c"
    break;

  case 182: /* stmt_core: PRINT LPAR error RPAR SEMICOLON  */
#line 704 "claudecompiler.y"
                                    {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2608 "claudecompiler.tab.c"
    break;

  case 183: /* stmt_core: method_invocation SEMICOLON  */
#line 708 "claudecompiler.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 2614 "claudecompiler.tab.c"
    break;

  case 184: /* stmt_core: PARSEINT LPAR error RPAR RPAR SEMICOLON  */
#line 709 "claudecompiler.y"
                                              {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2623 "claudecompiler.tab.c"
    break;

  case 185: /* stmt_core: parse_args SEMICOLON  */
#line 713 "claudecompiler.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2629 "claudecompiler.tab.c"
    break;

  case 186: /* stmt_core: SEMICOLON  */
#line 714 "claudecompiler.y"
              {
        (yyval.node) = newnode(Block, NULL);
    }
#line 2637 "claudecompiler.tab.c"
    break;

  case 187: /* stmt_core: error SEMICOLON  */
#line 717 "claudecompiler.y"
                    {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2646 "claudecompiler.tab.c"
    break;

  case 188: /* stmt_list: %empty  */
#line 724 "claudecompiler.y"
    { (yyval.node) = make_holder(); }
#line 2652 "claudecompiler.tab.c"
    break;

  case 189: /* stmt_list: stmt_list stmt  */
#line 725 "claudecompiler.y"
                   {
        if (!is_empty_block((yyvsp[0].node)))
            addchild((yyvsp[-1].node), (yyvsp[0].node));

        (yyval.node) = (yyvsp[-1].node);
    }
#line 2663 "claudecompiler.tab.c"
    break;

  case 191: /* assign_expr: IDENTIFIER ASSIGN assign_expr  */
#line 738 "claudecompiler.y"
                                  {
        (yyval.node) = newnode(Assign, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2673 "claudecompiler.tab.c"
    break;

  case 193: /* or_expr: or_expr OR and_expr  */
#line 747 "claudecompiler.y"
                        {
        (yyval.node) = newnode(Or, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2683 "claudecompiler.tab.c"
    break;

  case 195: /* and_expr: and_expr AND xor_expr  */
#line 756 "claudecompiler.y"
                          {
        (yyval.node) = newnode(And, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2693 "claudecompiler.tab.c"
    break;

  case 197: /* xor_expr: xor_expr XOR eq_expr  */
#line 765 "claudecompiler.y"
                         {
        (yyval.node) = newnode(Xor, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2703 "claudecompiler.tab.c"
    break;

  case 199: /* eq_expr: eq_expr EQ rel_expr  */
#line 774 "claudecompiler.y"
                        {
        (yyval.node) = newnode(Eq, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2713 "claudecompiler.tab.c"
    break;

  case 200: /* eq_expr: eq_expr NE rel_expr  */
#line 779 "claudecompiler.y"
                        {
        (yyval.node) = newnode(Ne, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2723 "claudecompiler.tab.c"
    break;

  case 202: /* rel_expr: rel_expr LT shift_expr  */
#line 788 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Lt, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2733 "claudecompiler.tab.c"
    break;

  case 203: /* rel_expr: rel_expr GT shift_expr  */
#line 793 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Gt, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2743 "claudecompiler.tab.c"
    break;

  case 204: /* rel_expr: rel_expr LE shift_expr  */
#line 798 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Le, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2753 "claudecompiler.tab.c"
    break;

  case 205: /* rel_expr: rel_expr GE shift_expr  */
#line 803 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Ge, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2763 "claudecompiler.tab.c"
    break;

  case 207: /* shift_expr: shift_expr LSHIFT add_expr  */
#line 812 "claudecompiler.y"
                               {
        (yyval.node) = newnode(Lshift, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2773 "claudecompiler.tab.c"
    break;

  case 208: /* shift_expr: shift_expr RSHIFT add_expr  */
#line 817 "claudecompiler.y"
                               {
        (yyval.node) = newnode(Rshift, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2783 "claudecompiler.tab.c"
    break;

  case 210: /* add_expr: add_expr PLUS mul_expr  */
#line 826 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Add, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2793 "claudecompiler.tab.c"
    break;

  case 211: /* add_expr: add_expr MINUS mul_expr  */
#line 831 "claudecompiler.y"
                            {
        (yyval.node) = newnode(Sub, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2803 "claudecompiler.tab.c"
    break;

  case 213: /* mul_expr: mul_expr STAR unary_expr  */
#line 840 "claudecompiler.y"
                             {
        (yyval.node) = newnode(Mul, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2813 "claudecompiler.tab.c"
    break;

  case 214: /* mul_expr: mul_expr DIV unary_expr  */
#line 845 "claudecompiler.y"
                            {
        (yyval.node) = newnode(Div, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2823 "claudecompiler.tab.c"
    break;

  case 215: /* mul_expr: mul_expr MOD unary_expr  */
#line 850 "claudecompiler.y"
                            {
        (yyval.node) = newnode(Mod, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2833 "claudecompiler.tab.c"
    break;

  case 217: /* unary_expr: NOT unary_expr  */
#line 859 "claudecompiler.y"
                   {
        (yyval.node) = newnode(Not, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2842 "claudecompiler.tab.c"
    break;

  case 218: /* unary_expr: MINUS unary_expr  */
#line 863 "claudecompiler.y"
                     {
        (yyval.node) = newnode(Minus, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2851 "claudecompiler.tab.c"
    break;

  case 219: /* unary_expr: PLUS unary_expr  */
#line 867 "claudecompiler.y"
                    {
        (yyval.node) = newnode(Plus, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2860 "claudecompiler.tab.c"
    break;

  case 221: /* primary_expr: IDENTIFIER  */
#line 875 "claudecompiler.y"
               {
        (yyval.node) = newnode(Identifier, (yyvsp[0].lexeme));
    }
#line 2868 "claudecompiler.tab.c"
    break;

  case 222: /* primary_expr: IDENTIFIER DOTLENGTH  */
#line 878 "claudecompiler.y"
                         {
        (yyval.node) = newnode(Length, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-1].lexeme)));
    }
#line 2877 "claudecompiler.tab.c"
    break;

  case 223: /* primary_expr: NATURAL  */
#line 882 "claudecompiler.y"
            {
        (yyval.node) = newnode(Natural, (yyvsp[0].lexeme));
    }
#line 2885 "claudecompiler.tab.c"
    break;

  case 224: /* primary_expr: DECIMAL  */
#line 885 "claudecompiler.y"
            {
        (yyval.node) = newnode(Decimal, (yyvsp[0].lexeme));
    }
#line 2893 "claudecompiler.tab.c"
    break;

  case 225: /* primary_expr: BOOLLIT  */
#line 888 "claudecompiler.y"
            {
        (yyval.node) = newnode(BoolLit, (yyvsp[0].lexeme));
    }
#line 2901 "claudecompiler.tab.c"
    break;

  case 228: /* primary_expr: LPAR expr RPAR  */
#line 893 "claudecompiler.y"
                   { (yyval.node) = (yyvsp[-1].node); }
#line 2907 "claudecompiler.tab.c"
    break;

  case 229: /* primary_expr: LPAR error RPAR  */
#line 894 "claudecompiler.y"
                    {
        yyerrok;
        (yyval.node) = newnode(Natural, "0");
    }
#line 2916 "claudecompiler.tab.c"
    break;

  case 230: /* method_invocation: IDENTIFIER LPAR args_opt RPAR  */
#line 901 "claudecompiler.y"
                                  {
        (yyval.node) = newnode(Call, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        append_holder((yyval.node), (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));
    }
#line 2927 "claudecompiler.tab.c"
    break;

  case 231: /* method_invocation: IDENTIFIER LPAR error RPAR  */
#line 907 "claudecompiler.y"
                               {
        yyerrok;
        (yyval.node) = newnode(Call, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
    }
#line 2937 "claudecompiler.tab.c"
    break;

  case 232: /* args_opt: %empty  */
#line 915 "claudecompiler.y"
    { (yyval.node) = make_holder(); }
#line 2943 "claudecompiler.tab.c"
    break;

  case 234: /* expr_list: expr  */
#line 920 "claudecompiler.y"
         {
        (yyval.node) = make_holder();
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2952 "claudecompiler.tab.c"
    break;

  case 235: /* expr_list: expr_list COMMA expr  */
#line 924 "claudecompiler.y"
                         {
        addchild((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2961 "claudecompiler.tab.c"
    break;

  case 236: /* expr_list: expr_list COMMA error  */
#line 928 "claudecompiler.y"
                          {
        yyerrok;
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2970 "claudecompiler.tab.c"
    break;

  case 237: /* parse_args: PARSEINT LPAR IDENTIFIER LSQ expr RSQ RPAR  */
#line 935 "claudecompiler.y"
                                               {
        (yyval.node) = newnode(ParseArgs, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-4].lexeme)));
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 2980 "claudecompiler.tab.c"
    break;

  case 238: /* parse_args: PARSEINT LPAR error RPAR  */
#line 940 "claudecompiler.y"
                             {
        yyerrok;
        (yyval.node) = newnode(ParseArgs, NULL);
    }
#line 2989 "claudecompiler.tab.c"
    break;

  case 239: /* type: INT  */
#line 947 "claudecompiler.y"
        { (yyval.node) = newnode(Int, NULL); }
#line 2995 "claudecompiler.tab.c"
    break;

  case 240: /* type: DOUBLE  */
#line 948 "claudecompiler.y"
           { (yyval.node) = newnode(Double, NULL); }
#line 3001 "claudecompiler.tab.c"
    break;

  case 241: /* type: BOOL  */
#line 949 "claudecompiler.y"
         { (yyval.node) = newnode(Bool, NULL); }
#line 3007 "claudecompiler.tab.c"
    break;


#line 3011 "claudecompiler.tab.c"

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

#line 952 "claudecompiler.y"


int main(int argc, char **argv) {
    int lex_only = 0;
    if (argc > 1) {
        if (strcmp(argv[1], "-l") == 0) { lex_only = 1; print_tokens = 1; }
        if (strcmp(argv[1], "-e1") == 0) { lex_only = 1; }
        if (strcmp(argv[1], "-t") == 0) { print_tree = 1; }
        if (strcmp(argv[1], "-e2") == 0) { only_errors = 1; }
    }
    if (lex_only) { while (yylex()) ; return 0; }
    yyparse();
    if (!syntax_errors && print_tree && ast) print_ast(ast, 0);
    if (ast) free_ast(ast);
    return 0;
}

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
int recovering_string_error = 0;
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
    if (recovering_string_error) return;
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
  YYSYMBOL_72_4 = 72,                      /* $@4  */
  YYSYMBOL_bad_string_tail = 73,           /* bad_string_tail  */
  YYSYMBOL_bad_string_items = 74,          /* bad_string_items  */
  YYSYMBOL_bad_string_item = 75,           /* bad_string_item  */
  YYSYMBOL_bad_string_after = 76,          /* bad_string_after  */
  YYSYMBOL_invalid_public_decl = 77,       /* invalid_public_decl  */
  YYSYMBOL_78_5 = 78,                      /* $@5  */
  YYSYMBOL_invalid_public_tail = 79,       /* invalid_public_tail  */
  YYSYMBOL_invalid_id_list = 80,           /* invalid_id_list  */
  YYSYMBOL_semis = 81,                     /* semis  */
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
#define YYLAST   603

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  244
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  413

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
       0,   162,   162,   172,   173,   178,   182,   186,   200,   204,
     208,   215,   219,   226,   233,   233,   249,   249,   260,   260,
     274,   280,   286,   292,   301,   305,   312,   317,   322,   330,
     340,   345,   346,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   402,   403,   406,   411,   411,   424,   433,   436,
     438,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     493,   494,   495,   496,   497,   501,   501,   512,   513,   514,
     515,   516,   519,   525,   526,   530,   531,   535,   549,   552,
     556,   563,   567,   574,   578,   597,   602,   608,   614,   621,
     628,   636,   644,   649,   655,   662,   666,   669,   673,   676,
     681,   685,   688,   692,   696,   700,   701,   705,   706,   709,
     716,   717,   726,   730,   735,   739,   744,   748,   753,   757,
     762,   766,   771,   776,   780,   785,   790,   795,   800,   804,
     809,   814,   818,   823,   828,   832,   837,   842,   847,   851,
     855,   859,   863,   867,   870,   874,   877,   880,   883,   884,
     885,   886,   893,   899,   907,   908,   912,   916,   920,   927,
     932,   935,   942,   943,   944
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
  "method_body_items", "$@4", "bad_string_tail", "bad_string_items",
  "bad_string_item", "bad_string_after", "invalid_public_decl", "$@5",
  "invalid_public_tail", "invalid_id_list", "semis", "var_decl", "var_ids",
  "stmt", "stmt_entry", "stmt_core", "stmt_list", "expr", "assign_expr",
  "or_expr", "and_expr", "xor_expr", "eq_expr", "rel_expr", "shift_expr",
  "add_expr", "mul_expr", "unary_expr", "primary_expr",
  "method_invocation", "args_opt", "expr_list", "parse_args", "type", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-347)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-235)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      34,    42,    53,    29,  -347,  -347,    11,    79,  -347,  -347,
     125,  -347,  -347,  -347,   273,    87,  -347,  -347,  -347,   153,
     114,   188,  -347,   119,  -347,  -347,   120,   133,   159,   142,
     163,  -347,   158,   189,  -347,   150,   164,  -347,  -347,    -9,
    -347,   244,  -347,  -347,  -347,  -347,  -347,  -347,    30,   216,
     222,  -347,    27,  -347,  -347,     6,   226,  -347,   227,  -347,
    -347,    23,   209,     8,   237,   257,    16,   271,   275,  -347,
    -347,  -347,   277,   283,   288,   293,    17,  -347,  -347,   298,
     296,   343,   334,  -347,  -347,    80,   302,   212,  -347,  -347,
     340,   193,   137,   245,   250,   303,   157,  -347,  -347,  -347,
     307,   541,   541,   541,   255,  -347,   305,  -347,   323,   326,
     325,   130,    39,   228,   252,   261,  -347,  -347,  -347,  -347,
     201,   299,   313,  -347,  -347,  -347,   546,  -347,   358,  -347,
     298,  -347,  -347,   359,  -347,   360,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
       2,  -347,  -347,  -347,  -347,  -347,  -347,  -347,   312,   362,
     363,   114,   364,   342,   317,   367,   319,   327,  -347,   328,
     324,   330,    21,   331,    25,  -347,  -347,   546,   304,     3,
    -347,  -347,  -347,   332,   333,  -347,   541,   541,   541,   541,
     541,   541,   541,   541,   541,   541,   541,   541,   541,   541,
     541,   541,   336,   337,   338,   339,    13,   341,  -347,  -347,
     390,  -347,  -347,   388,  -347,   344,   439,    45,     2,  -347,
     382,  -347,   446,   191,   361,  -347,   497,   546,  -347,   503,
    -347,  -347,  -347,   309,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,   507,  -347,  -347,   326,   325,   130,    39,    39,   228,
     228,   228,   228,   252,   252,   261,   261,  -347,  -347,  -347,
     502,   504,   505,   510,   546,  -347,   506,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,   114,  -347,
     385,   556,  -347,   534,   173,   558,  -347,   511,   559,   220,
     512,   546,  -347,  -347,   549,   553,   554,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,   520,   526,  -347,   490,  -347,   524,
     525,   575,  -347,  -347,   527,  -347,   535,  -347,  -347,  -347,
    -347,   536,  -347,     2,     2,   530,   243,   531,  -347,  -347,
    -347,  -347,  -347,  -347,     2,   577,  -347,  -347,   573,   585,
    -347,   191,   511
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     0,     2,     6,
       0,     4,     5,    10,     0,     0,   244,   242,   243,     0,
       0,     0,     8,     0,    82,    13,     0,    11,     0,     0,
     164,     9,     0,     0,     7,     0,     0,    22,    14,     0,
      24,     0,    85,    29,   145,    83,    84,    87,     0,     0,
       0,    20,     0,    12,    18,     0,     0,    23,     0,    26,
      89,     0,     0,     0,     0,     0,     0,     0,     0,   190,
     188,   163,     0,     0,     0,   161,     0,    16,    21,     0,
       0,     0,     0,    25,    86,     0,     0,     0,   146,   189,
       0,     0,     0,     0,     0,     0,   223,   225,   226,   227,
       0,     0,     0,     0,     0,   176,     0,   192,   194,   196,
     198,   200,   203,   208,   211,   214,   218,   222,   228,   229,
       0,     0,   164,   185,   187,   160,     0,   159,     0,   157,
       0,    31,    19,     0,    27,     0,    91,    92,    93,    94,
      95,    96,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,    89,
     140,   136,   137,   139,   138,    97,    90,   152,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   236,     0,
     235,     0,     0,     0,     0,   177,   224,     0,     0,   223,
     221,   220,   219,     0,     0,   175,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   223,     0,   165,   191,
       0,   162,    17,     0,    28,     0,     0,     0,   140,    88,
       0,   151,   153,     0,     0,   150,     0,     0,   180,     0,
     179,   233,   232,     0,   164,   164,   164,   164,   164,   164,
     193,     0,   231,   230,   195,   197,   199,   201,   202,   204,
     205,   206,   207,   209,   210,   212,   213,   215,   216,   217,
       0,     0,     0,   241,     0,   240,     0,    34,    35,    36,
      37,    38,    39,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      31,    30,    78,    79,    81,    80,    40,    32,     0,   135,
       0,     0,   144,     0,     0,     0,   155,   149,     0,     0,
       0,     0,   238,   237,   168,   170,   166,   173,   174,   172,
     241,   184,   183,   182,     0,     0,   158,     0,    15,     0,
       0,     0,   154,   156,     0,   178,     0,   164,   164,   164,
     186,     0,    33,   140,   140,     0,   148,     0,   169,   171,
     167,   239,   142,   143,   140,     0,   181,   141,     0,     0,
     153,     0,   147
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,   508,
     -31,   533,  -187,   462,   253,  -347,  -347,  -347,  -347,   415,
    -347,  -242,  -347,  -347,  -347,   187,  -346,  -347,  -347,  -119,
    -347,  -347,  -347,   -64,   391,  -347,   381,   383,   384,    98,
     100,   108,   111,   -94,  -347,   551,  -347,  -347,   555,   -14
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     6,    11,    28,    12,    56,   130,    79,    20,
      39,    40,    25,   132,   243,   347,    30,    60,    84,    85,
     186,   249,    45,    61,    88,   253,   357,    46,    76,    47,
      48,    71,   122,   237,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   199,   200,   119,    41
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      21,    52,   106,   239,   255,   247,   352,   210,   211,   212,
      80,    90,     7,    16,    17,    18,    49,    95,   127,    96,
      97,    98,   265,    99,    86,   206,   268,   196,   198,   202,
     204,    62,    87,    63,    91,   206,    57,   100,   396,   207,
     214,    58,     1,   101,   102,     3,    64,    92,    65,    66,
      67,    68,    92,     4,   248,    81,   234,    92,     8,   103,
     104,   294,   240,     9,    10,   412,   266,   128,   105,   129,
     269,   350,    78,   192,   351,     5,    69,    58,   221,   222,
     223,   224,    70,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,    13,   184,   185,    14,   287,   288,   289,   197,    22,
      96,    97,    98,    35,    99,   364,   365,   366,   367,   368,
     369,   402,   403,    16,    17,    18,    23,    36,   100,    50,
      24,   378,   407,    29,   101,   102,   250,   219,   220,    16,
      17,    18,    31,    36,    16,    17,    18,    32,    42,   206,
     103,   104,  -234,   207,    16,    17,    18,    37,    36,    26,
      38,    27,    53,   360,   194,    54,    96,    97,    98,   363,
      99,    92,   232,    51,    96,    97,    98,   233,    99,    33,
      43,    34,    55,   188,   100,   195,    44,    74,    37,    75,
     101,   102,   100,    16,    17,    18,   189,   190,   101,   102,
     375,    16,    17,    18,   250,    36,   103,   104,    16,    17,
      18,   355,    36,   356,   103,   104,   201,    59,    96,    97,
      98,   203,    99,    96,    97,    98,   213,    99,    96,    97,
      98,    89,    99,   225,   226,    51,   100,    77,   398,   399,
     400,   100,   101,   102,    15,    82,   100,   101,   102,   227,
     228,    93,   101,   102,    16,    17,    18,    19,   103,   104,
     229,   230,   231,   103,   104,   383,   405,   386,   103,   104,
     235,    94,   236,    97,    98,   271,    99,   236,    97,    98,
     362,    99,    96,    97,    98,   120,    99,   277,   278,   121,
     100,   279,   280,   281,   282,   100,   101,   102,    52,   123,
     100,   101,   102,   283,   284,   124,   101,   102,   285,   286,
     125,   126,   103,   104,   131,   133,   134,   103,   104,   135,
     193,   208,   103,   104,   187,   205,   216,   215,   217,   218,
     238,   241,   244,   245,   251,   252,   254,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   267,   272,   273,   250,
     250,   290,   291,   292,   293,   353,   295,   358,   379,   348,
     250,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   296,
     345,   346,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   349,   181,   182,   183,
     354,   184,   185,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   392,   342,   343,
     344,   359,   345,   346,   209,    97,    98,   361,    99,    96,
      97,    98,   370,    99,   371,   374,   372,   373,   376,   380,
     381,   382,   100,   383,   385,   384,   387,   100,   101,   102,
     388,   389,   390,   101,   102,   391,   393,   394,   395,   356,
     397,   401,   404,   406,   103,   104,   408,   409,   410,   103,
     104,    83,   242,   377,   246,   191,   411,   274,   270,    72,
     275,     0,   276,    73
};

static const yytype_int16 yycheck[] =
{
      14,    32,    66,   122,   191,     3,   248,   101,   102,   103,
       4,     3,     1,    11,    12,    13,    30,     1,     1,     3,
       4,     5,     1,     7,     1,    22,     1,    91,    92,    93,
      94,     1,     9,     3,    26,    22,    45,    21,   384,    26,
     104,    50,     8,    27,    28,     3,    16,    44,    18,    19,
      20,    21,    44,     0,    52,    49,   120,    44,    47,    43,
      44,    48,   126,    52,    53,   411,    45,    50,    52,    52,
      45,    26,    45,    87,    29,    46,    46,    50,    39,    40,
      41,    42,    52,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    52,    52,    53,     9,   229,   230,   231,     1,    52,
       3,     4,     5,     1,     7,   264,   265,   266,   267,   268,
     269,   393,   394,    11,    12,    13,     3,    15,    21,     1,
      46,   348,   404,    44,    27,    28,   180,    37,    38,    11,
      12,    13,    52,    15,    11,    12,    13,    44,    15,    22,
      43,    44,    45,    26,    11,    12,    13,    45,    15,     1,
      48,     3,     3,   257,     1,    45,     3,     4,     5,   263,
       7,    44,     1,    45,     3,     4,     5,     6,     7,    50,
      47,    52,    48,     1,    21,    22,    53,     1,    45,     3,
      27,    28,    21,    11,    12,    13,    14,    15,    27,    28,
     294,    11,    12,    13,   248,    15,    43,    44,    11,    12,
      13,    50,    15,    52,    43,    44,     1,     3,     3,     4,
       5,     1,     7,     3,     4,     5,     1,     7,     3,     4,
       5,    52,     7,    35,    36,    45,    21,    45,   387,   388,
     389,    21,    27,    28,     1,    49,    21,    27,    28,    27,
      28,    44,    27,    28,    11,    12,    13,    14,    43,    44,
      29,    30,    31,    43,    44,    52,    53,   361,    43,    44,
       1,    44,     3,     4,     5,     1,     7,     3,     4,     5,
       1,     7,     3,     4,     5,    44,     7,   219,   220,    44,
      21,   221,   222,   223,   224,    21,    27,    28,   359,    52,
      21,    27,    28,   225,   226,    52,    27,    28,   227,   228,
      52,    48,    43,    44,    46,    49,     3,    43,    44,    15,
      10,    44,    43,    44,    52,    52,    33,    52,    32,    34,
      47,     3,     3,     3,    52,     3,     3,     3,    26,    52,
       3,    52,    45,    45,    50,    45,    45,    45,    45,   393,
     394,    45,    45,    45,    45,     3,    45,    26,     3,    45,
     404,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    49,
      52,    53,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      44,    52,    53,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    44,    52,    53,     3,     4,     5,    44,     7,     3,
       4,     5,    45,     7,    52,    45,    52,    52,    52,     3,
      26,     3,    21,    52,    52,     6,    17,    21,    27,    28,
      17,    17,    52,    27,    28,    49,    52,    52,     3,    52,
      45,    45,    52,    52,    43,    44,     9,    14,     3,    43,
      44,    58,   130,   340,   179,    87,   409,   216,   207,    48,
     217,    -1,   218,    48
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    56,     3,     0,    46,    57,     1,    47,    52,
      53,    58,    60,    52,     9,     1,    11,    12,    13,    14,
      64,   104,    52,     3,    46,    67,     1,     3,    59,    44,
      71,    52,    44,    50,    52,     1,    15,    45,    48,    65,
      66,   104,    15,    47,    53,    77,    82,    84,    85,   104,
       1,    45,    65,     3,    45,    48,    61,    45,    50,     3,
      72,    78,     1,     3,    16,    18,    19,    20,    21,    46,
      52,    86,   100,   103,     1,     3,    83,    45,    45,    63,
       4,    49,    49,    66,    73,    74,     1,     9,    79,    52,
       3,    26,    44,    44,    44,     1,     3,     4,     5,     7,
      21,    27,    28,    43,    44,    52,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   103,
      44,    44,    87,    52,    52,    52,    48,     1,    50,    52,
      62,    46,    68,    49,     3,    15,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    52,    53,    75,    52,     1,    14,
      15,    64,   104,    10,     1,    22,    88,     1,    88,   101,
     102,     1,    88,     1,    88,    52,    22,    26,    44,     3,
      98,    98,    98,     1,    88,    52,    33,    32,    34,    37,
      38,    39,    40,    41,    42,    35,    36,    27,    28,    29,
      30,    31,     1,     6,    88,     1,     3,    88,    47,    84,
      88,     3,    68,    69,     3,     3,    74,     3,    52,    76,
     104,    52,     3,    80,     3,    67,     3,    26,    52,     3,
      52,    45,    45,    50,    45,     1,    45,    45,     1,    45,
      89,     1,    45,    45,    91,    92,    93,    94,    94,    95,
      95,    95,    95,    96,    96,    97,    97,    98,    98,    98,
      45,    45,    45,    45,    48,    45,    49,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    52,    53,    70,    45,    47,
      26,    29,    76,     3,    44,    50,    52,    81,    26,    44,
      88,    44,     1,    88,    84,    84,    84,    84,    84,    84,
      45,    52,    52,    52,    45,    88,    52,    69,    67,     3,
       3,    26,     3,    52,     6,    52,    88,    17,    17,    17,
      52,    49,    47,    52,    52,     3,    81,    45,    84,    84,
      84,    45,    76,    76,    52,    53,    52,    76,     9,    14,
       3,    80,    81
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
      70,    70,    71,    71,    71,    72,    71,    71,    73,    74,
      74,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      76,    76,    76,    76,    76,    78,    77,    79,    79,    79,
      79,    79,    79,    80,    80,    81,    81,    82,    82,    82,
      82,    83,    83,    84,    85,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      87,    87,    88,    89,    89,    90,    90,    91,    91,    92,
      92,    93,    93,    93,    94,    94,    94,    94,    94,    95,
      95,    95,    96,    96,    96,    97,    97,    97,    97,    98,
      98,    98,    98,    99,    99,    99,    99,    99,    99,    99,
      99,    99,   100,   100,   101,   101,   102,   102,   102,   103,
     103,   103,   104,   104,   104
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
       1,     1,     0,     2,     2,     0,     4,     2,     3,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       0,     6,     5,     5,     2,     0,     3,    11,     6,     4,
       3,     3,     2,     1,     3,     1,     2,     3,     6,     3,
       3,     1,     3,     2,     0,     3,     5,     7,     5,     7,
       5,     7,     5,     5,     5,     3,     2,     3,     6,     4,
       4,     8,     5,     5,     5,     2,     6,     2,     1,     2,
       0,     2,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       3,     3,     4,     4,     0,     1,     1,     3,     3,     7,
       4,     4,     1,     1,     1
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
#line 162 "claudecompiler.y"
                                              {
        (yyval.node) = newnode(Program, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        append_holder((yyval.node), (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));
        ast = (yyval.node);
    }
#line 1622 "claudecompiler.tab.c"
    break;

  case 3: /* class_body: %empty  */
#line 172 "claudecompiler.y"
    { (yyval.node) = make_holder(); }
#line 1628 "claudecompiler.tab.c"
    break;

  case 4: /* class_body: class_body field_decl  */
#line 173 "claudecompiler.y"
                          {
        append_holder((yyvsp[-1].node), (yyvsp[0].node));
        free_holder_only((yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1638 "claudecompiler.tab.c"
    break;

  case 5: /* class_body: class_body method_decl  */
#line 178 "claudecompiler.y"
                           {
        addchild((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1647 "claudecompiler.tab.c"
    break;

  case 6: /* class_body: class_body SEMICOLON  */
#line 182 "claudecompiler.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 1653 "claudecompiler.tab.c"
    break;

  case 7: /* field_decl: PUBLIC STATIC type field_ids SEMICOLON  */
#line 186 "claudecompiler.y"
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
#line 1672 "claudecompiler.tab.c"
    break;

  case 8: /* field_decl: PUBLIC STATIC error SEMICOLON  */
#line 200 "claudecompiler.y"
                                  {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 1681 "claudecompiler.tab.c"
    break;

  case 9: /* field_decl: PUBLIC STATIC type error SEMICOLON  */
#line 204 "claudecompiler.y"
                                       {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 1690 "claudecompiler.tab.c"
    break;

  case 10: /* field_decl: error SEMICOLON  */
#line 208 "claudecompiler.y"
                    {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 1699 "claudecompiler.tab.c"
    break;

  case 11: /* field_ids: IDENTIFIER  */
#line 215 "claudecompiler.y"
               {
        (yyval.node) = make_holder();
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1708 "claudecompiler.tab.c"
    break;

  case 12: /* field_ids: field_ids COMMA IDENTIFIER  */
#line 219 "claudecompiler.y"
                               {
        addchild((yyvsp[-2].node), newnode(Identifier, (yyvsp[0].lexeme)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1717 "claudecompiler.tab.c"
    break;

  case 13: /* method_decl: PUBLIC STATIC method_header method_body  */
#line 226 "claudecompiler.y"
                                            {
        (yyval.node) = newnode(MethodDecl, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), (yyvsp[0].node));
        pending_error_after_block = 0;
        recovering_string_error = 0;
    }
#line 1729 "claudecompiler.tab.c"
    break;

  case 14: /* $@1: %empty  */
#line 233 "claudecompiler.y"
                                           {
        saved_error_line = token_line;
        saved_error_col = token_column;
    }
#line 1738 "claudecompiler.tab.c"
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
#line 1756 "claudecompiler.tab.c"
    break;

  case 16: /* $@2: %empty  */
#line 249 "claudecompiler.y"
                                                  {
        yyerrok;
    }
#line 1764 "claudecompiler.tab.c"
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
#line 1778 "claudecompiler.tab.c"
    break;

  case 18: /* $@3: %empty  */
#line 260 "claudecompiler.y"
                                                  {
        yyerrok;
    }
#line 1786 "claudecompiler.tab.c"
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
#line 1800 "claudecompiler.tab.c"
    break;

  case 20: /* method_header: type IDENTIFIER LPAR RPAR  */
#line 274 "claudecompiler.y"
                              {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), (yyvsp[-3].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), newnode(MethodParams, NULL));
    }
#line 1811 "claudecompiler.tab.c"
    break;

  case 21: /* method_header: type IDENTIFIER LPAR param_list RPAR  */
#line 280 "claudecompiler.y"
                                         {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1822 "claudecompiler.tab.c"
    break;

  case 22: /* method_header: VOID IDENTIFIER LPAR RPAR  */
#line 286 "claudecompiler.y"
                              {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), newnode(Void, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), newnode(MethodParams, NULL));
    }
#line 1833 "claudecompiler.tab.c"
    break;

  case 23: /* method_header: VOID IDENTIFIER LPAR param_list RPAR  */
#line 292 "claudecompiler.y"
                                         {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), newnode(Void, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1844 "claudecompiler.tab.c"
    break;

  case 24: /* param_list: param_decl  */
#line 301 "claudecompiler.y"
               {
        (yyval.node) = newnode(MethodParams, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1853 "claudecompiler.tab.c"
    break;

  case 25: /* param_list: param_list COMMA param_decl  */
#line 305 "claudecompiler.y"
                                {
        addchild((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1862 "claudecompiler.tab.c"
    break;

  case 26: /* param_decl: type IDENTIFIER  */
#line 312 "claudecompiler.y"
                    {
        (yyval.node) = newnode(ParamDecl, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1872 "claudecompiler.tab.c"
    break;

  case 27: /* param_decl: STRING LSQ RSQ IDENTIFIER  */
#line 317 "claudecompiler.y"
                              {
        (yyval.node) = newnode(ParamDecl, NULL);
        addchild((yyval.node), newnode(StringArray, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1882 "claudecompiler.tab.c"
    break;

  case 28: /* param_decl: STRING LSQ NATURAL RSQ IDENTIFIER  */
#line 322 "claudecompiler.y"
                                      {
        (yyval.node) = newnode(ParamDecl, NULL);
        addchild((yyval.node), newnode(StringArray, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1892 "claudecompiler.tab.c"
    break;

  case 29: /* method_body: LBRACE method_body_items RBRACE  */
#line 330 "claudecompiler.y"
                                    {
        (yyval.node) = newnode(MethodBody, NULL);
        append_holder((yyval.node), (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));
        pending_error_after_block = 0;
        recovering_string_error = 0;
    }
#line 1904 "claudecompiler.tab.c"
    break;

  case 30: /* invalid_method_body: LBRACE invalid_body_items RBRACE  */
#line 340 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(MethodBody, NULL);
    }
#line 1912 "claudecompiler.tab.c"
    break;

  case 33: /* invalid_body_item: LBRACE invalid_body_items RBRACE  */
#line 350 "claudecompiler.y"
                                     { }
#line 1918 "claudecompiler.tab.c"
    break;

  case 34: /* invalid_body_item: IDENTIFIER  */
#line 351 "claudecompiler.y"
               { }
#line 1924 "claudecompiler.tab.c"
    break;

  case 35: /* invalid_body_item: NATURAL  */
#line 352 "claudecompiler.y"
            { }
#line 1930 "claudecompiler.tab.c"
    break;

  case 36: /* invalid_body_item: DECIMAL  */
#line 353 "claudecompiler.y"
            { }
#line 1936 "claudecompiler.tab.c"
    break;

  case 37: /* invalid_body_item: STRLIT  */
#line 354 "claudecompiler.y"
           { }
#line 1942 "claudecompiler.tab.c"
    break;

  case 38: /* invalid_body_item: BOOLLIT  */
#line 355 "claudecompiler.y"
            { }
#line 1948 "claudecompiler.tab.c"
    break;

  case 39: /* invalid_body_item: CLASS  */
#line 356 "claudecompiler.y"
          { }
#line 1954 "claudecompiler.tab.c"
    break;

  case 40: /* invalid_body_item: PUBLIC  */
#line 357 "claudecompiler.y"
           { }
#line 1960 "claudecompiler.tab.c"
    break;

  case 41: /* invalid_body_item: STATIC  */
#line 358 "claudecompiler.y"
           { }
#line 1966 "claudecompiler.tab.c"
    break;

  case 42: /* invalid_body_item: RESERVED  */
#line 359 "claudecompiler.y"
             { }
#line 1972 "claudecompiler.tab.c"
    break;

  case 43: /* invalid_body_item: BOOL  */
#line 360 "claudecompiler.y"
         { }
#line 1978 "claudecompiler.tab.c"
    break;

  case 44: /* invalid_body_item: INT  */
#line 361 "claudecompiler.y"
        { }
#line 1984 "claudecompiler.tab.c"
    break;

  case 45: /* invalid_body_item: DOUBLE  */
#line 362 "claudecompiler.y"
           { }
#line 1990 "claudecompiler.tab.c"
    break;

  case 46: /* invalid_body_item: VOID  */
#line 363 "claudecompiler.y"
         { }
#line 1996 "claudecompiler.tab.c"
    break;

  case 47: /* invalid_body_item: STRING  */
#line 364 "claudecompiler.y"
           { }
#line 2002 "claudecompiler.tab.c"
    break;

  case 48: /* invalid_body_item: IF  */
#line 365 "claudecompiler.y"
       { }
#line 2008 "claudecompiler.tab.c"
    break;

  case 49: /* invalid_body_item: ELSE  */
#line 366 "claudecompiler.y"
         { }
#line 2014 "claudecompiler.tab.c"
    break;

  case 50: /* invalid_body_item: WHILE  */
#line 367 "claudecompiler.y"
          { }
#line 2020 "claudecompiler.tab.c"
    break;

  case 51: /* invalid_body_item: RETURN  */
#line 368 "claudecompiler.y"
           { }
#line 2026 "claudecompiler.tab.c"
    break;

  case 52: /* invalid_body_item: PRINT  */
#line 369 "claudecompiler.y"
          { }
#line 2032 "claudecompiler.tab.c"
    break;

  case 53: /* invalid_body_item: PARSEINT  */
#line 370 "claudecompiler.y"
             { }
#line 2038 "claudecompiler.tab.c"
    break;

  case 54: /* invalid_body_item: DOTLENGTH  */
#line 371 "claudecompiler.y"
              { }
#line 2044 "claudecompiler.tab.c"
    break;

  case 55: /* invalid_body_item: INC  */
#line 372 "claudecompiler.y"
        { }
#line 2050 "claudecompiler.tab.c"
    break;

  case 56: /* invalid_body_item: DEC  */
#line 373 "claudecompiler.y"
        { }
#line 2056 "claudecompiler.tab.c"
    break;

  case 57: /* invalid_body_item: ARROW  */
#line 374 "claudecompiler.y"
          { }
#line 2062 "claudecompiler.tab.c"
    break;

  case 58: /* invalid_body_item: ASSIGN  */
#line 375 "claudecompiler.y"
           { }
#line 2068 "claudecompiler.tab.c"
    break;

  case 59: /* invalid_body_item: PLUS  */
#line 376 "claudecompiler.y"
         { }
#line 2074 "claudecompiler.tab.c"
    break;

  case 60: /* invalid_body_item: MINUS  */
#line 377 "claudecompiler.y"
          { }
#line 2080 "claudecompiler.tab.c"
    break;

  case 61: /* invalid_body_item: STAR  */
#line 378 "claudecompiler.y"
         { }
#line 2086 "claudecompiler.tab.c"
    break;

  case 62: /* invalid_body_item: DIV  */
#line 379 "claudecompiler.y"
        { }
#line 2092 "claudecompiler.tab.c"
    break;

  case 63: /* invalid_body_item: MOD  */
#line 380 "claudecompiler.y"
        { }
#line 2098 "claudecompiler.tab.c"
    break;

  case 64: /* invalid_body_item: AND  */
#line 381 "claudecompiler.y"
        { }
#line 2104 "claudecompiler.tab.c"
    break;

  case 65: /* invalid_body_item: OR  */
#line 382 "claudecompiler.y"
       { }
#line 2110 "claudecompiler.tab.c"
    break;

  case 66: /* invalid_body_item: XOR  */
#line 383 "claudecompiler.y"
        { }
#line 2116 "claudecompiler.tab.c"
    break;

  case 67: /* invalid_body_item: LSHIFT  */
#line 384 "claudecompiler.y"
           { }
#line 2122 "claudecompiler.tab.c"
    break;

  case 68: /* invalid_body_item: RSHIFT  */
#line 385 "claudecompiler.y"
           { }
#line 2128 "claudecompiler.tab.c"
    break;

  case 69: /* invalid_body_item: EQ  */
#line 386 "claudecompiler.y"
       { }
#line 2134 "claudecompiler.tab.c"
    break;

  case 70: /* invalid_body_item: NE  */
#line 387 "claudecompiler.y"
       { }
#line 2140 "claudecompiler.tab.c"
    break;

  case 71: /* invalid_body_item: LT  */
#line 388 "claudecompiler.y"
       { }
#line 2146 "claudecompiler.tab.c"
    break;

  case 72: /* invalid_body_item: GT  */
#line 389 "claudecompiler.y"
       { }
#line 2152 "claudecompiler.tab.c"
    break;

  case 73: /* invalid_body_item: LE  */
#line 390 "claudecompiler.y"
       { }
#line 2158 "claudecompiler.tab.c"
    break;

  case 74: /* invalid_body_item: GE  */
#line 391 "claudecompiler.y"
       { }
#line 2164 "claudecompiler.tab.c"
    break;

  case 75: /* invalid_body_item: NOT  */
#line 392 "claudecompiler.y"
        { }
#line 2170 "claudecompiler.tab.c"
    break;

  case 76: /* invalid_body_item: LPAR  */
#line 393 "claudecompiler.y"
         { }
#line 2176 "claudecompiler.tab.c"
    break;

  case 77: /* invalid_body_item: RPAR  */
#line 394 "claudecompiler.y"
         { }
#line 2182 "claudecompiler.tab.c"
    break;

  case 78: /* invalid_body_item: LSQ  */
#line 395 "claudecompiler.y"
        { }
#line 2188 "claudecompiler.tab.c"
    break;

  case 79: /* invalid_body_item: RSQ  */
#line 396 "claudecompiler.y"
        { }
#line 2194 "claudecompiler.tab.c"
    break;

  case 80: /* invalid_body_item: SEMICOLON  */
#line 397 "claudecompiler.y"
              { }
#line 2200 "claudecompiler.tab.c"
    break;

  case 81: /* invalid_body_item: COMMA  */
#line 398 "claudecompiler.y"
          { }
#line 2206 "claudecompiler.tab.c"
    break;

  case 82: /* method_body_items: %empty  */
#line 402 "claudecompiler.y"
    { (yyval.node) = make_holder(); }
#line 2212 "claudecompiler.tab.c"
    break;

  case 83: /* method_body_items: method_body_items invalid_public_decl  */
#line 403 "claudecompiler.y"
                                          {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2220 "claudecompiler.tab.c"
    break;

  case 84: /* method_body_items: method_body_items var_decl  */
#line 406 "claudecompiler.y"
                               {
        append_holder((yyvsp[-1].node), (yyvsp[0].node));
        free_holder_only((yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2230 "claudecompiler.tab.c"
    break;

  case 85: /* $@4: %empty  */
#line 411 "claudecompiler.y"
                             {
        if (token_line != last_lex_error_line) {
            syntax_errors = 1;
            printf("Line %d, col %d: syntax error: String\n", token_line, token_column);
            syntax_error_count++;
        }
        recovering_string_error = 1;
    }
#line 2243 "claudecompiler.tab.c"
    break;

  case 86: /* method_body_items: method_body_items STRING $@4 bad_string_tail  */
#line 418 "claudecompiler.y"
                      {
        yyerrok;
        pending_error_after_block = 0;
        recovering_string_error = 0;
        (yyval.node) = (yyvsp[-3].node);
    }
#line 2254 "claudecompiler.tab.c"
    break;

  case 87: /* method_body_items: method_body_items stmt  */
#line 424 "claudecompiler.y"
                           {
        if (!is_empty_block((yyvsp[0].node)))
            addchild((yyvsp[-1].node), (yyvsp[0].node));

        (yyval.node) = (yyvsp[-1].node);
    }
#line 2265 "claudecompiler.tab.c"
    break;

  case 145: /* $@5: %empty  */
#line 501 "claudecompiler.y"
           {
        saved_public_line = token_line;
        syntax_errors = 1;
        printf("Line %d, col 5: syntax error: public\n", saved_public_line);
        syntax_error_count++;
    }
#line 2276 "claudecompiler.tab.c"
    break;

  case 146: /* invalid_public_decl: PUBLIC $@5 invalid_public_tail  */
#line 506 "claudecompiler.y"
                          {
        pending_error_after_block = 0;
    }
#line 2284 "claudecompiler.tab.c"
    break;

  case 151: /* invalid_public_tail: STATIC error SEMICOLON  */
#line 516 "claudecompiler.y"
                           {
        yyerrok;
    }
#line 2292 "claudecompiler.tab.c"
    break;

  case 152: /* invalid_public_tail: error SEMICOLON  */
#line 519 "claudecompiler.y"
                    {
        yyerrok;
    }
#line 2300 "claudecompiler.tab.c"
    break;

  case 157: /* var_decl: type var_ids SEMICOLON  */
#line 535 "claudecompiler.y"
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
#line 2319 "claudecompiler.tab.c"
    break;

  case 158: /* var_decl: type IDENTIFIER LSQ expr RSQ SEMICOLON  */
#line 549 "claudecompiler.y"
                                           {
        (yyval.node) = make_holder();
    }
#line 2327 "claudecompiler.tab.c"
    break;

  case 159: /* var_decl: type var_ids error  */
#line 552 "claudecompiler.y"
                       {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 2336 "claudecompiler.tab.c"
    break;

  case 160: /* var_decl: type error SEMICOLON  */
#line 556 "claudecompiler.y"
                         {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 2345 "claudecompiler.tab.c"
    break;

  case 161: /* var_ids: IDENTIFIER  */
#line 563 "claudecompiler.y"
               {
        (yyval.node) = make_holder();
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 2354 "claudecompiler.tab.c"
    break;

  case 162: /* var_ids: var_ids COMMA IDENTIFIER  */
#line 567 "claudecompiler.y"
                             {
        addchild((yyvsp[-2].node), newnode(Identifier, (yyvsp[0].lexeme)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2363 "claudecompiler.tab.c"
    break;

  case 163: /* stmt: stmt_entry stmt_core  */
#line 574 "claudecompiler.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2369 "claudecompiler.tab.c"
    break;

  case 164: /* stmt_entry: %empty  */
#line 578 "claudecompiler.y"
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
#line 2390 "claudecompiler.tab.c"
    break;

  case 165: /* stmt_core: LBRACE stmt_list RBRACE  */
#line 597 "claudecompiler.y"
                            {
        if (recovering_string_error)
            pending_error_after_block = 1;
        (yyval.node) = build_block_from_holder((yyvsp[-1].node));
    }
#line 2400 "claudecompiler.tab.c"
    break;

  case 166: /* stmt_core: IF LPAR expr RPAR stmt  */
#line 602 "claudecompiler.y"
                                                 {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 2411 "claudecompiler.tab.c"
    break;

  case 167: /* stmt_core: IF LPAR expr RPAR stmt ELSE stmt  */
#line 608 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2422 "claudecompiler.tab.c"
    break;

  case 168: /* stmt_core: IF LPAR error RPAR stmt  */
#line 614 "claudecompiler.y"
                                                  {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 2434 "claudecompiler.tab.c"
    break;

  case 169: /* stmt_core: IF LPAR error RPAR stmt ELSE stmt  */
#line 621 "claudecompiler.y"
                                      {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2446 "claudecompiler.tab.c"
    break;

  case 170: /* stmt_core: IF LPAR expr error stmt  */
#line 628 "claudecompiler.y"
                                                  {
        yyerrok;
        pending_error_after_block = 1;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 2459 "claudecompiler.tab.c"
    break;

  case 171: /* stmt_core: IF LPAR expr error stmt ELSE stmt  */
#line 636 "claudecompiler.y"
                                      {
        yyerrok;
        pending_error_after_block = 1;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2472 "claudecompiler.tab.c"
    break;

  case 172: /* stmt_core: WHILE LPAR expr RPAR stmt  */
#line 644 "claudecompiler.y"
                              {
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2482 "claudecompiler.tab.c"
    break;

  case 173: /* stmt_core: WHILE LPAR error RPAR stmt  */
#line 649 "claudecompiler.y"
                               {
        yyerrok;
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2493 "claudecompiler.tab.c"
    break;

  case 174: /* stmt_core: WHILE LPAR expr error stmt  */
#line 655 "claudecompiler.y"
                               {
        yyerrok;
        pending_error_after_block = 1;
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2505 "claudecompiler.tab.c"
    break;

  case 175: /* stmt_core: RETURN expr SEMICOLON  */
#line 662 "claudecompiler.y"
                          {
        (yyval.node) = newnode(Return, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 2514 "claudecompiler.tab.c"
    break;

  case 176: /* stmt_core: RETURN SEMICOLON  */
#line 666 "claudecompiler.y"
                     {
        (yyval.node) = newnode(Return, NULL);
    }
#line 2522 "claudecompiler.tab.c"
    break;

  case 177: /* stmt_core: RETURN error SEMICOLON  */
#line 669 "claudecompiler.y"
                           {
        yyerrok;
        (yyval.node) = newnode(Return, NULL);
    }
#line 2531 "claudecompiler.tab.c"
    break;

  case 178: /* stmt_core: IDENTIFIER IDENTIFIER RESERVED ASSIGN expr SEMICOLON  */
#line 673 "claudecompiler.y"
                                                         {
        (yyval.node) = newnode(Block, NULL);
    }
#line 2539 "claudecompiler.tab.c"
    break;

  case 179: /* stmt_core: IDENTIFIER ASSIGN expr SEMICOLON  */
#line 676 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(Assign, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 2549 "claudecompiler.tab.c"
    break;

  case 180: /* stmt_core: IDENTIFIER ASSIGN error SEMICOLON  */
#line 681 "claudecompiler.y"
                                      {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2558 "claudecompiler.tab.c"
    break;

  case 181: /* stmt_core: IDENTIFIER ASSIGN DOTLENGTH IDENTIFIER LPAR expr RPAR SEMICOLON  */
#line 685 "claudecompiler.y"
                                                                    {
        (yyval.node) = newnode(Block, NULL);
    }
#line 2566 "claudecompiler.tab.c"
    break;

  case 182: /* stmt_core: PRINT LPAR expr RPAR SEMICOLON  */
#line 688 "claudecompiler.y"
                                   {
        (yyval.node) = newnode(Print, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 2575 "claudecompiler.tab.c"
    break;

  case 183: /* stmt_core: PRINT LPAR STRLIT RPAR SEMICOLON  */
#line 692 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(Print, NULL);
        addchild((yyval.node), newnode(StrLit, (yyvsp[-2].lexeme)));
    }
#line 2584 "claudecompiler.tab.c"
    break;

  case 184: /* stmt_core: PRINT LPAR error RPAR SEMICOLON  */
#line 696 "claudecompiler.y"
                                    {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2593 "claudecompiler.tab.c"
    break;

  case 185: /* stmt_core: method_invocation SEMICOLON  */
#line 700 "claudecompiler.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 2599 "claudecompiler.tab.c"
    break;

  case 186: /* stmt_core: PARSEINT LPAR error RPAR RPAR SEMICOLON  */
#line 701 "claudecompiler.y"
                                              {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2608 "claudecompiler.tab.c"
    break;

  case 187: /* stmt_core: parse_args SEMICOLON  */
#line 705 "claudecompiler.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2614 "claudecompiler.tab.c"
    break;

  case 188: /* stmt_core: SEMICOLON  */
#line 706 "claudecompiler.y"
              {
        (yyval.node) = newnode(Block, NULL);
    }
#line 2622 "claudecompiler.tab.c"
    break;

  case 189: /* stmt_core: error SEMICOLON  */
#line 709 "claudecompiler.y"
                    {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2631 "claudecompiler.tab.c"
    break;

  case 190: /* stmt_list: %empty  */
#line 716 "claudecompiler.y"
    { (yyval.node) = make_holder(); }
#line 2637 "claudecompiler.tab.c"
    break;

  case 191: /* stmt_list: stmt_list stmt  */
#line 717 "claudecompiler.y"
                   {
        if (!is_empty_block((yyvsp[0].node)))
            addchild((yyvsp[-1].node), (yyvsp[0].node));

        (yyval.node) = (yyvsp[-1].node);
    }
#line 2648 "claudecompiler.tab.c"
    break;

  case 193: /* assign_expr: IDENTIFIER ASSIGN assign_expr  */
#line 730 "claudecompiler.y"
                                  {
        (yyval.node) = newnode(Assign, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2658 "claudecompiler.tab.c"
    break;

  case 195: /* or_expr: or_expr OR and_expr  */
#line 739 "claudecompiler.y"
                        {
        (yyval.node) = newnode(Or, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2668 "claudecompiler.tab.c"
    break;

  case 197: /* and_expr: and_expr AND xor_expr  */
#line 748 "claudecompiler.y"
                          {
        (yyval.node) = newnode(And, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2678 "claudecompiler.tab.c"
    break;

  case 199: /* xor_expr: xor_expr XOR eq_expr  */
#line 757 "claudecompiler.y"
                         {
        (yyval.node) = newnode(Xor, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2688 "claudecompiler.tab.c"
    break;

  case 201: /* eq_expr: eq_expr EQ rel_expr  */
#line 766 "claudecompiler.y"
                        {
        (yyval.node) = newnode(Eq, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2698 "claudecompiler.tab.c"
    break;

  case 202: /* eq_expr: eq_expr NE rel_expr  */
#line 771 "claudecompiler.y"
                        {
        (yyval.node) = newnode(Ne, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2708 "claudecompiler.tab.c"
    break;

  case 204: /* rel_expr: rel_expr LT shift_expr  */
#line 780 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Lt, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2718 "claudecompiler.tab.c"
    break;

  case 205: /* rel_expr: rel_expr GT shift_expr  */
#line 785 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Gt, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2728 "claudecompiler.tab.c"
    break;

  case 206: /* rel_expr: rel_expr LE shift_expr  */
#line 790 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Le, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2738 "claudecompiler.tab.c"
    break;

  case 207: /* rel_expr: rel_expr GE shift_expr  */
#line 795 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Ge, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2748 "claudecompiler.tab.c"
    break;

  case 209: /* shift_expr: shift_expr LSHIFT add_expr  */
#line 804 "claudecompiler.y"
                               {
        (yyval.node) = newnode(Lshift, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2758 "claudecompiler.tab.c"
    break;

  case 210: /* shift_expr: shift_expr RSHIFT add_expr  */
#line 809 "claudecompiler.y"
                               {
        (yyval.node) = newnode(Rshift, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2768 "claudecompiler.tab.c"
    break;

  case 212: /* add_expr: add_expr PLUS mul_expr  */
#line 818 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Add, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2778 "claudecompiler.tab.c"
    break;

  case 213: /* add_expr: add_expr MINUS mul_expr  */
#line 823 "claudecompiler.y"
                            {
        (yyval.node) = newnode(Sub, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2788 "claudecompiler.tab.c"
    break;

  case 215: /* mul_expr: mul_expr STAR unary_expr  */
#line 832 "claudecompiler.y"
                             {
        (yyval.node) = newnode(Mul, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2798 "claudecompiler.tab.c"
    break;

  case 216: /* mul_expr: mul_expr DIV unary_expr  */
#line 837 "claudecompiler.y"
                            {
        (yyval.node) = newnode(Div, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2808 "claudecompiler.tab.c"
    break;

  case 217: /* mul_expr: mul_expr MOD unary_expr  */
#line 842 "claudecompiler.y"
                            {
        (yyval.node) = newnode(Mod, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2818 "claudecompiler.tab.c"
    break;

  case 219: /* unary_expr: NOT unary_expr  */
#line 851 "claudecompiler.y"
                   {
        (yyval.node) = newnode(Not, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2827 "claudecompiler.tab.c"
    break;

  case 220: /* unary_expr: MINUS unary_expr  */
#line 855 "claudecompiler.y"
                     {
        (yyval.node) = newnode(Minus, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2836 "claudecompiler.tab.c"
    break;

  case 221: /* unary_expr: PLUS unary_expr  */
#line 859 "claudecompiler.y"
                    {
        (yyval.node) = newnode(Plus, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2845 "claudecompiler.tab.c"
    break;

  case 223: /* primary_expr: IDENTIFIER  */
#line 867 "claudecompiler.y"
               {
        (yyval.node) = newnode(Identifier, (yyvsp[0].lexeme));
    }
#line 2853 "claudecompiler.tab.c"
    break;

  case 224: /* primary_expr: IDENTIFIER DOTLENGTH  */
#line 870 "claudecompiler.y"
                         {
        (yyval.node) = newnode(Length, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-1].lexeme)));
    }
#line 2862 "claudecompiler.tab.c"
    break;

  case 225: /* primary_expr: NATURAL  */
#line 874 "claudecompiler.y"
            {
        (yyval.node) = newnode(Natural, (yyvsp[0].lexeme));
    }
#line 2870 "claudecompiler.tab.c"
    break;

  case 226: /* primary_expr: DECIMAL  */
#line 877 "claudecompiler.y"
            {
        (yyval.node) = newnode(Decimal, (yyvsp[0].lexeme));
    }
#line 2878 "claudecompiler.tab.c"
    break;

  case 227: /* primary_expr: BOOLLIT  */
#line 880 "claudecompiler.y"
            {
        (yyval.node) = newnode(BoolLit, (yyvsp[0].lexeme));
    }
#line 2886 "claudecompiler.tab.c"
    break;

  case 230: /* primary_expr: LPAR expr RPAR  */
#line 885 "claudecompiler.y"
                   { (yyval.node) = (yyvsp[-1].node); }
#line 2892 "claudecompiler.tab.c"
    break;

  case 231: /* primary_expr: LPAR error RPAR  */
#line 886 "claudecompiler.y"
                    {
        yyerrok;
        (yyval.node) = newnode(Natural, "0");
    }
#line 2901 "claudecompiler.tab.c"
    break;

  case 232: /* method_invocation: IDENTIFIER LPAR args_opt RPAR  */
#line 893 "claudecompiler.y"
                                  {
        (yyval.node) = newnode(Call, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        append_holder((yyval.node), (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));
    }
#line 2912 "claudecompiler.tab.c"
    break;

  case 233: /* method_invocation: IDENTIFIER LPAR error RPAR  */
#line 899 "claudecompiler.y"
                               {
        yyerrok;
        (yyval.node) = newnode(Call, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
    }
#line 2922 "claudecompiler.tab.c"
    break;

  case 234: /* args_opt: %empty  */
#line 907 "claudecompiler.y"
    { (yyval.node) = make_holder(); }
#line 2928 "claudecompiler.tab.c"
    break;

  case 236: /* expr_list: expr  */
#line 912 "claudecompiler.y"
         {
        (yyval.node) = make_holder();
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2937 "claudecompiler.tab.c"
    break;

  case 237: /* expr_list: expr_list COMMA expr  */
#line 916 "claudecompiler.y"
                         {
        addchild((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2946 "claudecompiler.tab.c"
    break;

  case 238: /* expr_list: expr_list COMMA error  */
#line 920 "claudecompiler.y"
                          {
        yyerrok;
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2955 "claudecompiler.tab.c"
    break;

  case 239: /* parse_args: PARSEINT LPAR IDENTIFIER LSQ expr RSQ RPAR  */
#line 927 "claudecompiler.y"
                                               {
        (yyval.node) = newnode(ParseArgs, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-4].lexeme)));
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 2965 "claudecompiler.tab.c"
    break;

  case 240: /* parse_args: PARSEINT LPAR expr RPAR  */
#line 932 "claudecompiler.y"
                            {
        (yyval.node) = newnode(ParseArgs, NULL);
    }
#line 2973 "claudecompiler.tab.c"
    break;

  case 241: /* parse_args: PARSEINT LPAR error RPAR  */
#line 935 "claudecompiler.y"
                             {
        yyerrok;
        (yyval.node) = newnode(ParseArgs, NULL);
    }
#line 2982 "claudecompiler.tab.c"
    break;

  case 242: /* type: INT  */
#line 942 "claudecompiler.y"
        { (yyval.node) = newnode(Int, NULL); }
#line 2988 "claudecompiler.tab.c"
    break;

  case 243: /* type: DOUBLE  */
#line 943 "claudecompiler.y"
           { (yyval.node) = newnode(Double, NULL); }
#line 2994 "claudecompiler.tab.c"
    break;

  case 244: /* type: BOOL  */
#line 944 "claudecompiler.y"
         { (yyval.node) = newnode(Bool, NULL); }
#line 3000 "claudecompiler.tab.c"
    break;


#line 3004 "claudecompiler.tab.c"

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

#line 947 "claudecompiler.y"


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

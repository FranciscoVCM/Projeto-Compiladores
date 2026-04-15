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
#line 1 "jucompiler.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex();
extern int line;
extern int column;
extern int token_line;
extern int token_column;
extern int print_tokens;
extern char *yytext;
extern char token_text[];
extern int last_lex_error_line;
extern int yychar;

struct node *ast = NULL;

int print_tree = 0;
int only_errors = 0;
int syntax_errors = 0;
int syntax_error_count = 0;

static struct node *clone_type_node(struct node *node) {
    if (!node)
        return NULL;
    return newnode(node->category, node->token);
}

static struct node *make_holder() {
    return newnode(Program, NULL);
}

static void append_holder(struct node *dst, struct node *src) {
    struct node_list *child;
    if (!dst || !src || !src->children)
        return;
    child = src->children->next;
    while (child) {
        addchild(dst, child->node);
        child = child->next;
    }
    src->children->next = NULL;
}

static int child_count(struct node *node) {
    int count = 0;
    struct node_list *child;

    if (!node || !node->children)
        return 0;

    child = node->children->next;
    while (child) {
        count++;
        child = child->next;
    }
    return count;
}

static int is_empty_block(struct node *node) {
    return node && node->category == Block && child_count(node) == 0;
}

static int meaningful_child_count(struct node *holder) {
    int count = 0;
    struct node_list *child;

    if (!holder || !holder->children)
        return 0;

    child = holder->children->next;
    while (child) {
        if (!is_empty_block(child->node))
            count++;
        child = child->next;
    }
    return count;
}

static struct node *first_meaningful_child(struct node *holder) {
    struct node_list *child;

    if (!holder || !holder->children)
        return NULL;

    child = holder->children->next;
    while (child) {
        if (!is_empty_block(child->node))
            return child->node;
        child = child->next;
    }
    return NULL;
}

static void append_meaningful_children(struct node *dst, struct node *src) {
    struct node_list *child;

    if (!dst || !src || !src->children)
        return;

    child = src->children->next;
    while (child) {
        if (!is_empty_block(child->node))
            addchild(dst, child->node);
        child = child->next;
    }
}

static void free_holder_only(struct node *node) {
    if (!node)
        return;
    if (node->children)
        free(node->children);
    free(node);
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
    syntax_errors = 1;

    if (only_errors)
        return;

    if (token_line == last_lex_error_line)
        return;

    if (yychar == 0 && syntax_error_count > 0)
        return;

    printf("Line %d, col %d: syntax error: %s\n", token_line, token_column, token_text);
    syntax_error_count++;
}


#line 229 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    NATURAL = 259,                 /* NATURAL  */
    DECIMAL = 260,                 /* DECIMAL  */
    STRLIT = 261,                  /* STRLIT  */
    BOOLLIT = 262,                 /* BOOLLIT  */
    CLASS = 263,                   /* CLASS  */
    PUBLIC = 264,                  /* PUBLIC  */
    STATIC = 265,                  /* STATIC  */
    RESERVED = 266,                /* RESERVED  */
    BOOL = 267,                    /* BOOL  */
    INT = 268,                     /* INT  */
    DOUBLE = 269,                  /* DOUBLE  */
    VOID = 270,                    /* VOID  */
    STRING = 271,                  /* STRING  */
    IF = 272,                      /* IF  */
    ELSE = 273,                    /* ELSE  */
    WHILE = 274,                   /* WHILE  */
    RETURN = 275,                  /* RETURN  */
    PRINT = 276,                   /* PRINT  */
    PARSEINT = 277,                /* PARSEINT  */
    DOTLENGTH = 278,               /* DOTLENGTH  */
    INC = 279,                     /* INC  */
    DEC = 280,                     /* DEC  */
    ARROW = 281,                   /* ARROW  */
    ASSIGN = 282,                  /* ASSIGN  */
    PLUS = 283,                    /* PLUS  */
    MINUS = 284,                   /* MINUS  */
    STAR = 285,                    /* STAR  */
    DIV = 286,                     /* DIV  */
    MOD = 287,                     /* MOD  */
    AND = 288,                     /* AND  */
    OR = 289,                      /* OR  */
    XOR = 290,                     /* XOR  */
    LSHIFT = 291,                  /* LSHIFT  */
    RSHIFT = 292,                  /* RSHIFT  */
    EQ = 293,                      /* EQ  */
    NE = 294,                      /* NE  */
    LT = 295,                      /* LT  */
    GT = 296,                      /* GT  */
    LE = 297,                      /* LE  */
    GE = 298,                      /* GE  */
    NOT = 299,                     /* NOT  */
    LPAR = 300,                    /* LPAR  */
    RPAR = 301,                    /* RPAR  */
    LBRACE = 302,                  /* LBRACE  */
    RBRACE = 303,                  /* RBRACE  */
    LSQ = 304,                     /* LSQ  */
    RSQ = 305,                     /* RSQ  */
    SEMICOLON = 306,               /* SEMICOLON  */
    COMMA = 307,                   /* COMMA  */
    LOWER_THAN_ELSE = 308          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IDENTIFIER 258
#define NATURAL 259
#define DECIMAL 260
#define STRLIT 261
#define BOOLLIT 262
#define CLASS 263
#define PUBLIC 264
#define STATIC 265
#define RESERVED 266
#define BOOL 267
#define INT 268
#define DOUBLE 269
#define VOID 270
#define STRING 271
#define IF 272
#define ELSE 273
#define WHILE 274
#define RETURN 275
#define PRINT 276
#define PARSEINT 277
#define DOTLENGTH 278
#define INC 279
#define DEC 280
#define ARROW 281
#define ASSIGN 282
#define PLUS 283
#define MINUS 284
#define STAR 285
#define DIV 286
#define MOD 287
#define AND 288
#define OR 289
#define XOR 290
#define LSHIFT 291
#define RSHIFT 292
#define EQ 293
#define NE 294
#define LT 295
#define GT 296
#define LE 297
#define GE 298
#define NOT 299
#define LPAR 300
#define RPAR 301
#define LBRACE 302
#define RBRACE 303
#define LSQ 304
#define RSQ 305
#define SEMICOLON 306
#define COMMA 307
#define LOWER_THAN_ELSE 308

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 159 "jucompiler.y"

    char *lexeme;
    struct node *node;

#line 393 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
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
  YYSYMBOL_LOWER_THAN_ELSE = 53,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 54,                  /* $accept  */
  YYSYMBOL_program = 55,                   /* program  */
  YYSYMBOL_class_body = 56,                /* class_body  */
  YYSYMBOL_field_decl = 57,                /* field_decl  */
  YYSYMBOL_field_ids = 58,                 /* field_ids  */
  YYSYMBOL_method_decl = 59,               /* method_decl  */
  YYSYMBOL_method_header = 60,             /* method_header  */
  YYSYMBOL_formal_params = 61,             /* formal_params  */
  YYSYMBOL_param_list = 62,                /* param_list  */
  YYSYMBOL_param_decl = 63,                /* param_decl  */
  YYSYMBOL_method_body = 64,               /* method_body  */
  YYSYMBOL_method_body_items = 65,         /* method_body_items  */
  YYSYMBOL_var_decl = 66,                  /* var_decl  */
  YYSYMBOL_var_ids = 67,                   /* var_ids  */
  YYSYMBOL_stmt = 68,                      /* stmt  */
  YYSYMBOL_stmt_list = 69,                 /* stmt_list  */
  YYSYMBOL_expr = 70,                      /* expr  */
  YYSYMBOL_assign_expr = 71,               /* assign_expr  */
  YYSYMBOL_or_expr = 72,                   /* or_expr  */
  YYSYMBOL_and_expr = 73,                  /* and_expr  */
  YYSYMBOL_xor_expr = 74,                  /* xor_expr  */
  YYSYMBOL_eq_expr = 75,                   /* eq_expr  */
  YYSYMBOL_rel_expr = 76,                  /* rel_expr  */
  YYSYMBOL_shift_expr = 77,                /* shift_expr  */
  YYSYMBOL_add_expr = 78,                  /* add_expr  */
  YYSYMBOL_mul_expr = 79,                  /* mul_expr  */
  YYSYMBOL_unary_expr = 80,                /* unary_expr  */
  YYSYMBOL_primary_expr = 81,              /* primary_expr  */
  YYSYMBOL_method_invocation = 82,         /* method_invocation  */
  YYSYMBOL_args_opt = 83,                  /* args_opt  */
  YYSYMBOL_expr_list = 84,                 /* expr_list  */
  YYSYMBOL_parse_args = 85,                /* parse_args  */
  YYSYMBOL_type = 86                       /* type  */
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
#define YYLAST   282

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  191

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   308


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
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   201,   201,   212,   215,   221,   226,   230,   238,   256,
     261,   269,   278,   285,   292,   300,   311,   314,   318,   323,
     331,   337,   346,   352,   359,   367,   370,   376,   382,   390,
     408,   413,   421,   425,   430,   435,   442,   449,   457,   465,
     471,   476,   480,   486,   491,   496,   500,   504,   508,   516,
     519,   528,   532,   538,   542,   548,   552,   558,   562,   568,
     572,   578,   584,   588,   594,   600,   606,   612,   616,   622,
     628,   632,   638,   644,   648,   654,   660,   666,   670,   675,
     680,   685,   689,   693,   698,   702,   706,   710,   711,   712,
     716,   724,   731,   740,   743,   747,   752,   760,   769,   773,
     777
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
  "LOWER_THAN_ELSE", "$accept", "program", "class_body", "field_decl",
  "field_ids", "method_decl", "method_header", "formal_params",
  "param_list", "param_decl", "method_body", "method_body_items",
  "var_decl", "var_ids", "stmt", "stmt_list", "expr", "assign_expr",
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

#define YYPACT_NINF (-94)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-94)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       9,    19,    37,   -38,   -94,   -94,    43,    12,    72,   -94,
     -94,   -94,   -94,   -94,   115,   -94,   -94,   -94,    87,   -34,
     101,    75,    13,   -94,   108,    -3,     7,    94,    64,    27,
     -94,   140,   100,   106,   110,   107,   -94,   159,   -94,    -6,
      -9,   119,   129,   147,   132,   134,    86,   -94,   -94,   -94,
     -94,   137,   139,   197,   155,   156,   -94,   -94,   153,   -94,
      83,   -94,   -94,   -94,   229,   177,   229,   229,    23,   -94,
     -94,   -94,   237,   237,   237,   182,   -94,   157,   -94,   173,
     176,   183,    16,    98,    38,    51,   164,   -94,   -94,   -94,
     -94,   209,   214,   171,    97,   -94,   -94,   -94,    50,   -94,
     -94,   217,   -94,   174,   178,   -94,   184,   187,     1,   189,
     -94,   229,     6,   -94,   -94,   -94,   199,   200,   -94,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   201,   202,   179,   -94,    11,
     -94,   -94,   -94,   226,   -94,   -94,   -94,   -94,   229,   146,
     146,   146,   -94,   -94,   -94,   176,   183,    16,    98,    98,
      38,    38,    38,    38,    51,    51,   164,   164,   -94,   -94,
     -94,   192,   198,   229,   -94,   -94,   -94,   -94,   204,   232,
     234,   -94,   -94,   -94,   206,   146,   146,   215,   -94,   -94,
     -94
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     0,     0,     2,
       6,     4,     5,     7,     0,   100,    98,    99,     0,     0,
       0,     0,     0,    11,     9,     0,     0,     0,     0,     0,
       8,     0,     0,     0,     0,    17,    18,     0,    24,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    47,    26,
      27,     0,     0,     0,     0,     0,    10,    15,     0,    13,
       0,    20,    23,    28,     0,     0,     0,     0,    82,    84,
      85,    86,     0,     0,     0,     0,    41,     0,    51,    53,
      55,    57,    59,    62,    67,    70,    73,    77,    81,    87,
      88,     0,     0,     0,     0,    45,    46,    30,     0,    14,
      12,     0,    19,     0,     0,    95,     0,    94,     0,     0,
      83,     0,    82,    80,    79,    78,     0,     0,    40,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,     0,
      32,    50,    29,     0,    21,    42,    92,    91,     0,     0,
       0,     0,    52,    90,    89,    54,    56,    58,    60,    61,
      63,    64,    65,    66,    68,    69,    71,    72,    74,    75,
      76,     0,     0,     0,    33,    48,    31,    96,     0,    37,
      35,    39,    44,    43,     0,     0,     0,     0,    38,    36,
      97
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -94,   -94,   -94,   -94,   -94,   -94,   -94,   231,   -94,   203,
     -94,   -94,   -94,   -94,   -93,   -94,   -60,   151,   -94,   145,
     148,   149,   -13,    46,     3,     5,   -62,   -94,   -28,   -94,
     -94,   -25,    10
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     6,    11,    25,    12,    19,    34,    35,    36,
      23,    28,    49,    98,    50,    94,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,   106,
     107,    90,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,   141,   149,    52,   103,   105,   108,   109,    32,     5,
     113,   114,   115,    22,    27,   117,   -25,     1,    64,    15,
      16,    17,     3,    33,    20,   -25,   -25,   -25,    54,   110,
     -25,   136,   -25,   -25,   -25,   -25,    65,     4,    53,    15,
      16,    17,    62,    33,     7,    63,   110,   150,    30,    31,
     111,    65,     8,   -16,   122,   123,   179,   180,   181,   174,
     -25,   -25,   175,    13,   -25,    39,    51,    40,    65,    52,
     168,   169,   170,   -16,   128,   129,    15,    16,    17,   130,
     131,    41,    14,    42,    43,    44,    45,    93,   177,   -49,
      21,     9,   188,   189,    10,    15,    16,    17,   139,    33,
      40,   142,   143,   -49,    24,   -49,   -49,   -49,   -49,   158,
     159,    46,    47,   184,    41,    48,    42,    43,    44,    45,
      26,    51,    51,    51,    52,    52,    52,    15,    16,    17,
      18,   164,   165,   -49,   -49,   166,   167,   -49,   124,   125,
     126,   127,    38,    56,    46,   140,    57,   178,    48,    40,
      68,    69,    70,    29,    71,    58,    59,    51,    51,    60,
      52,    52,    61,    41,    66,    42,    43,    44,    45,    45,
     160,   161,   162,   163,    67,    72,    73,    91,   104,    92,
      68,    69,    70,   116,    71,    68,    69,    70,    95,    71,
      96,    74,    75,    46,   132,   133,   134,    48,    76,    45,
      97,    99,   100,   101,    45,    72,    73,   119,   118,   120,
      72,    73,    68,    69,    70,   135,    71,   137,   121,   138,
     144,    74,    75,   -93,   146,   145,    74,    75,   173,   176,
     147,    45,    68,    69,    70,   151,    71,    72,    73,   148,
     112,    69,    70,   182,    71,   153,   154,   171,   172,   183,
     185,    45,   186,    74,    75,   175,   187,    72,    73,    45,
      55,   190,   152,   102,   155,    72,    73,     0,   156,     0,
     157,     0,     0,    74,    75,     0,     0,     0,     0,     0,
       0,    74,    75
};

static const yytype_int16 yycheck[] =
{
      28,    94,     1,    28,    64,    65,    66,    67,     1,    47,
      72,    73,    74,    47,     1,    75,     3,     8,    27,    12,
      13,    14,     3,    16,    14,    12,    13,    14,     1,    23,
      17,    91,    19,    20,    21,    22,    45,     0,    28,    12,
      13,    14,    48,    16,     1,    51,    23,    46,    51,    52,
      27,    45,     9,    46,    38,    39,   149,   150,   151,    48,
      47,    48,    51,    51,    51,     1,    94,     3,    45,    94,
     132,   133,   134,    46,    36,    37,    12,    13,    14,    28,
      29,    17,    10,    19,    20,    21,    22,     1,   148,     3,
       3,    48,   185,   186,    51,    12,    13,    14,     1,    16,
       3,    51,    52,    17,     3,    19,    20,    21,    22,   122,
     123,    47,    48,   173,    17,    51,    19,    20,    21,    22,
      45,   149,   150,   151,   149,   150,   151,    12,    13,    14,
      15,   128,   129,    47,    48,   130,   131,    51,    40,    41,
      42,    43,    48,     3,    47,    48,    46,     1,    51,     3,
       3,     4,     5,    45,     7,    49,    46,   185,   186,    52,
     185,   186,     3,    17,    45,    19,    20,    21,    22,    22,
     124,   125,   126,   127,    45,    28,    29,    45,     1,    45,
       3,     4,     5,     1,     7,     3,     4,     5,    51,     7,
      51,    44,    45,    47,    30,    31,    32,    51,    51,    22,
       3,    46,    46,    50,    22,    28,    29,    34,    51,    33,
      28,    29,     3,     4,     5,     6,     7,     3,    35,    48,
       3,    44,    45,    46,    46,    51,    44,    45,    49,     3,
      46,    22,     3,     4,     5,    46,     7,    28,    29,    52,
       3,     4,     5,    51,     7,    46,    46,    46,    46,    51,
      18,    22,    18,    44,    45,    51,    50,    28,    29,    22,
      29,    46,   111,    60,   119,    28,    29,    -1,   120,    -1,
     121,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    55,     3,     0,    47,    56,     1,     9,    48,
      51,    57,    59,    51,    10,    12,    13,    14,    15,    60,
      86,     3,    47,    64,     3,    58,    45,     1,    65,    45,
      51,    52,     1,    16,    61,    62,    63,    86,    48,     1,
       3,    17,    19,    20,    21,    22,    47,    48,    51,    66,
      68,    82,    85,    86,     1,    61,     3,    46,    49,    46,
      52,     3,    48,    51,    27,    45,    45,    45,     3,     4,
       5,     7,    28,    29,    44,    45,    51,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      85,    45,    45,     1,    69,    51,    51,     3,    67,    46,
      46,    50,    63,    70,     1,    70,    83,    84,    70,    70,
      23,    27,     3,    80,    80,    80,     1,    70,    51,    34,
      33,    35,    38,    39,    40,    41,    42,    43,    36,    37,
      28,    29,    30,    31,    32,     6,    70,     3,    48,     1,
      48,    68,    51,    52,     3,    51,    46,    46,    52,     1,
      46,    46,    71,    46,    46,    73,    74,    75,    76,    76,
      77,    77,    77,    77,    78,    78,    79,    79,    80,    80,
      80,    46,    46,    49,    48,    51,     3,    70,     1,    68,
      68,    68,    51,    51,    70,    18,    18,    50,    68,    68,
      46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    54,    55,    56,    56,    56,    56,    56,    57,    58,
      58,    59,    60,    60,    60,    60,    61,    61,    62,    62,
      63,    63,    64,    64,    64,    65,    65,    65,    65,    66,
      67,    67,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    69,
      69,    70,    71,    71,    72,    72,    73,    73,    74,    74,
      75,    75,    75,    76,    76,    76,    76,    76,    77,    77,
      77,    78,    78,    78,    79,    79,    79,    79,    80,    80,
      80,    80,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    82,    82,    83,    83,    84,    84,    85,    86,    86,
      86
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     0,     2,     2,     2,     3,     5,     1,
       3,     4,     5,     5,     5,     5,     0,     1,     1,     3,
       2,     4,     3,     4,     3,     0,     2,     2,     3,     3,
       1,     3,     3,     4,     3,     5,     7,     5,     7,     5,
       3,     2,     4,     5,     5,     2,     2,     1,     2,     0,
       2,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     2,     2,
       2,     1,     1,     2,     1,     1,     1,     1,     1,     3,
       3,     4,     4,     0,     1,     1,     3,     7,     1,     1,
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
#line 202 "jucompiler.y"
    {
        (yyval.node) = newnode(Program, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        append_holder((yyval.node), (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));
        ast = (yyval.node);
    }
#line 1616 "y.tab.c"
    break;

  case 3: /* class_body: %empty  */
#line 212 "jucompiler.y"
    {
        (yyval.node) = make_holder();
    }
#line 1624 "y.tab.c"
    break;

  case 4: /* class_body: class_body field_decl  */
#line 216 "jucompiler.y"
    {
        append_holder((yyvsp[-1].node), (yyvsp[0].node));
        free_holder_only((yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1634 "y.tab.c"
    break;

  case 5: /* class_body: class_body method_decl  */
#line 222 "jucompiler.y"
    {
        addchild((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1643 "y.tab.c"
    break;

  case 6: /* class_body: class_body SEMICOLON  */
#line 227 "jucompiler.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1651 "y.tab.c"
    break;

  case 7: /* class_body: class_body error SEMICOLON  */
#line 231 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1660 "y.tab.c"
    break;

  case 8: /* field_decl: PUBLIC STATIC type field_ids SEMICOLON  */
#line 239 "jucompiler.y"
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
#line 1679 "y.tab.c"
    break;

  case 9: /* field_ids: IDENTIFIER  */
#line 257 "jucompiler.y"
    {
        (yyval.node) = make_holder();
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1688 "y.tab.c"
    break;

  case 10: /* field_ids: field_ids COMMA IDENTIFIER  */
#line 262 "jucompiler.y"
    {
        addchild((yyvsp[-2].node), newnode(Identifier, (yyvsp[0].lexeme)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1697 "y.tab.c"
    break;

  case 11: /* method_decl: PUBLIC STATIC method_header method_body  */
#line 270 "jucompiler.y"
    {
        (yyval.node) = newnode(MethodDecl, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1707 "y.tab.c"
    break;

  case 12: /* method_header: type IDENTIFIER LPAR formal_params RPAR  */
#line 279 "jucompiler.y"
    {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1718 "y.tab.c"
    break;

  case 13: /* method_header: VOID IDENTIFIER LPAR formal_params RPAR  */
#line 286 "jucompiler.y"
    {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), newnode(Void, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1729 "y.tab.c"
    break;

  case 14: /* method_header: type IDENTIFIER LPAR error RPAR  */
#line 293 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), newnode(MethodParams, NULL));
    }
#line 1741 "y.tab.c"
    break;

  case 15: /* method_header: VOID IDENTIFIER LPAR error RPAR  */
#line 301 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), newnode(Void, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), newnode(MethodParams, NULL));
    }
#line 1753 "y.tab.c"
    break;

  case 16: /* formal_params: %empty  */
#line 311 "jucompiler.y"
    {
        (yyval.node) = newnode(MethodParams, NULL);
    }
#line 1761 "y.tab.c"
    break;

  case 18: /* param_list: param_decl  */
#line 319 "jucompiler.y"
    {
        (yyval.node) = newnode(MethodParams, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1770 "y.tab.c"
    break;

  case 19: /* param_list: param_list COMMA param_decl  */
#line 324 "jucompiler.y"
    {
        addchild((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1779 "y.tab.c"
    break;

  case 20: /* param_decl: type IDENTIFIER  */
#line 332 "jucompiler.y"
    {
        (yyval.node) = newnode(ParamDecl, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1789 "y.tab.c"
    break;

  case 21: /* param_decl: STRING LSQ RSQ IDENTIFIER  */
#line 338 "jucompiler.y"
    {
        (yyval.node) = newnode(ParamDecl, NULL);
        addchild((yyval.node), newnode(StringArray, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1799 "y.tab.c"
    break;

  case 22: /* method_body: LBRACE method_body_items RBRACE  */
#line 347 "jucompiler.y"
    {
        (yyval.node) = newnode(MethodBody, NULL);
        append_holder((yyval.node), (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));
    }
#line 1809 "y.tab.c"
    break;

  case 23: /* method_body: LBRACE method_body_items error RBRACE  */
#line 353 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = newnode(MethodBody, NULL);
        append_holder((yyval.node), (yyvsp[-2].node));
        free_holder_only((yyvsp[-2].node));
    }
#line 1820 "y.tab.c"
    break;

  case 24: /* method_body: LBRACE error RBRACE  */
#line 360 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = newnode(MethodBody, NULL);
    }
#line 1829 "y.tab.c"
    break;

  case 25: /* method_body_items: %empty  */
#line 367 "jucompiler.y"
    {
        (yyval.node) = make_holder();
    }
#line 1837 "y.tab.c"
    break;

  case 26: /* method_body_items: method_body_items var_decl  */
#line 371 "jucompiler.y"
    {
        append_holder((yyvsp[-1].node), (yyvsp[0].node));
        free_holder_only((yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1847 "y.tab.c"
    break;

  case 27: /* method_body_items: method_body_items stmt  */
#line 377 "jucompiler.y"
    {
        if (!is_empty_block((yyvsp[0].node)))
            addchild((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1857 "y.tab.c"
    break;

  case 28: /* method_body_items: method_body_items error SEMICOLON  */
#line 383 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1866 "y.tab.c"
    break;

  case 29: /* var_decl: type var_ids SEMICOLON  */
#line 391 "jucompiler.y"
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
#line 1885 "y.tab.c"
    break;

  case 30: /* var_ids: IDENTIFIER  */
#line 409 "jucompiler.y"
    {
        (yyval.node) = make_holder();
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1894 "y.tab.c"
    break;

  case 31: /* var_ids: var_ids COMMA IDENTIFIER  */
#line 414 "jucompiler.y"
    {
        addchild((yyvsp[-2].node), newnode(Identifier, (yyvsp[0].lexeme)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1903 "y.tab.c"
    break;

  case 32: /* stmt: LBRACE stmt_list RBRACE  */
#line 422 "jucompiler.y"
    {
        (yyval.node) = build_block_from_holder((yyvsp[-1].node));
    }
#line 1911 "y.tab.c"
    break;

  case 33: /* stmt: LBRACE stmt_list error RBRACE  */
#line 426 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = build_block_from_holder((yyvsp[-2].node));
    }
#line 1920 "y.tab.c"
    break;

  case 34: /* stmt: LBRACE error RBRACE  */
#line 431 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 1929 "y.tab.c"
    break;

  case 35: /* stmt: IF LPAR expr RPAR stmt  */
#line 436 "jucompiler.y"
    {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 1940 "y.tab.c"
    break;

  case 36: /* stmt: IF LPAR expr RPAR stmt ELSE stmt  */
#line 443 "jucompiler.y"
    {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1951 "y.tab.c"
    break;

  case 37: /* stmt: IF LPAR expr error stmt  */
#line 450 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 1963 "y.tab.c"
    break;

  case 38: /* stmt: IF LPAR expr error stmt ELSE stmt  */
#line 458 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1975 "y.tab.c"
    break;

  case 39: /* stmt: WHILE LPAR expr RPAR stmt  */
#line 466 "jucompiler.y"
    {
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1985 "y.tab.c"
    break;

  case 40: /* stmt: RETURN expr SEMICOLON  */
#line 472 "jucompiler.y"
    {
        (yyval.node) = newnode(Return, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1994 "y.tab.c"
    break;

  case 41: /* stmt: RETURN SEMICOLON  */
#line 477 "jucompiler.y"
    {
        (yyval.node) = newnode(Return, NULL);
    }
#line 2002 "y.tab.c"
    break;

  case 42: /* stmt: IDENTIFIER ASSIGN expr SEMICOLON  */
#line 481 "jucompiler.y"
    {
        (yyval.node) = newnode(Assign, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 2012 "y.tab.c"
    break;

  case 43: /* stmt: PRINT LPAR expr RPAR SEMICOLON  */
#line 487 "jucompiler.y"
    {
        (yyval.node) = newnode(Print, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 2021 "y.tab.c"
    break;

  case 44: /* stmt: PRINT LPAR STRLIT RPAR SEMICOLON  */
#line 492 "jucompiler.y"
    {
        (yyval.node) = newnode(Print, NULL);
        addchild((yyval.node), newnode(StrLit, (yyvsp[-2].lexeme)));
    }
#line 2030 "y.tab.c"
    break;

  case 45: /* stmt: method_invocation SEMICOLON  */
#line 497 "jucompiler.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2038 "y.tab.c"
    break;

  case 46: /* stmt: parse_args SEMICOLON  */
#line 501 "jucompiler.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2046 "y.tab.c"
    break;

  case 47: /* stmt: SEMICOLON  */
#line 505 "jucompiler.y"
    {
        (yyval.node) = newnode(Block, NULL);
    }
#line 2054 "y.tab.c"
    break;

  case 48: /* stmt: error SEMICOLON  */
#line 509 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2063 "y.tab.c"
    break;

  case 49: /* stmt_list: %empty  */
#line 516 "jucompiler.y"
    {
        (yyval.node) = make_holder();
    }
#line 2071 "y.tab.c"
    break;

  case 50: /* stmt_list: stmt_list stmt  */
#line 520 "jucompiler.y"
    {
        if (!is_empty_block((yyvsp[0].node)))
            addchild((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2081 "y.tab.c"
    break;

  case 52: /* assign_expr: IDENTIFIER ASSIGN assign_expr  */
#line 533 "jucompiler.y"
    {
        (yyval.node) = newnode(Assign, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2091 "y.tab.c"
    break;

  case 54: /* or_expr: or_expr OR and_expr  */
#line 543 "jucompiler.y"
    {
        (yyval.node) = newnode(Or, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2101 "y.tab.c"
    break;

  case 56: /* and_expr: and_expr AND xor_expr  */
#line 553 "jucompiler.y"
    {
        (yyval.node) = newnode(And, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2111 "y.tab.c"
    break;

  case 58: /* xor_expr: xor_expr XOR eq_expr  */
#line 563 "jucompiler.y"
    {
        (yyval.node) = newnode(Xor, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2121 "y.tab.c"
    break;

  case 60: /* eq_expr: eq_expr EQ rel_expr  */
#line 573 "jucompiler.y"
    {
        (yyval.node) = newnode(Eq, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2131 "y.tab.c"
    break;

  case 61: /* eq_expr: eq_expr NE rel_expr  */
#line 579 "jucompiler.y"
    {
        (yyval.node) = newnode(Ne, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2141 "y.tab.c"
    break;

  case 63: /* rel_expr: rel_expr LT shift_expr  */
#line 589 "jucompiler.y"
    {
        (yyval.node) = newnode(Lt, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2151 "y.tab.c"
    break;

  case 64: /* rel_expr: rel_expr GT shift_expr  */
#line 595 "jucompiler.y"
    {
        (yyval.node) = newnode(Gt, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2161 "y.tab.c"
    break;

  case 65: /* rel_expr: rel_expr LE shift_expr  */
#line 601 "jucompiler.y"
    {
        (yyval.node) = newnode(Le, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2171 "y.tab.c"
    break;

  case 66: /* rel_expr: rel_expr GE shift_expr  */
#line 607 "jucompiler.y"
    {
        (yyval.node) = newnode(Ge, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2181 "y.tab.c"
    break;

  case 68: /* shift_expr: shift_expr LSHIFT add_expr  */
#line 617 "jucompiler.y"
    {
        (yyval.node) = newnode(Lshift, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2191 "y.tab.c"
    break;

  case 69: /* shift_expr: shift_expr RSHIFT add_expr  */
#line 623 "jucompiler.y"
    {
        (yyval.node) = newnode(Rshift, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2201 "y.tab.c"
    break;

  case 71: /* add_expr: add_expr PLUS mul_expr  */
#line 633 "jucompiler.y"
    {
        (yyval.node) = newnode(Add, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2211 "y.tab.c"
    break;

  case 72: /* add_expr: add_expr MINUS mul_expr  */
#line 639 "jucompiler.y"
    {
        (yyval.node) = newnode(Sub, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2221 "y.tab.c"
    break;

  case 74: /* mul_expr: mul_expr STAR unary_expr  */
#line 649 "jucompiler.y"
    {
        (yyval.node) = newnode(Mul, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2231 "y.tab.c"
    break;

  case 75: /* mul_expr: mul_expr DIV unary_expr  */
#line 655 "jucompiler.y"
    {
        (yyval.node) = newnode(Div, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2241 "y.tab.c"
    break;

  case 76: /* mul_expr: mul_expr MOD unary_expr  */
#line 661 "jucompiler.y"
    {
        (yyval.node) = newnode(Mod, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2251 "y.tab.c"
    break;

  case 78: /* unary_expr: NOT unary_expr  */
#line 671 "jucompiler.y"
    {
        (yyval.node) = newnode(Not, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2260 "y.tab.c"
    break;

  case 79: /* unary_expr: MINUS unary_expr  */
#line 676 "jucompiler.y"
    {
        (yyval.node) = newnode(Minus, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2269 "y.tab.c"
    break;

  case 80: /* unary_expr: PLUS unary_expr  */
#line 681 "jucompiler.y"
    {
        (yyval.node) = newnode(Plus, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2278 "y.tab.c"
    break;

  case 82: /* primary_expr: IDENTIFIER  */
#line 690 "jucompiler.y"
    {
        (yyval.node) = newnode(Identifier, (yyvsp[0].lexeme));
    }
#line 2286 "y.tab.c"
    break;

  case 83: /* primary_expr: IDENTIFIER DOTLENGTH  */
#line 694 "jucompiler.y"
    {
        (yyval.node) = newnode(Length, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-1].lexeme)));
    }
#line 2295 "y.tab.c"
    break;

  case 84: /* primary_expr: NATURAL  */
#line 699 "jucompiler.y"
    {
        (yyval.node) = newnode(Natural, (yyvsp[0].lexeme));
    }
#line 2303 "y.tab.c"
    break;

  case 85: /* primary_expr: DECIMAL  */
#line 703 "jucompiler.y"
    {
        (yyval.node) = newnode(Decimal, (yyvsp[0].lexeme));
    }
#line 2311 "y.tab.c"
    break;

  case 86: /* primary_expr: BOOLLIT  */
#line 707 "jucompiler.y"
    {
        (yyval.node) = newnode(BoolLit, (yyvsp[0].lexeme));
    }
#line 2319 "y.tab.c"
    break;

  case 89: /* primary_expr: LPAR expr RPAR  */
#line 713 "jucompiler.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2327 "y.tab.c"
    break;

  case 90: /* primary_expr: LPAR error RPAR  */
#line 717 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = NULL;
    }
#line 2336 "y.tab.c"
    break;

  case 91: /* method_invocation: IDENTIFIER LPAR args_opt RPAR  */
#line 725 "jucompiler.y"
    {
        (yyval.node) = newnode(Call, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        append_holder((yyval.node), (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));
    }
#line 2347 "y.tab.c"
    break;

  case 92: /* method_invocation: IDENTIFIER LPAR error RPAR  */
#line 732 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = newnode(Call, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
    }
#line 2357 "y.tab.c"
    break;

  case 93: /* args_opt: %empty  */
#line 740 "jucompiler.y"
    {
        (yyval.node) = make_holder();
    }
#line 2365 "y.tab.c"
    break;

  case 95: /* expr_list: expr  */
#line 748 "jucompiler.y"
    {
        (yyval.node) = make_holder();
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2374 "y.tab.c"
    break;

  case 96: /* expr_list: expr_list COMMA expr  */
#line 753 "jucompiler.y"
    {
        addchild((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2383 "y.tab.c"
    break;

  case 97: /* parse_args: PARSEINT LPAR IDENTIFIER LSQ expr RSQ RPAR  */
#line 761 "jucompiler.y"
    {
        (yyval.node) = newnode(ParseArgs, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-4].lexeme)));
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 2393 "y.tab.c"
    break;

  case 98: /* type: INT  */
#line 770 "jucompiler.y"
    {
        (yyval.node) = newnode(Int, NULL);
    }
#line 2401 "y.tab.c"
    break;

  case 99: /* type: DOUBLE  */
#line 774 "jucompiler.y"
    {
        (yyval.node) = newnode(Double, NULL);
    }
#line 2409 "y.tab.c"
    break;

  case 100: /* type: BOOL  */
#line 778 "jucompiler.y"
    {
        (yyval.node) = newnode(Bool, NULL);
    }
#line 2417 "y.tab.c"
    break;


#line 2421 "y.tab.c"

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

#line 783 "jucompiler.y"


int main(int argc, char **argv) {
    int lex_only = 0;

    if (argc > 1) {
        if (strcmp(argv[1], "-l") == 0) {
            lex_only = 1;
            print_tokens = 1;
        }

        if (strcmp(argv[1], "-e1") == 0) {
            lex_only = 1;
        }

        if (strcmp(argv[1], "-t") == 0) {
            print_tree = 1;
        }

        if (strcmp(argv[1], "-e2") == 0) {
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

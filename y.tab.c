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

struct node *ast = NULL;

int print_tree = 0;
int only_errors = 0;
int syntax_errors = 0;

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

void yyerror(char *s) {
    syntax_errors = 1;
    if (!only_errors)
        printf("Line %d, col %d: syntax error: %s\n", token_line, token_column, yytext);
}

#line 192 "y.tab.c"

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
    BOOL = 266,                    /* BOOL  */
    INT = 267,                     /* INT  */
    DOUBLE = 268,                  /* DOUBLE  */
    VOID = 269,                    /* VOID  */
    STRING = 270,                  /* STRING  */
    IF = 271,                      /* IF  */
    ELSE = 272,                    /* ELSE  */
    WHILE = 273,                   /* WHILE  */
    RETURN = 274,                  /* RETURN  */
    PRINT = 275,                   /* PRINT  */
    PARSEINT = 276,                /* PARSEINT  */
    DOTLENGTH = 277,               /* DOTLENGTH  */
    INC = 278,                     /* INC  */
    DEC = 279,                     /* DEC  */
    ARROW = 280,                   /* ARROW  */
    ASSIGN = 281,                  /* ASSIGN  */
    PLUS = 282,                    /* PLUS  */
    MINUS = 283,                   /* MINUS  */
    STAR = 284,                    /* STAR  */
    DIV = 285,                     /* DIV  */
    MOD = 286,                     /* MOD  */
    AND = 287,                     /* AND  */
    OR = 288,                      /* OR  */
    XOR = 289,                     /* XOR  */
    LSHIFT = 290,                  /* LSHIFT  */
    RSHIFT = 291,                  /* RSHIFT  */
    EQ = 292,                      /* EQ  */
    NE = 293,                      /* NE  */
    LT = 294,                      /* LT  */
    GT = 295,                      /* GT  */
    LE = 296,                      /* LE  */
    GE = 297,                      /* GE  */
    NOT = 298,                     /* NOT  */
    LPAR = 299,                    /* LPAR  */
    RPAR = 300,                    /* RPAR  */
    LBRACE = 301,                  /* LBRACE  */
    RBRACE = 302,                  /* RBRACE  */
    LSQ = 303,                     /* LSQ  */
    RSQ = 304,                     /* RSQ  */
    SEMICOLON = 305,               /* SEMICOLON  */
    COMMA = 306,                   /* COMMA  */
    LOWER_THAN_ELSE = 307,         /* LOWER_THAN_ELSE  */
    UMINUS = 308,                  /* UMINUS  */
    UPLUS = 309                    /* UPLUS  */
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
#define BOOL 266
#define INT 267
#define DOUBLE 268
#define VOID 269
#define STRING 270
#define IF 271
#define ELSE 272
#define WHILE 273
#define RETURN 274
#define PRINT 275
#define PARSEINT 276
#define DOTLENGTH 277
#define INC 278
#define DEC 279
#define ARROW 280
#define ASSIGN 281
#define PLUS 282
#define MINUS 283
#define STAR 284
#define DIV 285
#define MOD 286
#define AND 287
#define OR 288
#define XOR 289
#define LSHIFT 290
#define RSHIFT 291
#define EQ 292
#define NE 293
#define LT 294
#define GT 295
#define LE 296
#define GE 297
#define NOT 298
#define LPAR 299
#define RPAR 300
#define LBRACE 301
#define RBRACE 302
#define LSQ 303
#define RSQ 304
#define SEMICOLON 305
#define COMMA 306
#define LOWER_THAN_ELSE 307
#define UMINUS 308
#define UPLUS 309

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 122 "jucompiler.y"

    char *lexeme;
    struct node *node;

#line 358 "y.tab.c"

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
  YYSYMBOL_SEMICOLON = 50,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 51,                     /* COMMA  */
  YYSYMBOL_LOWER_THAN_ELSE = 52,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_UMINUS = 53,                    /* UMINUS  */
  YYSYMBOL_UPLUS = 54,                     /* UPLUS  */
  YYSYMBOL_YYACCEPT = 55,                  /* $accept  */
  YYSYMBOL_program = 56,                   /* program  */
  YYSYMBOL_class_body = 57,                /* class_body  */
  YYSYMBOL_field_decl = 58,                /* field_decl  */
  YYSYMBOL_field_ids = 59,                 /* field_ids  */
  YYSYMBOL_method_decl = 60,               /* method_decl  */
  YYSYMBOL_method_header = 61,             /* method_header  */
  YYSYMBOL_formal_params = 62,             /* formal_params  */
  YYSYMBOL_param_list = 63,                /* param_list  */
  YYSYMBOL_param_decl = 64,                /* param_decl  */
  YYSYMBOL_method_body = 65,               /* method_body  */
  YYSYMBOL_method_body_items = 66,         /* method_body_items  */
  YYSYMBOL_var_decl = 67,                  /* var_decl  */
  YYSYMBOL_var_ids = 68,                   /* var_ids  */
  YYSYMBOL_stmt = 69,                      /* stmt  */
  YYSYMBOL_stmt_list = 70,                 /* stmt_list  */
  YYSYMBOL_expr = 71,                      /* expr  */
  YYSYMBOL_method_invocation = 72,         /* method_invocation  */
  YYSYMBOL_args_opt = 73,                  /* args_opt  */
  YYSYMBOL_expr_list = 74,                 /* expr_list  */
  YYSYMBOL_parse_args = 75,                /* parse_args  */
  YYSYMBOL_type = 76                       /* type  */
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
#define YYLAST   441

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  161

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
       0,   173,   173,   184,   187,   193,   198,   202,   210,   228,
     233,   241,   250,   257,   267,   270,   274,   279,   287,   296,
     305,   308,   314,   319,   327,   345,   350,   358,   374,   381,
     388,   396,   404,   410,   415,   419,   425,   430,   434,   438,
     445,   448,   453,   461,   465,   469,   473,   477,   481,   482,
     483,   489,   495,   501,   507,   513,   519,   525,   531,   537,
     543,   549,   555,   561,   567,   573,   579,   585,   590,   595,
     600,   605,   612,   622,   625,   629,   634,   642,   651,   655,
     659,   663
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
  "BOOL", "INT", "DOUBLE", "VOID", "STRING", "IF", "ELSE", "WHILE",
  "RETURN", "PRINT", "PARSEINT", "DOTLENGTH", "INC", "DEC", "ARROW",
  "ASSIGN", "PLUS", "MINUS", "STAR", "DIV", "MOD", "AND", "OR", "XOR",
  "LSHIFT", "RSHIFT", "EQ", "NE", "LT", "GT", "LE", "GE", "NOT", "LPAR",
  "RPAR", "LBRACE", "RBRACE", "LSQ", "RSQ", "SEMICOLON", "COMMA",
  "LOWER_THAN_ELSE", "UMINUS", "UPLUS", "$accept", "program", "class_body",
  "field_decl", "field_ids", "method_decl", "method_header",
  "formal_params", "param_list", "param_decl", "method_body",
  "method_body_items", "var_decl", "var_ids", "stmt", "stmt_list", "expr",
  "method_invocation", "args_opt", "expr_list", "parse_args", "type", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-52)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,    16,    21,   -13,   -52,   -52,     0,    -8,    33,   -52,
     -52,   -52,   -52,   -52,   426,   -52,   -52,   -52,    46,    20,
      24,    69,    32,    28,   -52,   -52,    38,   -40,   208,   -52,
      68,   208,   -52,    82,    45,    41,   -52,    97,    52,   -24,
      59,    63,   117,    72,    73,   -52,   -52,   -52,   -52,   -52,
      62,    77,   110,    74,   -52,   -52,   208,   -52,   -52,     1,
       1,     1,     1,   -14,   -52,   -52,   -52,   -52,     1,     1,
       1,     1,   -52,   176,   -52,   -52,     1,   127,    90,   -52,
     -52,   -52,   -15,   -52,   -52,   200,   310,    86,    81,   155,
     247,     1,   113,   113,   113,   268,   -52,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,   -52,   289,    91,   102,   -52,   -52,   -52,
     144,   -52,   -52,     1,   130,   130,   130,   310,   -52,   112,
     112,   113,   113,   113,   352,   331,   373,    10,    10,   394,
     394,   135,   135,   135,   135,   103,     1,   -52,   -52,   310,
     137,   138,   -52,   -52,   224,   130,   130,   114,   -52,   -52,
     -52
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     0,     0,     2,
       6,     4,     5,     7,     0,    80,    78,    79,     0,     0,
       0,     0,     0,     0,    20,    11,     9,     0,    14,    81,
       0,    14,     8,     0,     0,    15,    16,     0,     0,     0,
       0,     0,     0,     0,     0,    40,    19,    39,    21,    22,
       0,     0,     0,     0,    10,    13,     0,    18,    23,     0,
      73,     0,     0,    43,    44,    45,    46,    47,     0,     0,
       0,     0,    34,     0,    48,    49,     0,     0,     0,    37,
      38,    25,     0,    12,    17,     0,    75,     0,    74,     0,
       0,     0,    69,    68,    67,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,    27,    41,    24,
       0,    35,    72,     0,     0,     0,     0,    50,    71,    51,
      52,    53,    54,    55,    56,    57,    58,    65,    66,    59,
      60,    61,    62,    63,    64,     0,     0,    42,    26,    76,
      30,    28,    32,    36,     0,     0,     0,     0,    31,    29,
      77
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -52,   -52,   -52,   -52,   -52,   -52,   -52,   141,   -52,   118,
     -52,   -52,   -52,   -52,   -51,   -52,   -45,   -30,   -52,   -52,
     -27,     4
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     6,    11,    27,    12,    20,    34,    35,    36,
      25,    30,    48,    82,    49,    78,    73,    74,    87,    88,
      75,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      50,     7,    59,    51,    63,    64,    65,    66,    67,     8,
      32,    33,    91,     1,    85,    86,    89,    90,    21,     3,
      60,     4,    44,    92,    93,    94,    95,   118,    68,    69,
      60,   114,    96,     5,    52,   119,   120,    97,    98,    99,
     100,   101,    13,    14,    70,    71,   127,     9,    50,    22,
      10,    51,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,    23,    38,
      24,    39,    26,   150,   151,   152,    28,    29,   149,    15,
      16,    17,    31,    19,    40,    54,    41,    42,    43,    44,
      55,   116,    56,    39,    50,    50,    50,    51,    51,    51,
      57,   154,    58,    61,   158,   159,    40,    62,    41,    42,
      43,    44,    79,    81,    45,    46,    76,    77,    47,    83,
      63,    64,    65,    66,    67,    50,    50,    80,    51,    51,
     115,   122,   123,    39,    96,    96,    45,   117,    44,   146,
      47,    99,   100,   101,    68,    69,    40,   148,    41,    42,
      43,    44,   147,   153,   155,   156,   124,    96,     0,   160,
      70,    71,    97,    98,    99,   100,   101,    72,     0,     0,
     105,   106,    53,     0,    84,     0,    45,    96,     0,     0,
      47,     0,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,    96,     0,
     125,     0,     0,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,    15,
      16,    17,    96,    19,     0,     0,   113,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,     0,     0,     0,    96,     0,     0,     0,
     121,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,     0,     0,    96,
       0,     0,     0,   157,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
      96,     0,   126,     0,     0,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,    96,     0,   128,     0,     0,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,    96,     0,   145,     0,     0,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,    96,     0,     0,     0,     0,    97,    98,
      99,   100,   101,   102,     0,   104,   105,   106,   107,   108,
     109,   110,   111,   112,    96,     0,     0,     0,     0,    97,
      98,    99,   100,   101,     0,     0,   104,   105,   106,   107,
     108,   109,   110,   111,   112,    96,     0,     0,     0,     0,
      97,    98,    99,   100,   101,     0,     0,     0,   105,   106,
     107,   108,   109,   110,   111,   112,    96,     0,     0,     0,
       0,    97,    98,    99,   100,   101,     0,     0,     0,   105,
     106,     0,     0,   109,   110,   111,   112,    15,    16,    17,
      18,    19
};

static const yytype_int16 yycheck[] =
{
      30,     1,    26,    30,     3,     4,     5,     6,     7,     9,
      50,    51,    26,     8,    59,    60,    61,    62,    14,     3,
      44,     0,    21,    68,    69,    70,    71,    78,    27,    28,
      44,    76,    22,    46,    30,    50,    51,    27,    28,    29,
      30,    31,    50,    10,    43,    44,    91,    47,    78,     3,
      50,    78,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,    48,     1,
      46,     3,     3,   124,   125,   126,    44,    49,   123,    11,
      12,    13,    44,    15,    16,     3,    18,    19,    20,    21,
      45,     1,    51,     3,   124,   125,   126,   124,   125,   126,
       3,   146,    50,    44,   155,   156,    16,    44,    18,    19,
      20,    21,    50,     3,    46,    47,    44,    44,    50,    45,
       3,     4,     5,     6,     7,   155,   156,    50,   155,   156,
       3,    45,    51,     3,    22,    22,    46,    47,    21,    48,
      50,    29,    30,    31,    27,    28,    16,     3,    18,    19,
      20,    21,    50,    50,    17,    17,     1,    22,    -1,    45,
      43,    44,    27,    28,    29,    30,    31,    50,    -1,    -1,
      35,    36,    31,    -1,    56,    -1,    46,    22,    -1,    -1,
      50,    -1,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    22,    -1,
      45,    -1,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    11,
      12,    13,    22,    15,    -1,    -1,    50,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      50,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    -1,    22,
      -1,    -1,    -1,    49,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      22,    -1,    45,    -1,    -1,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    22,    -1,    45,    -1,    -1,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    22,    -1,    45,    -1,    -1,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    22,    -1,    -1,    -1,    -1,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    22,    -1,    -1,    -1,    -1,    27,
      28,    29,    30,    31,    -1,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    22,    -1,    -1,    -1,    -1,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    22,    -1,    -1,    -1,
      -1,    27,    28,    29,    30,    31,    -1,    -1,    -1,    35,
      36,    -1,    -1,    39,    40,    41,    42,    11,    12,    13,
      14,    15
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    56,     3,     0,    46,    57,     1,     9,    47,
      50,    58,    60,    50,    10,    11,    12,    13,    14,    15,
      61,    76,     3,    48,    46,    65,     3,    59,    44,    49,
      66,    44,    50,    51,    62,    63,    64,    76,     1,     3,
      16,    18,    19,    20,    21,    46,    47,    50,    67,    69,
      72,    75,    76,    62,     3,    45,    51,     3,    50,    26,
      44,    44,    44,     3,     4,     5,     6,     7,    27,    28,
      43,    44,    50,    71,    72,    75,    44,    44,    70,    50,
      50,     3,    68,    45,    64,    71,    71,    73,    74,    71,
      71,    26,    71,    71,    71,    71,    22,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    50,    71,     3,     1,    47,    69,    50,
      51,    50,    45,    51,     1,    45,    45,    71,    45,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    45,    48,    50,     3,    71,
      69,    69,    69,    50,    71,    17,    17,    49,    69,    69,
      45
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    57,    57,    57,    57,    57,    58,    59,
      59,    60,    61,    61,    62,    62,    63,    63,    64,    65,
      66,    66,    66,    66,    67,    68,    68,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      70,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    72,    73,    73,    74,    74,    75,    76,    76,
      76,    76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     0,     2,     2,     2,     3,     5,     1,
       3,     4,     5,     5,     0,     1,     1,     3,     2,     3,
       0,     2,     2,     3,     3,     1,     3,     3,     5,     7,
       5,     7,     5,     3,     2,     4,     5,     2,     2,     1,
       0,     2,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       2,     3,     4,     0,     1,     1,     3,     7,     1,     1,
       1,     3
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
#line 174 "jucompiler.y"
    {
        (yyval.node) = newnode(Program, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        append_holder((yyval.node), (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));
        ast = (yyval.node);
    }
#line 1584 "y.tab.c"
    break;

  case 3: /* class_body: %empty  */
#line 184 "jucompiler.y"
    {
        (yyval.node) = make_holder();
    }
#line 1592 "y.tab.c"
    break;

  case 4: /* class_body: class_body field_decl  */
#line 188 "jucompiler.y"
    {
        append_holder((yyvsp[-1].node), (yyvsp[0].node));
        free_holder_only((yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1602 "y.tab.c"
    break;

  case 5: /* class_body: class_body method_decl  */
#line 194 "jucompiler.y"
    {
        addchild((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1611 "y.tab.c"
    break;

  case 6: /* class_body: class_body SEMICOLON  */
#line 199 "jucompiler.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1619 "y.tab.c"
    break;

  case 7: /* class_body: class_body error SEMICOLON  */
#line 203 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1628 "y.tab.c"
    break;

  case 8: /* field_decl: PUBLIC STATIC type field_ids SEMICOLON  */
#line 211 "jucompiler.y"
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
#line 1647 "y.tab.c"
    break;

  case 9: /* field_ids: IDENTIFIER  */
#line 229 "jucompiler.y"
    {
        (yyval.node) = make_holder();
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1656 "y.tab.c"
    break;

  case 10: /* field_ids: field_ids COMMA IDENTIFIER  */
#line 234 "jucompiler.y"
    {
        addchild((yyvsp[-2].node), newnode(Identifier, (yyvsp[0].lexeme)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1665 "y.tab.c"
    break;

  case 11: /* method_decl: PUBLIC STATIC method_header method_body  */
#line 242 "jucompiler.y"
    {
        (yyval.node) = newnode(MethodDecl, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1675 "y.tab.c"
    break;

  case 12: /* method_header: type IDENTIFIER LPAR formal_params RPAR  */
#line 251 "jucompiler.y"
    {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1686 "y.tab.c"
    break;

  case 13: /* method_header: VOID IDENTIFIER LPAR formal_params RPAR  */
#line 258 "jucompiler.y"
    {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), newnode(Void, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1697 "y.tab.c"
    break;

  case 14: /* formal_params: %empty  */
#line 267 "jucompiler.y"
    {
        (yyval.node) = newnode(MethodParams, NULL);
    }
#line 1705 "y.tab.c"
    break;

  case 16: /* param_list: param_decl  */
#line 275 "jucompiler.y"
    {
        (yyval.node) = newnode(MethodParams, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1714 "y.tab.c"
    break;

  case 17: /* param_list: param_list COMMA param_decl  */
#line 280 "jucompiler.y"
    {
        addchild((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1723 "y.tab.c"
    break;

  case 18: /* param_decl: type IDENTIFIER  */
#line 288 "jucompiler.y"
    {
        (yyval.node) = newnode(ParamDecl, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1733 "y.tab.c"
    break;

  case 19: /* method_body: LBRACE method_body_items RBRACE  */
#line 297 "jucompiler.y"
    {
        (yyval.node) = newnode(MethodBody, NULL);
        append_holder((yyval.node), (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));
    }
#line 1743 "y.tab.c"
    break;

  case 20: /* method_body_items: %empty  */
#line 305 "jucompiler.y"
    {
        (yyval.node) = make_holder();
    }
#line 1751 "y.tab.c"
    break;

  case 21: /* method_body_items: method_body_items var_decl  */
#line 309 "jucompiler.y"
    {
        append_holder((yyvsp[-1].node), (yyvsp[0].node));
        free_holder_only((yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1761 "y.tab.c"
    break;

  case 22: /* method_body_items: method_body_items stmt  */
#line 315 "jucompiler.y"
    {
        addchild((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1770 "y.tab.c"
    break;

  case 23: /* method_body_items: method_body_items error SEMICOLON  */
#line 320 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1779 "y.tab.c"
    break;

  case 24: /* var_decl: type var_ids SEMICOLON  */
#line 328 "jucompiler.y"
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
#line 1798 "y.tab.c"
    break;

  case 25: /* var_ids: IDENTIFIER  */
#line 346 "jucompiler.y"
    {
        (yyval.node) = make_holder();
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1807 "y.tab.c"
    break;

  case 26: /* var_ids: var_ids COMMA IDENTIFIER  */
#line 351 "jucompiler.y"
    {
        addchild((yyvsp[-2].node), newnode(Identifier, (yyvsp[0].lexeme)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1816 "y.tab.c"
    break;

  case 27: /* stmt: LBRACE stmt_list RBRACE  */
#line 359 "jucompiler.y"
    {
        int meaningful = meaningful_child_count((yyvsp[-1].node));

        if (meaningful == 0) {
            (yyval.node) = newnode(Block, NULL);
        } else if (meaningful == 1) {
            (yyval.node) = first_meaningful_child((yyvsp[-1].node));
            (yyvsp[-1].node)->children->next = NULL;
            free_holder_only((yyvsp[-1].node));
        } else {
            (yyval.node) = newnode(Block, NULL);
            append_meaningful_children((yyval.node), (yyvsp[-1].node));
            free_holder_only((yyvsp[-1].node));
        }
    }
#line 1836 "y.tab.c"
    break;

  case 28: /* stmt: IF LPAR expr RPAR stmt  */
#line 375 "jucompiler.y"
    {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 1847 "y.tab.c"
    break;

  case 29: /* stmt: IF LPAR expr RPAR stmt ELSE stmt  */
#line 382 "jucompiler.y"
    {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1858 "y.tab.c"
    break;

  case 30: /* stmt: IF LPAR expr error stmt  */
#line 389 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 1870 "y.tab.c"
    break;

  case 31: /* stmt: IF LPAR expr error stmt ELSE stmt  */
#line 397 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1882 "y.tab.c"
    break;

  case 32: /* stmt: WHILE LPAR expr RPAR stmt  */
#line 405 "jucompiler.y"
    {
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1892 "y.tab.c"
    break;

  case 33: /* stmt: RETURN expr SEMICOLON  */
#line 411 "jucompiler.y"
    {
        (yyval.node) = newnode(Return, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1901 "y.tab.c"
    break;

  case 34: /* stmt: RETURN SEMICOLON  */
#line 416 "jucompiler.y"
    {
        (yyval.node) = newnode(Return, NULL);
    }
#line 1909 "y.tab.c"
    break;

  case 35: /* stmt: IDENTIFIER ASSIGN expr SEMICOLON  */
#line 420 "jucompiler.y"
    {
        (yyval.node) = newnode(Assign, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1919 "y.tab.c"
    break;

  case 36: /* stmt: PRINT LPAR expr RPAR SEMICOLON  */
#line 426 "jucompiler.y"
    {
        (yyval.node) = newnode(Print, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 1928 "y.tab.c"
    break;

  case 37: /* stmt: method_invocation SEMICOLON  */
#line 431 "jucompiler.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1936 "y.tab.c"
    break;

  case 38: /* stmt: parse_args SEMICOLON  */
#line 435 "jucompiler.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1944 "y.tab.c"
    break;

  case 39: /* stmt: SEMICOLON  */
#line 439 "jucompiler.y"
    {
        (yyval.node) = newnode(Block, NULL);
    }
#line 1952 "y.tab.c"
    break;

  case 40: /* stmt_list: %empty  */
#line 445 "jucompiler.y"
    {
        (yyval.node) = make_holder();
    }
#line 1960 "y.tab.c"
    break;

  case 41: /* stmt_list: stmt_list stmt  */
#line 449 "jucompiler.y"
    {
        addchild((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1969 "y.tab.c"
    break;

  case 42: /* stmt_list: stmt_list error SEMICOLON  */
#line 454 "jucompiler.y"
    {
        yyerrok;
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1978 "y.tab.c"
    break;

  case 43: /* expr: IDENTIFIER  */
#line 462 "jucompiler.y"
    {
        (yyval.node) = newnode(Identifier, (yyvsp[0].lexeme));
    }
#line 1986 "y.tab.c"
    break;

  case 44: /* expr: NATURAL  */
#line 466 "jucompiler.y"
    {
        (yyval.node) = newnode(Natural, (yyvsp[0].lexeme));
    }
#line 1994 "y.tab.c"
    break;

  case 45: /* expr: DECIMAL  */
#line 470 "jucompiler.y"
    {
        (yyval.node) = newnode(Decimal, (yyvsp[0].lexeme));
    }
#line 2002 "y.tab.c"
    break;

  case 46: /* expr: STRLIT  */
#line 474 "jucompiler.y"
    {
        (yyval.node) = newnode(StrLit, (yyvsp[0].lexeme));
    }
#line 2010 "y.tab.c"
    break;

  case 47: /* expr: BOOLLIT  */
#line 478 "jucompiler.y"
    {
        (yyval.node) = newnode(BoolLit, (yyvsp[0].lexeme));
    }
#line 2018 "y.tab.c"
    break;

  case 50: /* expr: IDENTIFIER ASSIGN expr  */
#line 484 "jucompiler.y"
    {
        (yyval.node) = newnode(Assign, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2028 "y.tab.c"
    break;

  case 51: /* expr: expr PLUS expr  */
#line 490 "jucompiler.y"
    {
        (yyval.node) = newnode(Add, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2038 "y.tab.c"
    break;

  case 52: /* expr: expr MINUS expr  */
#line 496 "jucompiler.y"
    {
        (yyval.node) = newnode(Sub, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2048 "y.tab.c"
    break;

  case 53: /* expr: expr STAR expr  */
#line 502 "jucompiler.y"
    {
        (yyval.node) = newnode(Mul, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2058 "y.tab.c"
    break;

  case 54: /* expr: expr DIV expr  */
#line 508 "jucompiler.y"
    {
        (yyval.node) = newnode(Div, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2068 "y.tab.c"
    break;

  case 55: /* expr: expr MOD expr  */
#line 514 "jucompiler.y"
    {
        (yyval.node) = newnode(Mod, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2078 "y.tab.c"
    break;

  case 56: /* expr: expr AND expr  */
#line 520 "jucompiler.y"
    {
        (yyval.node) = newnode(And, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2088 "y.tab.c"
    break;

  case 57: /* expr: expr OR expr  */
#line 526 "jucompiler.y"
    {
        (yyval.node) = newnode(Or, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2098 "y.tab.c"
    break;

  case 58: /* expr: expr XOR expr  */
#line 532 "jucompiler.y"
    {
        (yyval.node) = newnode(Xor, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2108 "y.tab.c"
    break;

  case 59: /* expr: expr EQ expr  */
#line 538 "jucompiler.y"
    {
        (yyval.node) = newnode(Eq, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2118 "y.tab.c"
    break;

  case 60: /* expr: expr NE expr  */
#line 544 "jucompiler.y"
    {
        (yyval.node) = newnode(Ne, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2128 "y.tab.c"
    break;

  case 61: /* expr: expr LT expr  */
#line 550 "jucompiler.y"
    {
        (yyval.node) = newnode(Lt, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2138 "y.tab.c"
    break;

  case 62: /* expr: expr GT expr  */
#line 556 "jucompiler.y"
    {
        (yyval.node) = newnode(Gt, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2148 "y.tab.c"
    break;

  case 63: /* expr: expr LE expr  */
#line 562 "jucompiler.y"
    {
        (yyval.node) = newnode(Le, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2158 "y.tab.c"
    break;

  case 64: /* expr: expr GE expr  */
#line 568 "jucompiler.y"
    {
        (yyval.node) = newnode(Ge, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2168 "y.tab.c"
    break;

  case 65: /* expr: expr LSHIFT expr  */
#line 574 "jucompiler.y"
    {
        (yyval.node) = newnode(Lshift, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2178 "y.tab.c"
    break;

  case 66: /* expr: expr RSHIFT expr  */
#line 580 "jucompiler.y"
    {
        (yyval.node) = newnode(Rshift, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2188 "y.tab.c"
    break;

  case 67: /* expr: NOT expr  */
#line 586 "jucompiler.y"
    {
        (yyval.node) = newnode(Not, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2197 "y.tab.c"
    break;

  case 68: /* expr: MINUS expr  */
#line 591 "jucompiler.y"
    {
        (yyval.node) = newnode(Minus, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2206 "y.tab.c"
    break;

  case 69: /* expr: PLUS expr  */
#line 596 "jucompiler.y"
    {
        (yyval.node) = newnode(Plus, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2215 "y.tab.c"
    break;

  case 70: /* expr: expr DOTLENGTH  */
#line 601 "jucompiler.y"
    {
        (yyval.node) = newnode(Length, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 2224 "y.tab.c"
    break;

  case 71: /* expr: LPAR expr RPAR  */
#line 606 "jucompiler.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2232 "y.tab.c"
    break;

  case 72: /* method_invocation: IDENTIFIER LPAR args_opt RPAR  */
#line 613 "jucompiler.y"
    {
        (yyval.node) = newnode(Call, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        append_holder((yyval.node), (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));
    }
#line 2243 "y.tab.c"
    break;

  case 73: /* args_opt: %empty  */
#line 622 "jucompiler.y"
    {
        (yyval.node) = make_holder();
    }
#line 2251 "y.tab.c"
    break;

  case 75: /* expr_list: expr  */
#line 630 "jucompiler.y"
    {
        (yyval.node) = make_holder();
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2260 "y.tab.c"
    break;

  case 76: /* expr_list: expr_list COMMA expr  */
#line 635 "jucompiler.y"
    {
        addchild((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2269 "y.tab.c"
    break;

  case 77: /* parse_args: PARSEINT LPAR IDENTIFIER LSQ expr RSQ RPAR  */
#line 643 "jucompiler.y"
    {
        (yyval.node) = newnode(ParseArgs, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-4].lexeme)));
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 2279 "y.tab.c"
    break;

  case 78: /* type: INT  */
#line 652 "jucompiler.y"
    {
        (yyval.node) = newnode(Int, NULL);
    }
#line 2287 "y.tab.c"
    break;

  case 79: /* type: DOUBLE  */
#line 656 "jucompiler.y"
    {
        (yyval.node) = newnode(Double, NULL);
    }
#line 2295 "y.tab.c"
    break;

  case 80: /* type: BOOL  */
#line 660 "jucompiler.y"
    {
        (yyval.node) = newnode(Bool, NULL);
    }
#line 2303 "y.tab.c"
    break;

  case 81: /* type: STRING LSQ RSQ  */
#line 664 "jucompiler.y"
    {
        (yyval.node) = newnode(StringArray, NULL);
    }
#line 2311 "y.tab.c"
    break;


#line 2315 "y.tab.c"

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

#line 669 "jucompiler.y"


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

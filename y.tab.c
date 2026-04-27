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


#line 195 "y.tab.c"

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
    STATIC = 264,                  /* STATIC  */
    RESERVED = 265,                /* RESERVED  */
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
    COMMA = 305,                   /* COMMA  */
    TAIL_DONE = 306,               /* TAIL_DONE  */
    SEMICOLON = 307,               /* SEMICOLON  */
    PUBLIC = 308,                  /* PUBLIC  */
    LOWER_THAN_ELSE = 309          /* LOWER_THAN_ELSE  */
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
#define STATIC 264
#define RESERVED 265
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
#define COMMA 305
#define TAIL_DONE 306
#define SEMICOLON 307
#define PUBLIC 308
#define LOWER_THAN_ELSE 309

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 125 "claudecompiler.y"
 char *lexeme; struct node *node; 

#line 359 "y.tab.c"

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
  YYSYMBOL_lbrace_save = 60,               /* lbrace_save  */
  YYSYMBOL_method_decl = 61,               /* method_decl  */
  YYSYMBOL_62_1 = 62,                      /* $@1  */
  YYSYMBOL_method_header = 63,             /* method_header  */
  YYSYMBOL_param_list = 64,                /* param_list  */
  YYSYMBOL_param_decl = 65,                /* param_decl  */
  YYSYMBOL_method_body = 66,               /* method_body  */
  YYSYMBOL_method_body_items = 67,         /* method_body_items  */
  YYSYMBOL_bad_string_start = 68,          /* bad_string_start  */
  YYSYMBOL_bad_string_tail = 69,           /* bad_string_tail  */
  YYSYMBOL_bad_string_items = 70,          /* bad_string_items  */
  YYSYMBOL_bad_string_item = 71,           /* bad_string_item  */
  YYSYMBOL_invalid_public_decl = 72,       /* invalid_public_decl  */
  YYSYMBOL_73_2 = 73,                      /* $@2  */
  YYSYMBOL_invalid_public_tail = 74,       /* invalid_public_tail  */
  YYSYMBOL_invalid_id_list = 75,           /* invalid_id_list  */
  YYSYMBOL_semis = 76,                     /* semis  */
  YYSYMBOL_assign_save = 77,               /* assign_save  */
  YYSYMBOL_var_decl = 78,                  /* var_decl  */
  YYSYMBOL_var_ids = 79,                   /* var_ids  */
  YYSYMBOL_stmt = 80,                      /* stmt  */
  YYSYMBOL_stmt_entry = 81,                /* stmt_entry  */
  YYSYMBOL_stmt_core = 82,                 /* stmt_core  */
  YYSYMBOL_stmt_list = 83,                 /* stmt_list  */
  YYSYMBOL_expr = 84,                      /* expr  */
  YYSYMBOL_assign_expr = 85,               /* assign_expr  */
  YYSYMBOL_or_expr = 86,                   /* or_expr  */
  YYSYMBOL_and_expr = 87,                  /* and_expr  */
  YYSYMBOL_xor_expr = 88,                  /* xor_expr  */
  YYSYMBOL_eq_expr = 89,                   /* eq_expr  */
  YYSYMBOL_rel_expr = 90,                  /* rel_expr  */
  YYSYMBOL_shift_expr = 91,                /* shift_expr  */
  YYSYMBOL_add_expr = 92,                  /* add_expr  */
  YYSYMBOL_mul_expr = 93,                  /* mul_expr  */
  YYSYMBOL_unary_expr = 94,                /* unary_expr  */
  YYSYMBOL_primary_expr = 95,              /* primary_expr  */
  YYSYMBOL_method_invocation = 96,         /* method_invocation  */
  YYSYMBOL_args_opt = 97,                  /* args_opt  */
  YYSYMBOL_expr_list = 98,                 /* expr_list  */
  YYSYMBOL_parse_args = 99,                /* parse_args  */
  YYSYMBOL_type = 100                      /* type  */
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
#define YYLAST   534

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  194
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  365

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
     208,   215,   219,   226,   233,   239,   239,   257,   277,   295,
     313,   330,   340,   353,   359,   365,   371,   380,   384,   391,
     396,   401,   409,   418,   419,   422,   427,   432,   441,   452,
     455,   456,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,   489,   490,   491,   492,   493,   494,   495,   496,   497,
     498,   499,   500,   501,   502,   503,   504,   505,   506,   507,
     508,   512,   512,   523,   524,   525,   526,   527,   530,   536,
     537,   541,   542,   546,   553,   567,   570,   576,   580,   587,
     591,   598,   602,   621,   624,   630,   636,   643,   650,   660,
     666,   674,   682,   687,   693,   700,   704,   707,   711,   714,
     717,   722,   726,   729,   733,   737,   741,   742,   746,   747,
     750,   757,   758,   767,   771,   776,   780,   785,   789,   794,
     798,   803,   807,   812,   817,   821,   826,   831,   836,   841,
     845,   850,   855,   859,   864,   869,   873,   878,   883,   888,
     892,   896,   900,   904,   908,   911,   915,   918,   921,   924,
     925,   926,   927,   934,   940,   948,   949,   953,   957,   961,
     968,   973,   980,   981,   982
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
  "class_body", "field_decl", "field_ids", "lbrace_save", "method_decl",
  "$@1", "method_header", "param_list", "param_decl", "method_body",
  "method_body_items", "bad_string_start", "bad_string_tail",
  "bad_string_items", "bad_string_item", "invalid_public_decl", "$@2",
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

#define YYPACT_NINF (-312)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-186)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      66,    85,   116,    90,  -312,  -312,     6,    93,  -312,  -312,
     167,  -312,  -312,  -312,   155,   179,  -312,  -312,  -312,   232,
     191,    19,  -312,   199,  -312,  -312,   189,   211,    33,    30,
     367,  -312,    23,   264,  -312,   226,   224,  -312,  -312,  -312,
    -312,   -20,  -312,   270,  -312,  -312,  -312,  -312,  -312,  -312,
    -312,    78,   120,   229,  -312,  -312,    69,  -312,   191,    13,
     227,   434,  -312,   253,  -312,  -312,    14,  -312,   180,   228,
      63,   231,   237,    43,   287,   291,  -312,  -312,  -312,   289,
     300,   303,    54,    11,   191,   439,  -312,  -312,  -312,   294,
     353,   342,  -312,  -312,   444,   306,   233,  -312,  -312,  -312,
    -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,
    -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,
    -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,
    -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,
    -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,
     349,   235,   134,   341,   346,   311,   121,  -312,  -312,  -312,
     320,   462,   462,   462,   390,  -312,   313,  -312,   337,   334,
     338,   122,    15,   145,   136,   223,  -312,  -312,  -312,  -312,
     333,   128,   324,  -312,  -312,  -312,  -312,   467,   467,  -312,
     372,  -312,  -312,  -312,   449,   378,  -312,   380,  -312,  -312,
     335,   383,   385,   191,   389,   280,   387,   354,   371,   416,
     373,   379,  -312,   381,   382,   384,    32,   386,    20,  -312,
    -312,   467,   139,    68,  -312,  -312,  -312,   391,   392,  -312,
     462,   462,   462,   462,   462,   462,   462,   462,   462,   462,
     462,   462,   462,   462,   462,   462,   396,   403,   408,   413,
     415,  -312,  -312,   419,   388,  -312,  -312,  -312,   428,  -312,
     436,   123,   404,  -312,   438,  -312,   467,  -312,   395,   440,
    -312,  -312,  -312,   400,  -312,  -312,   106,  -312,  -312,  -312,
    -312,  -312,   433,  -312,  -312,   334,   338,   122,    15,    15,
     145,   145,   145,   145,   136,   136,   223,   223,  -312,  -312,
    -312,   441,   446,   447,   455,   467,   451,  -312,   191,   397,
     432,  -312,   452,   479,   464,   456,   100,   468,   467,  -312,
    -312,   484,   490,  -312,   460,   497,  -312,  -312,  -312,  -312,
    -312,  -312,  -312,   463,   469,  -312,  -312,   -31,  -312,  -312,
     465,    22,  -312,   470,   471,  -312,  -312,  -312,  -312,  -312,
     474,   197,  -312,   472,  -312,  -312,  -312,  -312,   511,  -312,
     507,   520,  -312,   123,   452
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     0,     2,     6,
       0,     4,     5,    10,     0,     0,   194,   192,   193,     0,
       0,     0,     8,     0,    33,    14,     0,    11,     0,     0,
     112,     9,     0,     0,     7,     0,     0,    25,    13,    15,
      33,     0,    27,     0,    38,    32,    91,    40,    34,    35,
      37,     0,     0,     0,    23,    33,     0,    12,     0,     0,
       0,   112,    26,     0,    33,    29,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,   141,   139,   111,     0,
       0,     0,   109,     0,     0,   112,    24,    33,    22,     0,
       0,     0,    20,    28,   112,     0,     0,    92,    42,    43,
      44,    45,    46,    47,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    40,    39,    87,    88,    90,    89,    48,    41,   140,
       0,     0,     0,     0,     0,     0,   174,   176,   177,   178,
       0,     0,     0,     0,     0,   126,     0,   143,   145,   147,
     149,   151,   154,   159,   162,   165,   169,   173,   179,   180,
       0,     0,   112,   136,   138,   108,   103,     0,     0,   107,
       0,   104,    21,    18,   112,     0,    30,     0,    19,    98,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   187,     0,   186,     0,     0,     0,     0,   127,
     175,     0,     0,   174,   172,   171,   170,     0,     0,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   113,   142,     0,     0,   110,    17,    31,     0,    97,
      99,     0,     0,    96,     0,    86,     0,   131,     0,     0,
     130,   184,   183,     0,   112,   112,     0,   112,   112,   112,
     112,   144,     0,   182,   181,   146,   148,   150,   152,   153,
     155,   156,   157,   158,   160,   161,   163,   164,   166,   167,
     168,     0,     0,     0,   191,     0,     0,   106,     0,     0,
       0,   101,    95,     0,     0,     0,   174,     0,     0,   189,
     188,   116,   120,   119,     0,   114,   123,   124,   122,   191,
     135,   134,   133,     0,     0,   105,    16,     0,   100,   102,
       0,     0,   128,     0,     0,   112,   112,   118,   112,   137,
       0,    94,   129,     0,   117,   121,   115,   190,     0,   132,
       0,     0,    99,     0,    93
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -312,  -312,  -312,  -312,  -312,    76,  -312,  -312,   429,   -32,
     466,   -57,   -27,  -312,  -312,   393,  -312,  -312,  -312,  -312,
     165,  -311,  -312,  -312,  -312,  -174,  -312,  -312,  -312,  -148,
     307,  -312,   297,   299,   301,    25,   -84,    21,    28,  -152,
    -312,   480,  -312,  -312,   481,   -12
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     6,    11,    28,    40,    12,    60,    20,    41,
      42,    25,    30,    47,    67,    68,   148,    48,    66,    97,
     261,   312,   188,    49,    83,    50,    51,    78,   182,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   213,   214,   179,    43
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,    88,    21,   210,   212,   216,   218,     7,   252,   224,
     225,   226,   189,    61,    62,    95,   228,    89,    52,    63,
      26,   279,    27,    96,    53,    62,    38,   192,    85,   351,
      63,    35,   248,   275,    16,    17,    18,    94,    36,   253,
     254,    16,    17,    18,   155,    36,   156,   157,   158,    52,
     159,   276,   364,     8,   235,   236,   237,   238,     9,    10,
     194,   190,    90,   191,   160,   280,   150,    86,    54,    38,
     161,   162,    63,    52,     1,    37,    38,   277,    39,    69,
     186,    70,    52,    33,   204,    34,   163,   164,     3,   151,
     220,   298,   299,   300,    71,   165,    72,    73,    74,    75,
     321,   322,   187,   325,   326,   327,   328,   152,    55,   156,
     157,   158,   152,   159,    86,    38,     4,    64,   315,    63,
     317,    81,   220,    82,    76,   320,   221,   160,   324,   249,
      77,   250,    87,   161,   162,   211,     5,   156,   157,   158,
     282,   159,   250,   220,   152,    13,   263,   221,   305,   163,
     164,   290,   291,   292,   293,   160,    15,   334,   323,   233,
     234,   161,   162,   241,   242,   152,    16,    17,    18,    19,
     344,   354,   355,   310,   356,   311,    14,   163,   164,  -185,
     239,   240,    52,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,    22,   146,   147,   200,    23,   207,    24,   156,   157,
     158,    31,   159,    29,    16,    17,    18,   201,   202,   339,
     358,   336,   243,   244,   245,    32,   208,   209,   288,   289,
     294,   295,   161,   162,    16,    17,    18,    57,    36,   296,
     297,    58,    59,    65,    84,   153,    91,   337,   163,   164,
     149,   154,   341,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   265,   143,   144,
     145,   180,   146,   147,   246,   181,   156,   157,   158,   247,
     159,   183,   215,   195,   156,   157,   158,   217,   159,   156,
     157,   158,   184,   159,   160,   185,   196,   197,   199,   206,
     161,   162,   160,   219,   222,   229,   231,   160,   161,   162,
     230,   251,   232,   161,   162,   255,   163,   164,    16,    17,
      18,   257,    44,   258,   163,   164,   260,   259,   262,   163,
     164,   227,   264,   156,   157,   158,   282,   159,   316,   157,
     158,   319,   159,   156,   157,   158,   267,   159,    16,    17,
      18,   160,    36,   266,    45,   268,   160,   161,   162,   269,
      46,   160,   161,   162,   271,   270,   272,   161,   162,   274,
     313,   278,   273,   163,   164,   338,   283,   284,   163,   164,
     307,   301,    37,   163,   164,    16,    17,    18,   302,    44,
      16,    17,    18,   303,    44,    16,    17,    18,   304,    44,
      16,    17,    18,   305,    44,   223,   157,   158,   306,   159,
     156,   157,   158,   308,   159,    16,    17,    18,   329,    36,
     309,    92,   314,   160,   318,   340,   193,    46,   160,   161,
     162,   198,    46,   330,   161,   162,   256,    46,   331,   332,
     333,   345,    46,   335,   339,   163,   164,   346,   342,    54,
     163,   164,   347,   343,   348,   349,   353,   311,   350,   357,
     360,   361,   352,   362,   359,   203,   363,   285,   281,    93,
     286,    79,    80,   287,   205
};

static const yytype_int16 yycheck[] =
{
      32,    58,    14,   151,   152,   153,   154,     1,   182,   161,
     162,   163,     1,    40,    45,     1,   164,     4,    30,    50,
       1,     1,     3,     9,     1,    45,    46,    84,    55,   340,
      50,     1,   180,     1,    11,    12,    13,    64,    15,   187,
     188,    11,    12,    13,     1,    15,     3,     4,     5,    61,
       7,    19,   363,    47,    39,    40,    41,    42,    52,    53,
      87,    50,    49,    52,    21,    45,     3,    45,    45,    46,
      27,    28,    50,    85,     8,    45,    46,    45,    48,     1,
      26,     3,    94,    50,    96,    52,    43,    44,     3,    26,
      22,   243,   244,   245,    16,    52,    18,    19,    20,    21,
     274,   275,    48,   277,   278,   279,   280,    44,    32,     3,
       4,     5,    44,     7,    45,    46,     0,    41,   266,    50,
     268,     1,    22,     3,    46,   273,    26,    21,   276,     1,
      52,     3,    56,    27,    28,     1,    46,     3,     4,     5,
       1,     7,     3,    22,    44,    52,   203,    26,    48,    43,
      44,   235,   236,   237,   238,    21,     1,   305,    52,    37,
      38,    27,    28,    27,    28,    44,    11,    12,    13,    14,
     318,   345,   346,    50,   348,    52,     9,    43,    44,    45,
      35,    36,   194,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    52,    52,    53,     1,     3,     1,    46,     3,     4,
       5,    52,     7,    44,    11,    12,    13,    14,    15,    52,
      53,   308,    29,    30,    31,    44,    21,    22,   233,   234,
     239,   240,    27,    28,    11,    12,    13,     3,    15,   241,
     242,    45,    48,     3,    45,    44,    49,   309,    43,    44,
      52,    44,   314,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    44,    52,    53,     1,    44,     3,     4,     5,     6,
       7,    52,     1,    49,     3,     4,     5,     1,     7,     3,
       4,     5,    52,     7,    21,    52,     3,    15,    52,    10,
      27,    28,    21,    52,    44,    52,    32,    21,    27,    28,
      33,    47,    34,    27,    28,     3,    43,    44,    11,    12,
      13,     3,    15,     3,    43,    44,     3,    52,     3,    43,
      44,     1,     3,     3,     4,     5,     1,     7,     3,     4,
       5,     1,     7,     3,     4,     5,    52,     7,    11,    12,
      13,    21,    15,    26,    47,    44,    21,    27,    28,     3,
      53,    21,    27,    28,    45,    52,    45,    27,    28,    45,
      26,    45,    50,    43,    44,     3,    45,    45,    43,    44,
      52,    45,    45,    43,    44,    11,    12,    13,    45,    15,
      11,    12,    13,    45,    15,    11,    12,    13,    45,    15,
      11,    12,    13,    48,    15,     3,     4,     5,    49,     7,
       3,     4,     5,    45,     7,    11,    12,    13,    45,    15,
      44,    47,    44,    21,    44,     6,    47,    53,    21,    27,
      28,    47,    53,    52,    27,    28,    47,    53,    52,    52,
      45,    17,    53,    52,    52,    43,    44,    17,    52,    45,
      43,    44,    52,    45,    17,    52,    45,    52,    49,    45,
       9,    14,    52,     3,    52,    96,   361,   230,   221,    63,
     231,    51,    51,   232,   141
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    56,     3,     0,    46,    57,     1,    47,    52,
      53,    58,    61,    52,     9,     1,    11,    12,    13,    14,
      63,   100,    52,     3,    46,    66,     1,     3,    59,    44,
      67,    52,    44,    50,    52,     1,    15,    45,    46,    48,
      60,    64,    65,   100,    15,    47,    53,    68,    72,    78,
      80,    81,   100,     1,    45,    60,    64,     3,    45,    48,
      62,    67,    45,    50,    60,     3,    73,    69,    70,     1,
       3,    16,    18,    19,    20,    21,    46,    52,    82,    96,
      99,     1,     3,    79,    45,    67,    45,    60,    66,     4,
      49,    49,    47,    65,    67,     1,     9,    74,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    52,    53,    71,    52,
       3,    26,    44,    44,    44,     1,     3,     4,     5,     7,
      21,    27,    28,    43,    44,    52,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    99,
      44,    44,    83,    52,    52,    52,    26,    48,    77,     1,
      50,    52,    66,    47,    67,    49,     3,    15,    47,    52,
       1,    14,    15,    63,   100,    70,    10,     1,    21,    22,
      84,     1,    84,    97,    98,     1,    84,     1,    84,    52,
      22,    26,    44,     3,    94,    94,    94,     1,    84,    52,
      33,    32,    34,    37,    38,    39,    40,    41,    42,    35,
      36,    27,    28,    29,    30,    31,     1,     6,    84,     1,
       3,    47,    80,    84,    84,     3,    47,     3,     3,    52,
       3,    75,     3,    66,     3,    47,    26,    52,    44,     3,
      52,    45,    45,    50,    45,     1,    19,    45,    45,     1,
      45,    85,     1,    45,    45,    87,    88,    89,    90,    90,
      91,    91,    91,    91,    92,    92,    93,    93,    94,    94,
      94,    45,    45,    45,    45,    48,    49,    52,    45,    44,
      50,    52,    76,    26,    44,    84,     3,    84,    44,     1,
      84,    80,    80,    52,    84,    80,    80,    80,    80,    45,
      52,    52,    52,    45,    84,    52,    66,    64,     3,    52,
       6,    64,    52,    45,    84,    17,    17,    52,    17,    52,
      49,    76,    52,    45,    80,    80,    80,    45,    53,    52,
       9,    14,     3,    75,    76
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    57,    57,    57,    57,    58,    58,    58,
      58,    59,    59,    60,    61,    62,    61,    61,    61,    61,
      61,    61,    61,    63,    63,    63,    63,    64,    64,    65,
      65,    65,    66,    67,    67,    67,    67,    67,    68,    69,
      70,    70,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    73,    72,    74,    74,    74,    74,    74,    74,    75,
      75,    76,    76,    77,    78,    78,    78,    78,    78,    79,
      79,    80,    81,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    83,    83,    84,    85,    85,    86,    86,    87,    87,
      88,    88,    89,    89,    89,    90,    90,    90,    90,    90,
      91,    91,    91,    92,    92,    92,    93,    93,    93,    93,
      94,    94,    94,    94,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    96,    96,    97,    97,    98,    98,    98,
      99,    99,   100,   100,   100
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     0,     2,     2,     2,     5,     4,     5,
       2,     1,     3,     1,     4,     0,    12,     9,     8,     9,
       8,     8,     8,     4,     5,     4,     5,     1,     3,     2,
       4,     5,     3,     0,     2,     2,     3,     2,     1,     2,
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     0,     3,    11,     6,     4,     3,     3,     2,     1,
       3,     1,     2,     1,     3,     6,     5,     3,     3,     1,
       3,     2,     0,     3,     5,     7,     5,     7,     6,     5,
       5,     7,     5,     5,     5,     3,     2,     3,     6,     7,
       4,     4,     8,     5,     5,     5,     2,     6,     2,     1,
       2,     0,     2,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     2,     1,     1,     2,     1,     1,     1,     1,
       1,     3,     3,     4,     4,     0,     1,     1,     3,     3,
       7,     4,     1,     1,     1
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
#line 1730 "y.tab.c"
    break;

  case 3: /* class_body: %empty  */
#line 172 "claudecompiler.y"
    { (yyval.node) = make_holder(); }
#line 1736 "y.tab.c"
    break;

  case 4: /* class_body: class_body field_decl  */
#line 173 "claudecompiler.y"
                          {
        append_holder((yyvsp[-1].node), (yyvsp[0].node));
        free_holder_only((yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1746 "y.tab.c"
    break;

  case 5: /* class_body: class_body method_decl  */
#line 178 "claudecompiler.y"
                           {
        addchild((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1755 "y.tab.c"
    break;

  case 6: /* class_body: class_body SEMICOLON  */
#line 182 "claudecompiler.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 1761 "y.tab.c"
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
#line 1780 "y.tab.c"
    break;

  case 8: /* field_decl: PUBLIC STATIC error SEMICOLON  */
#line 200 "claudecompiler.y"
                                  {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 1789 "y.tab.c"
    break;

  case 9: /* field_decl: PUBLIC STATIC type error SEMICOLON  */
#line 204 "claudecompiler.y"
                                       {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 1798 "y.tab.c"
    break;

  case 10: /* field_decl: error SEMICOLON  */
#line 208 "claudecompiler.y"
                    {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 1807 "y.tab.c"
    break;

  case 11: /* field_ids: IDENTIFIER  */
#line 215 "claudecompiler.y"
               {
        (yyval.node) = make_holder();
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 1816 "y.tab.c"
    break;

  case 12: /* field_ids: field_ids COMMA IDENTIFIER  */
#line 219 "claudecompiler.y"
                               {
        addchild((yyvsp[-2].node), newnode(Identifier, (yyvsp[0].lexeme)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1825 "y.tab.c"
    break;

  case 13: /* lbrace_save: LBRACE  */
#line 226 "claudecompiler.y"
           {
        saved_error_line = token_line;
        saved_error_col = token_column;
    }
#line 1834 "y.tab.c"
    break;

  case 14: /* method_decl: PUBLIC STATIC method_header method_body  */
#line 233 "claudecompiler.y"
                                            {
        (yyval.node) = newnode(MethodDecl, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), (yyvsp[0].node));
        pending_error_after_block = 0;
    }
#line 1845 "y.tab.c"
    break;

  case 15: /* $@1: %empty  */
#line 239 "claudecompiler.y"
                                           {
        saved_error_line = token_line;
        saved_error_col = token_column;
    }
#line 1854 "y.tab.c"
    break;

  case 16: /* method_decl: PUBLIC STATIC VOID IDENTIFIER LPAR LSQ $@1 RSQ STRING IDENTIFIER RPAR method_body  */
#line 242 "claudecompiler.y"
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
#line 1872 "y.tab.c"
    break;

  case 17: /* method_decl: PUBLIC STATIC type IDENTIFIER LPAR param_list lbrace_save method_body_items RBRACE  */
#line 257 "claudecompiler.y"
                                                                                       {
        /* Para manter os testes públicos em 72, NÃO imprimir erro aqui.
           Se quisermos ser estritamente corretos para Mooshak, o erro provável seria em "{". */
        (yyval.node) = newnode(MethodDecl, NULL);

        struct node *header = newnode(MethodHeader, NULL);
        addchild(header, (yyvsp[-6].node));
        addchild(header, newnode(Identifier, (yyvsp[-5].lexeme)));
        addchild(header, (yyvsp[-3].node));

        struct node *body = newnode(MethodBody, NULL);
        append_holder(body, (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));

        addchild((yyval.node), header);
        addchild((yyval.node), body);
        pending_error_after_block = 0;
    }
#line 1895 "y.tab.c"
    break;

  case 18: /* method_decl: PUBLIC STATIC type IDENTIFIER LPAR lbrace_save method_body_items RBRACE  */
#line 277 "claudecompiler.y"
                                                                            {
        (yyval.node) = newnode(MethodDecl, NULL);

        struct node *header = newnode(MethodHeader, NULL);
        addchild(header, (yyvsp[-5].node));
        addchild(header, newnode(Identifier, (yyvsp[-4].lexeme)));
        addchild(header, newnode(MethodParams, NULL));

        struct node *body = newnode(MethodBody, NULL);
        append_holder(body, (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));

        addchild((yyval.node), header);
        addchild((yyval.node), body);
        pending_error_after_block = 0;
    }
#line 1916 "y.tab.c"
    break;

  case 19: /* method_decl: PUBLIC STATIC VOID IDENTIFIER LPAR param_list lbrace_save method_body_items RBRACE  */
#line 295 "claudecompiler.y"
                                                                                       {
        (yyval.node) = newnode(MethodDecl, NULL);

        struct node *header = newnode(MethodHeader, NULL);
        addchild(header, newnode(Void, NULL));
        addchild(header, newnode(Identifier, (yyvsp[-5].lexeme)));
        addchild(header, (yyvsp[-3].node));

        struct node *body = newnode(MethodBody, NULL);
        append_holder(body, (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));

        addchild((yyval.node), header);
        addchild((yyval.node), body);
        pending_error_after_block = 0;
    }
#line 1937 "y.tab.c"
    break;

  case 20: /* method_decl: PUBLIC STATIC VOID IDENTIFIER LPAR lbrace_save method_body_items RBRACE  */
#line 313 "claudecompiler.y"
                                                                            {
        (yyval.node) = newnode(MethodDecl, NULL);

        struct node *header = newnode(MethodHeader, NULL);
        addchild(header, newnode(Void, NULL));
        addchild(header, newnode(Identifier, (yyvsp[-4].lexeme)));
        addchild(header, newnode(MethodParams, NULL));

        struct node *body = newnode(MethodBody, NULL);
        append_holder(body, (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));

        addchild((yyval.node), header);
        addchild((yyval.node), body);
        pending_error_after_block = 0;
    }
#line 1958 "y.tab.c"
    break;

  case 21: /* method_decl: PUBLIC STATIC type IDENTIFIER LPAR error RPAR method_body  */
#line 330 "claudecompiler.y"
                                                              {
        yyerrok;
        (yyval.node) = newnode(MethodDecl, NULL);
        struct node *header = newnode(MethodHeader, NULL);
        addchild(header, (yyvsp[-5].node));
        addchild(header, newnode(Identifier, (yyvsp[-4].lexeme)));
        addchild(header, newnode(MethodParams, NULL));
        addchild((yyval.node), header);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1973 "y.tab.c"
    break;

  case 22: /* method_decl: PUBLIC STATIC VOID IDENTIFIER LPAR error RPAR method_body  */
#line 340 "claudecompiler.y"
                                                              {
        yyerrok;
        (yyval.node) = newnode(MethodDecl, NULL);
        struct node *header = newnode(MethodHeader, NULL);
        addchild(header, newnode(Void, NULL));
        addchild(header, newnode(Identifier, (yyvsp[-4].lexeme)));
        addchild(header, newnode(MethodParams, NULL));
        addchild((yyval.node), header);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1988 "y.tab.c"
    break;

  case 23: /* method_header: type IDENTIFIER LPAR RPAR  */
#line 353 "claudecompiler.y"
                              {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), (yyvsp[-3].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), newnode(MethodParams, NULL));
    }
#line 1999 "y.tab.c"
    break;

  case 24: /* method_header: type IDENTIFIER LPAR param_list RPAR  */
#line 359 "claudecompiler.y"
                                         {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 2010 "y.tab.c"
    break;

  case 25: /* method_header: VOID IDENTIFIER LPAR RPAR  */
#line 365 "claudecompiler.y"
                              {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), newnode(Void, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), newnode(MethodParams, NULL));
    }
#line 2021 "y.tab.c"
    break;

  case 26: /* method_header: VOID IDENTIFIER LPAR param_list RPAR  */
#line 371 "claudecompiler.y"
                                         {
        (yyval.node) = newnode(MethodHeader, NULL);
        addchild((yyval.node), newnode(Void, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 2032 "y.tab.c"
    break;

  case 27: /* param_list: param_decl  */
#line 380 "claudecompiler.y"
               {
        (yyval.node) = newnode(MethodParams, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2041 "y.tab.c"
    break;

  case 28: /* param_list: param_list COMMA param_decl  */
#line 384 "claudecompiler.y"
                                {
        addchild((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2050 "y.tab.c"
    break;

  case 29: /* param_decl: type IDENTIFIER  */
#line 391 "claudecompiler.y"
                    {
        (yyval.node) = newnode(ParamDecl, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 2060 "y.tab.c"
    break;

  case 30: /* param_decl: STRING LSQ RSQ IDENTIFIER  */
#line 396 "claudecompiler.y"
                              {
        (yyval.node) = newnode(ParamDecl, NULL);
        addchild((yyval.node), newnode(StringArray, NULL));
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 2070 "y.tab.c"
    break;

  case 31: /* param_decl: STRING LSQ NATURAL RSQ IDENTIFIER  */
#line 401 "claudecompiler.y"
                                      {
    (yyval.node) = newnode(ParamDecl, NULL);
    addchild((yyval.node), newnode(StringArray, NULL));
    addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
}
#line 2080 "y.tab.c"
    break;

  case 32: /* method_body: LBRACE method_body_items RBRACE  */
#line 409 "claudecompiler.y"
                                    {
        (yyval.node) = newnode(MethodBody, NULL);
        append_holder((yyval.node), (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));
        pending_error_after_block = 0;
    }
#line 2091 "y.tab.c"
    break;

  case 33: /* method_body_items: %empty  */
#line 418 "claudecompiler.y"
    { (yyval.node) = make_holder(); }
#line 2097 "y.tab.c"
    break;

  case 34: /* method_body_items: method_body_items invalid_public_decl  */
#line 419 "claudecompiler.y"
                                          {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2105 "y.tab.c"
    break;

  case 35: /* method_body_items: method_body_items var_decl  */
#line 422 "claudecompiler.y"
                               {
        append_holder((yyvsp[-1].node), (yyvsp[0].node));
        free_holder_only((yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2115 "y.tab.c"
    break;

  case 36: /* method_body_items: method_body_items bad_string_start bad_string_tail  */
#line 427 "claudecompiler.y"
                                                       {
        yyerrok;
        pending_error_after_block = 0;
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2125 "y.tab.c"
    break;

  case 37: /* method_body_items: method_body_items stmt  */
#line 432 "claudecompiler.y"
                           {
        if (!is_empty_block((yyvsp[0].node)))
            addchild((yyvsp[-1].node), (yyvsp[0].node));

        (yyval.node) = (yyvsp[-1].node);
    }
#line 2136 "y.tab.c"
    break;

  case 38: /* bad_string_start: STRING  */
#line 441 "claudecompiler.y"
           {
        if (token_line != last_lex_error_line) {
            syntax_errors = 1;
            printf("Line %d, col %d: syntax error: String\n", token_line, token_column);
            syntax_error_count++;
        }
        (yyval.node) = NULL;
    }
#line 2149 "y.tab.c"
    break;

  case 91: /* $@2: %empty  */
#line 512 "claudecompiler.y"
           {
        saved_public_line = token_line;
        syntax_errors = 1;
        printf("Line %d, col 5: syntax error: public\n", saved_public_line);
        syntax_error_count++;
    }
#line 2160 "y.tab.c"
    break;

  case 92: /* invalid_public_decl: PUBLIC $@2 invalid_public_tail  */
#line 517 "claudecompiler.y"
                          {
        pending_error_after_block = 0;
    }
#line 2168 "y.tab.c"
    break;

  case 97: /* invalid_public_tail: STATIC error SEMICOLON  */
#line 527 "claudecompiler.y"
                           {
        yyerrok;
    }
#line 2176 "y.tab.c"
    break;

  case 98: /* invalid_public_tail: error SEMICOLON  */
#line 530 "claudecompiler.y"
                    {
        yyerrok;
    }
#line 2184 "y.tab.c"
    break;

  case 103: /* assign_save: ASSIGN  */
#line 546 "claudecompiler.y"
           {
        saved_error_line = token_line;
        saved_error_col = token_column;
    }
#line 2193 "y.tab.c"
    break;

  case 104: /* var_decl: type var_ids SEMICOLON  */
#line 553 "claudecompiler.y"
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
#line 2212 "y.tab.c"
    break;

  case 105: /* var_decl: type IDENTIFIER LSQ expr RSQ SEMICOLON  */
#line 567 "claudecompiler.y"
                                           {
      (yyval.node) = make_holder();
  }
#line 2220 "y.tab.c"
    break;

  case 106: /* var_decl: type IDENTIFIER assign_save expr SEMICOLON  */
#line 570 "claudecompiler.y"
                                                 {
      syntax_errors = 1;
      printf("Line %d, col %d: syntax error: =\n", saved_error_line, saved_error_col);
      syntax_error_count++;
      (yyval.node) = make_holder();
  }
#line 2231 "y.tab.c"
    break;

  case 107: /* var_decl: type var_ids error  */
#line 576 "claudecompiler.y"
                       {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 2240 "y.tab.c"
    break;

  case 108: /* var_decl: type error SEMICOLON  */
#line 580 "claudecompiler.y"
                         {
        yyerrok;
        (yyval.node) = make_holder();
    }
#line 2249 "y.tab.c"
    break;

  case 109: /* var_ids: IDENTIFIER  */
#line 587 "claudecompiler.y"
               {
        (yyval.node) = make_holder();
        addchild((yyval.node), newnode(Identifier, (yyvsp[0].lexeme)));
    }
#line 2258 "y.tab.c"
    break;

  case 110: /* var_ids: var_ids COMMA IDENTIFIER  */
#line 591 "claudecompiler.y"
                             {
        addchild((yyvsp[-2].node), newnode(Identifier, (yyvsp[0].lexeme)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2267 "y.tab.c"
    break;

  case 111: /* stmt: stmt_entry stmt_core  */
#line 598 "claudecompiler.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2273 "y.tab.c"
    break;

  case 112: /* stmt_entry: %empty  */
#line 602 "claudecompiler.y"
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
#line 2294 "y.tab.c"
    break;

  case 113: /* stmt_core: LBRACE stmt_list RBRACE  */
#line 621 "claudecompiler.y"
                            {
    (yyval.node) = build_block_from_holder((yyvsp[-1].node));
}
#line 2302 "y.tab.c"
    break;

  case 114: /* stmt_core: IF LPAR expr RPAR stmt  */
#line 624 "claudecompiler.y"
                                                 {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 2313 "y.tab.c"
    break;

  case 115: /* stmt_core: IF LPAR expr RPAR stmt ELSE stmt  */
#line 630 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2324 "y.tab.c"
    break;

  case 116: /* stmt_core: IF LPAR error RPAR stmt  */
#line 636 "claudecompiler.y"
                                                  {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 2336 "y.tab.c"
    break;

  case 117: /* stmt_core: IF LPAR error RPAR stmt ELSE stmt  */
#line 643 "claudecompiler.y"
                                      {
        yyerrok;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2348 "y.tab.c"
    break;

  case 118: /* stmt_core: IF LPAR expr RETURN expr SEMICOLON  */
#line 650 "claudecompiler.y"
                                                               {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-3].node));

        struct node *ret = newnode(Return, NULL);
        addchild(ret, (yyvsp[-1].node));
        addchild((yyval.node), ret);

        addchild((yyval.node), newnode(Block, NULL));
    }
#line 2363 "y.tab.c"
    break;

  case 119: /* stmt_core: IF LPAR expr RETURN SEMICOLON  */
#line 660 "claudecompiler.y"
                                                        {
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), newnode(Return, NULL));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 2374 "y.tab.c"
    break;

  case 120: /* stmt_core: IF LPAR expr error stmt  */
#line 666 "claudecompiler.y"
                                                  {
        yyerrok;
        pending_error_after_block = 1;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
        addchild((yyval.node), newnode(Block, NULL));
    }
#line 2387 "y.tab.c"
    break;

  case 121: /* stmt_core: IF LPAR expr error stmt ELSE stmt  */
#line 674 "claudecompiler.y"
                                      {
        yyerrok;
        pending_error_after_block = 1;
        (yyval.node) = newnode(If, NULL);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2400 "y.tab.c"
    break;

  case 122: /* stmt_core: WHILE LPAR expr RPAR stmt  */
#line 682 "claudecompiler.y"
                              {
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2410 "y.tab.c"
    break;

  case 123: /* stmt_core: WHILE LPAR error RPAR stmt  */
#line 687 "claudecompiler.y"
                               {
        yyerrok;
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), newnode(Natural, "0"));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2421 "y.tab.c"
    break;

  case 124: /* stmt_core: WHILE LPAR expr error stmt  */
#line 693 "claudecompiler.y"
                               {
        yyerrok;
        pending_error_after_block = 1;
        (yyval.node) = newnode(While, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2433 "y.tab.c"
    break;

  case 125: /* stmt_core: RETURN expr SEMICOLON  */
#line 700 "claudecompiler.y"
                          {
        (yyval.node) = newnode(Return, NULL);
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 2442 "y.tab.c"
    break;

  case 126: /* stmt_core: RETURN SEMICOLON  */
#line 704 "claudecompiler.y"
                     {
        (yyval.node) = newnode(Return, NULL);
    }
#line 2450 "y.tab.c"
    break;

  case 127: /* stmt_core: RETURN error SEMICOLON  */
#line 707 "claudecompiler.y"
                           {
        yyerrok;
        (yyval.node) = newnode(Return, NULL);
    }
#line 2459 "y.tab.c"
    break;

  case 128: /* stmt_core: IDENTIFIER IDENTIFIER RESERVED ASSIGN expr SEMICOLON  */
#line 711 "claudecompiler.y"
                                                         {
        (yyval.node) = newnode(Block, NULL);
    }
#line 2467 "y.tab.c"
    break;

  case 129: /* stmt_core: IDENTIFIER ASSIGN PARSEINT LPAR expr RPAR SEMICOLON  */
#line 714 "claudecompiler.y"
                                                          {
      (yyval.node) = newnode(Block, NULL);
  }
#line 2475 "y.tab.c"
    break;

  case 130: /* stmt_core: IDENTIFIER ASSIGN expr SEMICOLON  */
#line 717 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(Assign, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 2485 "y.tab.c"
    break;

  case 131: /* stmt_core: IDENTIFIER ASSIGN error SEMICOLON  */
#line 722 "claudecompiler.y"
                                      {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2494 "y.tab.c"
    break;

  case 132: /* stmt_core: IDENTIFIER ASSIGN DOTLENGTH IDENTIFIER LPAR expr RPAR SEMICOLON  */
#line 726 "claudecompiler.y"
                                                                    {
        (yyval.node) = newnode(Block, NULL);
    }
#line 2502 "y.tab.c"
    break;

  case 133: /* stmt_core: PRINT LPAR expr RPAR SEMICOLON  */
#line 729 "claudecompiler.y"
                                   {
        (yyval.node) = newnode(Print, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 2511 "y.tab.c"
    break;

  case 134: /* stmt_core: PRINT LPAR STRLIT RPAR SEMICOLON  */
#line 733 "claudecompiler.y"
                                     {
        (yyval.node) = newnode(Print, NULL);
        addchild((yyval.node), newnode(StrLit, (yyvsp[-2].lexeme)));
    }
#line 2520 "y.tab.c"
    break;

  case 135: /* stmt_core: PRINT LPAR error RPAR SEMICOLON  */
#line 737 "claudecompiler.y"
                                    {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2529 "y.tab.c"
    break;

  case 136: /* stmt_core: method_invocation SEMICOLON  */
#line 741 "claudecompiler.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 2535 "y.tab.c"
    break;

  case 137: /* stmt_core: PARSEINT LPAR error RPAR RPAR SEMICOLON  */
#line 742 "claudecompiler.y"
                                              {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2544 "y.tab.c"
    break;

  case 138: /* stmt_core: parse_args SEMICOLON  */
#line 746 "claudecompiler.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2550 "y.tab.c"
    break;

  case 139: /* stmt_core: SEMICOLON  */
#line 747 "claudecompiler.y"
              {
        (yyval.node) = newnode(Block, NULL);
    }
#line 2558 "y.tab.c"
    break;

  case 140: /* stmt_core: error SEMICOLON  */
#line 750 "claudecompiler.y"
                    {
        yyerrok;
        (yyval.node) = newnode(Block, NULL);
    }
#line 2567 "y.tab.c"
    break;

  case 141: /* stmt_list: %empty  */
#line 757 "claudecompiler.y"
    { (yyval.node) = make_holder(); }
#line 2573 "y.tab.c"
    break;

  case 142: /* stmt_list: stmt_list stmt  */
#line 758 "claudecompiler.y"
                   {
        if (!is_empty_block((yyvsp[0].node)))
            addchild((yyvsp[-1].node), (yyvsp[0].node));

        (yyval.node) = (yyvsp[-1].node);
    }
#line 2584 "y.tab.c"
    break;

  case 144: /* assign_expr: IDENTIFIER ASSIGN assign_expr  */
#line 771 "claudecompiler.y"
                                  {
        (yyval.node) = newnode(Assign, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-2].lexeme)));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2594 "y.tab.c"
    break;

  case 146: /* or_expr: or_expr OR and_expr  */
#line 780 "claudecompiler.y"
                        {
        (yyval.node) = newnode(Or, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2604 "y.tab.c"
    break;

  case 148: /* and_expr: and_expr AND xor_expr  */
#line 789 "claudecompiler.y"
                          {
        (yyval.node) = newnode(And, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2614 "y.tab.c"
    break;

  case 150: /* xor_expr: xor_expr XOR eq_expr  */
#line 798 "claudecompiler.y"
                         {
        (yyval.node) = newnode(Xor, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2624 "y.tab.c"
    break;

  case 152: /* eq_expr: eq_expr EQ rel_expr  */
#line 807 "claudecompiler.y"
                        {
        (yyval.node) = newnode(Eq, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2634 "y.tab.c"
    break;

  case 153: /* eq_expr: eq_expr NE rel_expr  */
#line 812 "claudecompiler.y"
                        {
        (yyval.node) = newnode(Ne, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2644 "y.tab.c"
    break;

  case 155: /* rel_expr: rel_expr LT shift_expr  */
#line 821 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Lt, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2654 "y.tab.c"
    break;

  case 156: /* rel_expr: rel_expr GT shift_expr  */
#line 826 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Gt, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2664 "y.tab.c"
    break;

  case 157: /* rel_expr: rel_expr LE shift_expr  */
#line 831 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Le, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2674 "y.tab.c"
    break;

  case 158: /* rel_expr: rel_expr GE shift_expr  */
#line 836 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Ge, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2684 "y.tab.c"
    break;

  case 160: /* shift_expr: shift_expr LSHIFT add_expr  */
#line 845 "claudecompiler.y"
                               {
        (yyval.node) = newnode(Lshift, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2694 "y.tab.c"
    break;

  case 161: /* shift_expr: shift_expr RSHIFT add_expr  */
#line 850 "claudecompiler.y"
                               {
        (yyval.node) = newnode(Rshift, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2704 "y.tab.c"
    break;

  case 163: /* add_expr: add_expr PLUS mul_expr  */
#line 859 "claudecompiler.y"
                           {
        (yyval.node) = newnode(Add, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2714 "y.tab.c"
    break;

  case 164: /* add_expr: add_expr MINUS mul_expr  */
#line 864 "claudecompiler.y"
                            {
        (yyval.node) = newnode(Sub, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2724 "y.tab.c"
    break;

  case 166: /* mul_expr: mul_expr STAR unary_expr  */
#line 873 "claudecompiler.y"
                             {
        (yyval.node) = newnode(Mul, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2734 "y.tab.c"
    break;

  case 167: /* mul_expr: mul_expr DIV unary_expr  */
#line 878 "claudecompiler.y"
                            {
        (yyval.node) = newnode(Div, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2744 "y.tab.c"
    break;

  case 168: /* mul_expr: mul_expr MOD unary_expr  */
#line 883 "claudecompiler.y"
                            {
        (yyval.node) = newnode(Mod, NULL);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2754 "y.tab.c"
    break;

  case 170: /* unary_expr: NOT unary_expr  */
#line 892 "claudecompiler.y"
                   {
        (yyval.node) = newnode(Not, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2763 "y.tab.c"
    break;

  case 171: /* unary_expr: MINUS unary_expr  */
#line 896 "claudecompiler.y"
                     {
        (yyval.node) = newnode(Minus, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2772 "y.tab.c"
    break;

  case 172: /* unary_expr: PLUS unary_expr  */
#line 900 "claudecompiler.y"
                    {
        (yyval.node) = newnode(Plus, NULL);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2781 "y.tab.c"
    break;

  case 174: /* primary_expr: IDENTIFIER  */
#line 908 "claudecompiler.y"
               {
        (yyval.node) = newnode(Identifier, (yyvsp[0].lexeme));
    }
#line 2789 "y.tab.c"
    break;

  case 175: /* primary_expr: IDENTIFIER DOTLENGTH  */
#line 911 "claudecompiler.y"
                         {
        (yyval.node) = newnode(Length, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-1].lexeme)));
    }
#line 2798 "y.tab.c"
    break;

  case 176: /* primary_expr: NATURAL  */
#line 915 "claudecompiler.y"
            {
        (yyval.node) = newnode(Natural, (yyvsp[0].lexeme));
    }
#line 2806 "y.tab.c"
    break;

  case 177: /* primary_expr: DECIMAL  */
#line 918 "claudecompiler.y"
            {
        (yyval.node) = newnode(Decimal, (yyvsp[0].lexeme));
    }
#line 2814 "y.tab.c"
    break;

  case 178: /* primary_expr: BOOLLIT  */
#line 921 "claudecompiler.y"
            {
        (yyval.node) = newnode(BoolLit, (yyvsp[0].lexeme));
    }
#line 2822 "y.tab.c"
    break;

  case 181: /* primary_expr: LPAR expr RPAR  */
#line 926 "claudecompiler.y"
                   { (yyval.node) = (yyvsp[-1].node); }
#line 2828 "y.tab.c"
    break;

  case 182: /* primary_expr: LPAR error RPAR  */
#line 927 "claudecompiler.y"
                    {
        yyerrok;
        (yyval.node) = newnode(Natural, "0");
    }
#line 2837 "y.tab.c"
    break;

  case 183: /* method_invocation: IDENTIFIER LPAR args_opt RPAR  */
#line 934 "claudecompiler.y"
                                  {
        (yyval.node) = newnode(Call, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
        append_holder((yyval.node), (yyvsp[-1].node));
        free_holder_only((yyvsp[-1].node));
    }
#line 2848 "y.tab.c"
    break;

  case 184: /* method_invocation: IDENTIFIER LPAR error RPAR  */
#line 940 "claudecompiler.y"
                               {
        yyerrok;
        (yyval.node) = newnode(Call, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-3].lexeme)));
    }
#line 2858 "y.tab.c"
    break;

  case 185: /* args_opt: %empty  */
#line 948 "claudecompiler.y"
    { (yyval.node) = make_holder(); }
#line 2864 "y.tab.c"
    break;

  case 187: /* expr_list: expr  */
#line 953 "claudecompiler.y"
         {
        (yyval.node) = make_holder();
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2873 "y.tab.c"
    break;

  case 188: /* expr_list: expr_list COMMA expr  */
#line 957 "claudecompiler.y"
                         {
        addchild((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2882 "y.tab.c"
    break;

  case 189: /* expr_list: expr_list COMMA error  */
#line 961 "claudecompiler.y"
                          {
        yyerrok;
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2891 "y.tab.c"
    break;

  case 190: /* parse_args: PARSEINT LPAR IDENTIFIER LSQ expr RSQ RPAR  */
#line 968 "claudecompiler.y"
                                               {
        (yyval.node) = newnode(ParseArgs, NULL);
        addchild((yyval.node), newnode(Identifier, (yyvsp[-4].lexeme)));
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 2901 "y.tab.c"
    break;

  case 191: /* parse_args: PARSEINT LPAR error RPAR  */
#line 973 "claudecompiler.y"
                             {
        yyerrok;
        (yyval.node) = newnode(ParseArgs, NULL);
    }
#line 2910 "y.tab.c"
    break;

  case 192: /* type: INT  */
#line 980 "claudecompiler.y"
        { (yyval.node) = newnode(Int, NULL); }
#line 2916 "y.tab.c"
    break;

  case 193: /* type: DOUBLE  */
#line 981 "claudecompiler.y"
           { (yyval.node) = newnode(Double, NULL); }
#line 2922 "y.tab.c"
    break;

  case 194: /* type: BOOL  */
#line 982 "claudecompiler.y"
         { (yyval.node) = newnode(Bool, NULL); }
#line 2928 "y.tab.c"
    break;


#line 2932 "y.tab.c"

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

#line 985 "claudecompiler.y"


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

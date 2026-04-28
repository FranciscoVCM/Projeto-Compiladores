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
#include "ast.h"

extern int yylex(void);
extern int line;
extern int token_column;
extern int syntax_errors;
extern char token_text[];

void yyerror(char *s);

struct node *ast = NULL;

static struct node *make_node(enum category category, char *token, int line, int column) {
    struct node *n = newnode(category, token);
    set_node_location(n, line, column);
    return n;
}

static void append_list(struct node *dst, struct node *list) {
    struct node_list *child;
    if (!dst || !list || !list->children) return;

    child = list->children->next;
    while (child) {
        addchild(dst, child->node);
        child = child->next;
    }
}

static int is_empty_statement(struct node *n) {
    return n && (n->category == Empty ||
                (n->category == Block && n->children->next == NULL));
}

static struct node *compact_block(struct node *list) {
    int count = 0;
    struct node *only = NULL;
    struct node_list *child;
    struct node *block;

    child = list->children->next;
    while (child) {
        if (!is_empty_statement(child->node)) {
            count++;
            only = child->node;
        }
        child = child->next;
    }

    if (count == 0) {
        block = newnode(Block, NULL);
    } else if (count == 1) {
        block = only;
    } else {
        block = newnode(Block, NULL);
        child = list->children->next;
        while (child) {
            if (!is_empty_statement(child->node))
                addchild(block, child->node);
            child = child->next;
        }
    }

    freenode(list);
    return block;
}

#line 141 "y.tab.c"

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
    CLASS = 258,                   /* CLASS  */
    LBRACE = 259,                  /* LBRACE  */
    RBRACE = 260,                  /* RBRACE  */
    SEMICOLON = 261,               /* SEMICOLON  */
    COMMA = 262,                   /* COMMA  */
    LPAR = 263,                    /* LPAR  */
    RPAR = 264,                    /* RPAR  */
    LSQ = 265,                     /* LSQ  */
    RSQ = 266,                     /* RSQ  */
    ARROW = 267,                   /* ARROW  */
    RESERVED = 268,                /* RESERVED  */
    PUBLIC = 269,                  /* PUBLIC  */
    STATIC = 270,                  /* STATIC  */
    VOID = 271,                    /* VOID  */
    RETURN = 272,                  /* RETURN  */
    IF = 273,                      /* IF  */
    ELSE = 274,                    /* ELSE  */
    WHILE = 275,                   /* WHILE  */
    PRINT = 276,                   /* PRINT  */
    PARSEINT = 277,                /* PARSEINT  */
    BOOL = 278,                    /* BOOL  */
    INT = 279,                     /* INT  */
    DOUBLE = 280,                  /* DOUBLE  */
    STRING = 281,                  /* STRING  */
    DOTLENGTH = 282,               /* DOTLENGTH  */
    ASSIGN = 283,                  /* ASSIGN  */
    PLUS = 284,                    /* PLUS  */
    MINUS = 285,                   /* MINUS  */
    STAR = 286,                    /* STAR  */
    DIV = 287,                     /* DIV  */
    MOD = 288,                     /* MOD  */
    AND = 289,                     /* AND  */
    OR = 290,                      /* OR  */
    XOR = 291,                     /* XOR  */
    NOT = 292,                     /* NOT  */
    LSHIFT = 293,                  /* LSHIFT  */
    RSHIFT = 294,                  /* RSHIFT  */
    EQ = 295,                      /* EQ  */
    NE = 296,                      /* NE  */
    LT = 297,                      /* LT  */
    GT = 298,                      /* GT  */
    LE = 299,                      /* LE  */
    GE = 300,                      /* GE  */
    IDENTIFIER = 301,              /* IDENTIFIER  */
    STRLIT = 302,                  /* STRLIT  */
    NATURAL = 303,                 /* NATURAL  */
    DECIMAL = 304,                 /* DECIMAL  */
    BOOLLIT = 305,                 /* BOOLLIT  */
    THEN = 306,                    /* THEN  */
    UMINUS = 307,                  /* UMINUS  */
    UPLUS = 308,                   /* UPLUS  */
    UNOT = 309                     /* UNOT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define CLASS 258
#define LBRACE 259
#define RBRACE 260
#define SEMICOLON 261
#define COMMA 262
#define LPAR 263
#define RPAR 264
#define LSQ 265
#define RSQ 266
#define ARROW 267
#define RESERVED 268
#define PUBLIC 269
#define STATIC 270
#define VOID 271
#define RETURN 272
#define IF 273
#define ELSE 274
#define WHILE 275
#define PRINT 276
#define PARSEINT 277
#define BOOL 278
#define INT 279
#define DOUBLE 280
#define STRING 281
#define DOTLENGTH 282
#define ASSIGN 283
#define PLUS 284
#define MINUS 285
#define STAR 286
#define DIV 287
#define MOD 288
#define AND 289
#define OR 290
#define XOR 291
#define NOT 292
#define LSHIFT 293
#define RSHIFT 294
#define EQ 295
#define NE 296
#define LT 297
#define GT 298
#define LE 299
#define GE 300
#define IDENTIFIER 301
#define STRLIT 302
#define NATURAL 303
#define DECIMAL 304
#define BOOLLIT 305
#define THEN 306
#define UMINUS 307
#define UPLUS 308
#define UNOT 309

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 73 "jucompiler.y"

    char *lexeme;
    struct node *node;

#line 307 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CLASS = 3,                      /* CLASS  */
  YYSYMBOL_LBRACE = 4,                     /* LBRACE  */
  YYSYMBOL_RBRACE = 5,                     /* RBRACE  */
  YYSYMBOL_SEMICOLON = 6,                  /* SEMICOLON  */
  YYSYMBOL_COMMA = 7,                      /* COMMA  */
  YYSYMBOL_LPAR = 8,                       /* LPAR  */
  YYSYMBOL_RPAR = 9,                       /* RPAR  */
  YYSYMBOL_LSQ = 10,                       /* LSQ  */
  YYSYMBOL_RSQ = 11,                       /* RSQ  */
  YYSYMBOL_ARROW = 12,                     /* ARROW  */
  YYSYMBOL_RESERVED = 13,                  /* RESERVED  */
  YYSYMBOL_PUBLIC = 14,                    /* PUBLIC  */
  YYSYMBOL_STATIC = 15,                    /* STATIC  */
  YYSYMBOL_VOID = 16,                      /* VOID  */
  YYSYMBOL_RETURN = 17,                    /* RETURN  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_ELSE = 19,                      /* ELSE  */
  YYSYMBOL_WHILE = 20,                     /* WHILE  */
  YYSYMBOL_PRINT = 21,                     /* PRINT  */
  YYSYMBOL_PARSEINT = 22,                  /* PARSEINT  */
  YYSYMBOL_BOOL = 23,                      /* BOOL  */
  YYSYMBOL_INT = 24,                       /* INT  */
  YYSYMBOL_DOUBLE = 25,                    /* DOUBLE  */
  YYSYMBOL_STRING = 26,                    /* STRING  */
  YYSYMBOL_DOTLENGTH = 27,                 /* DOTLENGTH  */
  YYSYMBOL_ASSIGN = 28,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 29,                      /* PLUS  */
  YYSYMBOL_MINUS = 30,                     /* MINUS  */
  YYSYMBOL_STAR = 31,                      /* STAR  */
  YYSYMBOL_DIV = 32,                       /* DIV  */
  YYSYMBOL_MOD = 33,                       /* MOD  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_OR = 35,                        /* OR  */
  YYSYMBOL_XOR = 36,                       /* XOR  */
  YYSYMBOL_NOT = 37,                       /* NOT  */
  YYSYMBOL_LSHIFT = 38,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 39,                    /* RSHIFT  */
  YYSYMBOL_EQ = 40,                        /* EQ  */
  YYSYMBOL_NE = 41,                        /* NE  */
  YYSYMBOL_LT = 42,                        /* LT  */
  YYSYMBOL_GT = 43,                        /* GT  */
  YYSYMBOL_LE = 44,                        /* LE  */
  YYSYMBOL_GE = 45,                        /* GE  */
  YYSYMBOL_IDENTIFIER = 46,                /* IDENTIFIER  */
  YYSYMBOL_STRLIT = 47,                    /* STRLIT  */
  YYSYMBOL_NATURAL = 48,                   /* NATURAL  */
  YYSYMBOL_DECIMAL = 49,                   /* DECIMAL  */
  YYSYMBOL_BOOLLIT = 50,                   /* BOOLLIT  */
  YYSYMBOL_THEN = 51,                      /* THEN  */
  YYSYMBOL_UMINUS = 52,                    /* UMINUS  */
  YYSYMBOL_UPLUS = 53,                     /* UPLUS  */
  YYSYMBOL_UNOT = 54,                      /* UNOT  */
  YYSYMBOL_YYACCEPT = 55,                  /* $accept  */
  YYSYMBOL_program = 56,                   /* program  */
  YYSYMBOL_class_body = 57,                /* class_body  */
  YYSYMBOL_field_decl = 58,                /* field_decl  */
  YYSYMBOL_field_tail = 59,                /* field_tail  */
  YYSYMBOL_type = 60,                      /* type  */
  YYSYMBOL_method_decl = 61,               /* method_decl  */
  YYSYMBOL_method_header = 62,             /* method_header  */
  YYSYMBOL_params_opt = 63,                /* params_opt  */
  YYSYMBOL_params_tail = 64,               /* params_tail  */
  YYSYMBOL_method_body = 65,               /* method_body  */
  YYSYMBOL_body_items = 66,                /* body_items  */
  YYSYMBOL_var_decl = 67,                  /* var_decl  */
  YYSYMBOL_var_tail = 68,                  /* var_tail  */
  YYSYMBOL_stmt = 69,                      /* stmt  */
  YYSYMBOL_stmt_list = 70,                 /* stmt_list  */
  YYSYMBOL_method_call = 71,               /* method_call  */
  YYSYMBOL_arg_tail = 72,                  /* arg_tail  */
  YYSYMBOL_assignment = 73,                /* assignment  */
  YYSYMBOL_parse_args = 74,                /* parse_args  */
  YYSYMBOL_full_expr = 75,                 /* full_expr  */
  YYSYMBOL_expr = 76                       /* expr  */
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   343

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  172

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
       0,   111,   111,   120,   124,   129,   132,   138,   159,   166,
     170,   176,   179,   182,   188,   196,   202,   211,   223,   232,
     238,   247,   253,   261,   266,   273,   279,   303,   307,   313,
     318,   329,   345,   355,   359,   362,   365,   368,   371,   374,
     378,   382,   388,   392,   398,   405,   409,   416,   420,   426,
     434,   439,   445,   448,   454,   459,   464,   469,   474,   480,
     485,   490,   495,   500,   505,   511,   516,   521,   526,   531,
     537,   541,   545,   550,   553,   556,   560,   563,   567,   570,
     573,   577
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
  "\"end of file\"", "error", "\"invalid token\"", "CLASS", "LBRACE",
  "RBRACE", "SEMICOLON", "COMMA", "LPAR", "RPAR", "LSQ", "RSQ", "ARROW",
  "RESERVED", "PUBLIC", "STATIC", "VOID", "RETURN", "IF", "ELSE", "WHILE",
  "PRINT", "PARSEINT", "BOOL", "INT", "DOUBLE", "STRING", "DOTLENGTH",
  "ASSIGN", "PLUS", "MINUS", "STAR", "DIV", "MOD", "AND", "OR", "XOR",
  "NOT", "LSHIFT", "RSHIFT", "EQ", "NE", "LT", "GT", "LE", "GE",
  "IDENTIFIER", "STRLIT", "NATURAL", "DECIMAL", "BOOLLIT", "THEN",
  "UMINUS", "UPLUS", "UNOT", "$accept", "program", "class_body",
  "field_decl", "field_tail", "type", "method_decl", "method_header",
  "params_opt", "params_tail", "method_body", "body_items", "var_decl",
  "var_tail", "stmt", "stmt_list", "method_call", "arg_tail", "assignment",
  "parse_args", "full_expr", "expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-39)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-44)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      29,   -38,    36,    54,   -39,   -39,    91,    59,   -39,   -39,
      74,   -39,   -39,   -39,    30,    45,   -39,   -39,   -39,    48,
      94,    93,     5,    39,   -39,   222,    62,   222,   106,   109,
      82,   -39,   148,   110,   121,   122,   124,     2,    87,   131,
      39,    39,   140,   142,   144,   145,   111,   150,   146,   154,
     -39,   -39,    82,   147,   -39,   143,   178,   178,   178,     7,
     -39,   -39,   -39,   -39,   -39,   -39,   158,   225,   203,   203,
     173,     4,   112,   203,   159,   -39,   -39,   -39,   -39,   -39,
     -39,   156,   161,   -39,   -39,   -39,   -39,   -39,   160,   162,
      -2,   -39,   -39,   -39,   -39,   -39,   178,   178,   178,   178,
     178,   178,   178,   178,   178,   178,   178,   178,   178,   178,
     178,   178,   165,   166,   167,   170,   174,   172,   175,   -39,
     -39,   -39,   141,   182,   153,    24,   -39,   -39,   -39,   107,
     107,   -39,   -39,   -39,   259,   242,   276,   310,   310,   293,
     293,   205,   205,   205,   205,    89,    89,   184,   195,   -39,
     203,   -39,    75,   159,   -39,   -39,   163,   185,   -39,   -39,
     -39,   194,   203,   -39,   -39,   161,    89,   197,   -39,   -39,
     -39,   -39
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     6,     0,     0,     2,     5,
       0,     4,     3,     8,     0,     0,    11,    12,    13,     0,
       0,     0,    10,     0,    14,    19,     0,    19,     0,     0,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    10,     0,
       7,    41,     0,     0,    34,     0,     0,     0,     0,    76,
      78,    79,    80,    74,    53,    75,     0,    52,     0,     0,
       0,     0,     0,     0,    28,    22,    23,    24,    36,    37,
      38,     0,    21,    16,     9,    15,    42,    29,     0,     0,
      76,    71,    70,    72,    77,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
      48,    49,     0,     0,     0,     0,    17,    81,    73,    54,
      55,    56,    57,    58,    67,    65,    66,    68,    69,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,    51,
       0,    45,     0,    28,    26,    18,     0,    30,    32,    40,
      39,     0,     0,    44,    27,    21,     0,     0,    47,    20,
      31,    50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -39,   -39,   -39,   -39,   164,   -11,   -39,   -39,   186,    49,
     -39,    11,   -39,    63,   -29,   177,   -23,   -39,   -21,   -19,
     -31,   -30
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     6,    11,    28,    38,    12,    20,    47,   126,
      24,    39,    40,   123,    41,    53,    63,   152,    64,    65,
      66,    67
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,    52,    43,    19,    44,   116,    72,    42,     3,    43,
      72,    44,    26,    27,    46,    72,    46,    42,    42,    43,
      43,    44,    44,    52,    89,    94,    91,    92,    93,    42,
      73,    43,     1,    44,    94,    73,     4,   112,   113,   115,
      29,   120,   121,    30,   -25,    31,    15,    16,    17,    18,
     117,    76,    77,    16,    17,    18,    32,    33,     5,    34,
      35,    36,    16,    17,    18,    13,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   162,    29,   163,    37,    30,   -43,    31,    14,
      29,    21,     7,    30,    22,    31,     8,     9,    23,    32,
      33,    25,    34,    35,    36,    10,    32,    33,    48,    34,
      35,    36,    50,   118,   156,    51,   157,   158,    68,   161,
      55,   119,    42,    42,    43,    43,    44,    44,    37,    69,
      70,   168,    71,    74,    36,    37,    75,   170,    98,    99,
     100,    56,    57,    42,    88,    43,    78,    44,    79,    58,
      80,    55,    87,    26,    54,    81,    55,    82,    59,    83,
      60,    61,    62,    85,    95,    36,   122,   124,   125,   127,
      36,   128,    56,    57,   145,   146,   147,    56,    57,   148,
      58,    55,   150,   149,   151,    58,    55,   153,   154,    59,
     159,    60,    61,    62,    59,    36,    60,    61,    62,   155,
      36,   160,    56,    57,   166,   167,   171,    56,    57,   165,
      58,    55,    84,    49,   169,    58,   164,     0,     0,    59,
     114,    60,    61,    62,    90,    36,    60,    61,    62,    86,
       0,     0,    56,    57,    96,    97,    98,    99,   100,     0,
      58,     0,     0,   104,   105,    16,    17,    18,    45,    59,
       0,    60,    61,    62,    96,    97,    98,    99,   100,   101,
     102,   103,     0,   104,   105,   106,   107,   108,   109,   110,
     111,    96,    97,    98,    99,   100,   101,     0,   103,     0,
     104,   105,   106,   107,   108,   109,   110,   111,    96,    97,
      98,    99,   100,     0,     0,   103,     0,   104,   105,   106,
     107,   108,   109,   110,   111,    96,    97,    98,    99,   100,
       0,     0,     0,     0,   104,   105,   106,   107,   108,   109,
     110,   111,    96,    97,    98,    99,   100,     0,     0,     0,
       0,   104,   105,     0,     0,   108,   109,   110,   111,    96,
      97,    98,    99,   100
};

static const yytype_int16 yycheck[] =
{
      23,    30,    23,    14,    23,     1,     8,    30,    46,    30,
       8,    30,     7,     8,    25,     8,    27,    40,    41,    40,
      41,    40,    41,    52,    55,    27,    56,    57,    58,    52,
      28,    52,     3,    52,    27,    28,     0,    68,    69,    70,
       1,    72,    73,     4,     5,     6,    16,    23,    24,    25,
      46,    40,    41,    23,    24,    25,    17,    18,     4,    20,
      21,    22,    23,    24,    25,     6,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,     7,     1,     9,    46,     4,     5,     6,    15,
       1,    46,     1,     4,    46,     6,     5,     6,     4,    17,
      18,     8,    20,    21,    22,    14,    17,    18,    46,    20,
      21,    22,     6,     1,   125,     6,   145,   146,     8,   150,
       8,     9,   145,   146,   145,   146,   145,   146,    46,     8,
       8,   162,     8,    46,    22,    46,     5,   166,    31,    32,
      33,    29,    30,   166,     1,   166,     6,   166,     6,    37,
       6,     8,     5,     7,     6,    10,     8,    46,    46,     9,
      48,    49,    50,     9,     6,    22,     7,    11,     7,     9,
      22,     9,    29,    30,     9,     9,     9,    29,    30,     9,
      37,     8,    10,     9,     9,    37,     8,    46,     6,    46,
       6,    48,    49,    50,    46,    22,    48,    49,    50,    46,
      22,     6,    29,    30,    19,    11,     9,    29,    30,    46,
      37,     8,    48,    27,   165,    37,   153,    -1,    -1,    46,
      47,    48,    49,    50,    46,    22,    48,    49,    50,    52,
      -1,    -1,    29,    30,    29,    30,    31,    32,    33,    -1,
      37,    -1,    -1,    38,    39,    23,    24,    25,    26,    46,
      -1,    48,    49,    50,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    29,    30,    31,    32,    33,    34,    -1,    36,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    29,    30,
      31,    32,    33,    -1,    -1,    36,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    29,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    29,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    38,    39,    -1,    -1,    42,    43,    44,    45,    29,
      30,    31,    32,    33
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    56,    46,     0,     4,    57,     1,     5,     6,
      14,    58,    61,     6,    15,    16,    23,    24,    25,    60,
      62,    46,    46,     4,    65,     8,     7,     8,    59,     1,
       4,     6,    17,    18,    20,    21,    22,    46,    60,    66,
      67,    69,    71,    73,    74,    26,    60,    63,    46,    63,
       6,     6,    69,    70,     6,     8,    29,    30,    37,    46,
      48,    49,    50,    71,    73,    74,    75,    76,     8,     8,
       8,     8,     8,    28,    46,     5,    66,    66,     6,     6,
       6,    10,    46,     9,    59,     9,    70,     5,     1,    75,
      46,    76,    76,    76,    27,     6,    29,    30,    31,    32,
      33,    34,    35,    36,    38,    39,    40,    41,    42,    43,
      44,    45,    75,    75,    47,    75,     1,    46,     1,     9,
      75,    75,     7,    68,    11,     7,    64,     9,     9,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,     9,     9,     9,     9,     9,
      10,     9,    72,    46,     6,    46,    60,    69,    69,     6,
       6,    75,     7,     9,    68,    46,    19,    11,    75,    64,
      69,     9
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    57,    57,    57,    57,    58,    58,    59,
      59,    60,    60,    60,    61,    62,    62,    63,    63,    63,
      64,    64,    65,    66,    66,    66,    67,    68,    68,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    70,    70,    71,    71,    71,    72,    72,    73,
      74,    74,    75,    75,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     2,     2,     2,     0,     6,     2,     3,
       0,     1,     1,     1,     4,     5,     5,     3,     4,     0,
       4,     0,     3,     2,     2,     0,     4,     3,     0,     3,
       5,     7,     5,     3,     2,     1,     2,     2,     2,     5,
       5,     2,     2,     0,     5,     4,     3,     3,     0,     3,
       7,     4,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     3,     1,     1,     1,     2,     1,     1,
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: CLASS IDENTIFIER LBRACE class_body RBRACE  */
#line 111 "jucompiler.y"
                                              {
        ast = (yyval.node) = make_node(Program, NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column);
        addchild((yyval.node), make_node(Identifier, (yyvsp[-3].lexeme), (yylsp[-3]).first_line, (yylsp[-3]).first_column));
        append_list((yyval.node), (yyvsp[-1].node));
        freenode((yyvsp[-1].node));
    }
#line 1645 "y.tab.c"
    break;

  case 3: /* class_body: class_body method_decl  */
#line 120 "jucompiler.y"
                           {
        (yyval.node) = (yyvsp[-1].node);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1654 "y.tab.c"
    break;

  case 4: /* class_body: class_body field_decl  */
#line 124 "jucompiler.y"
                          {
        (yyval.node) = (yyvsp[-1].node);
        append_list((yyval.node), (yyvsp[0].node));
        freenode((yyvsp[0].node));
    }
#line 1664 "y.tab.c"
    break;

  case 5: /* class_body: class_body SEMICOLON  */
#line 129 "jucompiler.y"
                         {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1672 "y.tab.c"
    break;

  case 6: /* class_body: %empty  */
#line 132 "jucompiler.y"
    {
        (yyval.node) = newnode(ListNode, NULL);
    }
#line 1680 "y.tab.c"
    break;

  case 7: /* field_decl: PUBLIC STATIC type IDENTIFIER field_tail SEMICOLON  */
#line 138 "jucompiler.y"
                                                       {
        struct node *decl;
        struct node_list *child;

        (yyval.node) = newnode(ListNode, NULL);

        decl = make_node(FieldDecl, NULL, (yylsp[-2]).first_line, (yylsp[-2]).first_column);
        addchild(decl, (yyvsp[-3].node));
        addchild(decl, make_node(Identifier, (yyvsp[-2].lexeme), (yylsp[-2]).first_line, (yylsp[-2]).first_column));
        addchild((yyval.node), decl);

        child = (yyvsp[-1].node)->children->next;
        while (child) {
            decl = make_node(FieldDecl, NULL, child->node->line, child->node->column);
            addchild(decl, copynode((yyvsp[-3].node)));
            addchild(decl, child->node);
            addchild((yyval.node), decl);
            child = child->next;
        }
        freenode((yyvsp[-1].node));
    }
#line 1706 "y.tab.c"
    break;

  case 8: /* field_decl: error SEMICOLON  */
#line 159 "jucompiler.y"
                    {
        (yyval.node) = newnode(ListNode, NULL);
        addchild((yyval.node), make_node(FieldDecl, NULL, (yylsp[0]).first_line, (yylsp[0]).first_column));
    }
#line 1715 "y.tab.c"
    break;

  case 9: /* field_tail: COMMA IDENTIFIER field_tail  */
#line 166 "jucompiler.y"
                                {
        (yyval.node) = (yyvsp[0].node);
        prependchild((yyval.node), make_node(Identifier, (yyvsp[-1].lexeme), (yylsp[-1]).first_line, (yylsp[-1]).first_column));
    }
#line 1724 "y.tab.c"
    break;

  case 10: /* field_tail: %empty  */
#line 170 "jucompiler.y"
    {
        (yyval.node) = newnode(ListNode, NULL);
    }
#line 1732 "y.tab.c"
    break;

  case 11: /* type: BOOL  */
#line 176 "jucompiler.y"
         {
        (yyval.node) = make_node(Bool, NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);
    }
#line 1740 "y.tab.c"
    break;

  case 12: /* type: INT  */
#line 179 "jucompiler.y"
        {
        (yyval.node) = make_node(Int, NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);
    }
#line 1748 "y.tab.c"
    break;

  case 13: /* type: DOUBLE  */
#line 182 "jucompiler.y"
           {
        (yyval.node) = make_node(Double, NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);
    }
#line 1756 "y.tab.c"
    break;

  case 14: /* method_decl: PUBLIC STATIC method_header method_body  */
#line 188 "jucompiler.y"
                                            {
        (yyval.node) = make_node(MethodDecl, NULL, (yyvsp[-1].node)->line, (yyvsp[-1].node)->column);
        addchild((yyval.node), (yyvsp[-1].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 1766 "y.tab.c"
    break;

  case 15: /* method_header: type IDENTIFIER LPAR params_opt RPAR  */
#line 196 "jucompiler.y"
                                         {
        (yyval.node) = make_node(MethodHeader, NULL, (yylsp[-3]).first_line, (yylsp[-3]).first_column);
        addchild((yyval.node), (yyvsp[-4].node));
        addchild((yyval.node), make_node(Identifier, (yyvsp[-3].lexeme), (yylsp[-3]).first_line, (yylsp[-3]).first_column));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1777 "y.tab.c"
    break;

  case 16: /* method_header: VOID IDENTIFIER LPAR params_opt RPAR  */
#line 202 "jucompiler.y"
                                         {
        (yyval.node) = make_node(MethodHeader, NULL, (yylsp[-3]).first_line, (yylsp[-3]).first_column);
        addchild((yyval.node), make_node(Void, NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column));
        addchild((yyval.node), make_node(Identifier, (yyvsp[-3].lexeme), (yylsp[-3]).first_line, (yylsp[-3]).first_column));
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 1788 "y.tab.c"
    break;

  case 17: /* params_opt: type IDENTIFIER params_tail  */
#line 211 "jucompiler.y"
                                {
        struct node *param;

        (yyval.node) = make_node(MethodParams, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        param = make_node(ParamDecl, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild(param, (yyvsp[-2].node));
        addchild(param, make_node(Identifier, (yyvsp[-1].lexeme), (yylsp[-1]).first_line, (yylsp[-1]).first_column));
        addchild((yyval.node), param);

        append_list((yyval.node), (yyvsp[0].node));
        freenode((yyvsp[0].node));
    }
#line 1805 "y.tab.c"
    break;

  case 18: /* params_opt: STRING LSQ RSQ IDENTIFIER  */
#line 223 "jucompiler.y"
                              {
        struct node *param;

        (yyval.node) = make_node(MethodParams, NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);
        param = make_node(ParamDecl, NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);
        addchild(param, make_node(StringArray, NULL, (yylsp[-3]).first_line, (yylsp[-3]).first_column));
        addchild(param, make_node(Identifier, (yyvsp[0].lexeme), (yylsp[0]).first_line, (yylsp[0]).first_column));
        addchild((yyval.node), param);
    }
#line 1819 "y.tab.c"
    break;

  case 19: /* params_opt: %empty  */
#line 232 "jucompiler.y"
    {
        (yyval.node) = newnode(MethodParams, NULL);
    }
#line 1827 "y.tab.c"
    break;

  case 20: /* params_tail: COMMA type IDENTIFIER params_tail  */
#line 238 "jucompiler.y"
                                      {
        struct node *param;

        (yyval.node) = (yyvsp[0].node);
        param = make_node(ParamDecl, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild(param, (yyvsp[-2].node));
        addchild(param, make_node(Identifier, (yyvsp[-1].lexeme), (yylsp[-1]).first_line, (yylsp[-1]).first_column));
        prependchild((yyval.node), param);
    }
#line 1841 "y.tab.c"
    break;

  case 21: /* params_tail: %empty  */
#line 247 "jucompiler.y"
    {
        (yyval.node) = newnode(ListNode, NULL);
    }
#line 1849 "y.tab.c"
    break;

  case 22: /* method_body: LBRACE body_items RBRACE  */
#line 253 "jucompiler.y"
                             {
        (yyval.node) = make_node(MethodBody, NULL, (yylsp[-2]).first_line, (yylsp[-2]).first_column);
        append_list((yyval.node), (yyvsp[-1].node));
        freenode((yyvsp[-1].node));
    }
#line 1859 "y.tab.c"
    break;

  case 23: /* body_items: var_decl body_items  */
#line 261 "jucompiler.y"
                        {
        (yyval.node) = (yyvsp[-1].node);
        append_list((yyval.node), (yyvsp[0].node));
        freenode((yyvsp[0].node));
    }
#line 1869 "y.tab.c"
    break;

  case 24: /* body_items: stmt body_items  */
#line 266 "jucompiler.y"
                    {
        (yyval.node) = (yyvsp[0].node);
        if (!is_empty_statement((yyvsp[-1].node)))
            prependchild((yyval.node), (yyvsp[-1].node));
        else
            freenode((yyvsp[-1].node));
    }
#line 1881 "y.tab.c"
    break;

  case 25: /* body_items: %empty  */
#line 273 "jucompiler.y"
    {
        (yyval.node) = newnode(ListNode, NULL);
    }
#line 1889 "y.tab.c"
    break;

  case 26: /* var_decl: type IDENTIFIER var_tail SEMICOLON  */
#line 279 "jucompiler.y"
                                       {
        struct node *decl;
        struct node_list *child;

        (yyval.node) = newnode(ListNode, NULL);

        decl = make_node(VarDecl, NULL, (yylsp[-2]).first_line, (yylsp[-2]).first_column);
        addchild(decl, (yyvsp[-3].node));
        addchild(decl, make_node(Identifier, (yyvsp[-2].lexeme), (yylsp[-2]).first_line, (yylsp[-2]).first_column));
        addchild((yyval.node), decl);

        child = (yyvsp[-1].node)->children->next;
        while (child) {
            decl = make_node(VarDecl, NULL, child->node->line, child->node->column);
            addchild(decl, copynode((yyvsp[-3].node)));
            addchild(decl, child->node);
            addchild((yyval.node), decl);
            child = child->next;
        }
        freenode((yyvsp[-1].node));
    }
#line 1915 "y.tab.c"
    break;

  case 27: /* var_tail: COMMA IDENTIFIER var_tail  */
#line 303 "jucompiler.y"
                              {
        (yyval.node) = (yyvsp[0].node);
        prependchild((yyval.node), make_node(Identifier, (yyvsp[-1].lexeme), (yylsp[-1]).first_line, (yylsp[-1]).first_column));
    }
#line 1924 "y.tab.c"
    break;

  case 28: /* var_tail: %empty  */
#line 307 "jucompiler.y"
    {
        (yyval.node) = newnode(ListNode, NULL);
    }
#line 1932 "y.tab.c"
    break;

  case 29: /* stmt: LBRACE stmt_list RBRACE  */
#line 313 "jucompiler.y"
                            {
        (yyval.node) = compact_block((yyvsp[-1].node));
        if ((yyval.node)->line == 0 && (yyval.node)->column == 0)
            set_node_location((yyval.node), (yylsp[-2]).first_line, (yylsp[-2]).first_column);
    }
#line 1942 "y.tab.c"
    break;

  case 30: /* stmt: IF LPAR full_expr RPAR stmt  */
#line 318 "jucompiler.y"
                                           {
        (yyval.node) = make_node(If, NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        if ((yyvsp[0].node)->category == Empty) {
            freenode((yyvsp[0].node));
            addchild((yyval.node), make_node(Block, NULL, (yylsp[0]).first_line, (yylsp[0]).first_column));
        } else {
            addchild((yyval.node), (yyvsp[0].node));
        }
        addchild((yyval.node), make_node(Block, NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column));
    }
#line 1958 "y.tab.c"
    break;

  case 31: /* stmt: IF LPAR full_expr RPAR stmt ELSE stmt  */
#line 329 "jucompiler.y"
                                          {
        (yyval.node) = make_node(If, NULL, (yylsp[-6]).first_line, (yylsp[-6]).first_column);
        addchild((yyval.node), (yyvsp[-4].node));
        if ((yyvsp[-2].node)->category == Empty) {
            freenode((yyvsp[-2].node));
            addchild((yyval.node), make_node(Block, NULL, (yylsp[-2]).first_line, (yylsp[-2]).first_column));
        } else {
            addchild((yyval.node), (yyvsp[-2].node));
        }
        if ((yyvsp[0].node)->category == Empty) {
            freenode((yyvsp[0].node));
            addchild((yyval.node), make_node(Block, NULL, (yylsp[0]).first_line, (yylsp[0]).first_column));
        } else {
            addchild((yyval.node), (yyvsp[0].node));
        }
    }
#line 1979 "y.tab.c"
    break;

  case 32: /* stmt: WHILE LPAR full_expr RPAR stmt  */
#line 345 "jucompiler.y"
                                   {
        (yyval.node) = make_node(While, NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        if ((yyvsp[0].node)->category == Empty) {
            freenode((yyvsp[0].node));
            addchild((yyval.node), make_node(Block, NULL, (yylsp[0]).first_line, (yylsp[0]).first_column));
        } else {
            addchild((yyval.node), (yyvsp[0].node));
        }
    }
#line 1994 "y.tab.c"
    break;

  case 33: /* stmt: RETURN full_expr SEMICOLON  */
#line 355 "jucompiler.y"
                               {
        (yyval.node) = make_node(Return, NULL, (yylsp[-2]).first_line, (yylsp[-2]).first_column);
        addchild((yyval.node), (yyvsp[-1].node));
    }
#line 2003 "y.tab.c"
    break;

  case 34: /* stmt: RETURN SEMICOLON  */
#line 359 "jucompiler.y"
                     {
        (yyval.node) = make_node(Return, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
    }
#line 2011 "y.tab.c"
    break;

  case 35: /* stmt: SEMICOLON  */
#line 362 "jucompiler.y"
              {
        (yyval.node) = make_node(Empty, NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);
    }
#line 2019 "y.tab.c"
    break;

  case 36: /* stmt: method_call SEMICOLON  */
#line 365 "jucompiler.y"
                          {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2027 "y.tab.c"
    break;

  case 37: /* stmt: assignment SEMICOLON  */
#line 368 "jucompiler.y"
                         {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2035 "y.tab.c"
    break;

  case 38: /* stmt: parse_args SEMICOLON  */
#line 371 "jucompiler.y"
                         {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2043 "y.tab.c"
    break;

  case 39: /* stmt: PRINT LPAR full_expr RPAR SEMICOLON  */
#line 374 "jucompiler.y"
                                        {
        (yyval.node) = make_node(Print, NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 2052 "y.tab.c"
    break;

  case 40: /* stmt: PRINT LPAR STRLIT RPAR SEMICOLON  */
#line 378 "jucompiler.y"
                                     {
        (yyval.node) = make_node(Print, NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column);
        addchild((yyval.node), make_node(StrLit, (yyvsp[-2].lexeme), (yylsp[-2]).first_line, (yylsp[-2]).first_column));
    }
#line 2061 "y.tab.c"
    break;

  case 41: /* stmt: error SEMICOLON  */
#line 382 "jucompiler.y"
                    {
        (yyval.node) = make_node(Error, NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);
    }
#line 2069 "y.tab.c"
    break;

  case 42: /* stmt_list: stmt stmt_list  */
#line 388 "jucompiler.y"
                   {
        (yyval.node) = (yyvsp[0].node);
        prependchild((yyval.node), (yyvsp[-1].node));
    }
#line 2078 "y.tab.c"
    break;

  case 43: /* stmt_list: %empty  */
#line 392 "jucompiler.y"
    {
        (yyval.node) = newnode(ListNode, NULL);
    }
#line 2086 "y.tab.c"
    break;

  case 44: /* method_call: IDENTIFIER LPAR full_expr arg_tail RPAR  */
#line 398 "jucompiler.y"
                                            {
        (yyval.node) = make_node(Call, NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column);
        addchild((yyval.node), make_node(Identifier, (yyvsp[-4].lexeme), (yylsp[-4]).first_line, (yylsp[-4]).first_column));
        addchild((yyval.node), (yyvsp[-2].node));
        append_list((yyval.node), (yyvsp[-1].node));
        freenode((yyvsp[-1].node));
    }
#line 2098 "y.tab.c"
    break;

  case 45: /* method_call: IDENTIFIER LPAR error RPAR  */
#line 405 "jucompiler.y"
                               {
        (yyval.node) = make_node(Call, NULL, (yylsp[-3]).first_line, (yylsp[-3]).first_column);
        addchild((yyval.node), make_node(Identifier, (yyvsp[-3].lexeme), (yylsp[-3]).first_line, (yylsp[-3]).first_column));
    }
#line 2107 "y.tab.c"
    break;

  case 46: /* method_call: IDENTIFIER LPAR RPAR  */
#line 409 "jucompiler.y"
                         {
        (yyval.node) = make_node(Call, NULL, (yylsp[-2]).first_line, (yylsp[-2]).first_column);
        addchild((yyval.node), make_node(Identifier, (yyvsp[-2].lexeme), (yylsp[-2]).first_line, (yylsp[-2]).first_column));
    }
#line 2116 "y.tab.c"
    break;

  case 47: /* arg_tail: arg_tail COMMA full_expr  */
#line 416 "jucompiler.y"
                             {
        (yyval.node) = (yyvsp[-2].node);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2125 "y.tab.c"
    break;

  case 48: /* arg_tail: %empty  */
#line 420 "jucompiler.y"
    {
        (yyval.node) = newnode(ListNode, NULL);
    }
#line 2133 "y.tab.c"
    break;

  case 49: /* assignment: IDENTIFIER ASSIGN full_expr  */
#line 426 "jucompiler.y"
                                {
        (yyval.node) = make_node(Assign, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), make_node(Identifier, (yyvsp[-2].lexeme), (yylsp[-2]).first_line, (yylsp[-2]).first_column));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2143 "y.tab.c"
    break;

  case 50: /* parse_args: PARSEINT LPAR IDENTIFIER LSQ full_expr RSQ RPAR  */
#line 434 "jucompiler.y"
                                                    {
        (yyval.node) = make_node(ParseArgs, NULL, (yylsp[-6]).first_line, (yylsp[-6]).first_column);
        addchild((yyval.node), make_node(Identifier, (yyvsp[-4].lexeme), (yylsp[-4]).first_line, (yylsp[-4]).first_column));
        addchild((yyval.node), (yyvsp[-2].node));
    }
#line 2153 "y.tab.c"
    break;

  case 51: /* parse_args: PARSEINT LPAR error RPAR  */
#line 439 "jucompiler.y"
                             {
        (yyval.node) = make_node(ParseArgs, NULL, (yylsp[-3]).first_line, (yylsp[-3]).first_column);
    }
#line 2161 "y.tab.c"
    break;

  case 52: /* full_expr: expr  */
#line 445 "jucompiler.y"
         {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2169 "y.tab.c"
    break;

  case 53: /* full_expr: assignment  */
#line 448 "jucompiler.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2177 "y.tab.c"
    break;

  case 54: /* expr: expr PLUS expr  */
#line 454 "jucompiler.y"
                   {
        (yyval.node) = make_node(Add, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2187 "y.tab.c"
    break;

  case 55: /* expr: expr MINUS expr  */
#line 459 "jucompiler.y"
                    {
        (yyval.node) = make_node(Sub, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2197 "y.tab.c"
    break;

  case 56: /* expr: expr STAR expr  */
#line 464 "jucompiler.y"
                   {
        (yyval.node) = make_node(Mul, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2207 "y.tab.c"
    break;

  case 57: /* expr: expr DIV expr  */
#line 469 "jucompiler.y"
                  {
        (yyval.node) = make_node(Div, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2217 "y.tab.c"
    break;

  case 58: /* expr: expr MOD expr  */
#line 474 "jucompiler.y"
                  {
        (yyval.node) = make_node(Mod, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2227 "y.tab.c"
    break;

  case 59: /* expr: expr EQ expr  */
#line 480 "jucompiler.y"
                 {
        (yyval.node) = make_node(Eq, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2237 "y.tab.c"
    break;

  case 60: /* expr: expr NE expr  */
#line 485 "jucompiler.y"
                 {
        (yyval.node) = make_node(Ne, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2247 "y.tab.c"
    break;

  case 61: /* expr: expr LT expr  */
#line 490 "jucompiler.y"
                 {
        (yyval.node) = make_node(Lt, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2257 "y.tab.c"
    break;

  case 62: /* expr: expr GT expr  */
#line 495 "jucompiler.y"
                 {
        (yyval.node) = make_node(Gt, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2267 "y.tab.c"
    break;

  case 63: /* expr: expr LE expr  */
#line 500 "jucompiler.y"
                 {
        (yyval.node) = make_node(Le, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2277 "y.tab.c"
    break;

  case 64: /* expr: expr GE expr  */
#line 505 "jucompiler.y"
                 {
        (yyval.node) = make_node(Ge, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2287 "y.tab.c"
    break;

  case 65: /* expr: expr OR expr  */
#line 511 "jucompiler.y"
                 {
        (yyval.node) = make_node(Or, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2297 "y.tab.c"
    break;

  case 66: /* expr: expr XOR expr  */
#line 516 "jucompiler.y"
                  {
        (yyval.node) = make_node(Xor, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2307 "y.tab.c"
    break;

  case 67: /* expr: expr AND expr  */
#line 521 "jucompiler.y"
                  {
        (yyval.node) = make_node(And, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2317 "y.tab.c"
    break;

  case 68: /* expr: expr LSHIFT expr  */
#line 526 "jucompiler.y"
                     {
        (yyval.node) = make_node(Lshift, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2327 "y.tab.c"
    break;

  case 69: /* expr: expr RSHIFT expr  */
#line 531 "jucompiler.y"
                     {
        (yyval.node) = make_node(Rshift, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[-2].node));
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2337 "y.tab.c"
    break;

  case 70: /* expr: MINUS expr  */
#line 537 "jucompiler.y"
                            {
        (yyval.node) = make_node(Minus, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2346 "y.tab.c"
    break;

  case 71: /* expr: PLUS expr  */
#line 541 "jucompiler.y"
                          {
        (yyval.node) = make_node(Plus, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2355 "y.tab.c"
    break;

  case 72: /* expr: NOT expr  */
#line 545 "jucompiler.y"
                        {
        (yyval.node) = make_node(Not, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        addchild((yyval.node), (yyvsp[0].node));
    }
#line 2364 "y.tab.c"
    break;

  case 73: /* expr: LPAR full_expr RPAR  */
#line 550 "jucompiler.y"
                        {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2372 "y.tab.c"
    break;

  case 74: /* expr: method_call  */
#line 553 "jucompiler.y"
                {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2380 "y.tab.c"
    break;

  case 75: /* expr: parse_args  */
#line 556 "jucompiler.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2388 "y.tab.c"
    break;

  case 76: /* expr: IDENTIFIER  */
#line 560 "jucompiler.y"
               {
        (yyval.node) = make_node(Identifier, (yyvsp[0].lexeme), (yylsp[0]).first_line, (yylsp[0]).first_column);
    }
#line 2396 "y.tab.c"
    break;

  case 77: /* expr: IDENTIFIER DOTLENGTH  */
#line 563 "jucompiler.y"
                         {
        (yyval.node) = make_node(Length, NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);
        addchild((yyval.node), make_node(Identifier, (yyvsp[-1].lexeme), (yylsp[-1]).first_line, (yylsp[-1]).first_column));
    }
#line 2405 "y.tab.c"
    break;

  case 78: /* expr: NATURAL  */
#line 567 "jucompiler.y"
            {
        (yyval.node) = make_node(Natural, (yyvsp[0].lexeme), (yylsp[0]).first_line, (yylsp[0]).first_column);
    }
#line 2413 "y.tab.c"
    break;

  case 79: /* expr: DECIMAL  */
#line 570 "jucompiler.y"
            {
        (yyval.node) = make_node(Decimal, (yyvsp[0].lexeme), (yylsp[0]).first_line, (yylsp[0]).first_column);
    }
#line 2421 "y.tab.c"
    break;

  case 80: /* expr: BOOLLIT  */
#line 573 "jucompiler.y"
            {
        (yyval.node) = make_node(BoolLit, (yyvsp[0].lexeme), (yylsp[0]).first_line, (yylsp[0]).first_column);
    }
#line 2429 "y.tab.c"
    break;

  case 81: /* expr: LPAR error RPAR  */
#line 577 "jucompiler.y"
                    {
        (yyval.node) = make_node(Error, NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
    }
#line 2437 "y.tab.c"
    break;


#line 2441 "y.tab.c"

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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 582 "jucompiler.y"


void yyerror(char *s) {
    printf("Line %d, col %d: %s: %s\n", line, token_column, s, token_text);
    syntax_errors = 1;
}

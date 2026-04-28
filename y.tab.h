/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
#line 65 "meta2jucompiler.y"

    char *lexeme;
    struct node *node;

#line 180 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

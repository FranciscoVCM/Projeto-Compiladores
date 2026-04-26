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

#ifndef YY_YY_CLAUDECOMPILER_TAB_H_INCLUDED
# define YY_YY_CLAUDECOMPILER_TAB_H_INCLUDED
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 125 "claudecompiler.y"
 char *lexeme; struct node *node; 

#line 121 "claudecompiler.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_CLAUDECOMPILER_TAB_H_INCLUDED  */

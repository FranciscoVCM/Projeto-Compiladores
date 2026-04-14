%{
#include <stdio.h>
extern int yylex(void);
void yyerror(char *);
extern char *yytext;
extern int line;
extern int column;
%}

%token NATURAL
%token IF THEN ELSE

%left '+' '-'
%left '*' '/'
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE 
%%

calculator: expression                  { printf("%d", $1); }
          | calculator ',' expression      { printf(", %d", $3); }
;

expression: NATURAL                     { $$ = $1; }
          | expression '+' expression   { $$ = $1 + $3; }
          | expression '-' expression   { $$ = $1 - $3; }
          | expression '*' expression   { $$ = $1 * $3; }
          | expression '/' expression   { $$ = $1 / $3; }
          | '(' expression ')'   { $$ = $2; }
          | IF expression THEN expression ELSE expression
            { $$ = $2 ? $4 : $6; }
          ;

%%

void yyerror(char *error) {
    printf("Syntax error at line %d column %d near '%s'\n",
           line, column, yytext);
}

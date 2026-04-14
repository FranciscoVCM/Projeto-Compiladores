%{
#include "y.tab.h"
int yyparse(void);
int line = 1;
int column = 1;
%}
digit   [0-9]
%%
"if"    { return IF; }
"then"  { return THEN; }
"else"  { return ELSE; }
{digit}+                { yylval = atoi(yytext); column += yyleng; return NATURAL; }
[()=,*/+-]              { column += yyleng; return yytext[0]; }
[\t ]+                  { column += yyleng;}
\n                      { line++; column=1; return 0; }
.                       { printf("Unrecognized character\n"); }
%%
int main() {
    yyparse();
    return 0;
}
int yywrap() {
    return 1;
}

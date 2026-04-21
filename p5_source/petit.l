%{
#include "y.tab.h"
#include "ast.h"
#include "semantics.h"

#define PASS_TOKEN() yylval.lexeme = strdup(yytext);

int yyparse(void);
void yyerror(char *);

int lex_line = 1, lex_column = 1;
int syn_line = -1, syn_column = -1;
int errors = 0;

extern struct node *ast;
%}

%option noyywrap

%X COMMENT

digit   [0-9]
letter  [a-zA-Z]

%%

integer                     { syn_line = lex_line; syn_column = lex_column; lex_column += yyleng; return INTEGER; }
double                      { syn_line = lex_line; syn_column = lex_column; lex_column += yyleng; return DOUBLE; }
if                          { syn_line = lex_line; syn_column = lex_column; lex_column += yyleng; return IF; }
then                        { syn_line = lex_line; syn_column = lex_column; lex_column += yyleng; return THEN; }
else                        { syn_line = lex_line; syn_column = lex_column; lex_column += yyleng; return ELSE; }

{letter}({letter}|{digit})* {
    syn_line = lex_line; syn_column = lex_column; lex_column += yyleng;
    PASS_TOKEN();
    return IDENTIFIER;
}

{digit}+ {
    syn_line = lex_line; syn_column = lex_column; lex_column += yyleng;
    PASS_TOKEN();
    return NATURAL;
}

{digit}*"."{digit}+ {
    syn_line = lex_line; syn_column = lex_column; lex_column += yyleng;
    PASS_TOKEN();
    return DECIMAL;
}

"/*"                        { syn_line = lex_line; syn_column = lex_column; lex_column += yyleng; BEGIN(COMMENT); }
<COMMENT>"*/"               { lex_column += yyleng; BEGIN(INITIAL); }
<COMMENT>\n|\r|\r\n         { lex_line++; lex_column = 1; }
<COMMENT>.                  { lex_column += yyleng; }
<COMMENT><<EOF>>            { return 0; }

[\t ]+                      { lex_column += yyleng; }
\n|\r|\r\n                  { lex_line++; lex_column = 1; }
[()=,*/+-]                  { syn_line = lex_line; syn_column = lex_column; lex_column += yyleng; return yytext[0]; }
.                           { syn_line = lex_line; syn_column = lex_column; lex_column += yyleng; yyerror("unrecognized character"); }
<<EOF>>                     { syn_line = lex_line; syn_column = lex_column; return 0; }

%%

void yyerror(char *error) {
    errors++;
    printf("Found %s '%s' (%d,%d)\n", error, yytext, syn_line, syn_column);
}

int main(int argc, char *argv[]) {
    yyparse();
    if(errors == 0) {
        errors += check_program(ast);
        if(errors == 0) {
            show_symbol_table();
            show(ast, 0);
        }
    }
    return 0;
}
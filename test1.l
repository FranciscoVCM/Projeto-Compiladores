%{
#include <stdio.h>

int line = 1;
int column = 1;
int str_start_line;
int str_start_column;
%}

%X COMMENT STRING

digit   [0-9]
letter [a-zA-Z]
%%

"/*" { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); column += yyleng; }
<COMMENT>\n { line++; column = 1; }
<COMMENT>. { column += yyleng; }

\" {
    str_start_line = line;
    str_start_column = column;
    BEGIN(STRING);
    column += yyleng;
    printf("STRLIT(\"");
}

<STRING>\\[fnrt\\\"] {
    printf("%s", yytext);
    column += yyleng;
}

<STRING>\\[^fnrt\\\"] {
    printf("Line %d, col %d: invalid escape sequence (%s)\n",
           line, column, yytext);
    column += yyleng;
}

<STRING>[^\\\"\n]+ {
    printf("%s", yytext);
    column += yyleng;
}

<STRING>\" {
    printf("\")\n");
    column += yyleng;
    BEGIN(INITIAL);
}

<STRING>\n {
    printf("Line %d, col %d: unterminated string literal\n",
           str_start_line, str_start_column);
    line++;
    column = 1;
    BEGIN(INITIAL);
}

"true"  { printf("BOOLLIT(true)\n"); column += yyleng; }
"false" { printf("BOOLLIT(false)\n"); column += yyleng; }


"==" { printf("EQ\n"); column += yyleng; }
"!=" { printf("NE\n"); column += yyleng; }
">=" { printf("GE\n"); column += yyleng; }
"<=" { printf("LE\n"); column += yyleng; }
"&&" { printf("AND\n"); column += yyleng; }
"||" { printf("OR\n"); column += yyleng; }
"->" { printf("ARROW\n"); column += yyleng; }
"<<" { printf("LSHIFT\n"); column += yyleng; }
">>" { printf("RSHIFT\n"); column += yyleng; }

"="  { printf("ASSIGN\n"); column += yyleng; }
">"  { printf("GT\n"); column += yyleng; }
"<"  { printf("LT\n"); column += yyleng; }
"+"  { printf("PLUS\n"); column += yyleng; }
"-"  { printf("MINUS\n"); column += yyleng; }
"*"  { printf("STAR\n"); column += yyleng; }
"/"  { printf("DIV\n"); column += yyleng; }
"%"  { printf("MOD\n"); column += yyleng; }
"!"  { printf("NOT\n"); column += yyleng; }

"{"  { printf("LBRACE\n"); column += yyleng; }
"}"  { printf("RBRACE\n"); column += yyleng; }
"("  { printf("LPAR\n"); column += yyleng; }
")"  { printf("RPAR\n"); column += yyleng; }
"["  { printf("LSQ\n"); column += yyleng; }
"]"  { printf("RSQ\n"); column += yyleng; }
";"  { printf("SEMICOLON\n"); column += yyleng; }
","  { printf("COMMA\n"); column += yyleng; }

"class"   { printf("CLASS\n"); column += yyleng; }
"public"  { printf("PUBLIC\n"); column += yyleng; }
"static"  { printf("STATIC\n"); column += yyleng; }
"int"     { printf("INT\n"); column += yyleng; }
"double"  { printf("DOUBLE\n"); column += yyleng; }
"boolean" { printf("BOOL\n"); column += yyleng; }
"void"    { printf("VOID\n"); column += yyleng; }
"if"      { printf("IF\n"); column += yyleng; }
"else"    { printf("ELSE\n"); column += yyleng; }
"while"   { printf("WHILE\n"); column += yyleng; }
"return"  { printf("RETURN\n"); column += yyleng; }

{letter}({letter}|{digit})* {
    printf("IDENTIFIER(%s)\n", yytext);
    column += yyleng;
}

{digit}+ {
    printf("NATURAL(%s)\n", yytext);
    column += yyleng;
}

\n { line++; column = 1; }
[ \t]+ { column += yyleng; }

. {
    printf("Line %d, col %d: illegal character (%s)\n",
           line, column, yytext);
}

%%
int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
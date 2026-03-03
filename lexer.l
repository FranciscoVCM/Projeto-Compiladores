%{
    /* place here any C variables and definitions */
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
    printf("Line %d, column %d: invalid escape sequence (%s)\n",
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
    printf("Line %d, column %d: unterminated string\n",
           str_start_line, str_start_column);
    line++;
    column = 1;
    BEGIN(INITIAL);
}

{digit}+                { printf("NATURAL(%s)\n", yytext); column += yyleng; }
{digit}*"."{digit}+     { printf("DECIMAL(%s)\n", yytext); column += yyleng; } 
"integer"                       { printf("INTEGER\n"); column += yyleng; }
"double"                        { printf("DOUBLE\n"); column += yyleng; }
"if"                            { printf("IF\n"); column += yyleng; }
"then"                          { printf("THEN\n"); column += yyleng; }
"else"                          { printf("ELSE\n"); column += yyleng; }
{letter}({letter}|{digit})*     { printf("IDENTIFIER(%s)\n", yytext); column += yyleng; }
[()=,*/+-]              { printf("%s\n", yytext); column += yyleng; }
\n      { line++; column = 1;}
[ \t]+  { column += yyleng; }
. {  printf("Line %d, column %d: unrecognized character (%s)\n", line, column, yytext); }
%%
extern int yylex();
int main() {
    yylex();    /* run the lexical analysis automaton */
    return 0;
}
int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}
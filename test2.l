%{
#include <stdio.h>
#include <string.h>

int line = 1;
int column = 1;
int str_start_line;
int str_start_column;

int comment_start_line;
int comment_start_column;

int print_tokens = 0;
#define TOKEN(x) if(print_tokens){ printf(x "\n"); }

%}

%X COMMENT STRING

digit   [0-9]
letter  [a-zA-Z_$]
alnum   [a-zA-Z0-9_$]


%%

"/*" {
    comment_start_line = line;
    comment_start_column = column;
    BEGIN(COMMENT);
    column += yyleng;
}

<COMMENT>"*/" {
    BEGIN(INITIAL);
    column += yyleng;
}

<COMMENT>\n {
    line++;
    column = 1;
}

<COMMENT>. {
    column += yyleng;
}

"//".* {
    column += yyleng;
}

\" {
    str_start_line = line;
    str_start_column = column;
    BEGIN(STRING);
    column += yyleng;
    if (print_tokens) printf("STRLIT(\"");
}

<STRING>\\[fnrt\\\"] {
    if (print_tokens) printf("%s", yytext);
    column += yyleng;
}

<STRING>\\[^fnrt\\\"] {
    printf("Line %d, col %d: invalid escape sequence (%s)\n",
           line, column, yytext);
    column += yyleng;
}

<STRING>[^\\\"\n]+ {
    if (print_tokens) printf("%s", yytext);
    column += yyleng;
}

<STRING>\" {
    if (print_tokens) printf("\")\n");
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

"true"  { if(print_tokens) printf("BOOLLIT(true)\n"); column += yyleng; }
"false" { if(print_tokens) printf("BOOLLIT(false)\n"); column += yyleng; }

"System.out.print" { TOKEN("PRINT"); column += yyleng; }
"Integer.parseInt" { TOKEN("PARSEINT"); column += yyleng; }
".length"          { TOKEN("DOTLENGTH"); column += yyleng; }

"==" { TOKEN("EQ"); column += yyleng; }
"!=" { TOKEN("NE"); column += yyleng; }
">=" { TOKEN("GE"); column += yyleng; }
"<=" { TOKEN("LE"); column += yyleng; }
"&&" { TOKEN("AND"); column += yyleng; }
"||" { TOKEN("OR"); column += yyleng; }
"->" { TOKEN("ARROW"); column += yyleng; }
"<<" { TOKEN("LSHIFT"); column += yyleng; }
">>" { TOKEN("RSHIFT"); column += yyleng; }
"++" { TOKEN("RESERVED"); column += yyleng; }
"--" { TOKEN("RESERVED"); column += yyleng; }

"="  { TOKEN("ASSIGN"); column += yyleng; }
">"  { TOKEN("GT"); column += yyleng; }
"<"  { TOKEN("LT"); column += yyleng; }
"+"  { TOKEN("PLUS"); column += yyleng; }
"-"  { TOKEN("MINUS"); column += yyleng; }
"*"  { TOKEN("STAR"); column += yyleng; }
"/"  { TOKEN("DIV"); column += yyleng; }
"%"  { TOKEN("MOD"); column += yyleng; }
"!"  { TOKEN("NOT"); column += yyleng; }
"^"  { TOKEN("XOR"); column += yyleng; }

"{"  { TOKEN("LBRACE"); column += yyleng; }
"}"  { TOKEN("RBRACE"); column += yyleng; }
"("  { TOKEN("LPAR"); column += yyleng; }
")"  { TOKEN("RPAR"); column += yyleng; }
"["  { TOKEN("LSQ"); column += yyleng; }
"]"  { TOKEN("RSQ"); column += yyleng; }
";"  { TOKEN("SEMICOLON"); column += yyleng; }
","  { TOKEN("COMMA"); column += yyleng; }

"class"   { TOKEN("CLASS"); column += yyleng; }
"public"  { TOKEN("PUBLIC"); column += yyleng; }
"static"  { TOKEN("STATIC"); column += yyleng; }
"int"     { TOKEN("INT"); column += yyleng; }
"double"  { TOKEN("DOUBLE"); column += yyleng; }
"boolean" { TOKEN("BOOL"); column += yyleng; }
"void"    { TOKEN("VOID"); column += yyleng; }
"if"      { TOKEN("IF"); column += yyleng; }
"else"    { TOKEN("ELSE"); column += yyleng; }
"while"   { TOKEN("WHILE"); column += yyleng; }
"return"  { TOKEN("RETURN"); column += yyleng; }
"String"  { TOKEN("STRING"); column += yyleng; }

"null"    { TOKEN("RESERVED"); column += yyleng; }
"Integer" { TOKEN("RESERVED"); column += yyleng; }
"System"  { TOKEN("RESERVED"); column += yyleng; }

{letter}{alnum}* {
    if(print_tokens) printf("IDENTIFIER(%s)\n", yytext);
    column += yyleng;
}

{digit}+ {
    if(print_tokens) printf("NATURAL(%s)\n", yytext);
    column += yyleng;
}

\n { line++; column = 1; }
[ \t]+ { column += yyleng; }

. {
    printf("Line %d, col %d: illegal character (%s)\n",
           line, column, yytext);
}

%%
int main(int argc, char **argv) {

    if (argc > 1) {
        if (strcmp(argv[1], "-l") == 0)
            print_tokens = 1;
        else if (strcmp(argv[1], "-e1") == 0)
            print_tokens = 0;
    }

    yylex();
    return 0;
}

int yywrap() {

    if (YY_START == COMMENT) {
        printf("Line %d, col %d: unterminated comment\n",
               comment_start_line, comment_start_column);
        return 1;
    }

    return 1;
}
%{
#include <stdio.h>
#include <string.h>

int line = 1;
int column = 1;

int str_start_line;
int str_start_column;

int comment_start_line;
int comment_start_column;

int str_error;

char str_buffer[10000];
int str_index;

int print_tokens = 0;

#define TOKEN(t) if(print_tokens) printf("%s\n", t);

%}

%X COMMENT STRING

digit      [0-9]
nonzero    [1-9]
nat        {digit}(_*{digit})*
frac       {digit}(_*{digit})*
exp        [eE][+-]?{digit}(_*{digit})*
letter     [a-zA-Z_$]
alnum      [a-zA-Z0-9_$]

%%

"/*" {
    comment_start_line = line;
    comment_start_column = column;
    BEGIN(COMMENT);
    column += yyleng;
}

<COMMENT>{
    "*/" {
        column += yyleng;
        BEGIN(INITIAL);
    }

    [^*\r\n]+ {
        column += yyleng;
    }

    "*" {
        column += yyleng;
    }

    \r\n {
        line++;
        column = 1;
    }

    \r {
        line++;
        column = 1;
    }

    \n {
        line++;
        column = 1;
    }
}

"//"[^\r\n]* {
    column += yyleng;
}

\" {
    str_start_line = line;
    str_start_column = column;
    str_index = 0;
    str_error = 0;
    str_buffer[str_index++] = '"';
    BEGIN(STRING);
    column += yyleng;
}

<STRING>\\[fnrt\\\"] {
    if(!str_error) {
        for(int i = 0; i < yyleng; i++)
            str_buffer[str_index++] = yytext[i];
    }
    column += yyleng;
}

<STRING>\\[^fnrt\\\"] {
    printf("Line %d, col %d: invalid escape sequence (%s)\n",
           line, column, yytext);
    str_error = 1;
    column += yyleng;
}

<STRING>[^\\\"\r\n]+ {
    if(!str_error) {
        for(int i = 0; i < yyleng; i++)
            str_buffer[str_index++] = yytext[i];
    }
    column += yyleng;
}

<STRING>\" {
    if(!str_error && print_tokens) {
        str_buffer[str_index++] = '"';
        str_buffer[str_index] = '\0';
        printf("STRLIT(%s)\n", str_buffer);
    }
    column += yyleng;
    BEGIN(INITIAL);
}

<STRING>\r\n {
    printf("Line %d, col %d: unterminated string literal\n",
           str_start_line, str_start_column);
    line++;
    column = 1;
    BEGIN(INITIAL);
}

<STRING>\r {
    printf("Line %d, col %d: unterminated string literal\n",
           str_start_line, str_start_column);
    line++;
    column = 1;
    BEGIN(INITIAL);
}

<STRING>\n {
    printf("Line %d, col %d: unterminated string literal\n",
           str_start_line, str_start_column);
    line++;
    column = 1;
    BEGIN(INITIAL);
}

<STRING><<EOF>> {
    printf("Line %d, col %d: unterminated string literal\n",
           str_start_line, str_start_column);
    return 0;
}

"true"  { if(print_tokens) printf("BOOLLIT(true)\n"); column += yyleng; }
"false" { if(print_tokens) printf("BOOLLIT(false)\n"); column += yyleng; }

({nat}"."{frac}?{exp}?|"."{frac}{exp}?|{nat}{exp}) {
    if(print_tokens) printf("DECIMAL(%s)\n", yytext);
    column += yyleng;
}

{digit}+[eE][+-]? {
    printf("Line %d, col %d: invalid decimal literal (%s)\n",
           line, column, yytext);
    column += yyleng;
}

{nonzero}(_*{digit})* {
    if(print_tokens) printf("NATURAL(%s)\n", yytext);
    column += yyleng;
}

"0" {
    if(print_tokens) printf("NATURAL(0)\n");
    column += yyleng;
}

"++" { if(print_tokens) printf("RESERVED(++)\n"); column += yyleng; }
"--" { if(print_tokens) printf("RESERVED(--)\n"); column += yyleng; }

"System.out.print" { TOKEN("PRINT"); column += yyleng; }
"Integer.parseInt" { TOKEN("PARSEINT"); column += yyleng; }
".length"          { TOKEN("DOTLENGTH"); column += yyleng; }

"==" { TOKEN("EQ"); column += yyleng; }
"!=" { TOKEN("NE"); column += yyleng; }
">=" { TOKEN("GE"); column += yyleng; }
"<=" { TOKEN("LE"); column += yyleng; }
"&&" { TOKEN("AND"); column += yyleng; }
"||" { TOKEN("OR"); column += yyleng; }
"^"  { TOKEN("XOR"); column += yyleng; }
"->" { TOKEN("ARROW"); column += yyleng; }

"="  { TOKEN("ASSIGN"); column += yyleng; }
">>" { TOKEN("RSHIFT"); column += yyleng; }
"<<" { TOKEN("LSHIFT"); column += yyleng; }
">"  { TOKEN("GT"); column += yyleng; }
"<"  { TOKEN("LT"); column += yyleng; }

"+"  { TOKEN("PLUS"); column += yyleng; }
"-"  { TOKEN("MINUS"); column += yyleng; }

"*"  { TOKEN("STAR"); column += yyleng; }
"/"  { TOKEN("DIV"); column += yyleng; }
"%"  { TOKEN("MOD"); column += yyleng; }

"!"  { TOKEN("NOT"); column += yyleng; }

"{"  { TOKEN("LBRACE"); column += yyleng; }
"}"  { TOKEN("RBRACE"); column += yyleng; }
"("  { TOKEN("LPAR"); column += yyleng; }
")"  { TOKEN("RPAR"); column += yyleng; }
"["  { TOKEN("LSQ"); column += yyleng; }
"]"  { TOKEN("RSQ"); column += yyleng; }
";"  { TOKEN("SEMICOLON"); column += yyleng; }
","  { TOKEN("COMMA"); column += yyleng; }

"class"   { if(print_tokens) printf("CLASS\n"); column += yyleng; }
"public"  { if(print_tokens) printf("PUBLIC\n"); column += yyleng; }
"static"  { if(print_tokens) printf("STATIC\n"); column += yyleng; }
"int"     { if(print_tokens) printf("INT\n"); column += yyleng; }
"double"  { if(print_tokens) printf("DOUBLE\n"); column += yyleng; }
"boolean" { if(print_tokens) printf("BOOL\n"); column += yyleng; }
"void"    { if(print_tokens) printf("VOID\n"); column += yyleng; }
"if"      { if(print_tokens) printf("IF\n"); column += yyleng; }
"else"    { if(print_tokens) printf("ELSE\n"); column += yyleng; }
"while"   { if(print_tokens) printf("WHILE\n"); column += yyleng; }
"return"  { if(print_tokens) printf("RETURN\n"); column += yyleng; }
"String"  { if(print_tokens) printf("STRING\n"); column += yyleng; }

"abstract"|"assert"|"break"|"byte"|"case"|"catch"|"char"|"const"|"continue"|"default"|"do"|"enum"|"extends"|"final"|"finally"|"float"|"for"|"goto"|"implements"|"import"|"instanceof"|"interface"|"long"|"native"|"new"|"package"|"private"|"protected"|"short"|"strictfp"|"super"|"switch"|"synchronized"|"this"|"throw"|"throws"|"transient"|"try"|"volatile"|"null"|"Integer"|"System" {
    if(print_tokens) printf("RESERVED(%s)\n", yytext);
    column += yyleng;
}

{letter}{alnum}* {
    if(print_tokens) printf("IDENTIFIER(%s)\n", yytext);
    column += yyleng;
}

\r\n { line++; column = 1; }
\r   { line++; column = 1; }
\n   { line++; column = 1; }

[ \t]+ { column += yyleng; }

. {
    printf("Line %d, col %d: illegal character (%s)\n",
           line, column, yytext);
    column += yyleng;
}

%%

int main(int argc, char **argv) {
    if(argc > 1 && strcmp(argv[1], "-l") == 0)
        print_tokens = 1;
    yylex();
    return 0;
}

int yywrap() {
    if(YY_START == COMMENT) {
        printf("Line %d, col %d: unterminated comment\n",
               comment_start_line, comment_start_column);
    }
    if(YY_START == STRING) {
        printf("Line %d, col %d: unterminated string literal\n",
               str_start_line, str_start_column);
    }
    return 1;
}
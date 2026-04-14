%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "y.tab.h"

extern YYSTYPE yylval;

int line = 1;
int column = 1;
int token_line = 1;
int token_column = 1;

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

%X COMMENT STRING_STATE

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

<COMMENT><<EOF>> {
    printf("Line %d, col %d: unterminated comment\n",
           comment_start_line, comment_start_column);
    token_line = line;
    token_column = column;
    BEGIN(INITIAL);
    return 0;
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
    BEGIN(STRING_STATE);
    column += yyleng;
}

<STRING_STATE>\\(\r\n|\n|\r) {
    printf("Line %d, col %d: invalid escape sequence (\\)\n",
           line, column);
    printf("Line %d, col %d: unterminated string literal\n",
           str_start_line, str_start_column);
    line++;
    column = 1;
    BEGIN(INITIAL);
}

<STRING_STATE>\\[fnrt\\\"] {
    if(!str_error) {
        for(int i = 0; i < yyleng; i++)
            str_buffer[str_index++] = yytext[i];
    }
    column += yyleng;
}

<STRING_STATE>\\[^fnrt\\\"\r\n] {
    printf("Line %d, col %d: invalid escape sequence (%s)\n",
           line, column, yytext);
    str_error = 1;
    column += yyleng;
}

<STRING_STATE>[^\\\"\r\n]+ {
    if(!str_error) {
        for(int i = 0; i < yyleng; i++)
            str_buffer[str_index++] = yytext[i];
    }
    column += yyleng;
}

<STRING_STATE>\r\n {
    printf("Line %d, col %d: unterminated string literal\n",
           str_start_line, str_start_column);
    line++;
    column = 1;
    BEGIN(INITIAL);
}

<STRING_STATE>\r {
    printf("Line %d, col %d: unterminated string literal\n",
           str_start_line, str_start_column);
    line++;
    column = 1;
    BEGIN(INITIAL);
}

<STRING_STATE>\n {
    printf("Line %d, col %d: unterminated string literal\n",
           str_start_line, str_start_column);
    line++;
    column = 1;
    BEGIN(INITIAL);
}

<STRING_STATE>\" {
    if(!str_error) {
        str_buffer[str_index++] = '"';
        str_buffer[str_index] = '\0';

        if(print_tokens)
            printf("STRLIT(%s)\n", str_buffer);

        yylval.lexeme = strdup(str_buffer);
        token_line = str_start_line;
        token_column = str_start_column;
        column += yyleng;
        BEGIN(INITIAL);
        return STRLIT;
    }

    column += yyleng;
    BEGIN(INITIAL);
}

<STRING_STATE><<EOF>> {
    printf("Line %d, col %d: unterminated string literal\n",
           str_start_line, str_start_column);
    token_line = line;
    token_column = column;
    BEGIN(INITIAL);
    return 0;
}

"true"  {
    if(print_tokens) printf("BOOLLIT(true)\n");
    yylval.lexeme = strdup("true");
    token_line = line;
    token_column = column;
    column += yyleng;
    return BOOLLIT;
}

"false" {
    if(print_tokens) printf("BOOLLIT(false)\n");
    yylval.lexeme = strdup("false");
    token_line = line;
    token_column = column;
    column += yyleng;
    return BOOLLIT;
}

({nat}"."{frac}?{exp}?|"."{frac}{exp}?|{nat}{exp}) {
    if(print_tokens) printf("DECIMAL(%s)\n", yytext);
    yylval.lexeme = strdup(yytext);
    token_line = line;
    token_column = column;
    column += yyleng;
    return DECIMAL;
}

{nonzero}(_*{digit})* {
    if(print_tokens) printf("NATURAL(%s)\n", yytext);
    yylval.lexeme = strdup(yytext);
    token_line = line;
    token_column = column;
    column += yyleng;
    return NATURAL;
}

"0" {
    if(print_tokens) printf("NATURAL(0)\n");
    yylval.lexeme = strdup("0");
    token_line = line;
    token_column = column;
    column += yyleng;
    return NATURAL;
}

"++" { if(print_tokens) printf("RESERVED(++)\n"); token_line = line; token_column = column; column += yyleng; return INC; }
"--" { if(print_tokens) printf("RESERVED(--)\n"); token_line = line; token_column = column; column += yyleng; return DEC; }

"System.out.print" { TOKEN("PRINT"); token_line = line; token_column = column; column += yyleng; return PRINT; }
"Integer.parseInt" { TOKEN("PARSEINT"); token_line = line; token_column = column; column += yyleng; return PARSEINT; }
".length"          { TOKEN("DOTLENGTH"); token_line = line; token_column = column; column += yyleng; return DOTLENGTH; }

"==" { TOKEN("EQ"); token_line = line; token_column = column; column += yyleng; return EQ; }
"!=" { TOKEN("NE"); token_line = line; token_column = column; column += yyleng; return NE; }
">=" { TOKEN("GE"); token_line = line; token_column = column; column += yyleng; return GE; }
"<=" { TOKEN("LE"); token_line = line; token_column = column; column += yyleng; return LE; }
"&&" { TOKEN("AND"); token_line = line; token_column = column; column += yyleng; return AND; }
"||" { TOKEN("OR"); token_line = line; token_column = column; column += yyleng; return OR; }
"^"  { TOKEN("XOR"); token_line = line; token_column = column; column += yyleng; return XOR; }
"->" { TOKEN("ARROW"); token_line = line; token_column = column; column += yyleng; return ARROW; }

"="  { TOKEN("ASSIGN"); token_line = line; token_column = column; column += yyleng; return ASSIGN; }
">>" { TOKEN("RSHIFT"); token_line = line; token_column = column; column += yyleng; return RSHIFT; }
"<<" { TOKEN("LSHIFT"); token_line = line; token_column = column; column += yyleng; return LSHIFT; }
">"  { TOKEN("GT"); token_line = line; token_column = column; column += yyleng; return GT; }
"<"  { TOKEN("LT"); token_line = line; token_column = column; column += yyleng; return LT; }

"+"  { TOKEN("PLUS"); token_line = line; token_column = column; column += yyleng; return PLUS; }
"-"  { TOKEN("MINUS"); token_line = line; token_column = column; column += yyleng; return MINUS; }

"*"  { TOKEN("STAR"); token_line = line; token_column = column; column += yyleng; return STAR; }
"/"  { TOKEN("DIV"); token_line = line; token_column = column; column += yyleng; return DIV; }
"%"  { TOKEN("MOD"); token_line = line; token_column = column; column += yyleng; return MOD; }

"!"  { TOKEN("NOT"); token_line = line; token_column = column; column += yyleng; return NOT; }

"{"  { TOKEN("LBRACE"); token_line = line; token_column = column; column += yyleng; return LBRACE; }
"}"  { TOKEN("RBRACE"); token_line = line; token_column = column; column += yyleng; return RBRACE; }
"("  { TOKEN("LPAR"); token_line = line; token_column = column; column += yyleng; return LPAR; }
")"  { TOKEN("RPAR"); token_line = line; token_column = column; column += yyleng; return RPAR; }
"["  { TOKEN("LSQ"); token_line = line; token_column = column; column += yyleng; return LSQ; }
"]"  { TOKEN("RSQ"); token_line = line; token_column = column; column += yyleng; return RSQ; }
";"  { TOKEN("SEMICOLON"); token_line = line; token_column = column; column += yyleng; return SEMICOLON; }
","  { TOKEN("COMMA"); token_line = line; token_column = column; column += yyleng; return COMMA; }

"class"   { if(print_tokens) printf("CLASS\n"); token_line = line; token_column = column; column += yyleng; return CLASS; }
"public"  { if(print_tokens) printf("PUBLIC\n"); token_line = line; token_column = column; column += yyleng; return PUBLIC; }
"static"  { if(print_tokens) printf("STATIC\n"); token_line = line; token_column = column; column += yyleng; return STATIC; }
"int"     { if(print_tokens) printf("INT\n"); token_line = line; token_column = column; column += yyleng; return INT; }
"double"  { if(print_tokens) printf("DOUBLE\n"); token_line = line; token_column = column; column += yyleng; return DOUBLE; }
"boolean" { if(print_tokens) printf("BOOL\n"); token_line = line; token_column = column; column += yyleng; return BOOL; }
"void"    { if(print_tokens) printf("VOID\n"); token_line = line; token_column = column; column += yyleng; return VOID; }
"if"      { if(print_tokens) printf("IF\n"); token_line = line; token_column = column; column += yyleng; return IF; }
"else"    { if(print_tokens) printf("ELSE\n"); token_line = line; token_column = column; column += yyleng; return ELSE; }
"while"   { if(print_tokens) printf("WHILE\n"); token_line = line; token_column = column; column += yyleng; return WHILE; }
"return"  { if(print_tokens) printf("RETURN\n"); token_line = line; token_column = column; column += yyleng; return RETURN; }
"String"  { if(print_tokens) printf("STRING\n"); token_line = line; token_column = column; column += yyleng; return STRING; }

"abstract"|"assert"|"break"|"byte"|"case"|"catch"|"char"|"const"|"continue"|"default"|"do"|"enum"|"extends"|"final"|"finally"|"float"|"for"|"goto"|"implements"|"import"|"instanceof"|"interface"|"long"|"native"|"new"|"package"|"private"|"protected"|"short"|"strictfp"|"super"|"switch"|"synchronized"|"this"|"throw"|"throws"|"transient"|"try"|"volatile"|"null"|"Integer"|"System" {
    if(print_tokens) printf("RESERVED(%s)\n", yytext);
    token_line = line;
    token_column = column;
    column += yyleng;
    return RESERVED;
}

{letter}{alnum}* {
    if(print_tokens) printf("IDENTIFIER(%s)\n", yytext);
    yylval.lexeme = strdup(yytext);
    token_line = line;
    token_column = column;
    column += yyleng;
    return IDENTIFIER;
}

<INITIAL>\r\n { line++; column = 1; }
<INITIAL>\r   { line++; column = 1; }
<INITIAL>\n   { line++; column = 1; }

<INITIAL>[ \t\f]+ { column += yyleng; }

. {
    printf("Line %d, col %d: illegal character (%s)\n",
           line, column, yytext);
    column += yyleng;
}

%%

int yywrap() {
    return 1;
}
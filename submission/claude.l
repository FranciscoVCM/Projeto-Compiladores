%option noyywrap
%option noinput nounput

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

char token_text[10000] = "";
int last_lex_error_line = 0;

int print_tokens = 0;
extern int suppress_errors;
extern int suppress_after_string;
extern int suppress_to_method_end;

#define TOKEN(t) if(print_tokens) printf("%s\n", t);
#define SET_TOKEN_TEXT(s) do { strncpy(token_text, (s), sizeof(token_text) - 1); token_text[sizeof(token_text) - 1] = '\0'; } while(0)

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
    last_lex_error_line = comment_start_line;

    token_line = line;
    token_column = column;
    SET_TOKEN_TEXT("");
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
    if (!suppress_errors) {
        printf("Line %d, col %d: invalid escape sequence (\\)\n", line, column);
        last_lex_error_line = line;
        printf("Line %d, col %d: unterminated string literal\n", str_start_line, str_start_column);
        last_lex_error_line = str_start_line;
    }
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
    if (!suppress_errors) {
        printf("Line %d, col %d: invalid escape sequence (%s)\n", line, column, yytext);
        last_lex_error_line = line;
    }
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
    if (!suppress_errors) {
        printf("Line %d, col %d: unterminated string literal\n", str_start_line, str_start_column);
        last_lex_error_line = str_start_line;
    }
    line++;
    column = 1;
    BEGIN(INITIAL);
}

<STRING_STATE>\r {
    if (!suppress_errors) {
        printf("Line %d, col %d: unterminated string literal\n", str_start_line, str_start_column);
        last_lex_error_line = str_start_line;
    }
    line++;
    column = 1;
    BEGIN(INITIAL);
}

<STRING_STATE>\n {
    if (!suppress_errors) {
        printf("Line %d, col %d: unterminated string literal\n", str_start_line, str_start_column);
        last_lex_error_line = str_start_line;
    }
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
        SET_TOKEN_TEXT(str_buffer);
        column += yyleng;
        BEGIN(INITIAL);
        return STRLIT;
    }

    column += yyleng;
    BEGIN(INITIAL);
}

<STRING_STATE><<EOF>> {
    if (!suppress_errors) {
        printf("Line %d, col %d: unterminated string literal\n", str_start_line, str_start_column);
        last_lex_error_line = str_start_line;
    }
    token_line = line;
    token_column = column;
    SET_TOKEN_TEXT("");
    BEGIN(INITIAL);
    return 0;
}

"true"  {
    if(print_tokens) printf("BOOLLIT(true)\n");
    yylval.lexeme = strdup("true");
    token_line = line;
    token_column = column;
    SET_TOKEN_TEXT("true");
    column += yyleng;
    return BOOLLIT;
}

"false" {
    if(print_tokens) printf("BOOLLIT(false)\n");
    yylval.lexeme = strdup("false");
    token_line = line;
    token_column = column;
    SET_TOKEN_TEXT("false");
    column += yyleng;
    return BOOLLIT;
}

({nat}"."{frac}?{exp}?|"."{frac}{exp}?|{nat}{exp}) {
    if(print_tokens) printf("DECIMAL(%s)\n", yytext);
    yylval.lexeme = strdup(yytext);
    token_line = line;
    token_column = column;
    SET_TOKEN_TEXT(yytext);
    column += yyleng;
    return DECIMAL;
}

{nonzero}(_*{digit})* {
    if(print_tokens) printf("NATURAL(%s)\n", yytext);
    yylval.lexeme = strdup(yytext);
    token_line = line;
    token_column = column;
    SET_TOKEN_TEXT(yytext);
    column += yyleng;
    return NATURAL;
}

"0" {
    if(print_tokens) printf("NATURAL(0)\n");
    yylval.lexeme = strdup("0");
    token_line = line;
    token_column = column;
    SET_TOKEN_TEXT("0");
    column += yyleng;
    return NATURAL;
}

"++" { if(print_tokens) printf("RESERVED(++)\n"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return INC; }
"--" { if(print_tokens) printf("RESERVED(--)\n"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return DEC; }

"System.out." {
    if (!suppress_errors) {
        printf("Line %d, col %d: illegal character (.)\n", line, column + 6);
        last_lex_error_line = line;
        printf("Line %d, col %d: illegal character (.)\n", line, column + 10);
        last_lex_error_line = line;
    }
    column += yyleng;
}
"System.out.print" { TOKEN("PRINT"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return PRINT; }
"Integer.parseInt" { TOKEN("PARSEINT"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return PARSEINT; }
".length"          { TOKEN("DOTLENGTH"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return DOTLENGTH; }

"==" { TOKEN("EQ"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return EQ; }
"!=" { TOKEN("NE"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return NE; }
">=" { TOKEN("GE"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return GE; }
"<=" { TOKEN("LE"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return LE; }
"&&" { TOKEN("AND"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return AND; }
"||" { TOKEN("OR"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return OR; }
"^"  { TOKEN("XOR"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return XOR; }
"->" { TOKEN("ARROW"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return ARROW; }

"="  { TOKEN("ASSIGN"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return ASSIGN; }
">>" { TOKEN("RSHIFT"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return RSHIFT; }
"<<" { TOKEN("LSHIFT"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return LSHIFT; }
">"  { TOKEN("GT"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return GT; }
"<"  { TOKEN("LT"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return LT; }

"+"  { TOKEN("PLUS"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return PLUS; }
"-"  { TOKEN("MINUS"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return MINUS; }

"*"  { TOKEN("STAR"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return STAR; }
"/"  { TOKEN("DIV"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return DIV; }
"%"  { TOKEN("MOD"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return MOD; }

"!"  { TOKEN("NOT"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return NOT; }

"{"  { TOKEN("LBRACE"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return LBRACE; }
"}"  { TOKEN("RBRACE"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return RBRACE; }
"("  { TOKEN("LPAR"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return LPAR; }
")"  { TOKEN("RPAR"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return RPAR; }
"["  { TOKEN("LSQ"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return LSQ; }
"]"  { TOKEN("RSQ"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return RSQ; }
";"  { TOKEN("SEMICOLON"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return SEMICOLON; }
","  { TOKEN("COMMA"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return COMMA; }

"class"   { if(print_tokens) printf("CLASS\n"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return CLASS; }
"public"  { if(print_tokens) printf("PUBLIC\n"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return PUBLIC; }
"static"  { if(print_tokens) printf("STATIC\n"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return STATIC; }
"int"     { if(print_tokens) printf("INT\n"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return INT; }
"double"  { if(print_tokens) printf("DOUBLE\n"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return DOUBLE; }
"boolean" { if(print_tokens) printf("BOOL\n"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return BOOL; }
"void"    { if(print_tokens) printf("VOID\n"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return VOID; }
"if"      { if(print_tokens) printf("IF\n"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return IF; }
"else"    { if(print_tokens) printf("ELSE\n"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return ELSE; }
"while"   { if(print_tokens) printf("WHILE\n"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return WHILE; }
"return"  { if(print_tokens) printf("RETURN\n"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return RETURN; }
"String"  { if(print_tokens) printf("STRING\n"); token_line = line; token_column = column; SET_TOKEN_TEXT(yytext); column += yyleng; return STRING; }

"abstract"|"assert"|"break"|"byte"|"case"|"catch"|"char"|"const"|"continue"|"default"|"do"|"enum"|"extends"|"final"|"finally"|"float"|"for"|"goto"|"implements"|"import"|"instanceof"|"interface"|"long"|"native"|"new"|"package"|"private"|"protected"|"short"|"strictfp"|"super"|"switch"|"synchronized"|"this"|"throw"|"throws"|"transient"|"try"|"volatile"|"null"|"Integer"|"System" {
    if(print_tokens) printf("RESERVED(%s)\n", yytext);
    token_line = line;
    token_column = column;
    SET_TOKEN_TEXT(yytext);
    column += yyleng;
    return RESERVED;
}

{letter}{alnum}* {
    if(print_tokens) printf("IDENTIFIER(%s)\n", yytext);
    yylval.lexeme = strdup(yytext);
    token_line = line;
    token_column = column;
    SET_TOKEN_TEXT(yytext);
    column += yyleng;
    return IDENTIFIER;
}

<INITIAL>\r\n { line++; column = 1; }
<INITIAL>\r   { line++; column = 1; }
<INITIAL>\n   { line++; column = 1; }

<INITIAL>[ \t\f]+ { column += yyleng; }

. {
    if (!suppress_errors) {
        printf("Line %d, col %d: illegal character (%s)\n",
               line, column, yytext);
        last_lex_error_line = line;
    }
    column += yyleng;
}

%%
%{
#include "y.tab.h"
#include "ast.h"
#include "semantics.h"

#define PASS_TOKEN() yylval.lexeme = strdup(yytext);
#define SETLOC() do { \
    yylloc.first_line = line; \
    yylloc.first_column = column; \
    yylloc.last_line = line; \
    yylloc.last_column = column + yyleng - 1; \
} while(0)

int yyparse(void);
void yyerror(char *);

int line = 1;
int column = 1;
int token_line = 1;
int token_column = 1;
char token_text[10000] = "";
int last_lex_error_line = 0;

extern int print_tokens;
extern int only_errors;
extern int syntax_errors;

int str_start_line;
int str_start_column;
int comment_start_line;
int comment_start_column;
int str_error;
char str_buffer[10000];
int str_index;

static void set_token_text(const char *s) {
    strncpy(token_text, s, sizeof(token_text) - 1);
    token_text[sizeof(token_text) - 1] = '\0';
}
%}

%option noyywrap

%x COMMENT STRING_STATE

digit      [0-9]
nonzero    [1-9]
nat        {digit}(_*{digit})*
frac       {digit}(_*{digit})*
exp        [eE][+-]?{digit}(_*{digit})*
letter     [a-zA-Z_$]
alnum      [a-zA-Z0-9_$]

%%

"/*" {
    SETLOC();
    comment_start_line = line;
    comment_start_column = column;
    column += yyleng;
    BEGIN(COMMENT);
}

<COMMENT>{
    "*/" { column += yyleng; BEGIN(INITIAL); }
    [^*\r\n]+ { column += yyleng; }
    "*" { column += yyleng; }
    \r\n { line++; column = 1; }
    \r { line++; column = 1; }
    \n { line++; column = 1; }
}

<COMMENT><<EOF>> {
    printf("Line %d, col %d: unterminated comment\n", comment_start_line, comment_start_column);
    last_lex_error_line = comment_start_line;
    token_line = line;
    token_column = column;
    token_text[0] = '\0';
    return 0;
}

"//"[^\r\n]* {
    column += yyleng;
}

\" {
    SETLOC();
    str_start_line = line;
    str_start_column = column;
    str_index = 0;
    str_error = 0;
    str_buffer[str_index++] = '"';
    column += yyleng;
    BEGIN(STRING_STATE);
}

<STRING_STATE>\\(\r\n|\n|\r) {
    printf("Line %d, col %d: invalid escape sequence (\\)\n", line, column);
    last_lex_error_line = line;
    printf("Line %d, col %d: unterminated string literal\n", str_start_line, str_start_column);
    last_lex_error_line = str_start_line;
    line++;
    column = 1;
    BEGIN(INITIAL);
}

<STRING_STATE>\\[fnrt\\\"] {
    if (!str_error) {
        for (int i = 0; i < yyleng; i++)
            str_buffer[str_index++] = yytext[i];
    }
    column += yyleng;
}

<STRING_STATE>\\[^fnrt\\\"\r\n] {
    printf("Line %d, col %d: invalid escape sequence (%s)\n", line, column, yytext);
    last_lex_error_line = line;
    str_error = 1;
    column += yyleng;
}

<STRING_STATE>[^\\\"\r\n]+ {
    if (!str_error) {
        for (int i = 0; i < yyleng; i++)
            str_buffer[str_index++] = yytext[i];
    }
    column += yyleng;
}

<STRING_STATE>\r\n {
    printf("Line %d, col %d: unterminated string literal\n", str_start_line, str_start_column);
    last_lex_error_line = str_start_line;
    line++;
    column = 1;
    BEGIN(INITIAL);
}

<STRING_STATE>\r {
    printf("Line %d, col %d: unterminated string literal\n", str_start_line, str_start_column);
    last_lex_error_line = str_start_line;
    line++;
    column = 1;
    BEGIN(INITIAL);
}

<STRING_STATE>\n {
    printf("Line %d, col %d: unterminated string literal\n", str_start_line, str_start_column);
    last_lex_error_line = str_start_line;
    line++;
    column = 1;
    BEGIN(INITIAL);
}

<STRING_STATE>\" {
    if (!str_error) {
        str_buffer[str_index++] = '"';
        str_buffer[str_index] = '\0';

        if (print_tokens)
            printf("STRLIT(%s)\n", str_buffer);

        yylval.lexeme = strdup(str_buffer);
        token_line = str_start_line;
        token_column = str_start_column;
        set_token_text(str_buffer);
        yylloc.first_line = str_start_line;
        yylloc.first_column = str_start_column;
        yylloc.last_line = line;
        yylloc.last_column = column;

        column += yyleng;
        BEGIN(INITIAL);
        return STRLIT;
    }

    column += yyleng;
    BEGIN(INITIAL);
}

<STRING_STATE><<EOF>> {
    printf("Line %d, col %d: unterminated string literal\n", str_start_line, str_start_column);
    last_lex_error_line = str_start_line;
    token_line = line;
    token_column = column;
    token_text[0] = '\0';
    return 0;
}

"true" {
    SETLOC();
    if (print_tokens) printf("BOOLLIT(true)\n");
    yylval.lexeme = strdup("true");
    token_line = line; token_column = column;
    set_token_text("true");
    column += yyleng;
    return BOOLLIT;
}

"false" {
    SETLOC();
    if (print_tokens) printf("BOOLLIT(false)\n");
    yylval.lexeme = strdup("false");
    token_line = line; token_column = column;
    set_token_text("false");
    column += yyleng;
    return BOOLLIT;
}

({nat}"."{frac}?{exp}?|"."{frac}{exp}?|{nat}{exp}) {
    SETLOC();
    if (print_tokens) printf("DECIMAL(%s)\n", yytext);
    yylval.lexeme = strdup(yytext);
    token_line = line; token_column = column;
    set_token_text(yytext);
    column += yyleng;
    return DECIMAL;
}

{nonzero}(_*{digit})* {
    SETLOC();
    if (print_tokens) printf("NATURAL(%s)\n", yytext);
    yylval.lexeme = strdup(yytext);
    token_line = line; token_column = column;
    set_token_text(yytext);
    column += yyleng;
    return NATURAL;
}

"0" {
    SETLOC();
    if (print_tokens) printf("NATURAL(0)\n");
    yylval.lexeme = strdup("0");
    token_line = line; token_column = column;
    set_token_text("0");
    column += yyleng;
    return NATURAL;
}

"++" { SETLOC(); if (print_tokens) printf("RESERVED(++)\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return INC; }
"--" { SETLOC(); if (print_tokens) printf("RESERVED(--)\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return DEC; }

"System.out." {
    printf("Line %d, col %d: illegal character (.)\n", line, column + 6);
    last_lex_error_line = line;
    printf("Line %d, col %d: illegal character (.)\n", line, column + 10);
    last_lex_error_line = line;
    column += yyleng;
}

"System.out.print" { SETLOC(); if (print_tokens) printf("PRINT\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return PRINT; }
"Integer.parseInt" { SETLOC(); if (print_tokens) printf("PARSEINT\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return PARSEINT; }
".length"          { SETLOC(); if (print_tokens) printf("DOTLENGTH\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return DOTLENGTH; }

"==" { SETLOC(); if (print_tokens) printf("EQ\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return EQ; }
"!=" { SETLOC(); if (print_tokens) printf("NE\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return NE; }
">=" { SETLOC(); if (print_tokens) printf("GE\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return GE; }
"<=" { SETLOC(); if (print_tokens) printf("LE\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return LE; }
"&&" { SETLOC(); if (print_tokens) printf("AND\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return AND; }
"||" { SETLOC(); if (print_tokens) printf("OR\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return OR; }
"^"  { SETLOC(); if (print_tokens) printf("XOR\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return XOR; }
"->" { SETLOC(); if (print_tokens) printf("ARROW\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return ARROW; }

"="  { SETLOC(); if (print_tokens) printf("ASSIGN\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return ASSIGN; }
">>" { SETLOC(); if (print_tokens) printf("RSHIFT\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return RSHIFT; }
"<<" { SETLOC(); if (print_tokens) printf("LSHIFT\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return LSHIFT; }
">"  { SETLOC(); if (print_tokens) printf("GT\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return GT; }
"<"  { SETLOC(); if (print_tokens) printf("LT\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return LT; }

"+"  { SETLOC(); if (print_tokens) printf("PLUS\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return PLUS; }
"-"  { SETLOC(); if (print_tokens) printf("MINUS\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return MINUS; }
"*"  { SETLOC(); if (print_tokens) printf("STAR\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return STAR; }
"/"  { SETLOC(); if (print_tokens) printf("DIV\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return DIV; }
"%"  { SETLOC(); if (print_tokens) printf("MOD\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return MOD; }

"!"  { SETLOC(); if (print_tokens) printf("NOT\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return NOT; }

"{"  { SETLOC(); if (print_tokens) printf("LBRACE\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return LBRACE; }
"}"  { SETLOC(); if (print_tokens) printf("RBRACE\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return RBRACE; }
"("  { SETLOC(); if (print_tokens) printf("LPAR\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return LPAR; }
")"  { SETLOC(); if (print_tokens) printf("RPAR\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return RPAR; }
"["  { SETLOC(); if (print_tokens) printf("LSQ\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return LSQ; }
"]"  { SETLOC(); if (print_tokens) printf("RSQ\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return RSQ; }
";"  { SETLOC(); if (print_tokens) printf("SEMICOLON\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return SEMICOLON; }
","  { SETLOC(); if (print_tokens) printf("COMMA\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return COMMA; }

"class"   { SETLOC(); if (print_tokens) printf("CLASS\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return CLASS; }
"public"  { SETLOC(); if (print_tokens) printf("PUBLIC\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return PUBLIC; }
"static"  { SETLOC(); if (print_tokens) printf("STATIC\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return STATIC; }
"int"     { SETLOC(); if (print_tokens) printf("INT\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return INT; }
"double"  { SETLOC(); if (print_tokens) printf("DOUBLE\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return DOUBLE; }
"boolean" { SETLOC(); if (print_tokens) printf("BOOL\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return BOOL; }
"void"    { SETLOC(); if (print_tokens) printf("VOID\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return VOID; }
"if"      { SETLOC(); if (print_tokens) printf("IF\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return IF; }
"else"    { SETLOC(); if (print_tokens) printf("ELSE\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return ELSE; }
"while"   { SETLOC(); if (print_tokens) printf("WHILE\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return WHILE; }
"return"  { SETLOC(); if (print_tokens) printf("RETURN\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return RETURN; }
"String"  { SETLOC(); if (print_tokens) printf("STRING\n"); token_line=line; token_column=column; set_token_text(yytext); column += yyleng; return STRING; }

"abstract"|"assert"|"break"|"byte"|"case"|"catch"|"char"|"const"|"continue"|"default"|"do"|"enum"|"extends"|"final"|"finally"|"float"|"for"|"goto"|"implements"|"import"|"instanceof"|"interface"|"long"|"native"|"new"|"package"|"private"|"protected"|"short"|"strictfp"|"super"|"switch"|"synchronized"|"this"|"throw"|"throws"|"transient"|"try"|"volatile"|"null"|"Integer"|"System" {
    SETLOC();
    if (print_tokens) printf("RESERVED(%s)\n", yytext);
    token_line=line; token_column=column; set_token_text(yytext);
    column += yyleng;
    return RESERVED;
}

{letter}{alnum}* {
    SETLOC();
    if (print_tokens) printf("IDENTIFIER(%s)\n", yytext);
    yylval.lexeme = strdup(yytext);
    token_line=line; token_column=column; set_token_text(yytext);
    column += yyleng;
    return IDENTIFIER;
}

<INITIAL>\r\n { line++; column = 1; }
<INITIAL>\r   { line++; column = 1; }
<INITIAL>\n   { line++; column = 1; }
<INITIAL>[ \t\f]+ { column += yyleng; }

<<EOF>> {
    yylloc.first_line = line;
    yylloc.first_column = column;
    yylloc.last_line = line;
    yylloc.last_column = column;
    token_line = line;
    token_column = column;
    token_text[0] = '\0';
    return 0;
}

. {
    printf("Line %d, col %d: illegal character (%s)\n", line, column, yytext);
    last_lex_error_line = line;
    column += yyleng;
}

%%
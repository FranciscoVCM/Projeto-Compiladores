/*Francisco Vieira Cid Martins 2023211141*/
/*Rui Mário Teixeira Camarão 2023216522*/
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "y.tab.h"
#include "ast.h"
#include "semantics.h"
#include "codegen.h"

extern YYSTYPE yylval;
extern YYLTYPE yylloc;
extern struct node *ast;

int line = 1;
int column = 1;
int token_line = 1;
int token_column = 1;

int str_line = 1;
int str_column = 1;
int comment_line = 1;
int comment_column = 1;
int str_error = 0;

int print_tokens = 0;
int print_tree = 0;
int parse_mode = 0;
int lexical_only = 0;
int syntax_errors = 0;
int lexical_errors = 0;
int semantic_mode = 0;
int semantic_errors_only = 0;

char token_text[512] = "";
char str_buffer[200] = "";

#define SAVE_TOKEN() do { \
    token_line = line; \
    token_column = column; \
    yylloc.first_line = line; \
    yylloc.first_column = column; \
    yylloc.last_line = line; \
    yylloc.last_column = column + yyleng - 1; \
    strncpy(token_text, yytext, sizeof(token_text) - 1); \
    token_text[sizeof(token_text) - 1] = '\0'; \
} while (0)

#define SIMPLE_TOKEN(tok, name) do { \
    SAVE_TOKEN(); \
    column += yyleng; \
    if (print_tokens) printf("%s\n", name); \
    if (parse_mode || print_tree || semantic_mode || semantic_errors_only) return tok; \
} while (0)

#define VALUE_TOKEN(tok, name) do { \
    SAVE_TOKEN(); \
    yylval.lexeme = strdup(yytext); \
    column += yyleng; \
    if (print_tokens) printf(name "(%s)\n", yytext); \
    if (parse_mode || print_tree || semantic_mode || semantic_errors_only) return tok; \
} while (0)
%}

%X STRING_STATE LINE_COMMENT BLOCK_COMMENT

number      [0-9]
intpart     [0-9]("_"+[0-9]|[0-9])*
letter      ([a-z]|[A-Z]|\_|\$)
reserved    "++"|"--"|"null"|"Integer"|"System"|"abstract"|"assert"|"break"|"byte"|"case"|"catch"|"char"|"const"|"continue"|"default"|"do"|"double"|"final"|"finally"|"float"|"for"|"goto"|"implements"|"import"|"instanceof"|"interface"|"long"|"native"|"new"|"package"|"private"|"protected"|"public"|"return"|"short"|"static"|"strictfp"|"super"|"switch"|"synchronized"|"this"|"throw"|"throws"|"transient"|"try"|"void"|"volatile"|"enum"|"extends"

%%

"true"|"false"              { VALUE_TOKEN(BOOLLIT, "BOOLLIT"); }

"&&"                        { SIMPLE_TOKEN(AND, "AND"); }
"="                         { SIMPLE_TOKEN(ASSIGN, "ASSIGN"); }
"*"                         { SIMPLE_TOKEN(STAR, "STAR"); }
","                         { SIMPLE_TOKEN(COMMA, "COMMA"); }
"/"                         { SIMPLE_TOKEN(DIV, "DIV"); }
"=="                        { SIMPLE_TOKEN(EQ, "EQ"); }
">="                        { SIMPLE_TOKEN(GE, "GE"); }
">"                         { SIMPLE_TOKEN(GT, "GT"); }
"{"                         { SIMPLE_TOKEN(LBRACE, "LBRACE"); }
"<="                        { SIMPLE_TOKEN(LE, "LE"); }
"("                         { SIMPLE_TOKEN(LPAR, "LPAR"); }
"["                         { SIMPLE_TOKEN(LSQ, "LSQ"); }
"<"                         { SIMPLE_TOKEN(LT, "LT"); }
"-"                         { SIMPLE_TOKEN(MINUS, "MINUS"); }
"%"                         { SIMPLE_TOKEN(MOD, "MOD"); }
"!="                        { SIMPLE_TOKEN(NE, "NE"); }
"!"                         { SIMPLE_TOKEN(NOT, "NOT"); }
"||"                        { SIMPLE_TOKEN(OR, "OR"); }
"+"                         { SIMPLE_TOKEN(PLUS, "PLUS"); }
"}"                         { SIMPLE_TOKEN(RBRACE, "RBRACE"); }
")"                         { SIMPLE_TOKEN(RPAR, "RPAR"); }
"]"                         { SIMPLE_TOKEN(RSQ, "RSQ"); }
";"                         { SIMPLE_TOKEN(SEMICOLON, "SEMICOLON"); }
"->"                        { SIMPLE_TOKEN(ARROW, "ARROW"); }
"<<"                        { SIMPLE_TOKEN(LSHIFT, "LSHIFT"); }
">>"                        { SIMPLE_TOKEN(RSHIFT, "RSHIFT"); }
"^"                         { SIMPLE_TOKEN(XOR, "XOR"); }

"boolean"                   { SIMPLE_TOKEN(BOOL, "BOOL"); }
"class"                     { SIMPLE_TOKEN(CLASS, "CLASS"); }
".length"                   { SIMPLE_TOKEN(DOTLENGTH, "DOTLENGTH"); }
"double"                    { SIMPLE_TOKEN(DOUBLE, "DOUBLE"); }
"else"                      { SIMPLE_TOKEN(ELSE, "ELSE"); }
"if"                        { SIMPLE_TOKEN(IF, "IF"); }
"int"                       { SIMPLE_TOKEN(INT, "INT"); }
"System.out.print"          { SIMPLE_TOKEN(PRINT, "PRINT"); }
"Integer.parseInt"          { SIMPLE_TOKEN(PARSEINT, "PARSEINT"); }
"public"                    { SIMPLE_TOKEN(PUBLIC, "PUBLIC"); }
"return"                    { SIMPLE_TOKEN(RETURN, "RETURN"); }
"static"                    { SIMPLE_TOKEN(STATIC, "STATIC"); }
"String"                    { SIMPLE_TOKEN(STRING, "STRING"); }
"void"                      { SIMPLE_TOKEN(VOID, "VOID"); }
"while"                     { SIMPLE_TOKEN(WHILE, "WHILE"); }

{reserved}                  { VALUE_TOKEN(RESERVED, "RESERVED"); }

{letter}({number}|{letter})* { VALUE_TOKEN(IDENTIFIER, "IDENTIFIER"); }

0|[1-9]("_"+[0-9]|[0-9])*   { VALUE_TOKEN(NATURAL, "NATURAL"); }

({intpart}?\.{intpart}|{intpart}\.{intpart}?|{intpart}\.{intpart}?[eE][-+]?{intpart}|{intpart}?\.{intpart}[eE][-+]?{intpart}|{intpart}[eE][-+]?{intpart}) {
    VALUE_TOKEN(DECIMAL, "DECIMAL");
}

\" {
    token_line = line;
    token_column = column;
    yylloc.first_line = line;
    yylloc.first_column = column;
    yylloc.last_line = line;
    yylloc.last_column = column;

    str_line = line;
    str_column = column;
    column += yyleng;
    str_error = 0;
    str_buffer[0] = '\0';
    strcat(str_buffer, yytext);
    BEGIN STRING_STATE;
}

<STRING_STATE>\\[fnrt\\\"]|[^\r\n"] {
    column += yyleng;
    strcat(str_buffer, yytext);
}

<STRING_STATE>\\(\n|\r|\r\n) {
    printf("Line %d, col %d: invalid escape sequence (\\)\n", line, column);
    lexical_errors++;
    printf("Line %d, col %d: unterminated string literal\n", str_line, str_column);
    lexical_errors++;
    line++;
    column = 1;
    BEGIN INITIAL;
}

<STRING_STATE>\\. {
    printf("Line %d, col %d: invalid escape sequence (%s)\n", line, column, yytext);
    lexical_errors++;
    column += yyleng;
    str_error = 1;
}

<STRING_STATE>(\n|\r|\r\n) {
    printf("Line %d, col %d: unterminated string literal\n", str_line, str_column);
    lexical_errors++;
    line++;
    column = 1;
    BEGIN INITIAL;
}

<STRING_STATE><<EOF>> {
    printf("Line %d, col %d: unterminated string literal\n", str_line, str_column);
    lexical_errors++;
    token_text[0] = '\0';
    BEGIN INITIAL;
    return 1;
}

<STRING_STATE>\" {
    column += yyleng;
    strcat(str_buffer, yytext);

    if (!str_error && print_tokens)
        printf("STRLIT(%s)\n", str_buffer);

    if (!str_error && (parse_mode || print_tree || semantic_mode || semantic_errors_only)) {
        yylval.lexeme = strdup(str_buffer);

        token_line = str_line;
        token_column = str_column;
        yylloc.first_line = str_line;
        yylloc.first_column = str_column;
        yylloc.last_line = line;
        yylloc.last_column = column - 1;

        strncpy(token_text, str_buffer, sizeof(token_text) - 1);
        token_text[sizeof(token_text) - 1] = '\0';

        BEGIN INITIAL;
        return STRLIT;
    }

    str_error = 0;
    BEGIN INITIAL;
}

"/*" {
    comment_line = line;
    comment_column = column;
    column += yyleng;
    BEGIN BLOCK_COMMENT;
}

<BLOCK_COMMENT><<EOF>> {
    printf("Line %d, col %d: unterminated comment\n", comment_line, comment_column);
    lexical_errors++;
    token_text[0] = '\0';
    BEGIN INITIAL;
    break;
}

<BLOCK_COMMENT>"*/"         { column += yyleng; BEGIN INITIAL; }
<BLOCK_COMMENT>(\n|\r|\r\n) { column = 1; line++; }
<BLOCK_COMMENT>.            { column += yyleng; }

"//"                        { column += yyleng; BEGIN LINE_COMMENT; }
<LINE_COMMENT>(\n|\r|\r\n)  { column = 1; line++; BEGIN INITIAL; }
<LINE_COMMENT>.             { column += yyleng; }

\n|\r|\r\n                  { column = 1; line++; }
(\t|" "|\f)                 { column += yyleng; }

. {
    printf("Line %d, col %d: illegal character (%s)\n", line, column, yytext);
    lexical_errors++;
    column += yyleng;
}

%%

int main(int argc, char **argv) {
    int codegen_mode = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            lexical_only = 1;
            print_tokens = 1;
        } else if (strcmp(argv[i], "-e1") == 0) {
            lexical_only = 1;
        } else if (strcmp(argv[i], "-t") == 0) {
            print_tree = 1;
            parse_mode = 1;
        } else if (strcmp(argv[i], "-e2") == 0) {
            parse_mode = 1;
        } else if (strcmp(argv[i], "-s") == 0) {
            semantic_mode = 1;
            parse_mode = 1;
        } else if (strcmp(argv[i], "-e3") == 0) {
            semantic_errors_only = 1;
            parse_mode = 1;
        }
    }

    if (lexical_only) {
        yylex();
        return 0;
    }

    if (argc == 1) {
        codegen_mode = 1;
        parse_mode = 1;
    }

    yyparse();

    if (!syntax_errors && ast) {
        if (semantic_mode) {
            check_program(ast);
            show_symbol_tables();
            printf("\n");
            print_ast(ast, 0);
        } else if (semantic_errors_only) {
            if (!lexical_errors)
                check_program(ast);
        } else if (print_tree) {
            print_ast(ast, 0);
        } else if (codegen_mode) {
            if (!lexical_errors && check_program(ast) == 0)
                codegen_program(ast);
        }
    }

    return 0;
}

int yywrap(void) {
    token_line = line;
    token_column = column;
    token_text[0] = '\0';
    return 1;
}
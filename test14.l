%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"

extern YYSTYPE yylval;

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
    if(!str_error && print_tokens) {
        str_buffer[str_index++] = '"';
        str_buffer[str_index] = '\0';
        printf("STRLIT(%s)\n", str_buffer);
    }
    column += yyleng;
    BEGIN(INITIAL);
    return STRLIT;
}

<STRING_STATE><<EOF>> {
    printf("Line %d, col %d: unterminated string literal\n",
           str_start_line, str_start_column);
    BEGIN(INITIAL);
    return 0;
}

"true"  { if(print_tokens) printf("BOOLLIT(true)\n"); column += yyleng; return BOOLLIT; }
"false" { if(print_tokens) printf("BOOLLIT(false)\n"); column += yyleng; return BOOLLIT; }

({nat}"."{frac}?{exp}?|"."{frac}{exp}?|{nat}{exp}) {
    if(print_tokens) printf("DECIMAL(%s)\n", yytext);
    column += yyleng;
    return DECIMAL;
}

{nonzero}(_*{digit})* {
    if(print_tokens) printf("NATURAL(%s)\n", yytext);
    column += yyleng;
    return NATURAL;
}

"0" {
    if(print_tokens) printf("NATURAL(0)\n");
    column += yyleng;
    return NATURAL;
}

"++" { if(print_tokens) printf("RESERVED(++)\n"); column += yyleng; return INC; }
"--" { if(print_tokens) printf("RESERVED(--)\n"); column += yyleng; return DEC; }

"System.out.print" { TOKEN("PRINT"); column += yyleng; return PRINT; }
"Integer.parseInt" { TOKEN("PARSEINT"); column += yyleng; return PARSEINT; }
".length"          { TOKEN("DOTLENGTH"); column += yyleng; return DOTLENGTH; }

"==" { TOKEN("EQ"); column += yyleng; return EQ; }
"!=" { TOKEN("NE"); column += yyleng; return NE; }
">=" { TOKEN("GE"); column += yyleng; return GE; }
"<=" { TOKEN("LE"); column += yyleng; return LE; }
"&&" { TOKEN("AND"); column += yyleng; return AND; }
"||" { TOKEN("OR"); column += yyleng; return OR; }
"^"  { TOKEN("XOR"); column += yyleng; return XOR; }
"->" { TOKEN("ARROW"); column += yyleng; return ARROW; }

"="  { TOKEN("ASSIGN"); column += yyleng; return ASSIGN; }
">>" { TOKEN("RSHIFT"); column += yyleng; return RSHIFT; }
"<<" { TOKEN("LSHIFT"); column += yyleng; return LSHIFT; }
">"  { TOKEN("GT"); column += yyleng; return GT; }
"<"  { TOKEN("LT"); column += yyleng; return LT; }

"+"  { TOKEN("PLUS"); column += yyleng; return PLUS; }
"-"  { TOKEN("MINUS"); column += yyleng; return MINUS; }

"*"  { TOKEN("STAR"); column += yyleng; return STAR; }
"/"  { TOKEN("DIV"); column += yyleng; return DIV; }
"%"  { TOKEN("MOD"); column += yyleng; return MOD; }

"!"  { TOKEN("NOT"); column += yyleng; return NOT; }

"{"  { TOKEN("LBRACE"); column += yyleng; return LBRACE; }
"}"  { TOKEN("RBRACE"); column += yyleng; return RBRACE; }
"("  { TOKEN("LPAR"); column += yyleng; return LPAR; }
")"  { TOKEN("RPAR"); column += yyleng; return RPAR; }
"["  { TOKEN("LSQ"); column += yyleng; return LSQ; }
"]"  { TOKEN("RSQ"); column += yyleng; return RSQ; }
";"  { TOKEN("SEMICOLON"); column += yyleng; return SEMICOLON; }
","  { TOKEN("COMMA"); column += yyleng; return COMMA; }

"class"   { if(print_tokens) printf("CLASS\n"); column += yyleng; return CLASS; }
"public"  { if(print_tokens) printf("PUBLIC\n"); column += yyleng; return PUBLIC; }
"static"  { if(print_tokens) printf("STATIC\n"); column += yyleng; return STATIC; }
"int"     { if(print_tokens) printf("INT\n"); column += yyleng; return INT; }
"double"  { if(print_tokens) printf("DOUBLE\n"); column += yyleng; return DOUBLE; }
"boolean" { if(print_tokens) printf("BOOL\n"); column += yyleng; return BOOL; }
"void"    { if(print_tokens) printf("VOID\n"); column += yyleng; return VOID; }
"if"      { if(print_tokens) printf("IF\n"); column += yyleng; return IF; }
"else"    { if(print_tokens) printf("ELSE\n"); column += yyleng; return ELSE; }
"while"   { if(print_tokens) printf("WHILE\n"); column += yyleng; return WHILE; }
"return"  { if(print_tokens) printf("RETURN\n"); column += yyleng; return RETURN; }
"String"  { if(print_tokens) printf("STRING\n"); column += yyleng; return STRING; }

"abstract"|"assert"|"break"|"byte"|"case"|"catch"|"char"|"const"|"continue"|"default"|"do"|"enum"|"extends"|"final"|"finally"|"float"|"for"|"goto"|"implements"|"import"|"instanceof"|"interface"|"long"|"native"|"new"|"package"|"private"|"protected"|"short"|"strictfp"|"super"|"switch"|"synchronized"|"this"|"throw"|"throws"|"transient"|"try"|"volatile"|"null"|"Integer"|"System" {
    if(print_tokens) printf("RESERVED(%s)\n", yytext);
    column += yyleng;
}

{letter}{alnum}* {
    if(print_tokens) printf("IDENTIFIER(%s)\n", yytext);
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
    if(YY_START == COMMENT) {
        printf("Line %d, col %d: unterminated comment\n",
               comment_start_line, comment_start_column);
    }
    return 1;
}
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex();
extern int line;
extern int column;
extern int print_tokens;
extern char *yytext;



struct node *ast = NULL;

int print_tree = 0;
int only_errors = 0;
int syntax_errors = 0;

void yyerror(char *s) {
    syntax_errors = 1;
    if (!only_errors)
        printf("Line %d, col %d: syntax error: %s\n", line, column, yytext);
}
%}

%union {
    char *lexeme;
    struct node *node;
}

/* TOKENS COM VALOR */
%token <lexeme> IDENTIFIER NATURAL DECIMAL STRLIT
%token BOOLLIT

/* TOKENS SEM VALOR */
%token CLASS PUBLIC STATIC
%token BOOL INT DOUBLE VOID STRING
%token IF ELSE WHILE RETURN
%token PRINT PARSEINT DOTLENGTH
%token INC
%token DEC
%token ARROW

%token ASSIGN
%token PLUS MINUS STAR DIV MOD
%token AND OR XOR LSHIFT RSHIFT
%token EQ NE LT GT LE GE
%token NOT
%token LPAR RPAR LBRACE RBRACE LSQ RSQ
%token SEMICOLON COMMA

/* PRECEDÊNCIA */
%left OR
%left AND
%left XOR
%left EQ NE
%left LT GT LE GE
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR DIV MOD
%right NOT
%right UMINUS

%type <node> program class_body member
%type <node> field_decl
%type <node> method_decl method_header method_body
%type <node> formal_params param_list param_decl
%type <node> stmt stmt_list
%type <node> expr
%type <node> type

%%

program:
    CLASS IDENTIFIER LBRACE class_body RBRACE
    {
        $$ = newnode(Program, NULL);
        addchild($$, newnode(Identifier, $2));
        addchild($$, $4);
        ast = $$;
    }
;

class_body:
    /* vazio */
    { $$ = newnode(MethodBody, NULL); }
|   class_body member
    { addchild($1, $2); $$ = $1; }
;

member:
    field_decl
|   method_decl
|   SEMICOLON
    { $$ = newnode(MethodBody, NULL); }
;

field_decl:
    PUBLIC STATIC type IDENTIFIER SEMICOLON
    {
        $$ = newnode(FieldDecl, NULL);
        addchild($$, $3);
        addchild($$, newnode(Identifier, $4));
    }
;

method_decl:
    PUBLIC STATIC method_header method_body
    {
        $$ = newnode(MethodDecl, NULL);
        addchild($$, $3);
        addchild($$, $4);
    }
;

method_header:
    type IDENTIFIER LPAR formal_params RPAR
    {
        $$ = newnode(MethodHeader, NULL);
        addchild($$, $1);
        addchild($$, newnode(Identifier, $2));
        addchild($$, $4);
    }
|   VOID IDENTIFIER LPAR formal_params RPAR
    {
        $$ = newnode(MethodHeader, NULL);
        addchild($$, newnode(Void, NULL));
        addchild($$, newnode(Identifier, $2));
        addchild($$, $4);
    }
;

formal_params:
    /* vazio */
    { $$ = newnode(MethodParams, NULL); }
|   param_list
;

param_list:
    param_decl
    {
        $$ = newnode(MethodParams, NULL);
        addchild($$, $1);
    }
|   param_list COMMA param_decl
    {
        addchild($1, $3);
        $$ = $1;
    }
;

param_decl:
    type IDENTIFIER
    {
        $$ = newnode(ParamDecl, NULL);
        addchild($$, $1);
        addchild($$, newnode(Identifier, $2));
    }
;

method_body:
    LBRACE stmt_list RBRACE
    {
        $$ = newnode(MethodBody, NULL);
        addchild($$, $2);
    }
;

stmt_list:
    /* vazio */
    { $$ = newnode(Block, NULL); }
|   stmt_list stmt
    { addchild($1, $2); $$ = $1; }
;

stmt:
    LBRACE stmt_list RBRACE
    {
        $$ = newnode(Block, NULL);
        addchild($$, $2);
    }
|   IF LPAR expr RPAR stmt
    {
        $$ = newnode(If, NULL);
        addchild($$, $3);
        addchild($$, $5);
    }
|   IF LPAR expr RPAR stmt ELSE stmt
    {
        $$ = newnode(If, NULL);
        addchild($$, $3);
        addchild($$, $5);
        addchild($$, $7);
    }
|   WHILE LPAR expr RPAR stmt
    {
        $$ = newnode(While, NULL);
        addchild($$, $3);
        addchild($$, $5);
    }
|   RETURN expr SEMICOLON
    {
        $$ = newnode(Return, NULL);
        addchild($$, $2);
    }
|   RETURN SEMICOLON
    { $$ = newnode(Return, NULL); }
|   expr SEMICOLON
    { $$ = $1; }
;

expr:
    IDENTIFIER
        { $$ = newnode(Identifier, $1); }
|   NATURAL
        { $$ = newnode(Natural, $1); }
|   DECIMAL
        { $$ = newnode(Decimal, $1); }
|   STRLIT
        { $$ = newnode(StrLit, $1); }
|   BOOLLIT
        { $$ = newnode(BoolLit, NULL); }
|   expr PLUS expr
        { $$ = newnode(Add, NULL); addchild($$, $1); addchild($$, $3); }
|   expr MINUS expr
        { $$ = newnode(Sub, NULL); addchild($$, $1); addchild($$, $3); }
|   expr STAR expr
        { $$ = newnode(Mul, NULL); addchild($$, $1); addchild($$, $3); }
|   expr DIV expr
        { $$ = newnode(Div, NULL); addchild($$, $1); addchild($$, $3); }
|   expr MOD expr
        { $$ = newnode(Mod, NULL); addchild($$, $1); addchild($$, $3); }
|   expr AND expr
        { $$ = newnode(And, NULL); addchild($$, $1); addchild($$, $3); }
|   expr OR expr
        { $$ = newnode(Or, NULL); addchild($$, $1); addchild($$, $3); }
|   expr EQ expr
        { $$ = newnode(Eq, NULL); addchild($$, $1); addchild($$, $3); }
|   expr NE expr
        { $$ = newnode(Ne, NULL); addchild($$, $1); addchild($$, $3); }
|   expr LT expr
        { $$ = newnode(Lt, NULL); addchild($$, $1); addchild($$, $3); }
|   expr GT expr
        { $$ = newnode(Gt, NULL); addchild($$, $1); addchild($$, $3); }
|   NOT expr
        { $$ = newnode(Not, NULL); addchild($$, $2); }
|   MINUS expr %prec UMINUS
        { $$ = newnode(Minus, NULL); addchild($$, $2); }
|   LPAR expr RPAR
        { $$ = $2; }
;

type:
    INT     { $$ = newnode(Int, NULL); }
|   DOUBLE  { $$ = newnode(Double, NULL); }
|   BOOL    { $$ = newnode(Bool, NULL); }
|   STRING LSQ RSQ
        { $$ = newnode(StringArray, NULL); }
;

%%

int main(int argc, char **argv) {

    int lex_only = 0;

    if (argc > 1) {

        if (strcmp(argv[1], "-l") == 0) {
            lex_only = 1;
            print_tokens = 1;   // 🔥 ATIVAR PRINT DO LEXER
        }

        if (strcmp(argv[1], "-t") == 0) {
            print_tree = 1;
        }

        if (strcmp(argv[1], "-e2") == 0) {
            only_errors = 1;
        }
    }

    if (lex_only) {
        while (yylex());
        return 0;
    }

    yyparse();

    if (!syntax_errors && print_tree && ast)
        print_ast(ast, 0);

    if (ast)
        free_ast(ast);

    return 0;
}
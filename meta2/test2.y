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

static int child_count(struct node *node) {
    int count = 0;
    struct node_list *child;

    if (!node || !node->children)
        return 0;

    child = node->children->next;
    while (child) {
        count++;
        child = child->next;
    }
    return count;
}

static struct node *first_child(struct node *node) {
    if (!node || !node->children || !node->children->next)
        return NULL;
    return node->children->next->node;
}

static void append_children(struct node *parent, struct node *holder) {
    struct node_list *tail;

    if (!parent || !holder || !holder->children)
        return;

    tail = parent->children;
    while (tail->next)
        tail = tail->next;

    tail->next = holder->children->next;
    holder->children->next = NULL;
}

static void free_holder(struct node *node) {
    if (!node)
        return;
    if (node->children)
        free(node->children);
    free(node);
}

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

%token <lexeme> IDENTIFIER NATURAL DECIMAL STRLIT
%token BOOLLIT

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

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%right ASSIGN
%left OR
%left AND
%left XOR
%left EQ NE
%left LT GT LE GE
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR DIV MOD
%right NOT
%right UMINUS UPLUS

%type <node> program class_body member
%type <node> field_decl var_decl
%type <node> method_decl method_header method_body method_body_items method_body_item
%type <node> formal_params param_list param_decl
%type <node> stmt stmt_list stmt_item
%type <node> expr type
%type <node> method_invocation parse_args args_opt arg_list

%%

program:
    CLASS IDENTIFIER LBRACE class_body RBRACE
    {
        ast = newnode(Program, NULL);
        addchild(ast, newnode(Identifier, $2));
        append_children(ast, $4);
        free_holder($4);
        $$ = ast;
    }
;

class_body:
    {
        $$ = newnode(Program, NULL);
    }
|   class_body member
    {
        if ($2)
            addchild($1, $2);
        $$ = $1;
    }
;

member:
    field_decl
|   method_decl
|   SEMICOLON
    {
        $$ = NULL;
    }
;

field_decl:
    type IDENTIFIER SEMICOLON
    {
        $$ = newnode(FieldDecl, NULL);
        addchild($$, $1);
        addchild($$, newnode(Identifier, $2));
    }
|   PUBLIC STATIC type IDENTIFIER SEMICOLON
    {
        $$ = newnode(FieldDecl, NULL);
        addchild($$, $3);
        addchild($$, newnode(Identifier, $4));
    }
;

var_decl:
    type IDENTIFIER SEMICOLON
    {
        $$ = newnode(VarDecl, NULL);
        addchild($$, $1);
        addchild($$, newnode(Identifier, $2));
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
    {
        $$ = newnode(MethodParams, NULL);
    }
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
    LBRACE method_body_items RBRACE
    {
        $$ = newnode(MethodBody, NULL);
        append_children($$, $2);
        free_holder($2);
    }
;

method_body_items:
    {
        $$ = newnode(MethodBody, NULL);
    }
|   method_body_items method_body_item
    {
        if ($2)
            addchild($1, $2);
        $$ = $1;
    }
;

method_body_item:
    var_decl
|   stmt
;

stmt:
    LBRACE stmt_list RBRACE
    {
        int n = child_count($2);
        if (n == 0) {
            $$ = newnode(Block, NULL);
        } else if (n == 1) {
            $$ = first_child($2);
        } else {
            $$ = newnode(Block, NULL);
            append_children($$, $2);
        }
        free_holder($2);
    }
|   IF LPAR expr RPAR stmt %prec LOWER_THAN_ELSE
    {
        $$ = newnode(If, NULL);
        addchild($$, $3);
        addchild($$, $5);
        addchild($$, newnode(Block, NULL));
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
    {
        $$ = newnode(Return, NULL);
    }
|   PRINT LPAR expr RPAR SEMICOLON
    {
        $$ = newnode(Print, NULL);
        addchild($$, $3);
    }
|   IDENTIFIER ASSIGN expr SEMICOLON
    {
        $$ = newnode(Assign, NULL);
        addchild($$, newnode(Identifier, $1));
        addchild($$, $3);
    }
|   expr SEMICOLON
    {
        $$ = $1;
    }
|   SEMICOLON
    {
        $$ = newnode(Block, NULL);
    }
;

stmt_list:
    {
        $$ = newnode(Block, NULL);
    }
|   stmt_list stmt_item
    {
        if ($2)
            addchild($1, $2);
        $$ = $1;
    }
;

stmt_item:
    stmt
|   var_decl
;

expr:
    IDENTIFIER
    {
        $$ = newnode(Identifier, $1);
    }
|   NATURAL
    {
        $$ = newnode(Natural, $1);
    }
|   DECIMAL
    {
        $$ = newnode(Decimal, $1);
    }
|   STRLIT
    {
        $$ = newnode(StrLit, $1);
    }
|   BOOLLIT
    {
        $$ = newnode(BoolLit, NULL);
    }
|   method_invocation
|   parse_args
|   expr PLUS expr
    {
        $$ = newnode(Add, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr MINUS expr
    {
        $$ = newnode(Sub, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr STAR expr
    {
        $$ = newnode(Mul, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr DIV expr
    {
        $$ = newnode(Div, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr MOD expr
    {
        $$ = newnode(Mod, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr AND expr
    {
        $$ = newnode(And, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr OR expr
    {
        $$ = newnode(Or, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr XOR expr
    {
        $$ = newnode(Xor, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr EQ expr
    {
        $$ = newnode(Eq, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr NE expr
    {
        $$ = newnode(Ne, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr LT expr
    {
        $$ = newnode(Lt, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr GT expr
    {
        $$ = newnode(Gt, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr LE expr
    {
        $$ = newnode(Le, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr GE expr
    {
        $$ = newnode(Ge, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr LSHIFT expr
    {
        $$ = newnode(Lshift, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   expr RSHIFT expr
    {
        $$ = newnode(Rshift, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   NOT expr
    {
        $$ = newnode(Not, NULL);
        addchild($$, $2);
    }
|   MINUS expr %prec UMINUS
    {
        $$ = newnode(Minus, NULL);
        addchild($$, $2);
    }
|   PLUS expr %prec UPLUS
    {
        $$ = newnode(Plus, NULL);
        addchild($$, $2);
    }
|   expr DOTLENGTH
    {
        $$ = newnode(Length, NULL);
        addchild($$, $1);
    }
|   LPAR expr RPAR
    {
        $$ = $2;
    }
;

method_invocation:
    IDENTIFIER LPAR args_opt RPAR
    {
        $$ = newnode(Call, NULL);
        addchild($$, newnode(Identifier, $1));
        append_children($$, $3);
        free_holder($3);
    }
;

args_opt:
    {
        $$ = newnode(MethodBody, NULL);
    }
|   arg_list
;

arg_list:
    expr
    {
        $$ = newnode(MethodBody, NULL);
        addchild($$, $1);
    }
|   arg_list COMMA expr
    {
        addchild($1, $3);
        $$ = $1;
    }
;

parse_args:
    PARSEINT LPAR IDENTIFIER LSQ expr RSQ RPAR
    {
        $$ = newnode(ParseArgs, NULL);
        addchild($$, newnode(Identifier, $3));
        addchild($$, $5);
    }
;

type:
    INT
    {
        $$ = newnode(Int, NULL);
    }
|   DOUBLE
    {
        $$ = newnode(Double, NULL);
    }
|   BOOL
    {
        $$ = newnode(Bool, NULL);
    }
|   STRING LSQ RSQ
    {
        $$ = newnode(StringArray, NULL);
    }
;

%%

int main(int argc, char **argv) {
    int lex_only = 0;

    if (argc > 1) {
        if (strcmp(argv[1], "-l") == 0) {
            lex_only = 1;
            print_tokens = 1;
        }

        if (strcmp(argv[1], "-e1") == 0) {
            lex_only = 1;
        }

        if (strcmp(argv[1], "-t") == 0) {
            print_tree = 1;
        }

        if (strcmp(argv[1], "-e2") == 0) {
            only_errors = 1;
        }
    }

    if (lex_only) {
        while (yylex())
            ;
        return 0;
    }

    yyparse();

    if (!syntax_errors && print_tree && ast)
        print_ast(ast, 0);

    if (ast)
        free_ast(ast);

    return 0;
}
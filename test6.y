%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex();
extern int line;
extern int column;
extern int token_line;
extern int token_column;
extern int print_tokens;
extern char *yytext;
extern char token_text[];
extern int last_lex_error_line;
extern int yychar;

struct node *ast = NULL;

int print_tree = 0;
int only_errors = 0;
int syntax_errors = 0;
int syntax_error_count = 0;

static struct node *clone_type_node(struct node *node) {
    if (!node)
        return NULL;
    return newnode(node->category, node->token);
}

static struct node *make_holder() {
    return newnode(Program, NULL);
}

static void append_holder(struct node *dst, struct node *src) {
    struct node_list *child;
    if (!dst || !src || !src->children)
        return;
    child = src->children->next;
    while (child) {
        addchild(dst, child->node);
        child = child->next;
    }
    src->children->next = NULL;
}

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

static int is_empty_block(struct node *node) {
    return node && node->category == Block && child_count(node) == 0;
}

static int meaningful_child_count(struct node *holder) {
    int count = 0;
    struct node_list *child;

    if (!holder || !holder->children)
        return 0;

    child = holder->children->next;
    while (child) {
        if (!is_empty_block(child->node))
            count++;
        child = child->next;
    }
    return count;
}

static struct node *first_meaningful_child(struct node *holder) {
    struct node_list *child;

    if (!holder || !holder->children)
        return NULL;

    child = holder->children->next;
    while (child) {
        if (!is_empty_block(child->node))
            return child->node;
        child = child->next;
    }
    return NULL;
}

static void append_meaningful_children(struct node *dst, struct node *src) {
    struct node_list *child;

    if (!dst || !src || !src->children)
        return;

    child = src->children->next;
    while (child) {
        if (!is_empty_block(child->node))
            addchild(dst, child->node);
        child = child->next;
    }
}

static void free_holder_only(struct node *node) {
    if (!node)
        return;
    if (node->children)
        free(node->children);
    free(node);
}

static struct node *build_block_from_holder(struct node *holder) {
    int meaningful = meaningful_child_count(holder);
    struct node *result;

    if (meaningful == 0) {
        result = newnode(Block, NULL);
        free_holder_only(holder);
        return result;
    }

    if (meaningful == 1) {
        result = first_meaningful_child(holder);
        holder->children->next = NULL;
        free_holder_only(holder);
        return result;
    }

    result = newnode(Block, NULL);
    append_meaningful_children(result, holder);
    free_holder_only(holder);
    return result;
}

void yyerror(char *s) {
    syntax_errors = 1;

    if (only_errors)
        return;

    if (token_line == last_lex_error_line)
        return;

    if (yychar == 0 && syntax_error_count > 0)
        return;

    printf("Line %d, col %d: syntax error: %s\n", token_line, token_column, token_text);
    syntax_error_count++;
}
%}

%union {
    char *lexeme;
    struct node *node;
}

%token <lexeme> IDENTIFIER NATURAL DECIMAL STRLIT BOOLLIT

%token CLASS PUBLIC STATIC RESERVED
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

%type <node> program class_body
%type <node> field_decl field_ids
%type <node> method_decl method_header method_body method_body_items
%type <node> formal_params param_list param_decl
%type <node> stmt stmt_list
%type <node> expr assign_expr or_expr and_expr xor_expr eq_expr rel_expr shift_expr add_expr mul_expr unary_expr primary_expr
%type <node> expr_list args_opt
%type <node> type
%type <node> var_decl var_ids
%type <node> method_invocation parse_args

%%

program:
    CLASS IDENTIFIER LBRACE class_body RBRACE
    {
        $$ = newnode(Program, NULL);
        addchild($$, newnode(Identifier, $2));
        append_holder($$, $4);
        free_holder_only($4);
        ast = $$;
    }
;

class_body:
    {
        $$ = make_holder();
    }
|   class_body field_decl
    {
        append_holder($1, $2);
        free_holder_only($2);
        $$ = $1;
    }
|   class_body method_decl
    {
        addchild($1, $2);
        $$ = $1;
    }
|   class_body SEMICOLON
    {
        $$ = $1;
    }
|   class_body error SEMICOLON
    {
        yyerrok;
        $$ = $1;
    }
;

field_decl:
    PUBLIC STATIC type field_ids SEMICOLON
    {
        struct node_list *child;
        $$ = make_holder();
        child = $4->children->next;
        while (child) {
            struct node *decl = newnode(FieldDecl, NULL);
            addchild(decl, clone_type_node($3));
            addchild(decl, newnode(Identifier, child->node->token));
            addchild($$, decl);
            child = child->next;
        }
        free_ast($3);
        free_ast($4);
    }
;

field_ids:
    IDENTIFIER
    {
        $$ = make_holder();
        addchild($$, newnode(Identifier, $1));
    }
|   field_ids COMMA IDENTIFIER
    {
        addchild($1, newnode(Identifier, $3));
        $$ = $1;
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
|   STRING LSQ RSQ IDENTIFIER
    {
        $$ = newnode(ParamDecl, NULL);
        addchild($$, newnode(StringArray, NULL));
        addchild($$, newnode(Identifier, $4));
    }
;

method_body:
    LBRACE method_body_items RBRACE
    {
        $$ = newnode(MethodBody, NULL);
        append_holder($$, $2);
        free_holder_only($2);
    }
|   LBRACE method_body_items error RBRACE
    {
        yyerrok;
        $$ = newnode(MethodBody, NULL);
        append_holder($$, $2);
        free_holder_only($2);
    }
|   LBRACE error RBRACE
    {
        yyerrok;
        $$ = newnode(MethodBody, NULL);
    }
;

method_body_items:
    {
        $$ = make_holder();
    }
|   method_body_items var_decl
    {
        append_holder($1, $2);
        free_holder_only($2);
        $$ = $1;
    }
|   method_body_items stmt
    {
        if (!is_empty_block($2))
            addchild($1, $2);
        $$ = $1;
    }
;

var_decl:
    type var_ids SEMICOLON
    {
        struct node_list *child;
        $$ = make_holder();
        child = $2->children->next;
        while (child) {
            struct node *decl = newnode(VarDecl, NULL);
            addchild(decl, clone_type_node($1));
            addchild(decl, newnode(Identifier, child->node->token));
            addchild($$, decl);
            child = child->next;
        }
        free_ast($1);
        free_ast($2);
    }
;

var_ids:
    IDENTIFIER
    {
        $$ = make_holder();
        addchild($$, newnode(Identifier, $1));
    }
|   var_ids COMMA IDENTIFIER
    {
        addchild($1, newnode(Identifier, $3));
        $$ = $1;
    }
;

stmt:
    LBRACE stmt_list RBRACE
    {
        $$ = build_block_from_holder($2);
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
|   IF LPAR expr error stmt %prec LOWER_THAN_ELSE
    {
        yyerrok;
        $$ = newnode(If, NULL);
        addchild($$, $3);
        addchild($$, $5);
        addchild($$, newnode(Block, NULL));
    }
|   IF LPAR expr error stmt ELSE stmt
    {
        yyerrok;
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
|   IDENTIFIER ASSIGN expr SEMICOLON
    {
        $$ = newnode(Assign, NULL);
        addchild($$, newnode(Identifier, $1));
        addchild($$, $3);
    }
|   PRINT LPAR expr RPAR SEMICOLON
    {
        $$ = newnode(Print, NULL);
        addchild($$, $3);
    }
|   PRINT LPAR STRLIT RPAR SEMICOLON
    {
        $$ = newnode(Print, NULL);
        addchild($$, newnode(StrLit, $3));
    }
|   method_invocation SEMICOLON
    {
        $$ = $1;
    }
|   parse_args SEMICOLON
    {
        $$ = $1;
    }
|   SEMICOLON
    {
        $$ = newnode(Block, NULL);
    }
|   error SEMICOLON
    {
        yyerrok;
        $$ = newnode(Block, NULL);
    }
;

stmt_list:
    {
        $$ = make_holder();
    }
|   stmt_list stmt
    {
        if (!is_empty_block($2))
            addchild($1, $2);
        $$ = $1;
    }
;

expr:
    assign_expr
;

assign_expr:
    IDENTIFIER ASSIGN assign_expr
    {
        $$ = newnode(Assign, NULL);
        addchild($$, newnode(Identifier, $1));
        addchild($$, $3);
    }
|   or_expr
;

or_expr:
    or_expr OR and_expr
    {
        $$ = newnode(Or, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   and_expr
;

and_expr:
    and_expr AND xor_expr
    {
        $$ = newnode(And, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   xor_expr
;

xor_expr:
    xor_expr XOR eq_expr
    {
        $$ = newnode(Xor, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   eq_expr
;

eq_expr:
    eq_expr EQ rel_expr
    {
        $$ = newnode(Eq, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   eq_expr NE rel_expr
    {
        $$ = newnode(Ne, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   rel_expr
;

rel_expr:
    rel_expr LT shift_expr
    {
        $$ = newnode(Lt, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   rel_expr GT shift_expr
    {
        $$ = newnode(Gt, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   rel_expr LE shift_expr
    {
        $$ = newnode(Le, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   rel_expr GE shift_expr
    {
        $$ = newnode(Ge, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   shift_expr
;

shift_expr:
    shift_expr LSHIFT add_expr
    {
        $$ = newnode(Lshift, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   shift_expr RSHIFT add_expr
    {
        $$ = newnode(Rshift, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   add_expr
;

add_expr:
    add_expr PLUS mul_expr
    {
        $$ = newnode(Add, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   add_expr MINUS mul_expr
    {
        $$ = newnode(Sub, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   mul_expr
;

mul_expr:
    mul_expr STAR unary_expr
    {
        $$ = newnode(Mul, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   mul_expr DIV unary_expr
    {
        $$ = newnode(Div, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   mul_expr MOD unary_expr
    {
        $$ = newnode(Mod, NULL);
        addchild($$, $1);
        addchild($$, $3);
    }
|   unary_expr
;

unary_expr:
    NOT unary_expr
    {
        $$ = newnode(Not, NULL);
        addchild($$, $2);
    }
|   MINUS unary_expr
    {
        $$ = newnode(Minus, NULL);
        addchild($$, $2);
    }
|   PLUS unary_expr
    {
        $$ = newnode(Plus, NULL);
        addchild($$, $2);
    }
|   primary_expr
;

primary_expr:
    IDENTIFIER
    {
        $$ = newnode(Identifier, $1);
    }
|   IDENTIFIER DOTLENGTH
    {
        $$ = newnode(Length, NULL);
        addchild($$, newnode(Identifier, $1));
    }
|   NATURAL
    {
        $$ = newnode(Natural, $1);
    }
|   DECIMAL
    {
        $$ = newnode(Decimal, $1);
    }
|   BOOLLIT
    {
        $$ = newnode(BoolLit, $1);
    }
|   method_invocation
|   parse_args
|   LPAR expr RPAR
    {
        $$ = $2;
    }
|   LPAR error RPAR
    {
        yyerrok;
        $$ = NULL;
    }
;

method_invocation:
    IDENTIFIER LPAR args_opt RPAR
    {
        $$ = newnode(Call, NULL);
        addchild($$, newnode(Identifier, $1));
        append_holder($$, $3);
        free_holder_only($3);
    }
|   IDENTIFIER LPAR error RPAR
    {
        yyerrok;
        $$ = newnode(Call, NULL);
        addchild($$, newnode(Identifier, $1));
    }
;

args_opt:
    {
        $$ = make_holder();
    }
|   expr_list
;

expr_list:
    expr
    {
        $$ = make_holder();
        addchild($$, $1);
    }
|   expr_list COMMA expr
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
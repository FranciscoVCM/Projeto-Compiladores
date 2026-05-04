%{
#include <stdio.h>
#include "ast.h"

extern int yylex(void);
extern int line;
extern int token_column;
extern int syntax_errors;
extern char token_text[];

void yyerror(char *s);

struct node *ast = NULL;

static struct node *make_node(enum category category, char *token, int line, int column) {
    struct node *n = newnode(category, token);
    set_node_location(n, line, column);
    return n;
}

static void append_list(struct node *dst, struct node *list) {
    struct node_list *child;
    if (!dst || !list || !list->children) return;

    child = list->children->next;
    while (child) {
        addchild(dst, child->node);
        child = child->next;
    }
}

static int is_empty_statement(struct node *n) {
    return n && (n->category == Empty ||
                (n->category == Block && n->children->next == NULL));
}

static struct node *compact_block(struct node *list) {
    int count = 0;
    struct node *only = NULL;
    struct node_list *child;
    struct node *block;

    child = list->children->next;
    while (child) {
        if (!is_empty_statement(child->node)) {
            count++;
            only = child->node;
        }
        child = child->next;
    }

    if (count == 0) {
        block = newnode(Block, NULL);
    } else if (count == 1) {
        block = only;
    } else {
        block = newnode(Block, NULL);
        child = list->children->next;
        while (child) {
            if (!is_empty_statement(child->node))
                addchild(block, child->node);
            child = child->next;
        }
    }

    freenode(list);
    return block;
}
%}

%locations

%union {
    char *lexeme;
    struct node *node;
}

%token CLASS LBRACE RBRACE SEMICOLON COMMA LPAR RPAR LSQ RSQ ARROW RESERVED
%token PUBLIC STATIC VOID RETURN IF ELSE WHILE PRINT PARSEINT
%token BOOL INT DOUBLE STRING DOTLENGTH ASSIGN
%token PLUS MINUS STAR DIV MOD AND OR XOR NOT LSHIFT RSHIFT EQ NE LT GT LE GE
%token <lexeme> IDENTIFIER STRLIT NATURAL DECIMAL BOOLLIT

%type <node> program class_body
%type <node> method_decl method_header method_body
%type <node> field_decl field_tail type
%type <node> params_opt params_tail
%type <node> body_items var_decl var_tail
%type <node> stmt stmt_list
%type <node> method_call arg_tail
%type <node> assignment parse_args
%type <node> expr full_expr

%nonassoc THEN
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
%right UMINUS UPLUS UNOT

%%

program:
    CLASS IDENTIFIER LBRACE class_body RBRACE {
        ast = $$ = make_node(Program, NULL, @1.first_line, @1.first_column);
        addchild($$, make_node(Identifier, $2, @2.first_line, @2.first_column));
        append_list($$, $4);
        freenode($4);
    }
;

class_body:
    class_body method_decl {
        $$ = $1;
        addchild($$, $2);
    }
  | class_body field_decl {
        $$ = $1;
        append_list($$, $2);
        freenode($2);
    }
  | class_body SEMICOLON {
        $$ = $1;
    }
  | {
        $$ = newnode(ListNode, NULL);
    }
;

field_decl:
    PUBLIC STATIC type IDENTIFIER field_tail SEMICOLON {
        struct node *decl;
        struct node_list *child;

        $$ = newnode(ListNode, NULL);

        decl = make_node(FieldDecl, NULL, @4.first_line, @4.first_column);
        addchild(decl, $3);
        addchild(decl, make_node(Identifier, $4, @4.first_line, @4.first_column));
        addchild($$, decl);

        child = $5->children->next;
        while (child) {
            decl = make_node(FieldDecl, NULL, child->node->line, child->node->column);
            addchild(decl, copynode($3));
            addchild(decl, child->node);
            addchild($$, decl);
            child = child->next;
        }
        freenode($5);
    }
  | error SEMICOLON {
        $$ = newnode(ListNode, NULL);
        addchild($$, make_node(FieldDecl, NULL, @2.first_line, @2.first_column));
    }
;

field_tail:
    COMMA IDENTIFIER field_tail {
        $$ = $3;
        prependchild($$, make_node(Identifier, $2, @2.first_line, @2.first_column));
    }
  | {
        $$ = newnode(ListNode, NULL);
    }
;

type:
    BOOL {
        $$ = make_node(Bool, NULL, @1.first_line, @1.first_column);
    }
  | INT {
        $$ = make_node(Int, NULL, @1.first_line, @1.first_column);
    }
  | DOUBLE {
        $$ = make_node(Double, NULL, @1.first_line, @1.first_column);
    }
;

method_decl:
    PUBLIC STATIC method_header method_body {
        $$ = make_node(MethodDecl, NULL, $3->line, $3->column);
        addchild($$, $3);
        addchild($$, $4);
    }
;

method_header:
    type IDENTIFIER LPAR params_opt RPAR {
        $$ = make_node(MethodHeader, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, make_node(Identifier, $2, @2.first_line, @2.first_column));
        addchild($$, $4);
    }
  | VOID IDENTIFIER LPAR params_opt RPAR {
        $$ = make_node(MethodHeader, NULL, @2.first_line, @2.first_column);
        addchild($$, make_node(Void, NULL, @1.first_line, @1.first_column));
        addchild($$, make_node(Identifier, $2, @2.first_line, @2.first_column));
        addchild($$, $4);
    }
;

params_opt:
    type IDENTIFIER params_tail {
        struct node *param;

        $$ = make_node(MethodParams, NULL, @2.first_line, @2.first_column);
        param = make_node(ParamDecl, NULL, @2.first_line, @2.first_column);
        addchild(param, $1);
        addchild(param, make_node(Identifier, $2, @2.first_line, @2.first_column));
        addchild($$, param);

        append_list($$, $3);
        freenode($3);
    }
  | STRING LSQ RSQ IDENTIFIER {
        struct node *param;

        $$ = make_node(MethodParams, NULL, @4.first_line, @4.first_column);
        param = make_node(ParamDecl, NULL, @4.first_line, @4.first_column);
        addchild(param, make_node(StringArray, NULL, @1.first_line, @1.first_column));
        addchild(param, make_node(Identifier, $4, @4.first_line, @4.first_column));
        addchild($$, param);
    }
  | {
        $$ = newnode(MethodParams, NULL);
    }
;

params_tail:
    COMMA type IDENTIFIER params_tail {
        struct node *param;

        $$ = $4;
        param = make_node(ParamDecl, NULL, @3.first_line, @3.first_column);
        addchild(param, $2);
        addchild(param, make_node(Identifier, $3, @3.first_line, @3.first_column));
        prependchild($$, param);
    }
  | {
        $$ = newnode(ListNode, NULL);
    }
;

method_body:
    LBRACE body_items RBRACE {
        $$ = make_node(MethodBody, NULL, @1.first_line, @1.first_column);
        append_list($$, $2);
        freenode($2);
    }
;

body_items:
    var_decl body_items {
        $$ = $1;
        append_list($$, $2);
        freenode($2);
    }
  | stmt body_items {
        $$ = $2;
        if (!is_empty_statement($1))
            prependchild($$, $1);
        else
            freenode($1);
    }
  | {
        $$ = newnode(ListNode, NULL);
    }
;

var_decl:
    type IDENTIFIER var_tail SEMICOLON {
        struct node *decl;
        struct node_list *child;

        $$ = newnode(ListNode, NULL);

        decl = make_node(VarDecl, NULL, @2.first_line, @2.first_column);
        addchild(decl, $1);
        addchild(decl, make_node(Identifier, $2, @2.first_line, @2.first_column));
        addchild($$, decl);

        child = $3->children->next;
        while (child) {
            decl = make_node(VarDecl, NULL, child->node->line, child->node->column);
            addchild(decl, copynode($1));
            addchild(decl, child->node);
            addchild($$, decl);
            child = child->next;
        }
        freenode($3);
    }
;

var_tail:
    COMMA IDENTIFIER var_tail {
        $$ = $3;
        prependchild($$, make_node(Identifier, $2, @2.first_line, @2.first_column));
    }
  | {
        $$ = newnode(ListNode, NULL);
    }
;

stmt:
    LBRACE stmt_list RBRACE {
        $$ = compact_block($2);
        if ($$->line == 0 && $$->column == 0)
            set_node_location($$, @1.first_line, @1.first_column);
    }
  | IF LPAR full_expr RPAR stmt %prec THEN {
        $$ = make_node(If, NULL, @1.first_line, @1.first_column);
        addchild($$, $3);
        if ($5->category == Empty) {
            freenode($5);
            addchild($$, make_node(Block, NULL, @5.first_line, @5.first_column));
        } else {
            addchild($$, $5);
        }
        addchild($$, make_node(Block, NULL, @1.first_line, @1.first_column));
    }
  | IF LPAR full_expr RPAR stmt ELSE stmt {
        $$ = make_node(If, NULL, @1.first_line, @1.first_column);
        addchild($$, $3);
        if ($5->category == Empty) {
            freenode($5);
            addchild($$, make_node(Block, NULL, @5.first_line, @5.first_column));
        } else {
            addchild($$, $5);
        }
        if ($7->category == Empty) {
            freenode($7);
            addchild($$, make_node(Block, NULL, @7.first_line, @7.first_column));
        } else {
            addchild($$, $7);
        }
    }
  | WHILE LPAR full_expr RPAR stmt {
        $$ = make_node(While, NULL, @1.first_line, @1.first_column);
        addchild($$, $3);
        if ($5->category == Empty) {
            freenode($5);
            addchild($$, make_node(Block, NULL, @5.first_line, @5.first_column));
        } else {
            addchild($$, $5);
        }
    }
  | RETURN full_expr SEMICOLON {
        $$ = make_node(Return, NULL, @1.first_line, @1.first_column);
        addchild($$, $2);
    }
  | RETURN SEMICOLON {
        $$ = make_node(Return, NULL, @1.first_line, @1.first_column);
    }
  | SEMICOLON {
        $$ = make_node(Empty, NULL, @1.first_line, @1.first_column);
    }
  | method_call SEMICOLON {
        $$ = $1;
    }
  | assignment SEMICOLON {
        $$ = $1;
    }
  | parse_args SEMICOLON {
        $$ = $1;
    }
  | PRINT LPAR full_expr RPAR SEMICOLON {
        $$ = make_node(Print, NULL, @1.first_line, @1.first_column);
        addchild($$, $3);
    }
  | PRINT LPAR STRLIT RPAR SEMICOLON {
        $$ = make_node(Print, NULL, @1.first_line, @1.first_column);
        addchild($$, make_node(StrLit, $3, @3.first_line, @3.first_column));
    }
  | error SEMICOLON {
        $$ = make_node(Error, NULL, @2.first_line, @2.first_column);
    }
;

stmt_list:
    stmt stmt_list {
        $$ = $2;
        prependchild($$, $1);
    }
  | {
        $$ = newnode(ListNode, NULL);
    }
;

method_call:
    IDENTIFIER LPAR full_expr arg_tail RPAR {
        $$ = make_node(Call, NULL, @1.first_line, @1.first_column);
        addchild($$, make_node(Identifier, $1, @1.first_line, @1.first_column));
        addchild($$, $3);
        append_list($$, $4);
        freenode($4);
    }
  | IDENTIFIER LPAR error RPAR {
        $$ = make_node(Call, NULL, @1.first_line, @1.first_column);
        addchild($$, make_node(Identifier, $1, @1.first_line, @1.first_column));
    }
  | IDENTIFIER LPAR RPAR {
        $$ = make_node(Call, NULL, @1.first_line, @1.first_column);
        addchild($$, make_node(Identifier, $1, @1.first_line, @1.first_column));
    }
;

arg_tail:
    arg_tail COMMA full_expr {
        $$ = $1;
        addchild($$, $3);
    }
  | {
        $$ = newnode(ListNode, NULL);
    }
;

assignment:
    IDENTIFIER ASSIGN full_expr {
        $$ = make_node(Assign, NULL, @2.first_line, @2.first_column);
        addchild($$, make_node(Identifier, $1, @1.first_line, @1.first_column));
        addchild($$, $3);
    }
;

parse_args:
    PARSEINT LPAR IDENTIFIER LSQ full_expr RSQ RPAR {
        $$ = make_node(ParseArgs, NULL, @1.first_line, @1.first_column);
        addchild($$, make_node(Identifier, $3, @3.first_line, @3.first_column));
        addchild($$, $5);
    }
  | PARSEINT LPAR error RPAR {
        $$ = make_node(ParseArgs, NULL, @1.first_line, @1.first_column);
    }
;

full_expr:
    expr {
        $$ = $1;
    }
  | assignment {
        $$ = $1;
    }
;

expr:
    expr PLUS expr {
        $$ = make_node(Add, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }
  | expr MINUS expr {
        $$ = make_node(Sub, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }
  | expr STAR expr {
        $$ = make_node(Mul, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }
  | expr DIV expr {
        $$ = make_node(Div, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }
  | expr MOD expr {
        $$ = make_node(Mod, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }

  | expr EQ expr {
        $$ = make_node(Eq, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }
  | expr NE expr {
        $$ = make_node(Ne, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }
  | expr LT expr {
        $$ = make_node(Lt, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }
  | expr GT expr {
        $$ = make_node(Gt, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }
  | expr LE expr {
        $$ = make_node(Le, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }
  | expr GE expr {
        $$ = make_node(Ge, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }

  | expr OR expr {
        $$ = make_node(Or, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }
  | expr XOR expr {
        $$ = make_node(Xor, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }
  | expr AND expr {
        $$ = make_node(And, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }
  | expr LSHIFT expr {
        $$ = make_node(Lshift, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }
  | expr RSHIFT expr {
        $$ = make_node(Rshift, NULL, @2.first_line, @2.first_column);
        addchild($$, $1);
        addchild($$, $3);
    }

  | MINUS expr %prec UMINUS {
        $$ = make_node(Minus, NULL, @1.first_line, @1.first_column);
        addchild($$, $2);
    }
  | PLUS expr %prec UPLUS {
        $$ = make_node(Plus, NULL, @1.first_line, @1.first_column);
        addchild($$, $2);
    }
  | NOT expr %prec UNOT {
        $$ = make_node(Not, NULL, @1.first_line, @1.first_column);
        addchild($$, $2);
    }

  | LPAR full_expr RPAR {
        $$ = $2;
    }
  | method_call {
        $$ = $1;
    }
  | parse_args {
        $$ = $1;
    }

  | IDENTIFIER {
        $$ = make_node(Identifier, $1, @1.first_line, @1.first_column);
    }
  | IDENTIFIER DOTLENGTH {
        $$ = make_node(Length, NULL, @2.first_line, @2.first_column);
        addchild($$, make_node(Identifier, $1, @1.first_line, @1.first_column));
    }
  | NATURAL {
        $$ = make_node(Natural, $1, @1.first_line, @1.first_column);
    }
  | DECIMAL {
        $$ = make_node(Decimal, $1, @1.first_line, @1.first_column);
    }
  | BOOLLIT {
        $$ = make_node(BoolLit, $1, @1.first_line, @1.first_column);
    }

  | LPAR error RPAR {
        $$ = make_node(Error, NULL, @2.first_line, @2.first_column);
    }
;

%%

void yyerror(char *s) {
    printf("Line %d, col %d: %s: %s\n", line, token_column, s, token_text);
    syntax_errors = 1;
}
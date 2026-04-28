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
        ast = $$ = newnode(Program, NULL);
        addchild($$, newnode(Identifier, $2));
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

        decl = newnode(FieldDecl, NULL);
        addchild(decl, $3);
        addchild(decl, newnode(Identifier, $4));
        addchild($$, decl);

        child = $5->children->next;
        while (child) {
            decl = newnode(FieldDecl, NULL);
            addchild(decl, copynode($3));
            addchild(decl, child->node);
            addchild($$, decl);
            child = child->next;
        }
        freenode($5);
    }
  | error SEMICOLON {
        $$ = newnode(ListNode, NULL);
        addchild($$, newnode(FieldDecl, NULL));
    }
;

field_tail:
    COMMA IDENTIFIER field_tail {
        $$ = $3;
        prependchild($$, newnode(Identifier, $2));
    }
  | {
        $$ = newnode(ListNode, NULL);
    }
;

type:
    BOOL   { $$ = newnode(Bool, NULL); }
  | INT    { $$ = newnode(Int, NULL); }
  | DOUBLE { $$ = newnode(Double, NULL); }
;

method_decl:
    PUBLIC STATIC method_header method_body {
        $$ = newnode(MethodDecl, NULL);
        addchild($$, $3);
        addchild($$, $4);
    }
;

method_header:
    type IDENTIFIER LPAR params_opt RPAR {
        $$ = newnode(MethodHeader, NULL);
        addchild($$, $1);
        addchild($$, newnode(Identifier, $2));
        addchild($$, $4);
    }
  | VOID IDENTIFIER LPAR params_opt RPAR {
        $$ = newnode(MethodHeader, NULL);
        addchild($$, newnode(Void, NULL));
        addchild($$, newnode(Identifier, $2));
        addchild($$, $4);
    }
;

params_opt:
    type IDENTIFIER params_tail {
        struct node *param;

        $$ = newnode(MethodParams, NULL);
        param = newnode(ParamDecl, NULL);
        addchild(param, $1);
        addchild(param, newnode(Identifier, $2));
        addchild($$, param);

        append_list($$, $3);
        freenode($3);
    }
  | STRING LSQ RSQ IDENTIFIER {
        struct node *param;

        $$ = newnode(MethodParams, NULL);
        param = newnode(ParamDecl, NULL);
        addchild(param, newnode(StringArray, NULL));
        addchild(param, newnode(Identifier, $4));
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
        param = newnode(ParamDecl, NULL);
        addchild(param, $2);
        addchild(param, newnode(Identifier, $3));
        prependchild($$, param);
    }
  | {
        $$ = newnode(ListNode, NULL);
    }
;

method_body:
    LBRACE body_items RBRACE {
        $$ = newnode(MethodBody, NULL);
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

        decl = newnode(VarDecl, NULL);
        addchild(decl, $1);
        addchild(decl, newnode(Identifier, $2));
        addchild($$, decl);

        child = $3->children->next;
        while (child) {
            decl = newnode(VarDecl, NULL);
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
        prependchild($$, newnode(Identifier, $2));
    }
  | {
        $$ = newnode(ListNode, NULL);
    }
;

stmt:
    LBRACE stmt_list RBRACE {
        $$ = compact_block($2);
    }
  | IF LPAR full_expr RPAR stmt %prec THEN {
        $$ = newnode(If, NULL);
        addchild($$, $3);
        if ($5->category == Empty) {
            freenode($5);
            addchild($$, newnode(Block, NULL));
        } else {
            addchild($$, $5);
        }
        addchild($$, newnode(Block, NULL));
    }
  | IF LPAR full_expr RPAR stmt ELSE stmt {
        $$ = newnode(If, NULL);
        addchild($$, $3);
        if ($5->category == Empty) {
            freenode($5);
            addchild($$, newnode(Block, NULL));
        } else {
            addchild($$, $5);
        }
        if ($7->category == Empty) {
            freenode($7);
            addchild($$, newnode(Block, NULL));
        } else {
            addchild($$, $7);
        }
    }
  | WHILE LPAR full_expr RPAR stmt {
        $$ = newnode(While, NULL);
        addchild($$, $3);
        if ($5->category == Empty) {
            freenode($5);
            addchild($$, newnode(Block, NULL));
        } else {
            addchild($$, $5);
        }
    }
  | RETURN full_expr SEMICOLON {
        $$ = newnode(Return, NULL);
        addchild($$, $2);
    }
  | RETURN SEMICOLON {
        $$ = newnode(Return, NULL);
    }
  | SEMICOLON {
        $$ = newnode(Empty, NULL);
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
        $$ = newnode(Print, NULL);
        addchild($$, $3);
    }
  | PRINT LPAR STRLIT RPAR SEMICOLON {
        $$ = newnode(Print, NULL);
        addchild($$, newnode(StrLit, $3));
    }
  | error SEMICOLON {
        $$ = newnode(Error, NULL);
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
        $$ = newnode(Call, NULL);
        addchild($$, newnode(Identifier, $1));
        addchild($$, $3);
        append_list($$, $4);
        freenode($4);
    }
  | IDENTIFIER LPAR error RPAR {
        $$ = newnode(Call, NULL);
        addchild($$, newnode(Identifier, $1));
    }
  | IDENTIFIER LPAR RPAR {
        $$ = newnode(Call, NULL);
        addchild($$, newnode(Identifier, $1));
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
        $$ = newnode(Assign, NULL);
        addchild($$, newnode(Identifier, $1));
        addchild($$, $3);
    }
;

parse_args:
    PARSEINT LPAR IDENTIFIER LSQ full_expr RSQ RPAR {
        $$ = newnode(ParseArgs, NULL);
        addchild($$, newnode(Identifier, $3));
        addchild($$, $5);
    }
  | PARSEINT LPAR error RPAR {
        $$ = newnode(ParseArgs, NULL);
    }
;

full_expr:
    expr       { $$ = $1; }
  | assignment { $$ = $1; }
;

expr:
    expr PLUS expr   { $$ = newnode(Add, NULL); addchild($$, $1); addchild($$, $3); }
  | expr MINUS expr  { $$ = newnode(Sub, NULL); addchild($$, $1); addchild($$, $3); }
  | expr STAR expr   { $$ = newnode(Mul, NULL); addchild($$, $1); addchild($$, $3); }
  | expr DIV expr    { $$ = newnode(Div, NULL); addchild($$, $1); addchild($$, $3); }
  | expr MOD expr    { $$ = newnode(Mod, NULL); addchild($$, $1); addchild($$, $3); }

  | expr EQ expr     { $$ = newnode(Eq, NULL); addchild($$, $1); addchild($$, $3); }
  | expr NE expr     { $$ = newnode(Ne, NULL); addchild($$, $1); addchild($$, $3); }
  | expr LT expr     { $$ = newnode(Lt, NULL); addchild($$, $1); addchild($$, $3); }
  | expr GT expr     { $$ = newnode(Gt, NULL); addchild($$, $1); addchild($$, $3); }
  | expr LE expr     { $$ = newnode(Le, NULL); addchild($$, $1); addchild($$, $3); }
  | expr GE expr     { $$ = newnode(Ge, NULL); addchild($$, $1); addchild($$, $3); }

  | expr OR expr     { $$ = newnode(Or, NULL); addchild($$, $1); addchild($$, $3); }
  | expr XOR expr    { $$ = newnode(Xor, NULL); addchild($$, $1); addchild($$, $3); }
  | expr AND expr    { $$ = newnode(And, NULL); addchild($$, $1); addchild($$, $3); }
  | expr LSHIFT expr { $$ = newnode(Lshift, NULL); addchild($$, $1); addchild($$, $3); }
  | expr RSHIFT expr { $$ = newnode(Rshift, NULL); addchild($$, $1); addchild($$, $3); }

  | MINUS expr %prec UMINUS { $$ = newnode(Minus, NULL); addchild($$, $2); }
  | PLUS expr  %prec UPLUS  { $$ = newnode(Plus, NULL); addchild($$, $2); }
  | NOT expr   %prec UNOT   { $$ = newnode(Not, NULL); addchild($$, $2); }

  | LPAR full_expr RPAR { $$ = $2; }
  | method_call         { $$ = $1; }
  | parse_args          { $$ = $1; }

  | IDENTIFIER           { $$ = newnode(Identifier, $1); }
  | IDENTIFIER DOTLENGTH { $$ = newnode(Length, NULL); addchild($$, newnode(Identifier, $1)); }
  | NATURAL              { $$ = newnode(Natural, $1); }
  | DECIMAL              { $$ = newnode(Decimal, $1); }
  | BOOLLIT              { $$ = newnode(BoolLit, $1); }

  | LPAR error RPAR      { $$ = newnode(Error, NULL); }
;

%%

void yyerror(char *s) {
    printf("Line %d, col %d: %s: %s\n", line, token_column, s, token_text);
    syntax_errors = 1;
}
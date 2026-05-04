/* START definitions section -- C code delimited by %{ ... %} and token declarations */

%{

#include <stdio.h>
#include "ast.h"

int yylex(void);
void yyerror(char *);

char* category_name(enum category c) {
    switch(c) {
        case Program: return "Program";
        case Function: return "Function";
        case Parameters: return "Parameters";
        case Parameter: return "Parameter";
        case Arguments: return "Arguments";
        case Integer: return "Integer";
        case Double: return "Double";
        case Identifier: return "Identifier";
        case Natural: return "Natural";
        case Decimal: return "Decimal";
        case Call: return "Call";
        case If: return "If";
        case Add: return "Add";
        case Sub: return "Sub";
        case Mul: return "Mul";
        case Div: return "Div";
        default: return "Unknown";
    }
}

void show(struct node *node, int depth) {
    if(node == NULL) return;

    for(int i = 0; i < depth; i++)
        printf("__");

    printf("%s", category_name(node->category));

    if(node->token)
        printf("(%s)", node->token);

    printf("\n");

    struct node_list *child = node->children->next;
    while(child != NULL) {
        show(child->node, depth + 1);
        child = child->next;
    }
}

struct node *ast;

%}

%token INTEGER DOUBLE IF THEN ELSE
%token<lexeme> IDENTIFIER NATURAL DECIMAL
%type<node> program function parameters parameter arguments expression functions

%left LOW
%left '+' '-'
%left '*' '/'

%union{
    char *lexeme;
    struct node *node;
}

/* START grammar rules section -- BNF grammar */

%%

program: functions {
    ast = $$ = $1;
}
;

functions: function {
    $$ = newnode(Program, NULL);
    addchild($$, $1);
}
| functions function {
    addchild($1, $2);
    $$ = $1;
}
;

function: IDENTIFIER '(' parameters ')' '=' expression {
    $$ = newnode(Function, NULL);
    addchild($$, newnode(Identifier, $1));
    addchild($$, $3);
    addchild($$, $6);
}
;

parameters: parameter {
    $$ = newnode(Parameters, NULL);
    addchild($$, $1);
}
    | parameters ',' parameter {
    addchild($1, $3);
    $$ = $1;
}
    ;

parameter: INTEGER IDENTIFIER {
    $$ = newnode(Parameter, NULL);
    addchild($$, newnode(Integer, NULL));
    addchild($$, newnode(Identifier, $2));
}
| DOUBLE IDENTIFIER {
    $$ = newnode(Parameter, NULL);
    addchild($$, newnode(Double, NULL));
    addchild($$, newnode(Identifier, $2));
};

arguments: expression {
    $$ = newnode(Arguments, NULL);
    addchild($$, $1);
}
| arguments ',' expression {
    addchild($1, $3);
    $$ = $1;
}
;

expression: IDENTIFIER {
    $$ = newnode(Identifier, $1);
}
    | NATURAL {
    $$ = newnode(Natural, $1);
}
    | DECIMAL {
    $$ = newnode(Decimal, $1);
}
    | IDENTIFIER '(' arguments ')' {
    $$ = newnode(Call, NULL);
    addchild($$, newnode(Identifier, $1));
    addchild($$, $3);
}
    | IF expression THEN expression ELSE expression %prec LOW {
    $$ = newnode(If, NULL);
    addchild($$, $2);
    addchild($$, $4);
    addchild($$, $6);
}
    | expression '+' expression {
    $$ = newnode(Add, NULL);
    addchild($$, $1);
    addchild($$, $3);
}
    | expression '-' expression {
    $$ = newnode(Sub, NULL);
    addchild($$, $1);
    addchild($$, $3);
}
    | expression '*' expression {
    $$ = newnode(Mul, NULL);
    addchild($$, $1);
    addchild($$, $3);
}
    | expression '/' expression {
    $$ = newnode(Div, NULL);
    addchild($$, $1);
    addchild($$, $3);
}
    | '(' expression ')' {
    $$ = $2;
}
    ;

%%

/* START subroutines section */

// all needed functions are collected in the .l and ast.* files

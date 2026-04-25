#ifndef _AST_H
#define _AST_H

enum category {
    Program,

    /* Declarations */
    FieldDecl,
    VarDecl,

    MethodDecl,
    MethodHeader,
    MethodParams,
    ParamDecl,
    MethodBody,

    /* Statements */
    Block,
    If,
    While,
    Return,
    Call,
    Print,
    ParseArgs,
    Assign,

    /* Operators */
    Or,
    And,
    Eq,
    Ne,
    Lt,
    Gt,
    Le,
    Ge,
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Lshift,
    Rshift,
    Xor,
    Not,
    Minus,
    Plus,
    Length,

    /* Terminals */
    Bool,
    BoolLit,
    Double,
    Decimal,
    Identifier,
    Int,
    Natural,
    StrLit,
    StringArray,
    Void
};

struct node {
    enum category category;
    char *token;
    struct node_list *children;
};

struct node_list {
    struct node *node;
    struct node_list *next;
};

struct node *newnode(enum category category, char *token);
void addchild(struct node *parent, struct node *child);
void print_ast(struct node *node, int depth);
void free_ast(struct node *node);

#endif
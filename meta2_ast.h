#ifndef AST_H
#define AST_H

enum category {
    Program,
    MethodDecl, FieldDecl,
    MethodHeader, MethodBody, MethodParams, ParamDecl,
    VarDecl,

    Bool, Int, Double, Void, StringArray,

    Block, If, While, Return, Print,
    Assign, Call, ParseArgs,

    Or, Xor, And,
    Eq, Ne, Lt, Gt, Le, Ge,
    Lshift, Rshift,
    Add, Sub, Mul, Div, Mod,
    Not, Minus, Plus,
    Length,

    Identifier, Natural, Decimal, BoolLit, StrLit,

    Empty,
    ListNode,
    Error
};

struct node_list {
    struct node *node;
    struct node_list *next;
};

struct node {
    enum category category;
    char *token;
    struct node_list *children;
};

struct node *newnode(enum category category, char *token);
struct node *copynode(struct node *n);

void addchild(struct node *parent, struct node *child);
void prependchild(struct node *parent, struct node *child);
void freenode(struct node *n);
int childcount(struct node *n);

void print_ast(struct node *node, int depth);
void show(struct node *node, int depth);

#endif
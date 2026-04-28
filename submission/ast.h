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

enum type {
    none_type,
    integer_type,
    double_type,
    bool_type,
    string_array_type,
    void_type,
    undef_type
};

struct node_list {
    struct node *node;
    struct node_list *next;
};

struct node {
    enum category category;
    char *token;
    struct node_list *children;

    int line;
    int column;

    enum type type;
    char *annotation;
};

struct node *newnode(enum category category, char *token);
struct node *copynode(struct node *n);

void set_node_location(struct node *node, int line, int column);

void addchild(struct node *parent, struct node *child);
void prependchild(struct node *parent, struct node *child);
void freenode(struct node *n);
void free_ast(struct node *n);
int childcount(struct node *n);

enum type category_to_type(enum category category);
const char *type_name(enum type type);
int is_expression_node(enum category category);

void print_ast(struct node *node, int depth);
void show(struct node *node, int depth);

#endif
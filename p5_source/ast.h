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

enum type {
    integer_type,
    double_type,
    bool_type,
    string_array_type,
    void_type,
    undef_type,
    none_type
};

struct node {
    enum category category;
    char *token;
    enum type type;
    char *annotation;
    int line;
    int column;
    struct node_list *children;
};

struct node_list {
    struct node *node;
    struct node_list *next;
};

struct node *newnode2(enum category category, char *token);
struct node *newnode4(enum category category, char *token, int line, int column);

#define GET_NEWNODE_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define newnode(...) GET_NEWNODE_MACRO(__VA_ARGS__, newnode4, unused, newnode2)(__VA_ARGS__)

void addchild(struct node *parent, struct node *child);
void print_ast(struct node *node, int depth);
void free_ast(struct node *node);

const char *type_name(enum type type);
enum type category_to_type(enum category category);
int is_expression_node(enum category category);

#endif
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

/* Helpers para Meta 3 */
const char *type_name(enum type type);
enum type category_to_type(enum category category);
int is_expression_node(enum category category);

#endif
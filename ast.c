#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"

struct node *newnode(enum category category, char *token) {
    struct node *new = malloc(sizeof(struct node));
    new->category = category;
    new->token = token ? strdup(token) : NULL;
    new->type = none_type;

    new->children = malloc(sizeof(struct node_list));
    new->children->node = NULL;
    new->children->next = NULL;

    return new;
}

void addchild(struct node *parent, struct node *child) {
    if (!parent || !child) return;

    struct node_list *new = malloc(sizeof(struct node_list));
    new->node = child;
    new->next = NULL;

    struct node_list *children = parent->children;
    while (children->next != NULL)
        children = children->next;

    children->next = new;
}

static const char *category_name[] = {
    "Program",
    "FieldDecl",
    "VarDecl",
    "MethodDecl",
    "MethodHeader",
    "MethodParams",
    "ParamDecl",
    "MethodBody",
    "Block",
    "If",
    "While",
    "Return",
    "Call",
    "Print",
    "ParseArgs",
    "Assign",
    "Or",
    "And",
    "Eq",
    "Ne",
    "Lt",
    "Gt",
    "Le",
    "Ge",
    "Add",
    "Sub",
    "Mul",
    "Div",
    "Mod",
    "Lshift",
    "Rshift",
    "Xor",
    "Not",
    "Minus",
    "Plus",
    "Length",
    "Bool",
    "BoolLit",
    "Double",
    "Decimal",
    "Identifier",
    "Int",
    "Natural",
    "StrLit",
    "StringArray",
    "Void"
};

const char *type_name(enum type type) {
    switch (type) {
        case integer_type: return "int";
        case double_type: return "double";
        case bool_type: return "boolean";
        case string_array_type: return "String[]";
        case void_type: return "void";
        case undef_type: return "undef";
        default: return "none";
    }
}

enum type category_to_type(enum category category) {
    switch (category) {
        case Int: return integer_type;
        case Double: return double_type;
        case Bool: return bool_type;
        case StringArray: return string_array_type;
        case Void: return void_type;
        default: return none_type;
    }
}

int is_expression_node(enum category category) {
    switch (category) {
        case Call:
        case ParseArgs:
        case Assign:
        case Or:
        case And:
        case Eq:
        case Ne:
        case Lt:
        case Gt:
        case Le:
        case Ge:
        case Add:
        case Sub:
        case Mul:
        case Div:
        case Mod:
        case Lshift:
        case Rshift:
        case Xor:
        case Not:
        case Minus:
        case Plus:
        case Length:
        case BoolLit:
        case Decimal:
        case Identifier:
        case Natural:
            return 1;
        default:
            return 0;
    }
}

void print_ast(struct node *node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++)
        printf("..");

    if (node->token)
        printf("%s(%s)", category_name[node->category], node->token);
    else
        printf("%s", category_name[node->category]);

    if (is_expression_node(node->category) && node->type != none_type)
        printf(" - %s", type_name(node->type));

    printf("\n");

    struct node_list *child = node->children->next;
    while (child) {
        print_ast(child->node, depth + 1);
        child = child->next;
    }
}

void free_ast(struct node *node) {
    if (!node) return;

    struct node_list *child = node->children;
    while (child) {
        if (child->node)
            free_ast(child->node);
        struct node_list *tmp = child;
        child = child->next;
        free(tmp);
    }

    if (node->token)
        free(node->token);

    free(node);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

struct node *newnode(enum category category, char *token) {
    struct node *n = malloc(sizeof(struct node));
    if (!n) exit(1);

    n->category = category;
    n->token = token;
    n->children = malloc(sizeof(struct node_list));
    if (!n->children) exit(1);

    n->children->node = NULL;
    n->children->next = NULL;

    n->line = 0;
    n->column = 0;
    n->type = none_type;
    n->annotation = NULL;

    return n;
}

struct node *copynode(struct node *n) {
    struct node *copy;

    if (!n) return NULL;

    copy = newnode(n->category, n->token ? strdup(n->token) : NULL);
    copy->line = n->line;
    copy->column = n->column;
    copy->type = n->type;

    if (n->annotation)
        copy->annotation = strdup(n->annotation);

    return copy;
}

void set_node_location(struct node *node, int line, int column) {
    if (!node) return;

    node->line = line;
    node->column = column;
}

void addchild(struct node *parent, struct node *child) {
    struct node_list *slot;
    struct node_list *new_child;

    if (!parent || !child) return;

    new_child = malloc(sizeof(struct node_list));
    if (!new_child) exit(1);

    new_child->node = child;
    new_child->next = NULL;

    slot = parent->children;
    while (slot->next)
        slot = slot->next;

    slot->next = new_child;
}

void prependchild(struct node *parent, struct node *child) {
    struct node_list *new_child;

    if (!parent || !child) return;

    new_child = malloc(sizeof(struct node_list));
    if (!new_child) exit(1);

    new_child->node = child;
    new_child->next = parent->children->next;
    parent->children->next = new_child;
}

int childcount(struct node *n) {
    int count = 0;
    struct node_list *child;

    if (!n || !n->children) return 0;

    child = n->children->next;
    while (child) {
        count++;
        child = child->next;
    }

    return count;
}

void freenode(struct node *n) {
    struct node_list *child;

    if (!n) return;

    child = n->children;
    while (child) {
        struct node_list *next = child->next;
        free(child);
        child = next;
    }

    if (n->token)
        free(n->token);

    if (n->annotation)
        free(n->annotation);

    free(n);
}

void free_ast(struct node *n) {
    struct node_list *child;

    if (!n) return;

    child = n->children;
    while (child) {
        struct node_list *next = child->next;

        if (child->node)
            free_ast(child->node);

        free(child);
        child = next;
    }

    if (n->token)
        free(n->token);

    if (n->annotation)
        free(n->annotation);

    free(n);
}

enum type category_to_type(enum category category) {
    switch (category) {
        case Int:
            return integer_type;
        case Double:
            return double_type;
        case Bool:
            return bool_type;
        case StringArray:
            return string_array_type;
        case Void:
            return void_type;
        default:
            return undef_type;
    }
}

const char *type_name(enum type type) {
    switch (type) {
        case integer_type:
            return "int";
        case double_type:
            return "double";
        case bool_type:
            return "boolean";
        case string_array_type:
            return "String[]";
        case void_type:
            return "void";
        case undef_type:
            return "undef";
        case none_type:
        default:
            return "none";
    }
}

int is_expression_node(enum category category) {
    switch (category) {
        case Assign:
        case Call:
        case ParseArgs:
        case Or:
        case Xor:
        case And:
        case Eq:
        case Ne:
        case Lt:
        case Gt:
        case Le:
        case Ge:
        case Lshift:
        case Rshift:
        case Add:
        case Sub:
        case Mul:
        case Div:
        case Mod:
        case Not:
        case Minus:
        case Plus:
        case Length:
        case Identifier:
        case Natural:
        case Decimal:
        case BoolLit:
            return 1;

        default:
            return 0;
    }
}

static const char *category_name(enum category category) {
    switch (category) {
        case Program:      return "Program";
        case MethodDecl:   return "MethodDecl";
        case FieldDecl:    return "FieldDecl";
        case MethodHeader: return "MethodHeader";
        case MethodBody:   return "MethodBody";
        case MethodParams: return "MethodParams";
        case ParamDecl:    return "ParamDecl";
        case VarDecl:      return "VarDecl";
        case Bool:         return "Bool";
        case Int:          return "Int";
        case Double:       return "Double";
        case Void:         return "Void";
        case StringArray:  return "StringArray";
        case Block:        return "Block";
        case If:           return "If";
        case While:        return "While";
        case Return:       return "Return";
        case Print:        return "Print";
        case Assign:       return "Assign";
        case Call:         return "Call";
        case ParseArgs:    return "ParseArgs";
        case Or:           return "Or";
        case Xor:          return "Xor";
        case And:          return "And";
        case Eq:           return "Eq";
        case Ne:           return "Ne";
        case Lt:           return "Lt";
        case Gt:           return "Gt";
        case Le:           return "Le";
        case Ge:           return "Ge";
        case Lshift:       return "Lshift";
        case Rshift:       return "Rshift";
        case Add:          return "Add";
        case Sub:          return "Sub";
        case Mul:          return "Mul";
        case Div:          return "Div";
        case Mod:          return "Mod";
        case Not:          return "Not";
        case Minus:        return "Minus";
        case Plus:         return "Plus";
        case Length:       return "Length";
        case Identifier:   return "Identifier";
        case Natural:      return "Natural";
        case Decimal:      return "Decimal";
        case BoolLit:      return "BoolLit";
        case StrLit:       return "StrLit";
        case Error:        return "Error";
        case Empty:
        case ListNode:
            return NULL;
    }

    return NULL;
}

void print_ast(struct node *node, int depth) {
    const char *name;
    struct node_list *child;

    if (!node) return;

    name = category_name(node->category);

    if (name) {
        for (int i = 0; i < depth * 2; i++)
            putchar('.');

        printf("%s", name);

        if (node->token)
            printf("(%s)", node->token);

        if (node->annotation)
            printf(" - %s", node->annotation);
        else if (node->type != none_type)
            printf(" - %s", type_name(node->type));

        putchar('\n');
    }

    child = node->children->next;
    while (child) {
        print_ast(child->node, depth + 1);
        child = child->next;
    }
}

void show(struct node *node, int depth) {
    print_ast(node, depth);
}
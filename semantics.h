#ifndef _SEMANTICS_H
#define _SEMANTICS_H

#include "ast.h"

struct parameter_list {
    enum type type;
    struct parameter_list *next;
};

struct symbol_list {
    char *name;
    enum type type;
    int is_parameter;
    struct parameter_list *params;
    struct node *node;
    struct symbol_list *next;
};

struct method_scope {
    char *name;
    struct parameter_list *params;
    struct symbol_list *symbols;
    struct method_scope *next;
};

extern int semantic_errors;

int check_program(struct node *program);
void show_symbol_tables(void);

#endif
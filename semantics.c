#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantics.h"

int semantic_errors = 0;

static char *class_name = NULL;
static struct symbol_list *global_table = NULL;
static struct method_scope *method_scopes = NULL;

/* ---------- Helpers de listas ---------- */

static struct symbol_list *new_symbol(char *name, enum type type, int is_parameter, struct node *node) {
    struct symbol_list *s = (struct symbol_list *)malloc(sizeof(struct symbol_list));
    s->name = strdup(name);
    s->type = type;
    s->is_parameter = is_parameter;
    s->params = NULL;
    s->node = node;
    s->next = NULL;
    return s;
}

static struct parameter_list *new_param(enum type type) {
    struct parameter_list *p = (struct parameter_list *)malloc(sizeof(struct parameter_list));
    p->type = type;
    p->next = NULL;
    return p;
}

static void append_param(struct parameter_list **list, enum type type) {
    struct parameter_list *new = new_param(type);

    if (*list == NULL) {
        *list = new;
        return;
    }

    struct parameter_list *cur = *list;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = new;
}

static void append_symbol(struct symbol_list **table, struct symbol_list *symbol) {
    if (*table == NULL) {
        *table = symbol;
        return;
    }

    struct symbol_list *cur = *table;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = symbol;
}

static struct method_scope *new_method_scope(char *name, struct parameter_list *params) {
    struct method_scope *m = (struct method_scope *)malloc(sizeof(struct method_scope));
    m->name = strdup(name);
    m->params = params;
    m->symbols = NULL;
    m->next = NULL;
    return m;
}

static void append_method_scope(struct method_scope **list, struct method_scope *scope) {
    if (*list == NULL) {
        *list = scope;
        return;
    }

    struct method_scope *cur = *list;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = scope;
}

static struct symbol_list *search_symbol(struct symbol_list *table, char *name) {
    while (table != NULL) {
        if (strcmp(table->name, name) == 0)
            return table;
        table = table->next;
    }
    return NULL;
}

/* ---------- Helpers de AST ---------- */

static struct node *get_child(struct node *node, int index) {
    int i = 0;
    struct node_list *child;

    if (!node || !node->children)
        return NULL;

    child = node->children->next;
    while (child != NULL) {
        if (i == index)
            return child->node;
        i++;
        child = child->next;
    }

    return NULL;
}

static struct parameter_list *build_method_param_types(struct node *method_params) {
    struct parameter_list *params = NULL;
    struct node_list *child;

    if (!method_params || !method_params->children)
        return NULL;

    child = method_params->children->next;
    while (child != NULL) {
        struct node *param_decl = child->node;
        struct node *type_node = get_child(param_decl, 0);
        append_param(&params, category_to_type(type_node->category));
        child = child->next;
    }

    return params;
}

/* ---------- Recolha global ---------- */

static void collect_field_decl(struct node *field_decl) {
    struct node *id = get_child(field_decl, 1);
    struct node *type_node = get_child(field_decl, 0);
    enum type type = category_to_type(type_node->category);

    if (search_symbol(global_table, id->token) == NULL)
        append_symbol(&global_table, new_symbol(id->token, type, 0, field_decl));
}

static void collect_var_decl(struct method_scope *scope, struct node *var_decl) {
    struct node *id = get_child(var_decl, 1);
    struct node *type_node = get_child(var_decl, 0);
    enum type type = category_to_type(type_node->category);

    if (search_symbol(scope->symbols, id->token) == NULL)
        append_symbol(&scope->symbols, new_symbol(id->token, type, 0, var_decl));
}

static void collect_method_decl(struct node *method_decl) {
    struct node *header = get_child(method_decl, 0);
    struct node *body = get_child(method_decl, 1);

    struct node *return_type_node = get_child(header, 0);
    struct node *id = get_child(header, 1);
    struct node *params_node = get_child(header, 2);

    enum type return_type = category_to_type(return_type_node->category);
    struct parameter_list *params = build_method_param_types(params_node);

    struct symbol_list *method_symbol = new_symbol(id->token, return_type, 0, method_decl);
    method_symbol->params = params;
    append_symbol(&global_table, method_symbol);

    struct method_scope *scope = new_method_scope(id->token, params);
    append_symbol(&scope->symbols, new_symbol("return", return_type, 0, method_decl));

    if (params_node && params_node->children) {
        struct node_list *child = params_node->children->next;
        while (child != NULL) {
            struct node *param_decl = child->node;
            struct node *ptype = get_child(param_decl, 0);
            struct node *pid = get_child(param_decl, 1);

            append_symbol(&scope->symbols,
                new_symbol(pid->token, category_to_type(ptype->category), 1, param_decl));

            child = child->next;
        }
    }

    if (body && body->children) {
        struct node_list *child = body->children->next;
        while (child != NULL) {
            if (child->node->category == VarDecl)
                collect_var_decl(scope, child->node);
            child = child->next;
        }
    }

    append_method_scope(&method_scopes, scope);
}

int check_program(struct node *program) {
    struct node_list *child;

    semantic_errors = 0;
    global_table = NULL;
    method_scopes = NULL;

    if (!program)
        return 0;

    child = program->children->next;
    if (child != NULL && child->node->category == Identifier && child->node->token != NULL)
        class_name = child->node->token;

    while (child != NULL) {
        if (child->node->category == FieldDecl)
            collect_field_decl(child->node);
        else if (child->node->category == MethodDecl)
            collect_method_decl(child->node);

        child = child->next;
    }

    return semantic_errors;
}

/* ---------- Impressão ---------- */

static void print_param_list(struct parameter_list *params) {
    printf("(");
    while (params != NULL) {
        printf("%s", type_name(params->type));
        if (params->next != NULL)
            printf(",");
        params = params->next;
        if (params != NULL)
            printf(" ");
    }
    printf(")");
}

static void print_global_table(void) {
    struct symbol_list *s = global_table;

    printf("===== Class %s Symbol Table =====\n", class_name ? class_name : "");

    while (s != NULL) {
        printf("%s", s->name);

        if (s->params != NULL) {
            printf("\t");
            print_param_list(s->params);
        }

        printf("\t%s\n", type_name(s->type));
        s = s->next;
    }
}

static void print_method_table(struct method_scope *scope) {
    struct symbol_list *s;

    printf("===== Method %s ", scope->name);
    print_param_list(scope->params);
    printf(" Symbol Table =====\n");

    s = scope->symbols;
    while (s != NULL) {
        printf("%s\t%s", s->name, type_name(s->type));
        if (s->is_parameter)
            printf("\tparam");
        printf("\n");
        s = s->next;
    }
}

void show_symbol_tables(void) {
    struct method_scope *m;

    print_global_table();

    m = method_scopes;
    while (m != NULL) {
        printf("\n");
        print_method_table(m);
        m = m->next;
    }
}
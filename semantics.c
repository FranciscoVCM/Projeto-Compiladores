#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantics.h"

int semantic_errors = 0;

static char *class_name = NULL;
static struct symbol_list *global_table = NULL;
static struct method_scope *method_scopes = NULL;

/* =========================================================
 * Helpers de listas
 * ========================================================= */

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

static struct method_scope *new_method_scope(char *name, enum type return_type, struct parameter_list *params, struct node *method_decl, struct node *body) {
    struct method_scope *m = (struct method_scope *)malloc(sizeof(struct method_scope));
    m->name = strdup(name);
    m->return_type = return_type;
    m->params = params;
    m->symbols = NULL;
    m->method_decl = method_decl;
    m->body = body;
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

static struct method_scope *find_method_scope(char *name, struct parameter_list *params) {
    struct method_scope *m = method_scopes;

    while (m != NULL) {
        if (strcmp(m->name, name) == 0) {
            struct parameter_list *a = m->params;
            struct parameter_list *b = params;
            int ok = 1;

            while (a != NULL && b != NULL) {
                if (a->type != b->type) {
                    ok = 0;
                    break;
                }
                a = a->next;
                b = b->next;
            }

            if (a != NULL || b != NULL)
                ok = 0;

            if (ok)
                return m;
        }
        m = m->next;
    }

    return NULL;
}

/* =========================================================
 * Helpers de AST
 * ========================================================= */

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

/* =========================================================
 * Recolha de símbolos
 * ========================================================= */

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

    struct method_scope *scope = new_method_scope(id->token, return_type, params, method_decl, body);
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

/* =========================================================
 * Inferência de tipos - Fase 2
 * ========================================================= */

static enum type check_expression(struct node *expr, struct method_scope *scope);

static enum type unify_numeric_binary(enum type left, enum type right) {
    if (left == undef_type || right == undef_type)
        return undef_type;

    if (left == integer_type && right == integer_type)
        return integer_type;

    if (left == double_type && right == double_type)
        return double_type;

    return undef_type;
}

static enum type check_call(struct node *expr, struct method_scope *scope) {
    struct node *id = get_child(expr, 0);
    struct parameter_list *arg_types = NULL;
    struct node_list *child;

    if (!id || !id->token) {
        expr->type = undef_type;
        return expr->type;
    }

    id->type = undef_type;

    child = id->children ? id->children->next : NULL;
    (void)child;

    struct node_list *arg = expr->children->next;
    if (arg != NULL)
        arg = arg->next;

    while (arg != NULL) {
        enum type t = check_expression(arg->node, scope);
        append_param(&arg_types, t);
        arg = arg->next;
    }

    struct method_scope *target = find_method_scope(id->token, arg_types);
    if (target != NULL) {
        id->type = target->return_type;
        expr->type = target->return_type;
    } else {
        id->type = undef_type;
        expr->type = undef_type;
    }

    return expr->type;
}

static enum type check_expression(struct node *expr, struct method_scope *scope) {
    if (expr == NULL)
        return none_type;

    switch (expr->category) {
        case Natural:
            expr->type = integer_type;
            return expr->type;

        case Decimal:
            expr->type = double_type;
            return expr->type;

        case BoolLit:
            expr->type = bool_type;
            return expr->type;

        case Identifier: {
            struct symbol_list *local = search_symbol(scope->symbols, expr->token);
            if (local != NULL) {
                expr->type = local->type;
                return expr->type;
            }

            struct symbol_list *global = search_symbol(global_table, expr->token);
            if (global != NULL) {
                expr->type = global->type;
                return expr->type;
            }

            expr->type = undef_type;
            return expr->type;
        }

        case Length: {
            struct node *base = get_child(expr, 0);
            check_expression(base, scope);
            expr->type = integer_type;
            return expr->type;
        }

        case ParseArgs: {
            struct node *id = get_child(expr, 0);
            struct node *index = get_child(expr, 1);

            check_expression(id, scope);
            check_expression(index, scope);

            expr->type = integer_type;
            return expr->type;
        }

        case Call:
            return check_call(expr, scope);

        case Assign: {
            struct node *lhs = get_child(expr, 0);
            struct node *rhs = get_child(expr, 1);
            enum type ltype = check_expression(lhs, scope);
            enum type rtype = check_expression(rhs, scope);

            if (ltype == rtype)
                expr->type = ltype;
            else if (ltype == undef_type || rtype == undef_type)
                expr->type = undef_type;
            else
                expr->type = undef_type;

            return expr->type;
        }

        case Add:
        case Sub:
        case Mul:
        case Div:
        case Mod:
        case Lshift:
        case Rshift: {
            enum type left = check_expression(get_child(expr, 0), scope);
            enum type right = check_expression(get_child(expr, 1), scope);
            expr->type = unify_numeric_binary(left, right);
            return expr->type;
        }

        case Lt:
        case Gt:
        case Le:
        case Ge: {
            enum type left = check_expression(get_child(expr, 0), scope);
            enum type right = check_expression(get_child(expr, 1), scope);

            if (left == undef_type || right == undef_type)
                expr->type = undef_type;
            else if ((left == integer_type && right == integer_type) ||
                     (left == double_type && right == double_type))
                expr->type = bool_type;
            else
                expr->type = undef_type;

            return expr->type;
        }

        case Eq:
        case Ne: {
            enum type left = check_expression(get_child(expr, 0), scope);
            enum type right = check_expression(get_child(expr, 1), scope);

            if (left == undef_type || right == undef_type)
                expr->type = undef_type;
            else if (left == right)
                expr->type = bool_type;
            else
                expr->type = undef_type;

            return expr->type;
        }

        case And:
        case Or:
        case Xor: {
            enum type left = check_expression(get_child(expr, 0), scope);
            enum type right = check_expression(get_child(expr, 1), scope);

            if (left == bool_type && right == bool_type)
                expr->type = bool_type;
            else if (left == undef_type || right == undef_type)
                expr->type = undef_type;
            else
                expr->type = undef_type;

            return expr->type;
        }

        case Not: {
            enum type t = check_expression(get_child(expr, 0), scope);
            if (t == bool_type)
                expr->type = bool_type;
            else if (t == undef_type)
                expr->type = undef_type;
            else
                expr->type = undef_type;
            return expr->type;
        }

        case Minus:
        case Plus: {
            enum type t = check_expression(get_child(expr, 0), scope);
            if (t == integer_type || t == double_type)
                expr->type = t;
            else if (t == undef_type)
                expr->type = undef_type;
            else
                expr->type = undef_type;
            return expr->type;
        }

        default:
            expr->type = none_type;
            return expr->type;
    }
}

static void annotate_statement_or_decl(struct node *node, struct method_scope *scope) {
    struct node_list *child;

    if (node == NULL)
        return;

    switch (node->category) {
        case VarDecl:
            return;

        case Return: {
            struct node *value = get_child(node, 0);
            if (value != NULL)
                check_expression(value, scope);
            return;
        }

        case Print: {
            struct node *value = get_child(node, 0);
            if (value != NULL && value->category != StrLit)
                check_expression(value, scope);
            return;
        }

        case If: {
            check_expression(get_child(node, 0), scope);
            annotate_statement_or_decl(get_child(node, 1), scope);
            annotate_statement_or_decl(get_child(node, 2), scope);
            return;
        }

        case While: {
            check_expression(get_child(node, 0), scope);
            annotate_statement_or_decl(get_child(node, 1), scope);
            return;
        }

        case Block:
        case MethodBody:
            child = node->children->next;
            while (child != NULL) {
                annotate_statement_or_decl(child->node, scope);
                child = child->next;
            }
            return;

        default:
            if (is_expression_node(node->category))
                check_expression(node, scope);
            return;
    }
}

static void annotate_all_methods(void) {
    struct method_scope *m = method_scopes;
    while (m != NULL) {
        annotate_statement_or_decl(m->body, m);
        m = m->next;
    }
}

/* =========================================================
 * API principal
 * ========================================================= */

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

    annotate_all_methods();

    return semantic_errors;
}

/* =========================================================
 * Impressão
 * ========================================================= */

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
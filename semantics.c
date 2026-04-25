#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "semantics.h"

int semantic_errors = 0;

static char *class_name = NULL;
static struct symbol_list *global_table = NULL;
static struct method_scope *method_scopes = NULL;

/* =========================================================
 * Helpers
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

static int param_count(struct parameter_list *p) {
    int n = 0;
    while (p) {
        n++;
        p = p->next;
    }
    return n;
}

static int params_exact_match(struct parameter_list *a, struct parameter_list *b) {
    while (a && b) {
        if (a->type != b->type)
            return 0;
        a = a->next;
        b = b->next;
    }
    return a == NULL && b == NULL;
}

static int is_compatible_type(enum type formal, enum type actual) {
    if (formal == actual)
        return 1;
    if (formal == double_type && actual == integer_type)
        return 1;
    return 0;
}

static int params_compatible(struct parameter_list *formal, struct parameter_list *actual) {
    while (formal && actual) {
        if (!is_compatible_type(formal->type, actual->type))
            return 0;
        formal = formal->next;
        actual = actual->next;
    }
    return formal == NULL && actual == NULL;
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

static void semantic_error_node(struct node *node, const char *msg) {
    semantic_errors++;
    printf("Line %d, col %d: %s\n", node ? node->line : 0, node ? node->column : 0, msg);
}

static void semantic_error_symbol(struct node *node, const char *fmt, const char *tok) {
    char buf[512];
    snprintf(buf, sizeof(buf), fmt, tok);
    semantic_error_node(node, buf);
}

static void semantic_error_op1(struct node *node, const char *op, enum type t) {
    char buf[512];
    snprintf(buf, sizeof(buf), "Operator %s cannot be applied to type %s", op, type_name(t));
    semantic_error_node(node, buf);
}

static void semantic_error_op2(struct node *node, const char *op, enum type t1, enum type t2) {
    char buf[512];
    snprintf(buf, sizeof(buf), "Operator %s cannot be applied to types %s, %s", op, type_name(t1), type_name(t2));
    semantic_error_node(node, buf);
}

static void semantic_error_stmt(struct node *node, enum type t, const char *stmt) {
    char buf[512];
    snprintf(buf, sizeof(buf), "Incompatible type %s in %s statement", type_name(t), stmt);
    semantic_error_node(node, buf);
}

static char *remove_underscores(const char *s) {
    size_t n = strlen(s);
    char *r = (char *)malloc(n + 1);
    size_t j = 0;
    for (size_t i = 0; i < n; i++) {
        if (s[i] != '_')
            r[j++] = s[i];
    }
    r[j] = '\0';
    return r;
}

static int natural_out_of_bounds(const char *tok) {
    char *clean = remove_underscores(tok);
    errno = 0;
    long long v = strtoll(clean, NULL, 10);
    free(clean);

    if (errno == ERANGE)
        return 1;
    if (v > INT_MAX)
        return 1;
    return 0;
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

static char *param_list_to_string(struct parameter_list *params) {
    char buffer[512];
    buffer[0] = '\0';
    strcat(buffer, "(");

    while (params != NULL) {
        strcat(buffer, type_name(params->type));
        if (params->next != NULL)
            strcat(buffer, ",");
        params = params->next;
    }

    strcat(buffer, ")");
    return strdup(buffer);
}

static char *call_signature_string(char *name, struct parameter_list *params) {
    char buffer[512];
    char *plist = param_list_to_string(params);
    snprintf(buffer, sizeof(buffer), "%s%s", name, plist);
    free(plist);
    return strdup(buffer);
}

static void set_annotation_string(struct node *node, const char *text) {
    if (!node) return;
    if (node->annotation) {
        free(node->annotation);
        node->annotation = NULL;
    }
    node->annotation = strdup(text);
}

/* =========================================================
 * Recolha de símbolos
 * ========================================================= */

static void collect_field_decl(struct node *field_decl) {
    struct node *id = get_child(field_decl, 1);
    struct node *type_node = get_child(field_decl, 0);
    enum type type = category_to_type(type_node->category);

    if (search_symbol(global_table, id->token) != NULL) {
        semantic_error_symbol(id, "Symbol %s already defined", id->token);
        return;
    }

    append_symbol(&global_table, new_symbol(id->token, type, 0, field_decl));
}

static void collect_method_decl(struct node *method_decl) {
    struct node *header = get_child(method_decl, 0);
    struct node *body = get_child(method_decl, 1);

    struct node *return_type_node = get_child(header, 0);
    struct node *id = get_child(header, 1);
    struct node *params_node = get_child(header, 2);

    enum type return_type = category_to_type(return_type_node->category);
    struct parameter_list *params = build_method_param_types(params_node);

    struct symbol_list *cur = global_table;
    while (cur != NULL) {
        if (strcmp(cur->name, id->token) == 0 &&
            cur->node != NULL &&
            cur->node->category == MethodDecl &&
            params_exact_match(cur->params, params)) {
            char *sig = call_signature_string(id->token, params);
            semantic_error_symbol(id, "Symbol %s already defined", sig);
            free(sig);
            return;
        }
        cur = cur->next;
    }

    {
        struct symbol_list *method_symbol = new_symbol(id->token, return_type, 0, method_decl);
        method_symbol->params = params;
        append_symbol(&global_table, method_symbol);
    }

    {
        struct method_scope *scope = new_method_scope(id->token, return_type, params, method_decl, body);
        append_symbol(&scope->symbols, new_symbol("return", return_type, 0, method_decl));

        if (params_node && params_node->children) {
            struct node_list *child = params_node->children->next;
            while (child != NULL) {
                struct node *param_decl = child->node;
                struct node *ptype = get_child(param_decl, 0);
                struct node *pid = get_child(param_decl, 1);

                if (search_symbol(scope->symbols, pid->token) != NULL) {
                    semantic_error_symbol(pid, "Symbol %s already defined", pid->token);
                } else {
                    append_symbol(&scope->symbols,
                        new_symbol(pid->token, category_to_type(ptype->category), 1, param_decl));
                }

                child = child->next;
            }
        }

        append_method_scope(&method_scopes, scope);
    }
}

static void declare_local_var(struct method_scope *scope, struct node *var_decl) {
    struct node *id = get_child(var_decl, 1);
    struct node *type_node = get_child(var_decl, 0);
    enum type type = category_to_type(type_node->category);

    if (search_symbol(scope->symbols, id->token) != NULL) {
        semantic_error_symbol(id, "Symbol %s already defined", id->token);
        return;
    }

    append_symbol(&scope->symbols, new_symbol(id->token, type, 0, var_decl));
}

/* =========================================================
 * Resolução de métodos
 * ========================================================= */

static struct method_scope *resolve_exact_method(char *name, struct parameter_list *arg_types) {
    struct method_scope *m = method_scopes;
    while (m != NULL) {
        if (strcmp(m->name, name) == 0 && params_exact_match(m->params, arg_types))
            return m;
        m = m->next;
    }
    return NULL;
}

static struct method_scope *resolve_compatible_method_unique(char *name, struct parameter_list *arg_types, int *ambiguous) {
    struct method_scope *m = method_scopes;
    struct method_scope *found = NULL;
    *ambiguous = 0;

    while (m != NULL) {
        if (strcmp(m->name, name) == 0 &&
            param_count(m->params) == param_count(arg_types) &&
            params_compatible(m->params, arg_types)) {
            if (found != NULL) {
                *ambiguous = 1;
                return NULL;
            }
            found = m;
        }
        m = m->next;
    }

    return found;
}

/* =========================================================
 * Verificação de expressões
 * ========================================================= */

static enum type check_expression(struct node *expr, struct method_scope *scope);

static enum type check_identifier_expr(struct node *expr, struct method_scope *scope) {
    struct symbol_list *local = search_symbol(scope->symbols, expr->token);
    if (local != NULL) {
        expr->type = local->type;
        return expr->type;
    }

    {
        struct symbol_list *global = search_symbol(global_table, expr->token);
        if (global != NULL) {
            expr->type = global->type;
            return expr->type;
        }
    }

    semantic_error_symbol(expr, "Cannot find symbol %s", expr->token);
    expr->type = undef_type;
    return expr->type;
}

static enum type check_call(struct node *expr, struct method_scope *scope) {
    struct node *id = get_child(expr, 0);
    struct parameter_list *arg_types = NULL;
    struct node_list *arg = expr->children->next;

    if (arg != NULL)
        arg = arg->next;

    while (arg != NULL) {
        append_param(&arg_types, check_expression(arg->node, scope));
        arg = arg->next;
    }

    if (!id || !id->token) {
        expr->type = undef_type;
        return expr->type;
    }

    {
        struct method_scope *exact = resolve_exact_method(id->token, arg_types);
        if (exact != NULL) {
            char *sig = param_list_to_string(exact->params);
            set_annotation_string(id, sig);
            id->type = exact->return_type;
            expr->type = exact->return_type;
            free(sig);
            return expr->type;
        }
    }

    {
        int ambiguous = 0;
        struct method_scope *compat = resolve_compatible_method_unique(id->token, arg_types, &ambiguous);
        if (ambiguous) {
            semantic_error_symbol(id, "Reference to method %s is ambiguous", id->token);
            id->type = undef_type;
            expr->type = undef_type;
            return expr->type;
        }

        if (compat != NULL) {
            char *sig = param_list_to_string(compat->params);
            set_annotation_string(id, sig);
            id->type = compat->return_type;
            expr->type = compat->return_type;
            free(sig);
            return expr->type;
        }
    }

    {
        char *call_sig = call_signature_string(id->token, arg_types);
        semantic_error_symbol(id, "Cannot find symbol %s", call_sig);
        free(call_sig);
    }

    id->type = undef_type;
    expr->type = undef_type;
    return expr->type;
}

static enum type check_binary_numeric(struct node *expr, struct method_scope *scope, const char *op, int allow_double) {
    enum type left = check_expression(get_child(expr, 0), scope);
    enum type right = check_expression(get_child(expr, 1), scope);

    if (left == integer_type && right == integer_type) {
        expr->type = integer_type;
        return expr->type;
    }

    if (allow_double) {
        if ((left == double_type && right == double_type) ||
            (left == double_type && right == integer_type) ||
            (left == integer_type && right == double_type)) {
            expr->type = double_type;
            return expr->type;
        }
    }

    semantic_error_op2(expr, op, left, right);
    expr->type = undef_type;
    return expr->type;
}

static enum type check_expression(struct node *expr, struct method_scope *scope) {
    if (expr == NULL)
        return none_type;

    switch (expr->category) {
        case Natural:
            if (expr->token && natural_out_of_bounds(expr->token))
                semantic_error_symbol(expr, "Number %s out of bounds", expr->token);
            expr->type = integer_type;
            return expr->type;

        case Decimal:
            expr->type = double_type;
            return expr->type;

        case BoolLit:
            expr->type = bool_type;
            return expr->type;

        case Identifier:
            return check_identifier_expr(expr, scope);

        case Length: {
            struct node *base = get_child(expr, 0);
            enum type t = check_expression(base, scope);
            if (t != string_array_type)
                semantic_error_op1(expr, ".length", t);
            expr->type = integer_type;
            return expr->type;
        }

        case ParseArgs: {
            struct node *id = get_child(expr, 0);
            struct node *index = get_child(expr, 1);
            enum type t1 = check_expression(id, scope);
            enum type t2 = check_expression(index, scope);

            if (!(t1 == string_array_type && t2 == integer_type))
                semantic_error_op2(expr, "Integer.parseInt", t1, t2);

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

            if (!(ltype == rtype || (ltype == double_type && rtype == integer_type)))
                semantic_error_op2(expr, "=", ltype, rtype);

            expr->type = ltype;
            return expr->type;
        }

        case Add:
            return check_binary_numeric(expr, scope, "+", 1);
        case Sub:
            return check_binary_numeric(expr, scope, "-", 1);
        case Mul:
            return check_binary_numeric(expr, scope, "*", 1);
        case Div:
            return check_binary_numeric(expr, scope, "/", 1);
        case Mod:
            return check_binary_numeric(expr, scope, "%", 0);
        case Lshift:
            return check_binary_numeric(expr, scope, "<<", 0);
        case Rshift:
            return check_binary_numeric(expr, scope, ">>", 0);

        case Lt:
        case Gt:
        case Le:
        case Ge: {
            enum type left = check_expression(get_child(expr, 0), scope);
            enum type right = check_expression(get_child(expr, 1), scope);

            if ((left == integer_type || left == double_type) &&
                (right == integer_type || right == double_type)) {
                expr->type = bool_type;
            } else {
                const char *op =
                    expr->category == Lt ? "<" :
                    expr->category == Gt ? ">" :
                    expr->category == Le ? "<=" : ">=";
                semantic_error_op2(expr, op, left, right);
                expr->type = undef_type;
            }
            return expr->type;
        }

        case Eq:
        case Ne: {
            enum type left = check_expression(get_child(expr, 0), scope);
            enum type right = check_expression(get_child(expr, 1), scope);

            if (left == right ||
                ((left == integer_type || left == double_type) &&
                 (right == integer_type || right == double_type))) {
                expr->type = bool_type;
            } else {
                semantic_error_op2(expr, expr->category == Eq ? "==" : "!=", left, right);
                expr->type = undef_type;
            }
            return expr->type;
        }

        case And:
        case Or:
        case Xor: {
            enum type left = check_expression(get_child(expr, 0), scope);
            enum type right = check_expression(get_child(expr, 1), scope);

            if (left == bool_type && right == bool_type) {
                expr->type = bool_type;
            } else {
                const char *op =
                    expr->category == And ? "&&" :
                    expr->category == Or ? "||" : "^";
                semantic_error_op2(expr, op, left, right);
                expr->type = undef_type;
            }
            return expr->type;
        }

        case Not: {
            enum type t = check_expression(get_child(expr, 0), scope);
            if (t == bool_type) {
                expr->type = bool_type;
            } else {
                semantic_error_op1(expr, "!", t);
                expr->type = undef_type;
            }
            return expr->type;
        }

        case Minus:
        case Plus: {
            enum type t = check_expression(get_child(expr, 0), scope);
            if (t == integer_type || t == double_type) {
                expr->type = t;
            } else {
                semantic_error_op1(expr, expr->category == Minus ? "-" : "+", t);
                expr->type = undef_type;
            }
            return expr->type;
        }

        default:
            expr->type = none_type;
            return expr->type;
    }
}

/* =========================================================
 * Statements
 * ========================================================= */

static void annotate_statement_or_decl(struct node *node, struct method_scope *scope) {
    struct node_list *child;

    if (node == NULL)
        return;

    switch (node->category) {
        case VarDecl:
            declare_local_var(scope, node);
            return;

        case Return: {
            struct node *value = get_child(node, 0);
            if (value == NULL) {
                if (scope->return_type != void_type)
                    semantic_error_stmt(node, void_type, "return");
                return;
            }

            {
                enum type t = check_expression(value, scope);
                if (!(t == scope->return_type || (scope->return_type == double_type && t == integer_type)))
                    semantic_error_stmt(value, t, "return");
            }
            return;
        }

        case Print: {
            struct node *value = get_child(node, 0);
            if (value != NULL && value->category != StrLit) {
                enum type t = check_expression(value, scope);
                if (!(t == integer_type || t == double_type || t == bool_type))
                    semantic_error_stmt(value, t, "print");
            }
            return;
        }

        case If: {
            enum type t = check_expression(get_child(node, 0), scope);
            if (t != bool_type)
                semantic_error_stmt(get_child(node, 0), t, "if");
            annotate_statement_or_decl(get_child(node, 1), scope);
            annotate_statement_or_decl(get_child(node, 2), scope);
            return;
        }

        case While: {
            enum type t = check_expression(get_child(node, 0), scope);
            if (t != bool_type)
                semantic_error_stmt(get_child(node, 0), t, "while");
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
 * API
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
    }
    printf(")");
}

static void print_global_table(void) {
    struct symbol_list *s = global_table;

    printf("===== Class %s Symbol Table =====\n", class_name ? class_name : "");

    while (s != NULL) {
        if (s->node != NULL && s->node->category == MethodDecl) {
            printf("%s\t", s->name);
            print_param_list(s->params);
            printf("\t%s\n", type_name(s->type));
        } else {
            printf("%s\t%s\n", s->name, type_name(s->type));
        }
        s = s->next;
    }
}

static void print_method_table(struct method_scope *scope) {
    struct symbol_list *s;

    printf("===== Method %s", scope->name);
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
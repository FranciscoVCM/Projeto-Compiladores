#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "semantics.h"
#include "codegen.h"

static int temporary = 1;
static int label_counter = 1;
static int string_counter = 0;
static enum type current_return_type = no_type;
static int block_terminated = 0;

struct cg_value {
    enum type type;
    int reg;
};

struct cg_var {
    char *name;
    enum type type;
    char *ptr;
    int is_global;
    struct cg_var *next;
};

static struct cg_var *global_vars = NULL;
static struct cg_var *local_vars = NULL;

static char *strdup_safe(const char *s) {
    if (!s)
        return NULL;
    return strdup(s);
}

static void free_cg_vars(struct cg_var *vars) {
    while (vars) {
        struct cg_var *next = vars->next;
        free(vars->name);
        free(vars->ptr);
        free(vars);
        vars = next;
    }
}

static void clear_local_vars(void) {
    free_cg_vars(local_vars);
    local_vars = NULL;
}

static void add_cg_var(struct cg_var **list, const char *name, enum type type,
                       const char *ptr, int is_global) {
    struct cg_var *v = malloc(sizeof(struct cg_var));
    if (!v)
        exit(1);

    v->name = strdup_safe(name);
    v->type = type;
    v->ptr = strdup_safe(ptr);
    v->is_global = is_global;
    v->next = NULL;

    if (*list == NULL) {
        *list = v;
    } else {
        struct cg_var *cur = *list;
        while (cur->next)
            cur = cur->next;
        cur->next = v;
    }
}

static struct cg_var *find_local_var(const char *name) {
    struct cg_var *v = local_vars;

    while (v) {
        if (strcmp(v->name, name) == 0)
            return v;
        v = v->next;
    }

    return NULL;
}

static struct cg_var *find_global_var(const char *name) {
    struct cg_var *v = global_vars;

    while (v) {
        if (strcmp(v->name, name) == 0)
            return v;
        v = v->next;
    }

    return NULL;
}

static struct cg_var *find_var(const char *name) {
    struct cg_var *v = find_local_var(name);

    if (v)
        return v;

    return find_global_var(name);
}


struct cg_string {
    struct node *node;
    char *label;
    char *encoded;
    int length;
    struct cg_string *next;
};

static struct cg_string *string_literals = NULL;

static void append_encoded_byte(char *out, size_t out_size, unsigned char c) {
    char tmp[8];

    if (c >= 32 && c <= 126 && c != '\\' && c != '"') {
        size_t len = strlen(out);
        if (len + 1 < out_size) {
            out[len] = (char)c;
            out[len + 1] = '\0';
        }
    } else {
        snprintf(tmp, sizeof(tmp), "\\%02X", c);
        strncat(out, tmp, out_size - strlen(out) - 1);
    }
}

static char *encode_string_literal(const char *token, int *length_out) {
    size_t n = strlen(token);
    char *out = calloc(n * 4 + 8, sizeof(char));
    int len = 0;

    if (!out)
        exit(1);

    for (size_t i = 1; i + 1 < n; i++) {
        unsigned char c = (unsigned char)token[i];

        if (c == '\\' && i + 1 < n - 1) {
            i++;
            switch (token[i]) {
                case 'n':
                    c = '\n';
                    break;
                case 't':
                    c = '\t';
                    break;
                case 'r':
                    c = '\r';
                    break;
                case 'f':
                    c = '\f';
                    break;
                case '\\':
                    c = '\\';
                    break;
                case '"':
                    c = '"';
                    break;
                default:
                    c = (unsigned char)token[i];
                    break;
            }
        }

        append_encoded_byte(out, n * 4 + 8, c);
        len++;
    }

    strncat(out, "\\00", n * 4 + 8 - strlen(out) - 1);
    len++;

    *length_out = len;
    return out;
}

static struct cg_string *find_string_literal(struct node *node) {
    struct cg_string *s = string_literals;

    while (s) {
        if (s->node == node)
            return s;
        s = s->next;
    }

    return NULL;
}

static void add_string_literal(struct node *node) {
    struct cg_string *s;
    char label[64];
    int length = 0;

    if (!node || !node->token)
        return;

    if (find_string_literal(node))
        return;

    s = malloc(sizeof(struct cg_string));
    if (!s)
        exit(1);

    snprintf(label, sizeof(label), "@.strlit.%d", string_counter++);

    s->node = node;
    s->label = strdup(label);
    s->encoded = encode_string_literal(node->token, &length);
    s->length = length;
    s->next = NULL;

    if (string_literals == NULL) {
        string_literals = s;
    } else {
        struct cg_string *cur = string_literals;
        while (cur->next)
            cur = cur->next;
        cur->next = s;
    }
}

static void collect_string_literals(struct node *node) {
    struct node_list *child;

    if (!node)
        return;

    if (node->category == StrLit)
        add_string_literal(node);

    if (!node->children)
        return;

    child = node->children->next;
    while (child) {
        collect_string_literals(child->node);
        child = child->next;
    }
}

static void emit_string_literals(void) {
    struct cg_string *s = string_literals;

    while (s) {
        printf("%s = private constant [%d x i8] c\"%s\"\n",
               s->label, s->length, s->encoded);
        s = s->next;
    }

    if (string_literals)
        printf("\n");
}

static void free_string_literals(void) {
    struct cg_string *s = string_literals;

    while (s) {
        struct cg_string *next = s->next;
        free(s->label);
        free(s->encoded);
        free(s);
        s = next;
    }

    string_literals = NULL;
}


static const char *llvm_type(enum type type) {
    switch (type) {
        case integer_type:
            return "i32";
        case double_type:
            return "double";
        case bool_type:
            return "i1";
        case void_type:
            return "void";
        case string_array_type:
            return "i8**";
        case string_type:
            return "i8*";
        default:
            return "i32";
    }
}

static const char *llvm_zero(enum type type) {
    switch (type) {
        case integer_type:
            return "0";
        case double_type:
            return "0.000000e+00";
        case bool_type:
            return "0";
        default:
            return "0";
    }
}

static enum type type_from_type_node(struct node *type_node) {
    if (!type_node)
        return undef_type;

    return category_to_type(type_node->category);
}

static char *remove_underscores_codegen(const char *s) {
    size_t n = strlen(s);
    char *r = malloc(n + 1);
    size_t j = 0;

    if (!r)
        exit(1);

    for (size_t i = 0; i < n; i++) {
        if (s[i] != '_')
            r[j++] = s[i];
    }

    r[j] = '\0';
    return r;
}


static void append_param_mangle(char *buffer, size_t size, enum type type) {
    switch (type) {
        case integer_type:
            strncat(buffer, "_int", size - strlen(buffer) - 1);
            break;
        case double_type:
            strncat(buffer, "_double", size - strlen(buffer) - 1);
            break;
        case bool_type:
            strncat(buffer, "_boolean", size - strlen(buffer) - 1);
            break;
        case string_array_type:
            strncat(buffer, "_StringArray", size - strlen(buffer) - 1);
            break;
        default:
            strncat(buffer, "_undef", size - strlen(buffer) - 1);
            break;
    }
}

static char *mangle_method_decl(struct node *method_decl) {
    char buffer[512];
    struct node *header = getchild(method_decl, 0);
    struct node *id = getchild(header, 1);
    struct node *params = getchild(header, 2);
    struct node_list *child;

    snprintf(buffer, sizeof(buffer), "@_%s", id->token);

    if (params && params->children) {
        child = params->children->next;
        while (child) {
            struct node *param = child->node;
            struct node *ptype = getchild(param, 0);
            append_param_mangle(buffer, sizeof(buffer),
                                type_from_type_node(ptype));
            child = child->next;
        }
    }

    return strdup(buffer);
}

static int parse_annotation_types(const char *annotation, enum type *types, int max_types) {
    int count = 0;
    const char *p = annotation;

    if (!annotation)
        return 0;

    while (*p && *p != '(')
        p++;

    if (*p == '(')
        p++;

    while (*p && *p != ')' && count < max_types) {
        if (strncmp(p, "int", 3) == 0) {
            types[count++] = integer_type;
            p += 3;
        } else if (strncmp(p, "double", 6) == 0) {
            types[count++] = double_type;
            p += 6;
        } else if (strncmp(p, "boolean", 7) == 0) {
            types[count++] = bool_type;
            p += 7;
        } else if (strncmp(p, "String[]", 8) == 0) {
            types[count++] = string_array_type;
            p += 8;
        } else {
            p++;
        }

        if (*p == ',')
            p++;
    }

    return count;
}

static char *mangle_method_call(struct node *id) {
    char buffer[512];
    enum type types[128];
    int n;

    snprintf(buffer, sizeof(buffer), "@_%s", id->token);

    n = parse_annotation_types(id->annotation, types, 128);
    for (int i = 0; i < n; i++)
        append_param_mangle(buffer, sizeof(buffer), types[i]);

    return strdup(buffer);
}


static int method_is_main_string_array(struct node *method_decl) {
    struct node *header = getchild(method_decl, 0);
    struct node *id = getchild(header, 1);
    struct node *params = getchild(header, 2);
    struct node *first_param;
    struct node *ptype;

    if (!id || strcmp(id->token, "main") != 0)
        return 0;

    if (!params || childcount(params) != 1)
        return 0;

    first_param = getchild(params, 0);
    ptype = getchild(first_param, 0);

    return ptype && ptype->category == StringArray;
}

static struct node *find_main_method(struct node *program) {
    struct node_list *child;

    if (!program || !program->children)
        return NULL;

    child = program->children->next;
    while (child) {
        if (child->node->category == MethodDecl &&
            method_is_main_string_array(child->node)) {
            return child->node;
        }

        child = child->next;
    }

    return NULL;
}


static void codegen_global_field(struct node *field_decl) {
    struct node *type_node = getchild(field_decl, 0);
    struct node *id = getchild(field_decl, 1);
    enum type type = type_from_type_node(type_node);

    if (!id || !id->token)
        return;

    printf("@%s = global %s %s\n", id->token, llvm_type(type), llvm_zero(type));

    {
        char ptr[512];
        snprintf(ptr, sizeof(ptr), "@%s", id->token);
        add_cg_var(&global_vars, id->token, type, ptr, 1);
    }
}

static void codegen_global_fields(struct node *program) {
    struct node_list *child;

    if (!program || !program->children)
        return;

    child = program->children->next;
    while (child) {
        if (child->node->category == FieldDecl)
            codegen_global_field(child->node);

        child = child->next;
    }
}


static void codegen_function_parameters_signature(struct node *params) {
    int first = 1;
    struct node_list *child;

    if (!params || !params->children)
        return;

    child = params->children->next;
    while (child) {
        struct node *param = child->node;
        struct node *type_node = getchild(param, 0);
        struct node *id = getchild(param, 1);
        enum type type = type_from_type_node(type_node);

        if (!first)
            printf(", ");

        if (type == string_array_type) {
            printf("i32 %%%s.argc, i8** %%%s.argv", id->token, id->token);
        } else {
            printf("%s %%%s.param", llvm_type(type), id->token);
        }

        first = 0;
        child = child->next;
    }
}

static void codegen_alloc_parameter(struct node *param) {
    struct node *type_node = getchild(param, 0);
    struct node *id = getchild(param, 1);
    enum type type = type_from_type_node(type_node);

    if (!id || !id->token)
        return;

    if (type == string_array_type) {
        char ptr[512];
        snprintf(ptr, sizeof(ptr), "%%%s.argv", id->token);
        add_cg_var(&local_vars, id->token, type, ptr, 0);
        return;
    }

    printf("  %%%s = alloca %s\n", id->token, llvm_type(type));
    printf("  store %s %%%s.param, %s* %%%s\n",
           llvm_type(type), id->token, llvm_type(type), id->token);

    {
        char ptr[512];
        snprintf(ptr, sizeof(ptr), "%%%s", id->token);
        add_cg_var(&local_vars, id->token, type, ptr, 0);
    }
}

static void codegen_alloc_parameters(struct node *params) {
    struct node_list *child;

    if (!params || !params->children)
        return;

    child = params->children->next;
    while (child) {
        codegen_alloc_parameter(child->node);
        child = child->next;
    }
}

static void codegen_alloc_local_var(struct node *var_decl) {
    struct node *type_node = getchild(var_decl, 0);
    struct node *id = getchild(var_decl, 1);
    enum type type = type_from_type_node(type_node);

    if (!id || !id->token)
        return;

    printf("  %%%s = alloca %s\n", id->token, llvm_type(type));

    {
        char ptr[512];
        snprintf(ptr, sizeof(ptr), "%%%s", id->token);
        add_cg_var(&local_vars, id->token, type, ptr, 0);
    }
}

static void codegen_alloc_locals_from_body(struct node *body) {
    struct node_list *child;

    if (!body || !body->children)
        return;

    child = body->children->next;
    while (child) {
        if (child->node->category == VarDecl)
            codegen_alloc_local_var(child->node);

        child = child->next;
    }
}


static struct cg_value codegen_expression(struct node *expr);

static struct cg_value make_value(enum type type, int reg) {
    struct cg_value v;
    v.type = type;
    v.reg = reg;
    return v;
}

static struct cg_value cast_value(struct cg_value value, enum type target) {
    if (value.type == target)
        return value;

    if (value.type == integer_type && target == double_type) {
        int tmp = temporary++;
        printf("  %%%d = sitofp i32 %%%d to double\n", tmp, value.reg);
        return make_value(double_type, tmp);
    }

    return value;
}

static struct cg_value codegen_natural(struct node *natural) {
    char *clean = remove_underscores_codegen(natural->token);
    int tmp = temporary++;

    printf("  %%%d = add i32 %s, 0\n", tmp, clean);

    free(clean);
    return make_value(integer_type, tmp);
}

static struct cg_value codegen_decimal(struct node *decimal) {
    char *clean = remove_underscores_codegen(decimal->token);
    double value = strtod(clean, NULL);
    int tmp = temporary++;

    printf("  %%%d = fadd double %.17e, 0.000000e+00\n", tmp, value);

    free(clean);
    return make_value(double_type, tmp);
}

static struct cg_value codegen_boollit(struct node *boollit) {
    int tmp = temporary++;
    int value = strcmp(boollit->token, "true") == 0 ? 1 : 0;

    printf("  %%%d = icmp ne i1 %d, 0\n", tmp, value);

    return make_value(bool_type, tmp);
}

static struct cg_value codegen_identifier(struct node *id) {
    struct cg_var *v = find_var(id->token);
    int tmp;

    if (!v)
        return make_value(undef_type, -1);

    if (v->type == string_array_type)
        return make_value(string_array_type, -1);

    tmp = temporary++;
    printf("  %%%d = load %s, %s* %s\n",
           tmp, llvm_type(v->type), llvm_type(v->type), v->ptr);

    return make_value(v->type, tmp);
}

static struct cg_value codegen_length(struct node *expr) {
    struct node *base = getchild(expr, 0);
    int tmp;
    if (base && base->category == Identifier) {
        tmp = temporary++;
        printf("  %%%d = sub i32 %%%s.argc, 1\n", tmp, base->token);
        return make_value(integer_type, tmp);
    }

    return make_value(integer_type, -1);
}

static struct cg_value codegen_parseargs(struct node *expr) {
    struct node *id = getchild(expr, 0);
    struct node *index_expr = getchild(expr, 1);
    struct cg_value index;
    int plus_one;
    int idx64;
    int ptr;
    int str;
    int result;

    if (!id || !index_expr)
        return make_value(integer_type, -1);

    index = codegen_expression(index_expr);

    plus_one = temporary++;
    printf("  %%%d = add i32 %%%d, 1\n", plus_one, index.reg);

    idx64 = temporary++;
    printf("  %%%d = sext i32 %%%d to i64\n", idx64, plus_one);

    ptr = temporary++;
    printf("  %%%d = getelementptr inbounds i8*, i8** %%%s.argv, i64 %%%d\n",
           ptr, id->token, idx64);

    str = temporary++;
    printf("  %%%d = load i8*, i8** %%%d\n", str, ptr);

    result = temporary++;
    printf("  %%%d = call i32 @atoi(i8* %%%d)\n", result, str);

    return make_value(integer_type, result);
}

static struct cg_value codegen_assignment(struct node *assign) {
    struct node *lhs = getchild(assign, 0);
    struct node *rhs = getchild(assign, 1);
    struct cg_var *var;
    struct cg_value value;

    if (!lhs || !rhs || lhs->category != Identifier)
        return make_value(undef_type, -1);

    var = find_var(lhs->token);
    if (!var)
        return make_value(undef_type, -1);

    value = codegen_expression(rhs);
    value = cast_value(value, var->type);

    printf("  store %s %%%d, %s* %s\n",
           llvm_type(var->type), value.reg, llvm_type(var->type), var->ptr);

    return make_value(var->type, value.reg);
}

static struct cg_value codegen_unary(struct node *expr) {
    struct cg_value v = codegen_expression(getchild(expr, 0));

    switch (expr->category) {
        case Plus:
            return v;

        case Minus:
            if (v.type == double_type) {
                int tmp = temporary++;
                printf("  %%%d = fsub double 0.000000e+00, %%%d\n", tmp, v.reg);
                return make_value(double_type, tmp);
            } else {
                int tmp = temporary++;
                printf("  %%%d = sub i32 0, %%%d\n", tmp, v.reg);
                return make_value(integer_type, tmp);
            }

        case Not: {
            int tmp = temporary++;
            printf("  %%%d = xor i1 %%%d, true\n", tmp, v.reg);
            return make_value(bool_type, tmp);
        }

        default:
            return v;
    }
}

static struct cg_value codegen_arithmetic(struct node *expr) {
    struct cg_value left = codegen_expression(getchild(expr, 0));
    struct cg_value right = codegen_expression(getchild(expr, 1));
    enum type result_type = expr->type;
    int tmp;

    if (result_type == double_type) {
        left = cast_value(left, double_type);
        right = cast_value(right, double_type);

        tmp = temporary++;

        switch (expr->category) {
            case Add:
                printf("  %%%d = fadd double %%%d, %%%d\n", tmp, left.reg, right.reg);
                break;
            case Sub:
                printf("  %%%d = fsub double %%%d, %%%d\n", tmp, left.reg, right.reg);
                break;
            case Mul:
                printf("  %%%d = fmul double %%%d, %%%d\n", tmp, left.reg, right.reg);
                break;
            case Div:
                printf("  %%%d = fdiv double %%%d, %%%d\n", tmp, left.reg, right.reg);
                break;
            default:
                break;
        }

        return make_value(double_type, tmp);
    }

    tmp = temporary++;

    switch (expr->category) {
        case Add:
            printf("  %%%d = add i32 %%%d, %%%d\n", tmp, left.reg, right.reg);
            break;
        case Sub:
            printf("  %%%d = sub i32 %%%d, %%%d\n", tmp, left.reg, right.reg);
            break;
        case Mul:
            printf("  %%%d = mul i32 %%%d, %%%d\n", tmp, left.reg, right.reg);
            break;
        case Div:
            printf("  %%%d = sdiv i32 %%%d, %%%d\n", tmp, left.reg, right.reg);
            break;
        case Mod:
            printf("  %%%d = srem i32 %%%d, %%%d\n", tmp, left.reg, right.reg);
            break;
        default:
            break;
    }

    return make_value(integer_type, tmp);
}

static struct cg_value codegen_shift_or_xor(struct node *expr) {
    struct cg_value left = codegen_expression(getchild(expr, 0));
    struct cg_value right = codegen_expression(getchild(expr, 1));
    int tmp = temporary++;

    if (expr->category == Lshift) {
        printf("  %%%d = shl i32 %%%d, %%%d\n", tmp, left.reg, right.reg);
        return make_value(integer_type, tmp);
    }

    if (expr->category == Rshift) {
        printf("  %%%d = ashr i32 %%%d, %%%d\n", tmp, left.reg, right.reg);
        return make_value(integer_type, tmp);
    }

    if (expr->type == bool_type) {
        printf("  %%%d = xor i1 %%%d, %%%d\n", tmp, left.reg, right.reg);
        return make_value(bool_type, tmp);
    }

    printf("  %%%d = xor i32 %%%d, %%%d\n", tmp, left.reg, right.reg);
    return make_value(integer_type, tmp);
}

static struct cg_value codegen_boolean_binary(struct node *expr) {
    struct cg_value left = codegen_expression(getchild(expr, 0));
    struct cg_value right = codegen_expression(getchild(expr, 1));
    int tmp = temporary++;

    if (expr->category == And)
        printf("  %%%d = and i1 %%%d, %%%d\n", tmp, left.reg, right.reg);
    else
        printf("  %%%d = or i1 %%%d, %%%d\n", tmp, left.reg, right.reg);

    return make_value(bool_type, tmp);
}

static struct cg_value codegen_relational(struct node *expr) {
    struct cg_value left = codegen_expression(getchild(expr, 0));
    struct cg_value right = codegen_expression(getchild(expr, 1));
    int tmp;

    if (left.type == double_type || right.type == double_type) {
        left = cast_value(left, double_type);
        right = cast_value(right, double_type);

        tmp = temporary++;

        switch (expr->category) {
            case Lt:
                printf("  %%%d = fcmp olt double %%%d, %%%d\n", tmp, left.reg, right.reg);
                break;
            case Gt:
                printf("  %%%d = fcmp ogt double %%%d, %%%d\n", tmp, left.reg, right.reg);
                break;
            case Le:
                printf("  %%%d = fcmp ole double %%%d, %%%d\n", tmp, left.reg, right.reg);
                break;
            case Ge:
                printf("  %%%d = fcmp oge double %%%d, %%%d\n", tmp, left.reg, right.reg);
                break;
            default:
                break;
        }
    } else {
        tmp = temporary++;

        switch (expr->category) {
            case Lt:
                printf("  %%%d = icmp slt i32 %%%d, %%%d\n", tmp, left.reg, right.reg);
                break;
            case Gt:
                printf("  %%%d = icmp sgt i32 %%%d, %%%d\n", tmp, left.reg, right.reg);
                break;
            case Le:
                printf("  %%%d = icmp sle i32 %%%d, %%%d\n", tmp, left.reg, right.reg);
                break;
            case Ge:
                printf("  %%%d = icmp sge i32 %%%d, %%%d\n", tmp, left.reg, right.reg);
                break;
            default:
                break;
        }
    }

    return make_value(bool_type, tmp);
}

static struct cg_value codegen_equality(struct node *expr) {
    struct cg_value left = codegen_expression(getchild(expr, 0));
    struct cg_value right = codegen_expression(getchild(expr, 1));
    int tmp;

    if (left.type == double_type || right.type == double_type) {
        left = cast_value(left, double_type);
        right = cast_value(right, double_type);

        tmp = temporary++;

        if (expr->category == Eq)
            printf("  %%%d = fcmp oeq double %%%d, %%%d\n", tmp, left.reg, right.reg);
        else
            printf("  %%%d = fcmp one double %%%d, %%%d\n", tmp, left.reg, right.reg);
    } else if (left.type == bool_type) {
        tmp = temporary++;

        if (expr->category == Eq)
            printf("  %%%d = icmp eq i1 %%%d, %%%d\n", tmp, left.reg, right.reg);
        else
            printf("  %%%d = icmp ne i1 %%%d, %%%d\n", tmp, left.reg, right.reg);
    } else {
        tmp = temporary++;

        if (expr->category == Eq)
            printf("  %%%d = icmp eq i32 %%%d, %%%d\n", tmp, left.reg, right.reg);
        else
            printf("  %%%d = icmp ne i32 %%%d, %%%d\n", tmp, left.reg, right.reg);
    }

    return make_value(bool_type, tmp);
}

static struct cg_value codegen_call(struct node *call) {
    struct node *id = getchild(call, 0);
    enum type formal_types[128];
    int formal_count = 0;
    int arg_count = 0;
    struct cg_value args[128];
    char *name;
    int tmp = -1;

    if (!id)
        return make_value(undef_type, -1);

    formal_count = parse_annotation_types(id->annotation, formal_types, 128);

    for (int i = 1; getchild(call, i) != NULL; i++) {
        struct node *arg = getchild(call, i);
        args[arg_count] = codegen_expression(arg);

        if (arg_count < formal_count)
            args[arg_count] = cast_value(args[arg_count], formal_types[arg_count]);

        arg_count++;
    }

    name = mangle_method_call(id);

    if (call->type == void_type) {
        printf("  call void %s(", name);
    } else {
        tmp = temporary++;
        printf("  %%%d = call %s %s(", tmp, llvm_type(call->type), name);
    }

    for (int i = 0; i < arg_count; i++) {
        if (i > 0)
            printf(", ");

        printf("%s %%%d", llvm_type(args[i].type), args[i].reg);
    }

    printf(")\n");

    free(name);
    return make_value(call->type, tmp);
}

static struct cg_value codegen_expression(struct node *expr) {
    if (!expr)
        return make_value(undef_type, -1);

    switch (expr->category) {
        case Natural:
            return codegen_natural(expr);

        case Decimal:
            return codegen_decimal(expr);

        case BoolLit:
            return codegen_boollit(expr);

        case Identifier:
            return codegen_identifier(expr);

        case Length:
            return codegen_length(expr);

        case ParseArgs:
            return codegen_parseargs(expr);

        case Assign:
            return codegen_assignment(expr);

        case Plus:
        case Minus:
        case Not:
            return codegen_unary(expr);

        case Add:
        case Sub:
        case Mul:
        case Div:
        case Mod:
            return codegen_arithmetic(expr);

        case Lshift:
        case Rshift:
        case Xor:
            return codegen_shift_or_xor(expr);

        case And:
        case Or:
            return codegen_boolean_binary(expr);

        case Lt:
        case Gt:
        case Le:
        case Ge:
            return codegen_relational(expr);

        case Eq:
        case Ne:
            return codegen_equality(expr);

        case Call:
            return codegen_call(expr);

        default:
            return make_value(undef_type, -1);
    }
}


static void emit_printf_format(const char *fmt_label, int fmt_len,
                               const char *arg_type, const char *arg_value) {
    int tmp = temporary++;

    printf("  %%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds "
           "([%d x i8], [%d x i8]* %s, i32 0, i32 0), %s %s)\n",
           tmp, fmt_len, fmt_len, fmt_label, arg_type, arg_value);
}

static void codegen_print_string_node(struct node *str_node) {
    struct cg_string *s = find_string_literal(str_node);
    char arg[512];

    if (!s)
        return;

    snprintf(arg, sizeof(arg),
             "getelementptr inbounds ([%d x i8], [%d x i8]* %s, i32 0, i32 0)",
             s->length, s->length, s->label);

    emit_printf_format("@.fmt_str", 3, "i8*", arg);
}

static void codegen_print_boolean(struct cg_value value) {
    int label = label_counter++;

    printf("  br i1 %%%d, label %%L%dprint_true, label %%L%dprint_false\n\n",
           value.reg, label, label);

    printf("L%dprint_true:\n", label);
    emit_printf_format("@.fmt_str", 3, "i8*",
                       "getelementptr inbounds ([5 x i8], [5 x i8]* @.str_true, i32 0, i32 0)");
    printf("  br label %%L%dprint_end\n\n", label);

    printf("L%dprint_false:\n", label);
    emit_printf_format("@.fmt_str", 3, "i8*",
                       "getelementptr inbounds ([6 x i8], [6 x i8]* @.str_false, i32 0, i32 0)");
    printf("  br label %%L%dprint_end\n\n", label);

    printf("L%dprint_end:\n", label);
}

static void codegen_print(struct node *print_node) {
    struct node *value_node = getchild(print_node, 0);
    struct cg_value value;
    char reg[64];

    if (!value_node)
        return;

    if (value_node->category == StrLit) {
        codegen_print_string_node(value_node);
        return;
    }

    value = codegen_expression(value_node);

    snprintf(reg, sizeof(reg), "%%%d", value.reg);

    if (value.type == integer_type) {
        emit_printf_format("@.fmt_int", 3, "i32", reg);
    } else if (value.type == double_type) {
        emit_printf_format("@.fmt_double", 6, "double", reg);
    } else if (value.type == bool_type) {
        codegen_print_boolean(value);
    }
}


static void codegen_return(struct node *ret) {
    struct node *value_node = getchild(ret, 0);
    struct cg_value value;

    if (current_return_type == void_type || value_node == NULL) {
        printf("  ret void\n");
        block_terminated = 1;
        return;
    }

    value = codegen_expression(value_node);
    value = cast_value(value, current_return_type);

    printf("  ret %s %%%d\n", llvm_type(current_return_type), value.reg);
    block_terminated = 1;
}

static void codegen_statement(struct node *stmt);
static void codegen_block_like(struct node *node);

static void codegen_block_like(struct node *node) {
    struct node_list *child;

    if (!node || block_terminated)
        return;

    if (node->category != Block) {
        codegen_statement(node);
        return;
    }

    child = node->children->next;
    while (child && !block_terminated) {
        codegen_statement(child->node);
        child = child->next;
    }
}

static void codegen_if(struct node *if_node) {
    int label = label_counter++;
    struct node *condition = getchild(if_node, 0);
    struct node *then_stmt = getchild(if_node, 1);
    struct node *else_stmt = getchild(if_node, 2);
    struct cg_value cond;

    cond = codegen_expression(condition);

    printf("  br i1 %%%d, label %%L%d_if_then, label %%L%d_if_else\n\n",
           cond.reg, label, label);

    printf("L%d_if_then:\n", label);
    block_terminated = 0;
    codegen_block_like(then_stmt);
    if (!block_terminated)
        printf("  br label %%L%d_if_end\n", label);
    printf("\n");

    printf("L%d_if_else:\n", label);
    block_terminated = 0;
    codegen_block_like(else_stmt);
    if (!block_terminated)
        printf("  br label %%L%d_if_end\n", label);
    printf("\n");

    printf("L%d_if_end:\n", label);
    block_terminated = 0;
}

static void codegen_while(struct node *while_node) {
    int label = label_counter++;
    struct node *condition = getchild(while_node, 0);
    struct node *body = getchild(while_node, 1);
    struct cg_value cond;

    printf("  br label %%L%d_while_cond\n\n", label);

    printf("L%d_while_cond:\n", label);
    cond = codegen_expression(condition);
    printf("  br i1 %%%d, label %%L%d_while_body, label %%L%d_while_end\n\n",
           cond.reg, label, label);

    printf("L%d_while_body:\n", label);
    block_terminated = 0;
    codegen_block_like(body);

    if (!block_terminated)
        printf("  br label %%L%d_while_cond\n", label);

    printf("\n");

    printf("L%d_while_end:\n", label);
    block_terminated = 0;
}

static void codegen_statement(struct node *stmt) {
    if (!stmt || block_terminated)
        return;

    switch (stmt->category) {
        case Assign:
        case Call:
        case ParseArgs:
            codegen_expression(stmt);
            break;

        case Print:
            codegen_print(stmt);
            break;

        case Return:
            codegen_return(stmt);
            break;

        case If:
            codegen_if(stmt);
            break;

        case While:
            codegen_while(stmt);
            break;

        case Block:
            codegen_block_like(stmt);
            break;

        default:
            break;
    }
}

static void codegen_body_statements(struct node *body) {
    struct node_list *child;

    if (!body || !body->children)
        return;

    child = body->children->next;
    while (child && !block_terminated) {
        if (child->node->category != VarDecl)
            codegen_statement(child->node);

        child = child->next;
    }
}


static void codegen_default_return(enum type return_type) {
    if (return_type == void_type) {
        printf("  ret void\n");
    } else {
        printf("  ret %s %s\n", llvm_type(return_type), llvm_zero(return_type));
    }
}

static void codegen_method(struct node *method_decl) {
    struct node *header = getchild(method_decl, 0);
    struct node *body = getchild(method_decl, 1);

    struct node *return_type_node = getchild(header, 0);
    struct node *params = getchild(header, 2);

    enum type return_type = type_from_type_node(return_type_node);
    char *llvm_name = mangle_method_decl(method_decl);

    temporary = 1;
    label_counter = 1;
    current_return_type = return_type;
    block_terminated = 0;
    clear_local_vars();

    printf("define %s %s(", llvm_type(return_type), llvm_name);
    codegen_function_parameters_signature(params);
    printf(") {\n");

    codegen_alloc_parameters(params);
    codegen_alloc_locals_from_body(body);

    codegen_body_statements(body);

    if (!block_terminated)
        codegen_default_return(return_type);

    printf("}\n\n");

    free(llvm_name);
    clear_local_vars();
}

static void codegen_methods(struct node *program) {
    struct node_list *child;

    if (!program || !program->children)
        return;

    child = program->children->next;
    while (child) {
        if (child->node->category == MethodDecl)
            codegen_method(child->node);

        child = child->next;
    }
}


static void codegen_entry_point(struct node *program) {
    struct node *main_method = find_main_method(program);

    printf("define i32 @main(i32 %%argc, i8** %%argv) {\n");

    if (main_method) {
        char *main_name = mangle_method_decl(main_method);
        struct node *header = getchild(main_method, 0);
        struct node *return_type_node = getchild(header, 0);
        enum type ret_type = type_from_type_node(return_type_node);

        if (ret_type == void_type) {
            printf("  call void %s(i32 %%argc, i8** %%argv)\n", main_name);
            printf("  ret i32 0\n");
        } else {
            printf("  %%1 = call %s %s(i32 %%argc, i8** %%argv)\n",
                   llvm_type(ret_type), main_name);

            if (ret_type == integer_type)
                printf("  ret i32 %%1\n");
            else
                printf("  ret i32 0\n");
        }

        free(main_name);
    } else {
        printf("  ret i32 0\n");
    }

    printf("}\n");
}


void codegen_program(struct node *program) {
    collect_string_literals(program);

    printf("declare i32 @printf(i8*, ...)\n");
    printf("declare i32 @atoi(i8*)\n\n");

    printf("@.fmt_int = private constant [3 x i8] c\"%%d\\00\"\n");
    printf("@.fmt_double = private constant [6 x i8] c\"%%.16e\\00\"\n");
    printf("@.fmt_str = private constant [3 x i8] c\"%%s\\00\"\n");
    printf("@.str_true = private constant [5 x i8] c\"true\\00\"\n");
    printf("@.str_false = private constant [6 x i8] c\"false\\00\"\n");

    if (string_literals)
        printf("\n");

    emit_string_literals();

    codegen_global_fields(program);

    if (global_vars)
        printf("\n");

    codegen_methods(program);
    codegen_entry_point(program);

    free_cg_vars(global_vars);
    global_vars = NULL;

    free_string_literals();
}
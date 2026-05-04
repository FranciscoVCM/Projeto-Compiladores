#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "semantics.h"
#include "codegen.h"

static int temporary = 1;
static int label_counter = 1;
static int string_counter = 0;

/* tabela de variáveis para codegen */

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

/* tipos llvm e nomes */

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

/* globais */

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

/* params e variaveis locais */

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

/* statements */

static void codegen_statement(struct node *stmt) {
    (void)stmt;
}

static void codegen_body_statements(struct node *body) {
    struct node_list *child;

    if (!body || !body->children)
        return;

    child = body->children->next;
    while (child) {
        if (child->node->category != VarDecl)
            codegen_statement(child->node);

        child = child->next;
    }
}

/* funcoes */

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
    clear_local_vars();

    printf("define %s %s(", llvm_type(return_type), llvm_name);
    codegen_function_parameters_signature(params);
    printf(") {\n");

    codegen_alloc_parameters(params);
    codegen_alloc_locals_from_body(body);

    codegen_body_statements(body);

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

            if (ret_type == integer_type) {
                printf("  ret i32 %%1\n");
            } else {
                printf("  ret i32 0\n");
            }
        }

        free(main_name);
    } else {
        printf("  ret i32 0\n");
    }

    printf("}\n");
}

void codegen_program(struct node *program) {
    printf("declare i32 @printf(i8*, ...)\n");
    printf("declare i32 @atoi(i8*)\n\n");

    printf("@.fmt_int = private constant [3 x i8] c\"%%d\\00\"\n");
    printf("@.fmt_double = private constant [6 x i8] c\"%%.16e\\00\"\n");
    printf("@.fmt_str = private constant [3 x i8] c\"%%s\\00\"\n");
    printf("@.str_true = private constant [5 x i8] c\"true\\00\"\n");
    printf("@.str_false = private constant [6 x i8] c\"false\\00\"\n\n");

    codegen_global_fields(program);

    if (global_vars)
        printf("\n");

    codegen_methods(program);
    codegen_entry_point(program);

    free_cg_vars(global_vars);
    global_vars = NULL;
}
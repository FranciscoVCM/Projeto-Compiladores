#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantics.h"
#include "codegen.h"

int temporary;   // sequence of temporary registers in a function

extern struct symbol_list *symbol_table;

int temporary;
int label_counter;
int codegen_expression(struct node *expression);

int codegen_if(struct node *ifnode) {
    int label = label_counter++;

    struct node *condition = getchild(ifnode, 0);
    struct node *then_expr = getchild(ifnode, 1);
    struct node *else_expr = getchild(ifnode, 2);

    int result_ptr = temporary++;
    printf("  %%%d = alloca i32\n", result_ptr);

    int cond_tmp = codegen_expression(condition);

    int bool_tmp = temporary++;
    printf("  %%%d = icmp ne i32 %%%d, 0\n", bool_tmp, cond_tmp);

    printf("  br i1 %%%d, label %%L%dthen, label %%L%delse\n\n",
           bool_tmp, label, label);

    printf("L%dthen:\n", label);
    int then_tmp = codegen_expression(then_expr);
    printf("  store i32 %%%d, i32* %%%d\n", then_tmp, result_ptr);
    printf("  br label %%L%dend\n\n", label);

    printf("L%delse:\n", label);
    int else_tmp = codegen_expression(else_expr);
    printf("  store i32 %%%d, i32* %%%d\n", else_tmp, result_ptr);
    printf("  br label %%L%dend\n\n", label);

    printf("L%dend:\n", label);
    int final_tmp = temporary++;
    printf("  %%%d = load i32, i32* %%%d\n", final_tmp, result_ptr);

    return final_tmp;
}

int codegen_call(struct node *call) {
    struct node *id = getchild(call, 0);
    struct node *arguments = getchild(call, 1);
    int args[128];
    int argc = 0;
    struct node *arg;

    if (arguments != NULL) {
        while ((arg = getchild(arguments, argc)) != NULL) {
            args[argc] = codegen_expression(arg);
            argc++;
        }
    }

    printf("  %%%d = call i32 @_%s(", temporary, id->token);

    for (int i = 0; i < argc; i++) {
        if (i > 0)
            printf(", ");
        printf("i32 %%%d", args[i]);
    }

    printf(")\n");

    return temporary++;
}

int codegen_natural(struct node *natural) {
    printf("  %%%d = add i32 %s, 0\n", temporary, natural->token);
    return temporary++;
}

int codegen_identifier(struct node *identifier) {
    printf("  %%%d = add i32 %%%s, 0\n", temporary, identifier->token);
    return temporary++;
}

int codegen_binary_operation(struct node *expression, const char *llvm_op) {
    int left = codegen_expression(getchild(expression, 0));
    int right = codegen_expression(getchild(expression, 1));

    printf("  %%%d = %s i32 %%%d, %%%d\n", temporary, llvm_op, left, right);

    return temporary++;
}

int codegen_expression(struct node *expression) {
    int tmp = -1;

    switch(expression->category) {
        case Natural:
            tmp = codegen_natural(expression);
            break;

        case Identifier:
            tmp = codegen_identifier(expression);
            break;

        case Add:
            tmp = codegen_binary_operation(expression, "add");
            break;

        case Sub:
            tmp = codegen_binary_operation(expression, "sub");
            break;

        case Mul:
            tmp = codegen_binary_operation(expression, "mul");
            break;

        case Div:
            tmp = codegen_binary_operation(expression, "sdiv");
            break;
        case Call:
            tmp = codegen_call(expression);
            break;
        case If:
            tmp = codegen_if(expression);
            break;
        default:
            break;
    }

    return tmp;
}

void codegen_parameters(struct node *parameters) {
    struct node *parameter;
    int curr = 0;
    while((parameter = getchild(parameters, curr++)) != NULL) {
        if(curr > 1)
            printf(", ");
        printf("i32 %%%s", getchild(parameter, 1)->token);
    }
}

void codegen_function(struct node *function) {
    temporary = 1;
    label_counter = 1;
    printf("define i32 @_%s(", getchild(function, 0)->token);
    codegen_parameters(getchild(function, 1));
    printf(") {\n");
    int tmp = codegen_expression(getchild(function, 2));
    printf("  ret i32 %%%d\n", tmp);
    printf("}\n\n");
}

// code generation begins here, with the AST root node
void codegen_program(struct node *program) {
    // predeclared I/O functions
    printf("declare i32 @_read(i32)\n");
    printf("declare i32 @_write(i32)\n\n");

    // generate code for each function
    struct node_list *function = program->children;
    while((function = function->next) != NULL)
        codegen_function(function->node);

    // generate the entry point which calls main(integer) if it exists
    struct symbol_list *entry = search_symbol(symbol_table, "main");
    if(entry != NULL && entry->node->category == Function)
        printf("define i32 @main() {\n"
               "  %%1 = call i32 @_main(i32 0)\n"
               "  ret i32 %%1\n"
               "}\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantics.h"

int semantic_errors = 0;

struct symbol_list *symbol_table;

struct symbol_list *insert_symbol(struct symbol_list *table, char *identifier, enum type type, struct node *node) {
    if(search_symbol(table, identifier) != NULL)
        return NULL;

    struct symbol_list *new = (struct symbol_list *) malloc(sizeof(struct symbol_list));
    new->identifier = strdup(identifier);
    new->type = type;
    new->node = node;
    new->next = NULL;

    struct symbol_list *symbol = table;
    while(symbol->next != NULL)
        symbol = symbol->next;

    symbol->next = new;
    return new;
}

struct symbol_list *search_symbol(struct symbol_list *table, char *identifier) {
    struct symbol_list *symbol;
    for(symbol = table->next; symbol != NULL; symbol = symbol->next)
        if(strcmp(symbol->identifier, identifier) == 0)
            return symbol;
    return NULL;
}

void show_symbol_table() {
    struct symbol_list *symbol;
    for(symbol = symbol_table->next; symbol != NULL; symbol = symbol->next)
        printf("Symbol %s : %s\n", symbol->identifier, type_name(symbol->type));
}

void check_parameters(struct node *parameters, struct symbol_list *scope) {
    struct node_list *child = parameters->children;

    while((child = child->next) != NULL) {
        struct node *parameter = child->node;
        struct node *type_node = getchild(parameter, 0);
        struct node *id = getchild(parameter, 1);

        enum type param_type = category_type(type_node->category);

        if(search_symbol(scope, id->token) == NULL) {
            insert_symbol(scope, id->token, param_type, parameter);
        } else {
            printf("Identifier %s already declared\n", id->token);
            semantic_errors++;
        }
    }
}

static enum type check_binary_expression(struct node *expression, struct symbol_list *scope, char *op_name) {
    enum type left_type = check_expression(getchild(expression, 0), scope);
    enum type right_type = check_expression(getchild(expression, 1), scope);

    if(left_type == no_type)
        expression->type = right_type;
    else if(right_type == no_type)
        expression->type = left_type;
    else if(left_type == right_type)
        expression->type = left_type;
    else {
        printf("Incompatible types in %s operation\n", op_name);
        semantic_errors++;
        expression->type = no_type;
    }

    return expression->type;
}

enum type check_expression(struct node *expression, struct symbol_list *scope) {
    if(expression == NULL)
        return no_type;

    switch(expression->category) {
        case Natural:
            expression->type = integer_type;
            return expression->type;

        case Decimal:
            expression->type = double_type;
            return expression->type;

        case Identifier: {
            struct symbol_list *symbol = search_symbol(scope, expression->token);
            if(symbol == NULL) {
                printf("Unknown identifier %s\n", expression->token);
                semantic_errors++;
                expression->type = no_type;
            } else {
                expression->type = symbol->type;
            }
            return expression->type;
        }

        case Call: {
            struct node *id = getchild(expression, 0);
            struct symbol_list *symbol = search_symbol(symbol_table, id->token);

            if(symbol == NULL) {
                printf("Unknown function %s\n", id->token);
                semantic_errors++;
                expression->type = no_type;
                return expression->type;
            }

            struct node *arguments = getchild(expression, 1);
            if(arguments != NULL) {
                struct node_list *arg = arguments->children;
                while((arg = arg->next) != NULL)
                    check_expression(arg->node, scope);
            }

            expression->type = symbol->type;
            return expression->type;
        }

        case If: {
            check_expression(getchild(expression, 0), scope);
            enum type then_type = check_expression(getchild(expression, 1), scope);
            enum type else_type = check_expression(getchild(expression, 2), scope);

            if(then_type == no_type)
                expression->type = else_type;
            else if(else_type == no_type)
                expression->type = then_type;
            else if(then_type == else_type)
                expression->type = then_type;
            else {
                printf("Incompatible types in if expression\n");
                semantic_errors++;
                expression->type = no_type;
            }

            return expression->type;
        }

        case Add:
            return check_binary_expression(expression, scope, "add");

        case Sub:
            return check_binary_expression(expression, scope, "sub");

        case Mul:
            return check_binary_expression(expression, scope, "mul");

        case Div:
            return check_binary_expression(expression, scope, "div");

        default:
            expression->type = no_type;
            return no_type;
    }
}

void check_function(struct node *function) {
    struct node *id = getchild(function, 0);

    if(search_symbol(symbol_table, id->token) == NULL) {
        insert_symbol(symbol_table, id->token, no_type, function);
    } else {
        printf("Identifier %s already declared\n", id->token);
        semantic_errors++;
    }

    struct symbol_list *scope = (struct symbol_list *) malloc(sizeof(struct symbol_list));
    scope->next = NULL;

    check_parameters(getchild(function, 1), scope);
    check_expression(getchild(function, 2), scope);
}

int check_program(struct node *program) {
    symbol_table = (struct symbol_list *) malloc(sizeof(struct symbol_list));
    symbol_table->next = NULL;

    struct node_list *child = program->children;
    while((child = child->next) != NULL)
        check_function(child->node);

    return semantic_errors;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "semantics.h"
#include "codegen.h"

static int temporary = 1;
static int label_counter = 1;
static int string_counter = 0;

void codegen_program(struct node *program) {
    (void)program;
    (void)temporary;
    (void)label_counter;
    (void)string_counter;

    printf("declare i32 @printf(i8*, ...)\n");
    printf("declare i32 @atoi(i8*)\n\n");

    printf("@.fmt_int = private constant [3 x i8] c\"%%d\\00\"\n");
    printf("@.fmt_double = private constant [5 x i8] c\"%%.16e\\00\"\n");
    printf("@.fmt_str = private constant [3 x i8] c\"%%s\\00\"\n");
    printf("@.str_true = private constant [5 x i8] c\"true\\00\"\n");
    printf("@.str_false = private constant [6 x i8] c\"false\\00\"\n");
}
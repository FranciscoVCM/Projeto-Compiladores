declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"

@.strlit.0 = private constant [2 x i8] c"\0A\00"
@.strlit.1 = private constant [2 x i8] c"\0A\00"

define i32 @_a_int(i32 %input.param) {
  %input = alloca i32
  store i32 %input.param, i32* %input
  %i = alloca i32
  %1 = add i32 0, 0
  store i32 %1, i32* %i
  br label %L1_while_cond

L1_while_cond:
  %2 = load i32, i32* %i
  %3 = add i32 10, 0
  %4 = icmp slt i32 %2, %3
  br i1 %4, label %L1_while_body, label %L1_while_end

L1_while_body:
  %5 = load i32, i32* %input
  %6 = add i32 2, 0
  %7 = add i32 %5, %6
  store i32 %7, i32* %input
  %8 = load i32, i32* %i
  %9 = add i32 1, 0
  %10 = add i32 %8, %9
  store i32 %10, i32* %i
  br label %L1_while_cond

L1_while_end:
  %11 = load i32, i32* %input
  ret i32 %11
}

define i32 @_b_int(i32 %input.param) {
  %input = alloca i32
  store i32 %input.param, i32* %input
  %k = alloca i32
  %1 = add i32 0, 0
  store i32 %1, i32* %k
  br label %L1_while_cond

L1_while_cond:
  %2 = load i32, i32* %k
  %3 = add i32 5, 0
  %4 = icmp slt i32 %2, %3
  br i1 %4, label %L1_while_body, label %L1_while_end

L1_while_body:
  %5 = load i32, i32* %input
  %6 = add i32 3, 0
  %7 = mul i32 %5, %6
  store i32 %7, i32* %input
  %8 = load i32, i32* %k
  %9 = add i32 1, 0
  %10 = add i32 %8, %9
  store i32 %10, i32* %k
  br label %L1_while_cond

L1_while_end:
  %11 = load i32, i32* %input
  ret i32 %11
}

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %input = alloca i32
  %aux = alloca i32
  %aux1 = alloca i32
  %1 = add i32 0, 0
  store i32 %1, i32* %aux
  %2 = add i32 0, 0
  store i32 %2, i32* %aux1
  %3 = add i32 0, 0
  %4 = add i32 %3, 1
  %5 = sext i32 %4 to i64
  %6 = getelementptr inbounds i8*, i8** %args.argv, i64 %5
  %7 = load i8*, i8** %6
  %8 = call i32 @atoi(i8* %7)
  store i32 %8, i32* %input
  %9 = load i32, i32* %input
  %10 = add i32 10, 0
  %11 = icmp slt i32 %9, %10
  br i1 %11, label %L1_if_then, label %L1_if_else

L1_if_then:
  %12 = load i32, i32* %input
  %13 = call i32 @_a_int(i32 %12)
  store i32 %13, i32* %aux
  br label %L1_if_end

L1_if_else:
  %14 = load i32, i32* %input
  %15 = call i32 @_b_int(i32 %14)
  store i32 %15, i32* %aux1
  br label %L1_if_end

L1_if_end:
  %16 = load i32, i32* %aux
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %16)
  %18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  %19 = load i32, i32* %aux1
  %20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %19)
  %21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.1, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

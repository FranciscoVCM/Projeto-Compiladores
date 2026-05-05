declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"
@.empty_str = private constant [1 x i8] c"\00"

@.strlit.0 = private constant [2 x i8] c"\0A\00"
@.strlit.1 = private constant [2 x i8] c"\0A\00"

define i32 @_a_int(i32 %input.param) {
  %input = alloca i32
  store i32 %input.param, i32* %input
  %i = alloca i32
  store i32 0, i32* %i
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
  store i32 0, i32* %k
  %1 = add i32 0, 0
  store i32 %1, i32* %k
  br label %L1_while_cond

L1_while_cond:
  %2 = load i32, i32* %k
  %3 = add i32 5, 0
  %4 = icmp slt i32 %2, %3
  br i1 %4, label %L1_while_body, label %L1_while_end

L1_while_body:
  %5 = load i32, i32* %k
  %6 = add i32 1, 0
  %7 = icmp eq i32 %5, %6
  br i1 %7, label %L2_if_then, label %L2_if_else

L2_if_then:
  %8 = load i32, i32* %input
  %9 = add i32 2, 0
  %10 = sub i32 %8, %9
  store i32 %10, i32* %input
  br label %L2_if_end

L2_if_else:
  %11 = load i32, i32* %k
  %12 = add i32 2, 0
  %13 = icmp eq i32 %11, %12
  br i1 %13, label %L3_if_then, label %L3_if_else

L3_if_then:
  %14 = load i32, i32* %input
  %15 = add i32 3, 0
  %16 = mul i32 %14, %15
  store i32 %16, i32* %input
  br label %L3_if_end

L3_if_else:
  br label %L3_if_end

L3_if_end:
  br label %L2_if_end

L2_if_end:
  %17 = load i32, i32* %k
  %18 = add i32 1, 0
  %19 = add i32 %17, %18
  store i32 %19, i32* %k
  br label %L1_while_cond

L1_while_end:
  %20 = load i32, i32* %input
  ret i32 %20
}

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %input = alloca i32
  store i32 0, i32* %input
  %aux = alloca i32
  store i32 0, i32* %aux
  %aux1 = alloca i32
  store i32 0, i32* %aux1
  %1 = add i32 0, 0
  store i32 %1, i32* %aux
  %2 = add i32 0, 0
  store i32 %2, i32* %aux1
  %3 = add i32 0, 0
  %4 = icmp sge i32 %3, 0
  %5 = add i32 %3, 1
  %6 = icmp slt i32 %5, %args.argc
  %7 = and i1 %4, %6
  br i1 %7, label %L1_parse_ok, label %L1_parse_bad

L1_parse_ok:
  %8 = sext i32 %5 to i64
  %9 = getelementptr inbounds i8*, i8** %args.argv, i64 %8
  %10 = load i8*, i8** %9
  br label %L1_parse_end

L1_parse_bad:
  br label %L1_parse_end

L1_parse_end:
  %11 = phi i8* [ %10, %L1_parse_ok ], [ getelementptr inbounds ([1 x i8], [1 x i8]* @.empty_str, i32 0, i32 0), %L1_parse_bad ]
  %12 = call i32 @atoi(i8* %11)
  store i32 %12, i32* %input
  %13 = load i32, i32* %input
  %14 = add i32 10, 0
  %15 = icmp slt i32 %13, %14
  br i1 %15, label %L2_if_then, label %L2_if_else

L2_if_then:
  %16 = load i32, i32* %input
  %17 = call i32 @_a_int(i32 %16)
  store i32 %17, i32* %aux
  br label %L2_if_end

L2_if_else:
  %18 = load i32, i32* %input
  %19 = call i32 @_b_int(i32 %18)
  store i32 %19, i32* %aux1
  br label %L2_if_end

L2_if_end:
  %20 = load i32, i32* %aux
  %21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %20)
  %22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  %23 = load i32, i32* %aux1
  %24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %23)
  %25 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.1, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

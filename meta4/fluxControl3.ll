declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"
@.empty_str = private constant [1 x i8] c"\00"

@.strlit.0 = private constant [10 x i8] c"Is pair: \00"
@.strlit.1 = private constant [3 x i8] c"|\0A\00"
@.strlit.2 = private constant [2 x i8] c"\0A\00"

define i32 @_b_int(i32 %input.param) {
  %input = alloca i32
  store i32 %input.param, i32* %input
  %k = alloca i32
  store i32 0, i32* %k
  %i = alloca i32
  store i32 0, i32* %i
  %g = alloca i32
  store i32 0, i32* %g
  %is_pair = alloca i32
  store i32 0, i32* %is_pair
  %1 = add i32 0, 0
  store i32 %1, i32* %k
  %2 = add i32 0, 0
  store i32 %2, i32* %i
  %3 = add i32 0, 0
  store i32 %3, i32* %g
  %4 = add i32 0, 0
  store i32 %4, i32* %is_pair
  br label %L1_while_cond

L1_while_cond:
  %5 = load i32, i32* %k
  %6 = add i32 5, 0
  %7 = icmp slt i32 %5, %6
  br i1 %7, label %L1_while_body, label %L1_while_end

L1_while_body:
  %8 = load i32, i32* %k
  %9 = add i32 1, 0
  %10 = icmp eq i32 %8, %9
  br i1 %10, label %L2_if_then, label %L2_if_else

L2_if_then:
  %11 = load i32, i32* %input
  %12 = add i32 2, 0
  %13 = sub i32 %11, %12
  store i32 %13, i32* %input
  %14 = add i32 0, 0
  store i32 %14, i32* %i
  %15 = add i32 0, 0
  store i32 %15, i32* %g
  br label %L3_while_cond

L3_while_cond:
  %16 = load i32, i32* %i
  %17 = add i32 100, 0
  %18 = icmp slt i32 %16, %17
  br i1 %18, label %L3_while_body, label %L3_while_end

L3_while_body:
  br label %L4_while_cond

L4_while_cond:
  %19 = load i32, i32* %g
  %20 = add i32 50, 0
  %21 = icmp slt i32 %19, %20
  br i1 %21, label %L4_while_body, label %L4_while_end

L4_while_body:
  %22 = load i32, i32* %input
  %23 = add i32 2, 0
  %24 = add i32 %22, %23
  store i32 %24, i32* %input
  %25 = load i32, i32* %g
  %26 = add i32 2, 0
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %L6_mod_zero, label %L6_mod_ok

L6_mod_ok:
  %28 = srem i32 %25, %26
  br label %L6_mod_end

L6_mod_zero:
  br label %L6_mod_end

L6_mod_end:
  %29 = phi i32 [ %28, %L6_mod_ok ], [ 0, %L6_mod_zero ]
  %30 = add i32 0, 0
  %31 = icmp eq i32 %29, %30
  br i1 %31, label %L5_if_then, label %L5_if_else

L5_if_then:
  %32 = load i32, i32* %is_pair
  %33 = add i32 1, 0
  %34 = add i32 %32, %33
  store i32 %34, i32* %is_pair
  br label %L5_if_end

L5_if_else:
  br label %L5_if_end

L5_if_end:
  %35 = load i32, i32* %g
  %36 = add i32 1, 0
  %37 = add i32 %35, %36
  store i32 %37, i32* %g
  br label %L4_while_cond

L4_while_end:
  %38 = add i32 0, 0
  store i32 %38, i32* %g
  %39 = load i32, i32* %i
  %40 = add i32 1, 0
  %41 = add i32 %39, %40
  store i32 %41, i32* %i
  br label %L3_while_cond

L3_while_end:
  br label %L2_if_end

L2_if_else:
  %42 = load i32, i32* %k
  %43 = add i32 2, 0
  %44 = icmp eq i32 %42, %43
  br i1 %44, label %L7_if_then, label %L7_if_else

L7_if_then:
  %45 = load i32, i32* %input
  %46 = add i32 3, 0
  %47 = mul i32 %45, %46
  store i32 %47, i32* %input
  br label %L7_if_end

L7_if_else:
  br label %L7_if_end

L7_if_end:
  br label %L2_if_end

L2_if_end:
  %48 = load i32, i32* %k
  %49 = add i32 1, 0
  %50 = add i32 %48, %49
  store i32 %50, i32* %k
  br label %L1_while_cond

L1_while_end:
  %51 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.strlit.0, i32 0, i32 0))
  %52 = load i32, i32* %is_pair
  %53 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %52)
  %54 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.strlit.1, i32 0, i32 0))
  %55 = load i32, i32* %input
  ret i32 %55
}

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %aux1 = alloca i32
  store i32 0, i32* %aux1
  %1 = add i32 40, 0
  store i32 %1, i32* %aux1
  %2 = load i32, i32* %aux1
  %3 = call i32 @_b_int(i32 %2)
  store i32 %3, i32* %aux1
  %4 = add i32 0, 0
  %5 = icmp sge i32 %4, 0
  %6 = add i32 %4, 1
  %7 = icmp slt i32 %6, %args.argc
  %8 = and i1 %5, %7
  br i1 %8, label %L1_parse_ok, label %L1_parse_bad

L1_parse_ok:
  %9 = sext i32 %6 to i64
  %10 = getelementptr inbounds i8*, i8** %args.argv, i64 %9
  %11 = load i8*, i8** %10
  br label %L1_parse_end

L1_parse_bad:
  br label %L1_parse_end

L1_parse_end:
  %12 = phi i8* [ %11, %L1_parse_ok ], [ getelementptr inbounds ([1 x i8], [1 x i8]* @.empty_str, i32 0, i32 0), %L1_parse_bad ]
  %13 = call i32 @atoi(i8* %12)
  %14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %13)
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.2, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"

@.strlit.0 = private constant [10 x i8] c"Is pair: \00"
@.strlit.1 = private constant [3 x i8] c"|\0A\00"
@.strlit.2 = private constant [2 x i8] c"\0A\00"

define i32 @_b_int(i32 %input.param) {
  %input = alloca i32
  store i32 %input.param, i32* %input
  %k = alloca i32
  %1 = add i32 0, 0
  store i32 %1, i32* %k
  %i = alloca i32
  %g = alloca i32
  %2 = add i32 0, 0
  store i32 %2, i32* %i
  %3 = add i32 0, 0
  store i32 %3, i32* %g
  %is_pair = alloca i32
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
  %27 = srem i32 %25, %26
  %28 = add i32 0, 0
  %29 = icmp eq i32 %27, %28
  br i1 %29, label %L5_if_then, label %L5_if_else

L5_if_then:
  %30 = load i32, i32* %is_pair
  %31 = add i32 1, 0
  %32 = add i32 %30, %31
  store i32 %32, i32* %is_pair
  br label %L5_if_end

L5_if_else:
  br label %L5_if_end

L5_if_end:
  %33 = load i32, i32* %g
  %34 = add i32 1, 0
  %35 = add i32 %33, %34
  store i32 %35, i32* %g
  br label %L4_while_cond

L4_while_end:
  %36 = add i32 0, 0
  store i32 %36, i32* %g
  %37 = load i32, i32* %i
  %38 = add i32 1, 0
  %39 = add i32 %37, %38
  store i32 %39, i32* %i
  br label %L3_while_cond

L3_while_end:
  br label %L2_if_end

L2_if_else:
  %40 = load i32, i32* %k
  %41 = add i32 2, 0
  %42 = icmp eq i32 %40, %41
  br i1 %42, label %L6_if_then, label %L6_if_else

L6_if_then:
  %43 = load i32, i32* %input
  %44 = add i32 3, 0
  %45 = mul i32 %43, %44
  store i32 %45, i32* %input
  br label %L6_if_end

L6_if_else:
  br label %L6_if_end

L6_if_end:
  br label %L2_if_end

L2_if_end:
  %46 = load i32, i32* %k
  %47 = add i32 1, 0
  %48 = add i32 %46, %47
  store i32 %48, i32* %k
  br label %L1_while_cond

L1_while_end:
  %49 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.strlit.0, i32 0, i32 0))
  %50 = load i32, i32* %is_pair
  %51 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %50)
  %52 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.strlit.1, i32 0, i32 0))
  %53 = load i32, i32* %input
  ret i32 %53
}

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %aux1 = alloca i32
  %1 = add i32 40, 0
  store i32 %1, i32* %aux1
  %2 = load i32, i32* %aux1
  %3 = call i32 @_b_int(i32 %2)
  store i32 %3, i32* %aux1
  %4 = add i32 0, 0
  %5 = add i32 %4, 1
  %6 = sext i32 %5 to i64
  %7 = getelementptr inbounds i8*, i8** %args.argv, i64 %6
  %8 = load i8*, i8** %7
  %9 = call i32 @atoi(i8* %8)
  %10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %9)
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.2, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

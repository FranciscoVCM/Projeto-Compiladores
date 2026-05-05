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
@.strlit.2 = private constant [2 x i8] c"\0A\00"
@.strlit.3 = private constant [2 x i8] c"\0A\00"
@.strlit.4 = private constant [2 x i8] c"\0A\00"

@b = global i1 0

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %1 = icmp ne i1 1, 0
  %2 = xor i1 %1, true
  store i1 %2, i1* @b
  %3 = load i1, i1* @b
  %4 = xor i1 %3, true
  %5 = xor i1 %4, true
  %6 = xor i1 %5, true
  %7 = xor i1 %6, true
  %8 = xor i1 %7, true
  %9 = xor i1 %8, true
  %10 = xor i1 %9, true
  br i1 %10, label %L1print_true, label %L1print_false

L1print_true:
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str_true, i32 0, i32 0))
  br label %L1print_end

L1print_false:
  %12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str_false, i32 0, i32 0))
  br label %L1print_end

L1print_end:
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  %14 = fadd double 4.20000000000000000e+02, 0.000000e+00
  %15 = fneg double %14
  %16 = fneg double %15
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %16)
  %18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.1, i32 0, i32 0))
  %19 = add i32 420, 0
  %20 = sub i32 0, %19
  %21 = sub i32 0, %20
  %22 = sub i32 0, %21
  %23 = sub i32 0, %22
  %24 = sub i32 0, %23
  %25 = add i32 421, 0
  %26 = sub i32 0, %25
  %27 = icmp sgt i32 %24, %26
  %28 = xor i1 %27, true
  br i1 %28, label %L2print_true, label %L2print_false

L2print_true:
  %29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str_true, i32 0, i32 0))
  br label %L2print_end

L2print_false:
  %30 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str_false, i32 0, i32 0))
  br label %L2print_end

L2print_end:
  %31 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.2, i32 0, i32 0))
  %32 = icmp ne i1 0, 0
  %33 = call i1 @_falseB()
  %34 = icmp eq i1 %32, %33
  %35 = xor i1 %34, true
  br i1 %35, label %L3print_true, label %L3print_false

L3print_true:
  %36 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str_true, i32 0, i32 0))
  br label %L3print_end

L3print_false:
  %37 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str_false, i32 0, i32 0))
  br label %L3print_end

L3print_end:
  %38 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.3, i32 0, i32 0))
  %39 = add i32 1, 0
  %40 = add i32 1, 0
  %41 = sub i32 %39, %40
  %42 = add i32 0, 0
  %43 = add i32 %41, %42
  %44 = sub i32 0, %43
  %45 = sub i32 0, %44
  %46 = icmp sge i32 %45, 0
  %47 = add i32 %45, 1
  %48 = icmp slt i32 %47, %args.argc
  %49 = and i1 %46, %48
  br i1 %49, label %L4_parse_ok, label %L4_parse_bad

L4_parse_ok:
  %50 = sext i32 %47 to i64
  %51 = getelementptr inbounds i8*, i8** %args.argv, i64 %50
  %52 = load i8*, i8** %51
  br label %L4_parse_end

L4_parse_bad:
  br label %L4_parse_end

L4_parse_end:
  %53 = phi i8* [ %52, %L4_parse_ok ], [ getelementptr inbounds ([1 x i8], [1 x i8]* @.empty_str, i32 0, i32 0), %L4_parse_bad ]
  %54 = call i32 @atoi(i8* %53)
  %55 = sub i32 0, %54
  %56 = sub i32 0, %55
  %57 = sub i32 0, %56
  %58 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %57)
  %59 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.4, i32 0, i32 0))
  ret void
}

define i1 @_falseB() {
  %1 = icmp ne i1 1, 0
  %2 = xor i1 %1, true
  ret i1 %2
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

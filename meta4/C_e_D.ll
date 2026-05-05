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
@.strlit.3 = private constant [22 x i8] c"Teste\09de \0Cstring\5C\22\0D%%\00"
@.strlit.4 = private constant [2 x i8] c"\0A\00"
@.strlit.5 = private constant [2 x i8] c"\0A\00"
@.strlit.6 = private constant [2 x i8] c"\0A\00"
@.strlit.7 = private constant [2 x i8] c"\0A\00"
@.strlit.8 = private constant [2 x i8] c"\0A\00"
@.strlit.9 = private constant [2 x i8] c"\0A\00"
@.strlit.10 = private constant [2 x i8] c"\0A\00"
@.strlit.11 = private constant [2 x i8] c"\0A\00"

@a = global i32 0
@b = global i32 0
@c = global i32 0
@d = global i32 0

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %i = alloca i32
  store i32 0, i32* %i
  %a = alloca i32
  store i32 0, i32* %a
  %i1 = alloca i32
  store i32 0, i32* %i1
  %i2 = alloca i32
  store i32 0, i32* %i2
  %i3 = alloca i32
  store i32 0, i32* %i3
  %d = alloca double
  store double 0.000000e+00, double* %d
  %1 = add i32 2, 0
  store i32 %1, i32* @a
  %2 = load i32, i32* @a
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %2)
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  %5 = add i32 0, 0
  %6 = add i32 3, 0
  %7 = add i32 %5, %6
  store i32 %7, i32* %a
  %8 = sitofp i32 %7 to double
  store double %8, double* %d
  %9 = load i32, i32* %a
  %10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %9)
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.1, i32 0, i32 0))
  %12 = load double, double* %d
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %12)
  %14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.2, i32 0, i32 0))
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.strlit.3, i32 0, i32 0))
  %16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.4, i32 0, i32 0))
  %17 = load i32, i32* %a
  %18 = add i32 1, 0
  %19 = add i32 %17, %18
  store i32 %19, i32* %a
  %20 = add i32 0, 0
  %21 = icmp sgt i32 %19, %20
  br i1 %21, label %L1_or_true, label %L1_or_right

L1_or_right:
  %22 = load i32, i32* %a
  %23 = add i32 3, 0
  %24 = add i32 %22, %23
  store i32 %24, i32* %a
  %25 = add i32 0, 0
  %26 = icmp sgt i32 %24, %25
  br label %L1_or_end

L1_or_true:
  br label %L1_or_end

L1_or_end:
  %27 = phi i1 [ 1, %L1_or_true ], [ %26, %L1_or_right ]
  br i1 %27, label %L2print_true, label %L2print_false

L2print_true:
  %28 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str_true, i32 0, i32 0))
  br label %L2print_end

L2print_false:
  %29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str_false, i32 0, i32 0))
  br label %L2print_end

L2print_end:
  %30 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.5, i32 0, i32 0))
  %31 = load i32, i32* %a
  %32 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %31)
  %33 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.6, i32 0, i32 0))
  %34 = load i32, i32* %a
  %35 = add i32 1, 0
  %36 = add i32 %34, %35
  store i32 %36, i32* %a
  %37 = add i32 0, 0
  %38 = icmp slt i32 %36, %37
  br i1 %38, label %L3_and_right, label %L3_and_false

L3_and_right:
  %39 = load i32, i32* %a
  %40 = add i32 3, 0
  %41 = add i32 %39, %40
  store i32 %41, i32* %a
  %42 = add i32 0, 0
  %43 = icmp slt i32 %41, %42
  br label %L3_and_end

L3_and_false:
  br label %L3_and_end

L3_and_end:
  %44 = phi i1 [ %43, %L3_and_right ], [ 0, %L3_and_false ]
  br i1 %44, label %L4print_true, label %L4print_false

L4print_true:
  %45 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str_true, i32 0, i32 0))
  br label %L4print_end

L4print_false:
  %46 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str_false, i32 0, i32 0))
  br label %L4print_end

L4print_end:
  %47 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.7, i32 0, i32 0))
  %48 = load i32, i32* %a
  %49 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %48)
  %50 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.8, i32 0, i32 0))
  %51 = fadd double 1.22999999999999993e-08, 0.000000e+00
  store double %51, double* %d
  %52 = load double, double* %d
  %53 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %52)
  %54 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.9, i32 0, i32 0))
  %55 = fadd double 0.00000000000000000e+00, 0.000000e+00
  store double %55, double* %d
  %56 = load double, double* %d
  %57 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %56)
  %58 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.10, i32 0, i32 0))
  %59 = fadd double 1.00000000000000000e+01, 0.000000e+00
  store double %59, double* %d
  %60 = load double, double* %d
  %61 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %60)
  %62 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.11, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

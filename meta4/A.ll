declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"

@.strlit.0 = private constant [2 x i8] c"\0A\00"
@.strlit.1 = private constant [2 x i8] c"\0A\00"
@.strlit.2 = private constant [2 x i8] c"\0A\00"
@.strlit.3 = private constant [2 x i8] c"\0A\00"
@.strlit.4 = private constant [2 x i8] c"\0A\00"
@.strlit.5 = private constant [2 x i8] c"\0A\00"
@.strlit.6 = private constant [2 x i8] c"\0A\00"
@.strlit.7 = private constant [2 x i8] c"\0A\00"
@.strlit.8 = private constant [2 x i8] c"\0A\00"
@.strlit.9 = private constant [2 x i8] c"\0A\00"
@.strlit.10 = private constant [2 x i8] c"\0A\00"
@.strlit.11 = private constant [2 x i8] c"\0A\00"
@.strlit.12 = private constant [2 x i8] c"\0A\00"
@.strlit.13 = private constant [2 x i8] c"\0A\00"

@global_var = global i32 0

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %a = alloca i32
  store i32 0, i32* %a
  %b = alloca i1
  store i1 0, i1* %b
  %c = alloca double
  store double 0.000000e+00, double* %c
  %1 = add i32 1, 0
  store i32 %1, i32* %a
  %2 = load i32, i32* %a
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %2)
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  %5 = add i32 1, 0
  store i32 %5, i32* %a
  %6 = load i32, i32* %a
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %6)
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.1, i32 0, i32 0))
  %9 = add i32 1, 0
  %10 = sub i32 0, %9
  store i32 %10, i32* %a
  %11 = load i32, i32* %a
  %12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %11)
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.2, i32 0, i32 0))
  %14 = icmp ne i1 1, 0
  store i1 %14, i1* %b
  %15 = load i1, i1* %b
  br i1 %15, label %L1print_true, label %L1print_false

L1print_true:
  %16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str_true, i32 0, i32 0))
  br label %L1print_end

L1print_false:
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str_false, i32 0, i32 0))
  br label %L1print_end

L1print_end:
  %18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.3, i32 0, i32 0))
  %19 = icmp ne i1 0, 0
  store i1 %19, i1* %b
  %20 = load i1, i1* %b
  br i1 %20, label %L2print_true, label %L2print_false

L2print_true:
  %21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str_true, i32 0, i32 0))
  br label %L2print_end

L2print_false:
  %22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str_false, i32 0, i32 0))
  br label %L2print_end

L2print_end:
  %23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.4, i32 0, i32 0))
  %24 = fadd double 2.00000000000000000e+00, 0.000000e+00
  store double %24, double* %c
  %25 = load double, double* %c
  %26 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %25)
  %27 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.5, i32 0, i32 0))
  %28 = fadd double 2.20000000000000018e+00, 0.000000e+00
  store double %28, double* %c
  %29 = load double, double* %c
  %30 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %29)
  %31 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.6, i32 0, i32 0))
  %32 = add i32 2, 0
  %33 = sitofp i32 %32 to double
  store double %33, double* %c
  %34 = load double, double* %c
  %35 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %34)
  %36 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.7, i32 0, i32 0))
  %37 = add i32 1, 0
  store i32 %37, i32* %a
  %38 = load i32, i32* %a
  %39 = sitofp i32 %38 to double
  store double %39, double* %c
  %40 = load double, double* %c
  %41 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %40)
  %42 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.8, i32 0, i32 0))
  %43 = fadd double 2.20000000000000018e+00, 0.000000e+00
  store double %43, double* %c
  %44 = load double, double* %c
  %45 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %44)
  %46 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.9, i32 0, i32 0))
  %47 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %48 = fneg double %47
  store double %48, double* %c
  %49 = load double, double* %c
  %50 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %49)
  %51 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.10, i32 0, i32 0))
  %52 = load i32, i32* %a
  %53 = sitofp i32 %52 to double
  store double %53, double* %c
  %54 = load double, double* %c
  %55 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %54)
  %56 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.11, i32 0, i32 0))
  %57 = load i32, i32* %a
  %58 = sub i32 0, %57
  %59 = sitofp i32 %58 to double
  store double %59, double* %c
  %60 = load double, double* %c
  %61 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %60)
  %62 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.12, i32 0, i32 0))
  %63 = add i32 10, 0
  store i32 %63, i32* @global_var
  %64 = load i32, i32* @global_var
  %65 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %64)
  %66 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.13, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

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

define void @_main_StringArray(i32 %uncommon_name.argc, i8** %uncommon_name.argv) {
  %d = alloca double
  store double 0.000000e+00, double* %d
  %1 = call double @_fun_double()
  store double %1, double* %d
  %2 = load double, double* %d
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %2)
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  %5 = call i32 @_fun_int()
  %6 = sitofp i32 %5 to double
  store double %6, double* %d
  %7 = load double, double* %d
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %7)
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.1, i32 0, i32 0))
  %10 = call double @_fun_double_from_int()
  store double %10, double* %d
  %11 = load double, double* %d
  %12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %11)
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.2, i32 0, i32 0))
  %14 = call double @_fun_double_from_int_fun()
  store double %14, double* %d
  %15 = load double, double* %d
  %16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %15)
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.3, i32 0, i32 0))
  %18 = call double @_fun_double_from_int_var()
  store double %18, double* %d
  %19 = load double, double* %d
  %20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %19)
  %21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.4, i32 0, i32 0))
  %22 = call double @_fun_double_from_args_StringArray(i32 %uncommon_name.argc, i8** %uncommon_name.argv)
  store double %22, double* %d
  %23 = load double, double* %d
  %24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %23)
  %25 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.5, i32 0, i32 0))
  %26 = call double @_fun_double_from_unary_plus_StringArray(i32 %uncommon_name.argc, i8** %uncommon_name.argv)
  store double %26, double* %d
  %27 = load double, double* %d
  %28 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %27)
  %29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.6, i32 0, i32 0))
  %30 = fadd double 1.30000000000000004e+00, 0.000000e+00
  %31 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %30)
  %32 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.7, i32 0, i32 0))
  ret void
}

define double @_fun_double() {
  %1 = fadd double 1.10000000000000009e+00, 0.000000e+00
  ret double %1
}

define i32 @_fun_int() {
  %1 = add i32 1, 0
  ret i32 %1
}

define double @_fun_double_from_int() {
  %1 = add i32 2, 0
  %2 = sitofp i32 %1 to double
  ret double %2
}

define double @_fun_double_from_int_fun() {
  %1 = call i32 @_fun_int()
  %2 = sitofp i32 %1 to double
  ret double %2
}

define double @_fun_double_from_int_var() {
  %d = alloca double
  store double 0.000000e+00, double* %d
  %1 = add i32 0, 0
  %2 = sitofp i32 %1 to double
  store double %2, double* %d
  %3 = load double, double* %d
  %4 = call i32 @_fun_int()
  %5 = sitofp i32 %4 to double
  %6 = fadd double %3, %5
  %7 = call double @_fun_double()
  %8 = fadd double %6, %7
  ret double %8
}

define double @_fun_double_from_args_StringArray(i32 %str_arr.argc, i8** %str_arr.argv) {
  %1 = sub i32 %str_arr.argc, 1
  %2 = sitofp i32 %1 to double
  ret double %2
}

define double @_fun_double_from_unary_plus_StringArray(i32 %str_arr.argc, i8** %str_arr.argv) {
  %1 = add i32 1, 0
  %2 = sitofp i32 %1 to double
  ret double %2
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

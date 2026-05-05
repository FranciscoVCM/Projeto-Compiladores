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

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %d = alloca double
  %1 = fadd double 5.50000000000000000e+00, 0.000000e+00
  %2 = add i32 2, 0
  %3 = sitofp i32 %2 to double
  %4 = frem double %1, %3
  store double %4, double* %d
  %5 = load double, double* %d
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %5)
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  %8 = add i32 5, 0
  %9 = fadd double 2.00000000000000000e+00, 0.000000e+00
  %10 = sitofp i32 %8 to double
  %11 = frem double %10, %9
  store double %11, double* %d
  %12 = load double, double* %d
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %12)
  %14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.1, i32 0, i32 0))
  %15 = fadd double 5.50000000000000000e+00, 0.000000e+00
  %16 = fadd double 2.00000000000000000e+00, 0.000000e+00
  %17 = frem double %15, %16
  store double %17, double* %d
  %18 = load double, double* %d
  %19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %18)
  %20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.2, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

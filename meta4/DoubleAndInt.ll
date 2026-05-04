declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"

@.strlit.0 = private constant [2 x i8] c"\0A\00"

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %i = alloca i32
  %1 = add i32 3, 0
  store i32 %1, i32* %i
  %j = alloca double
  %2 = add i32 4, 0
  %3 = sitofp i32 %2 to double
  store double %3, double* %j
  %4 = load i32, i32* %i
  %5 = load double, double* %j
  %6 = sitofp i32 %4 to double
  %7 = fadd double %6, %5
  store double %7, double* %j
  %8 = load i32, i32* %i
  %9 = load double, double* %j
  %10 = sitofp i32 %8 to double
  %11 = fdiv double %10, %9
  store double %11, double* %j
  %12 = load double, double* %j
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %12)
  %14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

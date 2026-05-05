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

define i1 @_bool() {
  %i = alloca i1
  store i1 0, i1* %i
  %1 = icmp ne i1 1, 0
  store i1 %1, i1* %i
  %2 = load i1, i1* %i
  br i1 %2, label %L1print_true, label %L1print_false

L1print_true:
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str_true, i32 0, i32 0))
  br label %L1print_end

L1print_false:
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str_false, i32 0, i32 0))
  br label %L1print_end

L1print_end:
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  %6 = load i1, i1* %i
  ret i1 %6
}

define i32 @_integer() {
  %i = alloca i32
  store i32 0, i32* %i
  %1 = add i32 1, 0
  store i32 %1, i32* %i
  %2 = load i32, i32* %i
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %2)
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.1, i32 0, i32 0))
  %5 = load i32, i32* %i
  ret i32 %5
}

define double @_real() {
  %i = alloca double
  store double 0.000000e+00, double* %i
  %1 = fadd double 1.00000000000000000e+00, 0.000000e+00
  store double %1, double* %i
  %2 = load double, double* %i
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %2)
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.2, i32 0, i32 0))
  %5 = load double, double* %i
  ret double %5
}

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %1 = call i1 @_bool()
  %2 = call i32 @_integer()
  %3 = call double @_real()
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.3, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

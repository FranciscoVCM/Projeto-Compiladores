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
  %5 = add i32 1, 0
  %6 = add i32 %4, %5
  %7 = load double, double* %j
  %8 = sitofp i32 %6 to double
  %9 = fcmp oeq double %8, %7
  br i1 %9, label %L1_if_then, label %L1_if_else

L1_if_then:
  %10 = load double, double* %j
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %10)
  br label %L1_if_end

L1_if_else:
  br label %L1_if_end

L1_if_end:
  %12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

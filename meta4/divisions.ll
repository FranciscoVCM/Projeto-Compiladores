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

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %n1 = alloca double
  %n2 = alloca double
  %1 = add i32 11, 0
  %2 = sub i32 0, %1
  %3 = sitofp i32 %2 to double
  store double %3, double* %n1
  %4 = add i32 53, 0
  %5 = sub i32 0, %4
  %6 = sitofp i32 %5 to double
  store double %6, double* %n2
  %7 = load double, double* %n2
  %8 = load double, double* %n1
  %9 = fdiv double %7, %8
  %10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %9)
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  %n3 = alloca i32
  %n4 = alloca i32
  %12 = add i32 11, 0
  %13 = sub i32 0, %12
  store i32 %13, i32* %n3
  %14 = add i32 53, 0
  %15 = sub i32 0, %14
  store i32 %15, i32* %n4
  %16 = load i32, i32* %n4
  %17 = load i32, i32* %n3
  %18 = sdiv i32 %16, %17
  %19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %18)
  %20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.1, i32 0, i32 0))
  %21 = add i32 11, 0
  store i32 %21, i32* %n3
  %22 = add i32 53, 0
  %23 = sub i32 0, %22
  store i32 %23, i32* %n4
  %24 = load i32, i32* %n4
  %25 = load i32, i32* %n3
  %26 = sdiv i32 %24, %25
  %27 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %26)
  %28 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.2, i32 0, i32 0))
  %29 = add i32 2, 0
  store i32 %29, i32* %n3
  %30 = add i32 85, 0
  %31 = sub i32 0, %30
  store i32 %31, i32* %n4
  %32 = load i32, i32* %n4
  %33 = load i32, i32* %n3
  %34 = srem i32 %32, %33
  %35 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %34)
  %36 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.3, i32 0, i32 0))
  %37 = add i32 2, 0
  %38 = sub i32 0, %37
  store i32 %38, i32* %n3
  %39 = add i32 85, 0
  store i32 %39, i32* %n4
  %40 = load i32, i32* %n4
  %41 = load i32, i32* %n3
  %42 = srem i32 %40, %41
  %43 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %42)
  %44 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.4, i32 0, i32 0))
  %45 = add i32 2, 0
  store i32 %45, i32* %n3
  %46 = add i32 85, 0
  store i32 %46, i32* %n4
  %47 = load i32, i32* %n4
  %48 = load i32, i32* %n3
  %49 = srem i32 %47, %48
  %50 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %49)
  %51 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.5, i32 0, i32 0))
  %52 = add i32 0, 0
  %53 = sitofp i32 %52 to double
  store double %53, double* %n1
  store double %53, double* %n2
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

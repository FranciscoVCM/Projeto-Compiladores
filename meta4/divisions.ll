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
@.strlit.5 = private constant [2 x i8] c"\0A\00"

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %n1 = alloca double
  store double 0.000000e+00, double* %n1
  %n2 = alloca double
  store double 0.000000e+00, double* %n2
  %n3 = alloca i32
  store i32 0, i32* %n3
  %n4 = alloca i32
  store i32 0, i32* %n4
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
  %12 = add i32 11, 0
  %13 = sub i32 0, %12
  store i32 %13, i32* %n3
  %14 = add i32 53, 0
  %15 = sub i32 0, %14
  store i32 %15, i32* %n4
  %16 = load i32, i32* %n4
  %17 = load i32, i32* %n3
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %L1_div_zero, label %L1_div_ok

L1_div_ok:
  %19 = sdiv i32 %16, %17
  br label %L1_div_end

L1_div_zero:
  br label %L1_div_end

L1_div_end:
  %20 = phi i32 [ %19, %L1_div_ok ], [ 0, %L1_div_zero ]
  %21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %20)
  %22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.1, i32 0, i32 0))
  %23 = add i32 11, 0
  store i32 %23, i32* %n3
  %24 = add i32 53, 0
  %25 = sub i32 0, %24
  store i32 %25, i32* %n4
  %26 = load i32, i32* %n4
  %27 = load i32, i32* %n3
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %L2_div_zero, label %L2_div_ok

L2_div_ok:
  %29 = sdiv i32 %26, %27
  br label %L2_div_end

L2_div_zero:
  br label %L2_div_end

L2_div_end:
  %30 = phi i32 [ %29, %L2_div_ok ], [ 0, %L2_div_zero ]
  %31 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %30)
  %32 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.2, i32 0, i32 0))
  %33 = add i32 2, 0
  store i32 %33, i32* %n3
  %34 = add i32 85, 0
  %35 = sub i32 0, %34
  store i32 %35, i32* %n4
  %36 = load i32, i32* %n4
  %37 = load i32, i32* %n3
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %L3_mod_zero, label %L3_mod_ok

L3_mod_ok:
  %39 = srem i32 %36, %37
  br label %L3_mod_end

L3_mod_zero:
  br label %L3_mod_end

L3_mod_end:
  %40 = phi i32 [ %39, %L3_mod_ok ], [ 0, %L3_mod_zero ]
  %41 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %40)
  %42 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.3, i32 0, i32 0))
  %43 = add i32 2, 0
  %44 = sub i32 0, %43
  store i32 %44, i32* %n3
  %45 = add i32 85, 0
  store i32 %45, i32* %n4
  %46 = load i32, i32* %n4
  %47 = load i32, i32* %n3
  %48 = icmp eq i32 %47, 0
  br i1 %48, label %L4_mod_zero, label %L4_mod_ok

L4_mod_ok:
  %49 = srem i32 %46, %47
  br label %L4_mod_end

L4_mod_zero:
  br label %L4_mod_end

L4_mod_end:
  %50 = phi i32 [ %49, %L4_mod_ok ], [ 0, %L4_mod_zero ]
  %51 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %50)
  %52 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.4, i32 0, i32 0))
  %53 = add i32 2, 0
  store i32 %53, i32* %n3
  %54 = add i32 85, 0
  store i32 %54, i32* %n4
  %55 = load i32, i32* %n4
  %56 = load i32, i32* %n3
  %57 = icmp eq i32 %56, 0
  br i1 %57, label %L5_mod_zero, label %L5_mod_ok

L5_mod_ok:
  %58 = srem i32 %55, %56
  br label %L5_mod_end

L5_mod_zero:
  br label %L5_mod_end

L5_mod_end:
  %59 = phi i32 [ %58, %L5_mod_ok ], [ 0, %L5_mod_zero ]
  %60 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %59)
  %61 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.5, i32 0, i32 0))
  %62 = add i32 0, 0
  %63 = sitofp i32 %62 to double
  store double %63, double* %n1
  store double %63, double* %n2
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

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

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %a = alloca i32
  store i32 0, i32* %a
  %b = alloca i32
  store i32 0, i32* %b
  %1 = add i32 10, 0
  store i32 %1, i32* %a
  %2 = add i32 0, 0
  store i32 %2, i32* %b
  %3 = load i32, i32* %a
  %4 = load i32, i32* %b
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %L1_div_zero, label %L1_div_ok

L1_div_ok:
  %6 = sdiv i32 %3, %4
  br label %L1_div_end

L1_div_zero:
  br label %L1_div_end

L1_div_end:
  %7 = phi i32 [ %6, %L1_div_ok ], [ 0, %L1_div_zero ]
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %7)
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  %10 = load i32, i32* %a
  %11 = load i32, i32* %b
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %L2_mod_zero, label %L2_mod_ok

L2_mod_ok:
  %13 = srem i32 %10, %11
  br label %L2_mod_end

L2_mod_zero:
  br label %L2_mod_end

L2_mod_end:
  %14 = phi i32 [ %13, %L2_mod_ok ], [ 0, %L2_mod_zero ]
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %14)
  %16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.1, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

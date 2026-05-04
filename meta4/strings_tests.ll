declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"

@.strlit.0 = private constant [7 x i8] c"\0D\5C\22\0C\09\0A\00"
@.strlit.1 = private constant [22 x i8] c"Number of arguments:\09\00"
@.strlit.2 = private constant [2 x i8] c"\0A\00"
@.strlit.3 = private constant [6 x i8] c"Arg (\00"
@.strlit.4 = private constant [4 x i8] c"): \00"
@.strlit.5 = private constant [2 x i8] c"\0A\00"
@.strlit.6 = private constant [16 x i8] c"No arguments :(\00"
@.strlit.7 = private constant [2 x i8] c"\0A\00"

@i = global i32 0

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %a = alloca i32
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.strlit.0, i32 0, i32 0))
  %2 = sub i32 %args.argc, 1
  store i32 %2, i32* %a
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.strlit.1, i32 0, i32 0))
  %4 = load i32, i32* %a
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %4)
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.2, i32 0, i32 0))
  %7 = load i32, i32* %a
  %8 = add i32 0, 0
  %9 = icmp sgt i32 %7, %8
  br i1 %9, label %L1_if_then, label %L1_if_else

L1_if_then:
  br label %L2_while_cond

L2_while_cond:
  %10 = load i32, i32* %a
  %11 = add i32 1, 0
  %12 = add i32 %10, %11
  %13 = load i32, i32* @i
  %14 = add i32 1, 0
  %15 = add i32 %13, %14
  store i32 %15, i32* @i
  %16 = icmp sgt i32 %12, %15
  br i1 %16, label %L2_while_body, label %L2_while_end

L2_while_body:
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.strlit.3, i32 0, i32 0))
  %18 = load i32, i32* @i
  %19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %18)
  %20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.strlit.4, i32 0, i32 0))
  %21 = load i32, i32* @i
  %22 = add i32 1, 0
  %23 = sub i32 %21, %22
  %24 = add i32 %23, 1
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds i8*, i8** %args.argv, i64 %25
  %27 = load i8*, i8** %26
  %28 = call i32 @atoi(i8* %27)
  %29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %28)
  %30 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.5, i32 0, i32 0))
  br label %L2_while_cond

L2_while_end:
  br label %L1_if_end

L1_if_else:
  %31 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.strlit.6, i32 0, i32 0))
  br label %L1_if_end

L1_if_end:
  %32 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.7, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

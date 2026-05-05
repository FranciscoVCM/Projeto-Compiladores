declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"

@.strlit.0 = private constant [2 x i8] c"\0A\00"
@.strlit.1 = private constant [2 x i8] c"\0A\00"

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %arg1 = alloca i32
  store i32 0, i32* %arg1
  %arg2 = alloca i32
  store i32 0, i32* %arg2
  %1 = add i32 0, 0
  %2 = add i32 %1, 1
  %3 = sext i32 %2 to i64
  %4 = getelementptr inbounds i8*, i8** %args.argv, i64 %3
  %5 = load i8*, i8** %4
  %6 = call i32 @atoi(i8* %5)
  store i32 %6, i32* %arg1
  %7 = add i32 1, 0
  %8 = add i32 %7, 1
  %9 = sext i32 %8 to i64
  %10 = getelementptr inbounds i8*, i8** %args.argv, i64 %9
  %11 = load i8*, i8** %10
  %12 = call i32 @atoi(i8* %11)
  store i32 %12, i32* %arg2
  %13 = load i32, i32* %arg1
  %14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %13)
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  %16 = load i32, i32* %arg2
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %16)
  %18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.1, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

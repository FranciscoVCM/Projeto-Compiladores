declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"

@.strlit.0 = private constant [2 x i8] c"\0A\00"
@.strlit.1 = private constant [2 x i8] c"\0A\00"

define i32 @_count_StringArray(i32 %x.argc, i8** %x.argv) {
  %1 = sub i32 %x.argc, 1
  ret i32 %1
}

define i32 @_first_StringArray(i32 %x.argc, i8** %x.argv) {
  %1 = add i32 0, 0
  %2 = add i32 %1, 1
  %3 = sext i32 %2 to i64
  %4 = getelementptr inbounds i8*, i8** %x.argv, i64 %3
  %5 = load i8*, i8** %4
  %6 = call i32 @atoi(i8* %5)
  ret i32 %6
}

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %1 = call i32 @_count_StringArray(i32 %args.argc, i8** %args.argv)
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %1)
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  %4 = call i32 @_first_StringArray(i32 %args.argc, i8** %args.argv)
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %4)
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.1, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

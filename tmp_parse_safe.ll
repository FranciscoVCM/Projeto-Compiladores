declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"
@.empty_str = private constant [1 x i8] c"\00"

@.strlit.0 = private constant [2 x i8] c"\0A\00"

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %1 = add i32 0, 0
  %2 = icmp sge i32 %1, 0
  %3 = add i32 %1, 1
  %4 = icmp slt i32 %3, %args.argc
  %5 = and i1 %2, %4
  br i1 %5, label %L1_parse_ok, label %L1_parse_bad

L1_parse_ok:
  %6 = sext i32 %3 to i64
  %7 = getelementptr inbounds i8*, i8** %args.argv, i64 %6
  %8 = load i8*, i8** %7
  br label %L1_parse_end

L1_parse_bad:
  br label %L1_parse_end

L1_parse_end:
  %9 = phi i8* [ %8, %L1_parse_ok ], [ getelementptr inbounds ([1 x i8], [1 x i8]* @.empty_str, i32 0, i32 0), %L1_parse_bad ]
  %10 = call i32 @atoi(i8* %9)
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %10)
  %12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

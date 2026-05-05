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
  %arg1 = alloca i32
  store i32 0, i32* %arg1
  %arg2 = alloca i32
  store i32 0, i32* %arg2
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
  store i32 %10, i32* %arg1
  %11 = add i32 1, 0
  %12 = icmp sge i32 %11, 0
  %13 = add i32 %11, 1
  %14 = icmp slt i32 %13, %args.argc
  %15 = and i1 %12, %14
  br i1 %15, label %L2_parse_ok, label %L2_parse_bad

L2_parse_ok:
  %16 = sext i32 %13 to i64
  %17 = getelementptr inbounds i8*, i8** %args.argv, i64 %16
  %18 = load i8*, i8** %17
  br label %L2_parse_end

L2_parse_bad:
  br label %L2_parse_end

L2_parse_end:
  %19 = phi i8* [ %18, %L2_parse_ok ], [ getelementptr inbounds ([1 x i8], [1 x i8]* @.empty_str, i32 0, i32 0), %L2_parse_bad ]
  %20 = call i32 @atoi(i8* %19)
  store i32 %20, i32* %arg2
  %21 = load i32, i32* %arg1
  %22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %21)
  %23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  %24 = load i32, i32* %arg2
  %25 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %24)
  %26 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.1, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"
@.empty_str = private constant [1 x i8] c"\00"

@.strlit.0 = private constant [19 x i8] c"I have a parameter\00"
@.strlit.1 = private constant [25 x i8] c"I don't have a parameter\00"
@.strlit.2 = private constant [2 x i8] c"\0A\00"

@overload = global i32 0

define void @_overload_int(i32 %n.param) {
  %n = alloca i32
  store i32 %n.param, i32* %n
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.strlit.0, i32 0, i32 0))
  ret void
}

define void @_overload() {
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.strlit.1, i32 0, i32 0))
  ret void
}

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %1 = sub i32 %args.argc, 1
  %2 = add i32 0, 0
  %3 = icmp sgt i32 %1, %2
  br i1 %3, label %L1_if_then, label %L1_if_else

L1_if_then:
  %4 = add i32 0, 0
  %5 = icmp sge i32 %4, 0
  %6 = add i32 %4, 1
  %7 = icmp slt i32 %6, %args.argc
  %8 = and i1 %5, %7
  br i1 %8, label %L2_parse_ok, label %L2_parse_bad

L2_parse_ok:
  %9 = sext i32 %6 to i64
  %10 = getelementptr inbounds i8*, i8** %args.argv, i64 %9
  %11 = load i8*, i8** %10
  br label %L2_parse_end

L2_parse_bad:
  br label %L2_parse_end

L2_parse_end:
  %12 = phi i8* [ %11, %L2_parse_ok ], [ getelementptr inbounds ([1 x i8], [1 x i8]* @.empty_str, i32 0, i32 0), %L2_parse_bad ]
  %13 = call i32 @atoi(i8* %12)
  call void @_overload_int(i32 %13)
  br label %L1_if_end

L1_if_else:
  call void @_overload()
  br label %L1_if_end

L1_if_end:
  %14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.2, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

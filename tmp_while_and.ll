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
  %i = alloca i32
  store i32 0, i32* %i
  %1 = add i32 0, 0
  store i32 %1, i32* %i
  br label %L1_while_cond

L1_while_cond:
  %2 = load i32, i32* %i
  %3 = add i32 100000, 0
  %4 = icmp slt i32 %2, %3
  br i1 %4, label %L2_and_right, label %L2_and_false

L2_and_right:
  %5 = add i32 1, 0
  %6 = add i32 1, 0
  %7 = icmp eq i32 %5, %6
  br label %L2_and_end

L2_and_false:
  br label %L2_and_end

L2_and_end:
  %8 = phi i1 [ %7, %L2_and_right ], [ 0, %L2_and_false ]
  br i1 %8, label %L1_while_body, label %L1_while_end

L1_while_body:
  %9 = load i32, i32* %i
  %10 = add i32 1, 0
  %11 = add i32 %9, %10
  store i32 %11, i32* %i
  br label %L1_while_cond

L1_while_end:
  %12 = load i32, i32* %i
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %12)
  %14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

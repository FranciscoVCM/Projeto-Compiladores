declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"

@.strlit.0 = private constant [2 x i8] c"\0A\00"

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %i = alloca i32
  %acc = alloca i32
  br label %L1_while_cond

L1_while_cond:
  %1 = load i32, i32* %i
  %2 = add i32 5, 0
  %3 = icmp slt i32 %1, %2
  br i1 %3, label %L1_while_body, label %L1_while_end

L1_while_body:
  %4 = load i32, i32* %acc
  %5 = load i32, i32* %i
  %6 = add i32 %4, %5
  store i32 %6, i32* %acc
  %7 = load i32, i32* %i
  %8 = add i32 1, 0
  %9 = add i32 %7, %8
  store i32 %9, i32* %i
  br label %L1_while_cond

L1_while_end:
  %10 = load i32, i32* %acc
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %10)
  %12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.0, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

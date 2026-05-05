declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"
@.empty_str = private constant [1 x i8] c"\00"
define i32 @_factorial_int(i32 %n.param) {
  %n = alloca i32
  store i32 %n.param, i32* %n
  %1 = load i32, i32* %n
  %2 = add i32 0, 0
  %3 = icmp eq i32 %1, %2
  br i1 %3, label %L1_if_then, label %L1_if_else

L1_if_then:
  %4 = add i32 1, 0
  ret i32 %4

L1_if_else:
  br label %L1_if_end

L1_if_end:
  %5 = load i32, i32* %n
  %6 = load i32, i32* %n
  %7 = add i32 1, 0
  %8 = sub i32 %6, %7
  %9 = call i32 @_factorial_int(i32 %8)
  %10 = mul i32 %5, %9
  ret i32 %10
}

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %argument = alloca i32
  store i32 0, i32* %argument
  %1 = add i32 7, 0
  store i32 %1, i32* %argument
  %2 = load i32, i32* %argument
  %3 = call i32 @_factorial_int(i32 %2)
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %3)
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

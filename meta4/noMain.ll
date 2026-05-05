declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"
@.empty_str = private constant [1 x i8] c"\00"
define i32 @_a_int(i32 %input.param) {
  %input = alloca i32
  store i32 %input.param, i32* %input
  %1 = load i32, i32* %input
  ret i32 %1
}

define i32 @_b_int(i32 %input.param) {
  %input = alloca i32
  store i32 %input.param, i32* %input
  %1 = load i32, i32* %input
  ret i32 %1
}

define i32 @main(i32 %argc, i8** %argv) {
  ret i32 0
}

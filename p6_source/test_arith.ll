declare i32 @_read(i32)
declare i32 @_write(i32)

define i32 @_calc(i32 %x) {
  %1 = add i32 %x, 0
  %2 = add i32 2, 0
  %3 = add i32 3, 0
  %4 = mul i32 %2, %3
  %5 = add i32 %1, %4
  %6 = add i32 4, 0
  %7 = add i32 2, 0
  %8 = sdiv i32 %6, %7
  %9 = sub i32 %5, %8
  ret i32 %9
}

define i32 @_main(i32 %i) {
  %1 = add i32 10, 0
  %2 = call i32 @_calc(i32 %1)
  ret i32 %2
}

define i32 @main() {
  %1 = call i32 @_main(i32 0)
  ret i32 %1
}

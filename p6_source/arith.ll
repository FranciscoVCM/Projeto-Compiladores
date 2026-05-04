declare i32 @_read(i32)
declare i32 @_write(i32)

define i32 @_arith(i32 %a, i32 %b) {
  %1 = add i32 %a, 0
  %2 = add i32 %a, 0
  %3 = add i32 %b, 0
  %4 = sdiv i32 %2, %3
  %5 = add i32 %b, 0
  %6 = mul i32 %4, %5
  %7 = sub i32 %1, %6
  ret i32 %7
}


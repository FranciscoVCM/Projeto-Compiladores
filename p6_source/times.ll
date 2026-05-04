declare i32 @_read(i32)
declare i32 @_write(i32)

define i32 @_times(i32 %a, i32 %b) {
  %1 = add i32 %a, 0
  %2 = add i32 %b, 0
  %3 = mul i32 %1, %2
  ret i32 %3
}


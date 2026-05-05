declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"
@.empty_str = private constant [1 x i8] c"\00"

@.strlit.0 = private constant [20 x i8] c"I have two doubles\0A\00"
@.strlit.1 = private constant [19 x i8] c"I have one double\0A\00"
@.strlit.2 = private constant [16 x i8] c"I have one int\0A\00"
@.strlit.3 = private constant [19 x i8] c"I'm the fake main\0A\00"
@.strlit.4 = private constant [2 x i8] c"\0A\00"
@.strlit.5 = private constant [5 x i8] c"\0Aa:\0A\00"
@.strlit.6 = private constant [11 x i8] c"Before if\0A\00"
@.strlit.7 = private constant [11 x i8] c"After ifs\0A\00"
@.strlit.8 = private constant [11 x i8] c"After ifs\0A\00"
@.strlit.9 = private constant [2 x i8] c"\0A\00"
@.strlit.10 = private constant [2 x i8] c"\0A\00"
@.strlit.11 = private constant [14 x i8] c"Before while\0A\00"

@overload = global i32 0

define i1 @_overload_boolean(i1 %n.param) {
  %n = alloca i1
  store i1 %n.param, i1* %n
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.strlit.0, i32 0, i32 0))
  %2 = icmp ne i1 0, 0
  ret i1 %2
}

define double @_overload_double(double %n.param) {
  %n = alloca double
  store double %n.param, double* %n
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.strlit.1, i32 0, i32 0))
  %2 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %3 = add i32 2, 0
  %4 = sitofp i32 %3 to double
  %5 = fmul double %2, %4
  %6 = add i32 2, 0
  %7 = call i32 @_main_int(i32 %6)
  %8 = add i32 5, 0
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %L1_div_zero, label %L1_div_ok

L1_div_ok:
  %10 = sdiv i32 %7, %8
  br label %L1_div_end

L1_div_zero:
  br label %L1_div_end

L1_div_end:
  %11 = phi i32 [ %10, %L1_div_ok ], [ 0, %L1_div_zero ]
  %12 = add i32 6, 0
  %13 = mul i32 %11, %12
  %14 = sitofp i32 %13 to double
  %15 = fadd double %5, %14
  %16 = add i32 2, 0
  %17 = add i32 3, 0
  %18 = mul i32 %16, %17
  %19 = sitofp i32 %18 to double
  %20 = fadd double %15, %19
  %21 = add i32 3, 0
  %22 = add i32 4, 0
  %23 = mul i32 %21, %22
  %24 = sitofp i32 %23 to double
  %25 = fadd double %20, %24
  %26 = add i32 2, 0
  %27 = add i32 8, 0
  %28 = mul i32 %26, %27
  %29 = sitofp i32 %28 to double
  %30 = fadd double %25, %29
  %31 = add i32 5, 0
  %32 = add i32 9, 0
  %33 = mul i32 %31, %32
  %34 = sitofp i32 %33 to double
  %35 = fadd double %30, %34
  %36 = add i32 2, 0
  %37 = add i32 2, 0
  %38 = call i32 @_overload_int_int(i32 %36, i32 %37)
  %39 = sitofp i32 %38 to double
  %40 = fadd double %35, %39
  ret double %40
}

define i32 @_overload_double_double(double %b.param, double %b1.param) {
  %b = alloca double
  store double %b.param, double* %b
  %b1 = alloca double
  store double %b1.param, double* %b1
  %overload = alloca double
  store double 0.000000e+00, double* %overload
  %1 = add i32 2, 0
  %2 = load i32, i32* @overload
  %3 = add i32 %1, %2
  store i32 %3, i32* @overload
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.strlit.2, i32 0, i32 0))
  %5 = add i32 5, 0
  ret i32 %5
}

define i32 @_overload_int_int(i32 %b.param, i32 %b1.param) {
  %b = alloca i32
  store i32 %b.param, i32* %b
  %b1 = alloca i32
  store i32 %b1.param, i32* %b1
  %1 = add i32 5, 0
  ret i32 %1
}

define i32 @_main_int(i32 %n.param) {
  %n = alloca i32
  store i32 %n.param, i32* %n
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.strlit.3, i32 0, i32 0))
  %2 = add i32 5, 0
  ret i32 %2
}

define void @_main_StringArray(i32 %args.argc, i8** %args.argv) {
  %a = alloca i32
  store i32 0, i32* %a
  %d = alloca double
  store double 0.000000e+00, double* %d
  %b = alloca i32
  store i32 0, i32* %b
  %b1 = alloca i1
  store i1 0, i1* %b1
  %d1 = alloca double
  store double 0.000000e+00, double* %d1
  %i = alloca i32
  store i32 0, i32* %i
  %j = alloca i32
  store i32 0, i32* %j
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
  %14 = sitofp i32 %13 to double
  %15 = call double @_overload_double(double %14)
  br label %L1_if_end

L1_if_else:
  %16 = add i32 5, 0
  %17 = sitofp i32 %16 to double
  %18 = call double @_overload_double(double %17)
  br label %L1_if_end

L1_if_end:
  %19 = icmp ne i1 0, 0
  %20 = xor i1 %19, true
  br i1 %20, label %L3print_true, label %L3print_false

L3print_true:
  %21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str_true, i32 0, i32 0))
  br label %L3print_end

L3print_false:
  %22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str_false, i32 0, i32 0))
  br label %L3print_end

L3print_end:
  %23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.4, i32 0, i32 0))
  %24 = add i32 2222222, 0
  store i32 %24, i32* %a
  %25 = fadd double 2.32323320000000000e+08, 0.000000e+00
  store double %25, double* %d
  %26 = add i32 3, 0
  store i32 %26, i32* %b
  %27 = load i32, i32* %a
  %28 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %27)
  %29 = icmp ne i1 1, 0
  store i1 %29, i1* %b1
  %30 = load i32, i32* %a
  %31 = load i32, i32* %a
  %32 = add i32 %30, %31
  %33 = load i32, i32* %a
  %34 = add i32 %32, %33
  %35 = add i32 8, 0
  %36 = add i32 2, 0
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %L4_mod_zero, label %L4_mod_ok

L4_mod_ok:
  %38 = srem i32 %35, %36
  br label %L4_mod_end

L4_mod_zero:
  br label %L4_mod_end

L4_mod_end:
  %39 = phi i32 [ %38, %L4_mod_ok ], [ 0, %L4_mod_zero ]
  %40 = add i32 %34, %39
  %41 = load double, double* %d
  %42 = add i32 3, 0
  %43 = sitofp i32 %42 to double
  %44 = fdiv double %41, %43
  %45 = sitofp i32 %40 to double
  %46 = fadd double %45, %44
  %47 = load i32, i32* %a
  %48 = load double, double* %d
  %49 = sitofp i32 %47 to double
  %50 = fmul double %49, %48
  %51 = fadd double %46, %50
  %52 = load double, double* %d
  %53 = fadd double %51, %52
  %54 = load i32, i32* %a
  %55 = sitofp i32 %54 to double
  %56 = fsub double %53, %55
  %57 = load i32, i32* %a
  %58 = load i32, i32* %b
  %59 = mul i32 %57, %58
  %60 = load double, double* %d
  %61 = sitofp i32 %59 to double
  %62 = fdiv double %61, %60
  %63 = load i32, i32* %a
  %64 = load i32, i32* %b
  %65 = mul i32 %63, %64
  %66 = load double, double* %d
  %67 = sitofp i32 %65 to double
  %68 = fdiv double %67, %66
  %69 = fmul double %62, %68
  %70 = fadd double %56, %69
  %71 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %72 = call double @_overload_double(double %71)
  %73 = fadd double %70, %72
  %74 = add i32 1, 0
  %75 = add i32 1, 0
  %76 = call i32 @_overload_int_int(i32 %74, i32 %75)
  %77 = sitofp i32 %76 to double
  store double %77, double* %d
  %78 = fadd double %73, %77
  %79 = add i32 5, 0
  %80 = call i32 @_main_int(i32 %79)
  %81 = sitofp i32 %80 to double
  %82 = fadd double %78, %81
  %83 = sub i32 %args.argc, 1
  %84 = add i32 1, 0
  %85 = sub i32 %83, %84
  %86 = icmp sge i32 %85, 0
  %87 = add i32 %85, 1
  %88 = icmp slt i32 %87, %args.argc
  %89 = and i1 %86, %88
  br i1 %89, label %L5_parse_ok, label %L5_parse_bad

L5_parse_ok:
  %90 = sext i32 %87 to i64
  %91 = getelementptr inbounds i8*, i8** %args.argv, i64 %90
  %92 = load i8*, i8** %91
  br label %L5_parse_end

L5_parse_bad:
  br label %L5_parse_end

L5_parse_end:
  %93 = phi i8* [ %92, %L5_parse_ok ], [ getelementptr inbounds ([1 x i8], [1 x i8]* @.empty_str, i32 0, i32 0), %L5_parse_bad ]
  %94 = call i32 @atoi(i8* %93)
  %95 = sitofp i32 %94 to double
  %96 = fadd double %82, %95
  %97 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %96)
  %98 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.strlit.5, i32 0, i32 0))
  %99 = load i32, i32* %a
  %100 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %99)
  %101 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.strlit.6, i32 0, i32 0))
  %102 = load i32, i32* %a
  %103 = add i32 2, 0
  %104 = add i32 2, 0
  %105 = mul i32 %103, %104
  %106 = add i32 3, 0
  %107 = add i32 5, 0
  %108 = icmp eq i32 %107, 0
  br i1 %108, label %L7_div_zero, label %L7_div_ok

L7_div_ok:
  %109 = sdiv i32 %106, %107
  br label %L7_div_end

L7_div_zero:
  br label %L7_div_end

L7_div_end:
  %110 = phi i32 [ %109, %L7_div_ok ], [ 0, %L7_div_zero ]
  %111 = add i32 %105, %110
  %112 = add i32 5, 0
  %113 = call i32 @_main_int(i32 %112)
  %114 = add i32 %111, %113
  %115 = icmp sge i32 %102, %114
  br i1 %115, label %L6_if_then, label %L6_if_else

L6_if_then:
  %116 = load i32, i32* %a
  %117 = add i32 2, 0
  %118 = icmp sle i32 %116, %117
  br i1 %118, label %L8_if_then, label %L8_if_else

L8_if_then:
  %119 = add i32 2, 0
  %120 = load i32, i32* %a
  %121 = icmp sge i32 %119, %120
  br i1 %121, label %L9_if_then, label %L9_if_else

L9_if_then:
  %122 = add i32 2, 0
  %123 = load i32, i32* %a
  %124 = icmp sle i32 %122, %123
  br i1 %124, label %L10_if_then, label %L10_if_else

L10_if_then:
  %125 = load i32, i32* %a
  %126 = add i32 2, 0
  %127 = icmp eq i32 %125, %126
  br i1 %127, label %L11_if_then, label %L11_if_else

L11_if_then:
  %128 = add i32 2, 0
  %129 = load i32, i32* %a
  %130 = icmp eq i32 %128, %129
  br i1 %130, label %L12_if_then, label %L12_if_else

L12_if_then:
  %131 = load i32, i32* %a
  %132 = add i32 2, 0
  %133 = icmp sgt i32 %131, %132
  br i1 %133, label %L13_if_then, label %L13_if_else

L13_if_then:
  %134 = load i32, i32* %a
  %135 = add i32 2, 0
  %136 = icmp slt i32 %134, %135
  br i1 %136, label %L14_if_then, label %L14_if_else

L14_if_then:
  %137 = add i32 2, 0
  %138 = load i32, i32* %a
  %139 = icmp sgt i32 %137, %138
  br i1 %139, label %L15_if_then, label %L15_if_else

L15_if_then:
  %140 = add i32 2, 0
  %141 = load i32, i32* %a
  %142 = icmp slt i32 %140, %141
  br i1 %142, label %L16_if_then, label %L16_if_else

L16_if_then:
  %143 = load i32, i32* %a
  %144 = add i32 2, 0
  %145 = icmp ne i32 %143, %144
  br i1 %145, label %L17_if_then, label %L17_if_else

L17_if_then:
  %146 = add i32 2, 0
  %147 = load i32, i32* %a
  %148 = icmp ne i32 %146, %147
  br i1 %148, label %L18_if_then, label %L18_if_else

L18_if_then:
  br label %L18_if_end

L18_if_else:
  br label %L18_if_end

L18_if_end:
  br label %L17_if_end

L17_if_else:
  br label %L17_if_end

L17_if_end:
  br label %L16_if_end

L16_if_else:
  br label %L16_if_end

L16_if_end:
  br label %L15_if_end

L15_if_else:
  br label %L15_if_end

L15_if_end:
  br label %L14_if_end

L14_if_else:
  br label %L14_if_end

L14_if_end:
  br label %L13_if_end

L13_if_else:
  br label %L13_if_end

L13_if_end:
  br label %L12_if_end

L12_if_else:
  br label %L12_if_end

L12_if_end:
  br label %L11_if_end

L11_if_else:
  br label %L11_if_end

L11_if_end:
  br label %L10_if_end

L10_if_else:
  br label %L10_if_end

L10_if_end:
  br label %L9_if_end

L9_if_else:
  br label %L9_if_end

L9_if_end:
  br label %L8_if_end

L8_if_else:
  br label %L8_if_end

L8_if_end:
  br label %L6_if_end

L6_if_else:
  br label %L6_if_end

L6_if_end:
  %149 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.strlit.7, i32 0, i32 0))
  %150 = load double, double* %d
  %151 = add i32 2, 0
  %152 = sitofp i32 %151 to double
  %153 = fcmp oge double %150, %152
  br i1 %153, label %L19_if_then, label %L19_if_else

L19_if_then:
  %154 = load double, double* %d
  %155 = add i32 2, 0
  %156 = sitofp i32 %155 to double
  %157 = fcmp ole double %154, %156
  br i1 %157, label %L20_if_then, label %L20_if_else

L20_if_then:
  %158 = add i32 2, 0
  %159 = load double, double* %d
  %160 = sitofp i32 %158 to double
  %161 = fcmp oge double %160, %159
  br i1 %161, label %L21_if_then, label %L21_if_else

L21_if_then:
  %162 = add i32 2, 0
  %163 = load double, double* %d
  %164 = sitofp i32 %162 to double
  %165 = fcmp ole double %164, %163
  br i1 %165, label %L22_if_then, label %L22_if_else

L22_if_then:
  %166 = load double, double* %d
  %167 = add i32 2, 0
  %168 = sitofp i32 %167 to double
  %169 = fcmp oeq double %166, %168
  br i1 %169, label %L23_if_then, label %L23_if_else

L23_if_then:
  %170 = add i32 2, 0
  %171 = load double, double* %d
  %172 = sitofp i32 %170 to double
  %173 = fcmp oeq double %172, %171
  br i1 %173, label %L24_if_then, label %L24_if_else

L24_if_then:
  %174 = load double, double* %d
  %175 = add i32 2, 0
  %176 = sitofp i32 %175 to double
  %177 = fcmp ogt double %174, %176
  br i1 %177, label %L25_if_then, label %L25_if_else

L25_if_then:
  %178 = load double, double* %d
  %179 = add i32 2, 0
  %180 = sitofp i32 %179 to double
  %181 = fcmp olt double %178, %180
  br i1 %181, label %L26_if_then, label %L26_if_else

L26_if_then:
  %182 = add i32 2, 0
  %183 = load double, double* %d
  %184 = sitofp i32 %182 to double
  %185 = fcmp ogt double %184, %183
  br i1 %185, label %L27_if_then, label %L27_if_else

L27_if_then:
  %186 = add i32 2, 0
  %187 = load double, double* %d
  %188 = sitofp i32 %186 to double
  %189 = fcmp olt double %188, %187
  br i1 %189, label %L28_if_then, label %L28_if_else

L28_if_then:
  %190 = load double, double* %d
  %191 = add i32 2, 0
  %192 = sitofp i32 %191 to double
  %193 = fcmp one double %190, %192
  br i1 %193, label %L29_if_then, label %L29_if_else

L29_if_then:
  %194 = add i32 2, 0
  %195 = load double, double* %d
  %196 = sitofp i32 %194 to double
  %197 = fcmp one double %196, %195
  br i1 %197, label %L30_if_then, label %L30_if_else

L30_if_then:
  br label %L30_if_end

L30_if_else:
  br label %L30_if_end

L30_if_end:
  br label %L29_if_end

L29_if_else:
  br label %L29_if_end

L29_if_end:
  br label %L28_if_end

L28_if_else:
  br label %L28_if_end

L28_if_end:
  br label %L27_if_end

L27_if_else:
  br label %L27_if_end

L27_if_end:
  br label %L26_if_end

L26_if_else:
  br label %L26_if_end

L26_if_end:
  br label %L25_if_end

L25_if_else:
  br label %L25_if_end

L25_if_end:
  br label %L24_if_end

L24_if_else:
  br label %L24_if_end

L24_if_end:
  br label %L23_if_end

L23_if_else:
  br label %L23_if_end

L23_if_end:
  br label %L22_if_end

L22_if_else:
  br label %L22_if_end

L22_if_end:
  br label %L21_if_end

L21_if_else:
  br label %L21_if_end

L21_if_end:
  br label %L20_if_end

L20_if_else:
  br label %L20_if_end

L20_if_end:
  br label %L19_if_end

L19_if_else:
  br label %L19_if_end

L19_if_end:
  %198 = load double, double* %d
  %199 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %200 = fcmp oge double %198, %199
  br i1 %200, label %L31_if_then, label %L31_if_else

L31_if_then:
  %201 = load double, double* %d
  %202 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %203 = fcmp ole double %201, %202
  br i1 %203, label %L32_if_then, label %L32_if_else

L32_if_then:
  %204 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %205 = load double, double* %d
  %206 = fcmp oge double %204, %205
  br i1 %206, label %L33_if_then, label %L33_if_else

L33_if_then:
  %207 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %208 = load double, double* %d
  %209 = fcmp ole double %207, %208
  br i1 %209, label %L34_if_then, label %L34_if_else

L34_if_then:
  %210 = load double, double* %d
  %211 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %212 = fcmp oeq double %210, %211
  br i1 %212, label %L35_if_then, label %L35_if_else

L35_if_then:
  %213 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %214 = load double, double* %d
  %215 = fcmp oeq double %213, %214
  br i1 %215, label %L36_if_then, label %L36_if_else

L36_if_then:
  %216 = load double, double* %d
  %217 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %218 = fcmp ogt double %216, %217
  br i1 %218, label %L37_if_then, label %L37_if_else

L37_if_then:
  %219 = load double, double* %d
  %220 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %221 = fcmp olt double %219, %220
  br i1 %221, label %L38_if_then, label %L38_if_else

L38_if_then:
  %222 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %223 = load double, double* %d
  %224 = fcmp ogt double %222, %223
  br i1 %224, label %L39_if_then, label %L39_if_else

L39_if_then:
  %225 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %226 = load double, double* %d
  %227 = fcmp olt double %225, %226
  br i1 %227, label %L40_if_then, label %L40_if_else

L40_if_then:
  %228 = load double, double* %d
  %229 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %230 = fcmp one double %228, %229
  br i1 %230, label %L41_if_then, label %L41_if_else

L41_if_then:
  %231 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %232 = load double, double* %d
  %233 = fcmp one double %231, %232
  br i1 %233, label %L42_if_then, label %L42_if_else

L42_if_then:
  br label %L42_if_end

L42_if_else:
  br label %L42_if_end

L42_if_end:
  br label %L41_if_end

L41_if_else:
  br label %L41_if_end

L41_if_end:
  br label %L40_if_end

L40_if_else:
  br label %L40_if_end

L40_if_end:
  br label %L39_if_end

L39_if_else:
  br label %L39_if_end

L39_if_end:
  br label %L38_if_end

L38_if_else:
  br label %L38_if_end

L38_if_end:
  br label %L37_if_end

L37_if_else:
  br label %L37_if_end

L37_if_end:
  br label %L36_if_end

L36_if_else:
  br label %L36_if_end

L36_if_end:
  br label %L35_if_end

L35_if_else:
  br label %L35_if_end

L35_if_end:
  br label %L34_if_end

L34_if_else:
  br label %L34_if_end

L34_if_end:
  br label %L33_if_end

L33_if_else:
  br label %L33_if_end

L33_if_end:
  br label %L32_if_end

L32_if_else:
  br label %L32_if_end

L32_if_end:
  br label %L31_if_end

L31_if_else:
  br label %L31_if_end

L31_if_end:
  %234 = load i1, i1* %b1
  %235 = icmp ne i1 1, 0
  %236 = icmp eq i1 %234, %235
  br i1 %236, label %L47_and_right, label %L47_and_false

L47_and_right:
  %237 = load double, double* %d
  %238 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %239 = fcmp oge double %237, %238
  br label %L47_and_end

L47_and_false:
  br label %L47_and_end

L47_and_end:
  %240 = phi i1 [ %239, %L47_and_right ], [ 0, %L47_and_false ]
  br i1 %240, label %L46_and_right, label %L46_and_false

L46_and_right:
  %241 = add i32 2, 0
  %242 = load double, double* %d
  %243 = sitofp i32 %241 to double
  %244 = fcmp oge double %243, %242
  br label %L46_and_end

L46_and_false:
  br label %L46_and_end

L46_and_end:
  %245 = phi i1 [ %244, %L46_and_right ], [ 0, %L46_and_false ]
  br i1 %245, label %L45_and_right, label %L45_and_false

L45_and_right:
  %246 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %247 = load double, double* %d
  %248 = fcmp ole double %246, %247
  br label %L45_and_end

L45_and_false:
  br label %L45_and_end

L45_and_end:
  %249 = phi i1 [ %248, %L45_and_right ], [ 0, %L45_and_false ]
  br i1 %249, label %L44_or_true, label %L44_or_right

L44_or_right:
  %250 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %251 = load double, double* %d
  %252 = fadd double 2.29999999999999982e+00, 0.000000e+00
  %253 = add i32 2, 0
  store i32 %253, i32* %a
  %254 = sitofp i32 %253 to double
  %255 = fadd double %252, %254
  %256 = add i32 2, 0
  %257 = sitofp i32 %256 to double
  store double %257, double* %d
  %258 = fadd double %255, %257
  store double %258, double* %d
  %259 = fadd double %251, %258
  %260 = fcmp oeq double %250, %259
  br label %L44_or_end

L44_or_true:
  br label %L44_or_end

L44_or_end:
  %261 = phi i1 [ 1, %L44_or_true ], [ %260, %L44_or_right ]
  br i1 %261, label %L43_if_then, label %L43_if_else

L43_if_then:
  %262 = icmp ne i1 1, 0
  %263 = load i1, i1* %b1
  %264 = icmp eq i1 %262, %263
  br i1 %264, label %L48_if_then, label %L48_if_else

L48_if_then:
  %265 = load i1, i1* %b1
  %266 = icmp ne i1 1, 0
  %267 = icmp ne i1 %265, %266
  br i1 %267, label %L49_if_then, label %L49_if_else

L49_if_then:
  %268 = icmp ne i1 1, 0
  %269 = load i1, i1* %b1
  %270 = icmp ne i1 %268, %269
  br i1 %270, label %L50_if_then, label %L50_if_else

L50_if_then:
  br label %L50_if_end

L50_if_else:
  br label %L50_if_end

L50_if_end:
  br label %L49_if_end

L49_if_else:
  br label %L49_if_end

L49_if_end:
  br label %L48_if_end

L48_if_else:
  br label %L48_if_end

L48_if_end:
  br label %L43_if_end

L43_if_else:
  br label %L43_if_end

L43_if_end:
  %271 = load i1, i1* %b1
  br i1 %271, label %L54_and_right, label %L54_and_false

L54_and_right:
  %272 = icmp ne i1 1, 0
  br label %L54_and_end

L54_and_false:
  br label %L54_and_end

L54_and_end:
  %273 = phi i1 [ %272, %L54_and_right ], [ 0, %L54_and_false ]
  br i1 %273, label %L53_or_true, label %L53_or_right

L53_or_right:
  %274 = load i1, i1* %b1
  br label %L53_or_end

L53_or_true:
  br label %L53_or_end

L53_or_end:
  %275 = phi i1 [ 1, %L53_or_true ], [ %274, %L53_or_right ]
  br i1 %275, label %L52_or_true, label %L52_or_right

L52_or_right:
  %276 = icmp ne i1 1, 0
  br i1 %276, label %L55_and_right, label %L55_and_false

L55_and_right:
  %277 = load i1, i1* %b1
  %278 = xor i1 %277, true
  %279 = icmp ne i1 0, 0
  %280 = xor i1 %278, %279
  br label %L55_and_end

L55_and_false:
  br label %L55_and_end

L55_and_end:
  %281 = phi i1 [ %280, %L55_and_right ], [ 0, %L55_and_false ]
  br label %L52_or_end

L52_or_true:
  br label %L52_or_end

L52_or_end:
  %282 = phi i1 [ 1, %L52_or_true ], [ %281, %L55_and_end ]
  br i1 %282, label %L51_if_then, label %L51_if_else

L51_if_then:
  %283 = icmp ne i1 1, 0
  br i1 %283, label %L59_and_right, label %L59_and_false

L59_and_right:
  %284 = load i1, i1* %b1
  br label %L59_and_end

L59_and_false:
  br label %L59_and_end

L59_and_end:
  %285 = phi i1 [ %284, %L59_and_right ], [ 0, %L59_and_false ]
  br i1 %285, label %L58_or_true, label %L58_or_right

L58_or_right:
  %286 = icmp ne i1 1, 0
  br label %L58_or_end

L58_or_true:
  br label %L58_or_end

L58_or_end:
  %287 = phi i1 [ 1, %L58_or_true ], [ %286, %L58_or_right ]
  br i1 %287, label %L57_or_true, label %L57_or_right

L57_or_right:
  %288 = load i1, i1* %b1
  br i1 %288, label %L60_and_right, label %L60_and_false

L60_and_right:
  %289 = icmp ne i1 0, 0
  %290 = load i1, i1* %b1
  %291 = xor i1 %290, true
  %292 = xor i1 %289, %291
  br label %L60_and_end

L60_and_false:
  br label %L60_and_end

L60_and_end:
  %293 = phi i1 [ %292, %L60_and_right ], [ 0, %L60_and_false ]
  br label %L57_or_end

L57_or_true:
  br label %L57_or_end

L57_or_end:
  %294 = phi i1 [ 1, %L57_or_true ], [ %293, %L60_and_end ]
  br i1 %294, label %L56_if_then, label %L56_if_else

L56_if_then:
  br label %L56_if_end

L56_if_else:
  br label %L56_if_end

L56_if_end:
  br label %L51_if_end

L51_if_else:
  br label %L51_if_end

L51_if_end:
  %295 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.strlit.8, i32 0, i32 0))
  %296 = load i32, i32* %a
  %297 = load double, double* %d
  %298 = fneg double %297
  %299 = sitofp i32 %296 to double
  %300 = fmul double %299, %298
  %301 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %300)
  %302 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.9, i32 0, i32 0))
  %303 = icmp ne i1 0, 0
  %304 = load i1, i1* %b1
  %305 = xor i1 %304, true
  %306 = xor i1 %303, %305
  br i1 %306, label %L61print_true, label %L61print_false

L61print_true:
  %307 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str_true, i32 0, i32 0))
  br label %L61print_end

L61print_false:
  %308 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str_false, i32 0, i32 0))
  br label %L61print_end

L61print_end:
  %309 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.10, i32 0, i32 0))
  %310 = sub i32 %args.argc, 1
  %311 = fadd double 1.10000000000000009e+00, 0.000000e+00
  %312 = sitofp i32 %310 to double
  %313 = fadd double %312, %311
  %314 = add i32 3, 0
  %315 = sitofp i32 %314 to double
  %316 = call double @_overload_double(double %315)
  %317 = fadd double %313, %316
  %318 = add i32 3, 0
  %319 = add i32 3, 0
  %320 = mul i32 %318, %319
  %321 = sitofp i32 %320 to double
  %322 = fadd double %317, %321
  %323 = add i32 2, 0
  %324 = sitofp i32 %323 to double
  %325 = fadd double %322, %324
  %326 = add i32 2, 0
  %327 = sitofp i32 %326 to double
  %328 = fadd double %325, %327
  %329 = add i32 2, 0
  %330 = sub i32 0, %329
  %331 = sitofp i32 %330 to double
  %332 = fadd double %328, %331
  %333 = add i32 3, 0
  %334 = add i32 3, 0
  %335 = icmp eq i32 %334, 0
  br i1 %335, label %L62_div_zero, label %L62_div_ok

L62_div_ok:
  %336 = sdiv i32 %333, %334
  br label %L62_div_end

L62_div_zero:
  br label %L62_div_end

L62_div_end:
  %337 = phi i32 [ %336, %L62_div_ok ], [ 0, %L62_div_zero ]
  %338 = sitofp i32 %337 to double
  %339 = fadd double %332, %338
  store double %339, double* %d1
  %340 = add i32 0, 0
  store i32 %340, i32* %i
  %341 = add i32 0, 0
  store i32 %341, i32* %j
  %342 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.strlit.11, i32 0, i32 0))
  br label %L63_while_cond

L63_while_cond:
  %343 = load i32, i32* %i
  %344 = add i32 10, 0
  %345 = icmp slt i32 %343, %344
  br i1 %345, label %L63_while_body, label %L63_while_end

L63_while_body:
  br label %L64_while_cond

L64_while_cond:
  %346 = add i32 10, 0
  %347 = load i32, i32* %i
  %348 = icmp sgt i32 %346, %347
  br i1 %348, label %L64_while_body, label %L64_while_end

L64_while_body:
  br label %L65_while_cond

L65_while_cond:
  %349 = add i32 20, 0
  %350 = load i32, i32* %j
  %351 = icmp sgt i32 %349, %350
  br i1 %351, label %L66_and_right, label %L66_and_false

L66_and_right:
  %352 = load i32, i32* %i
  %353 = add i32 10, 0
  %354 = icmp slt i32 %352, %353
  br label %L66_and_end

L66_and_false:
  br label %L66_and_end

L66_and_end:
  %355 = phi i1 [ %354, %L66_and_right ], [ 0, %L66_and_false ]
  br i1 %355, label %L65_while_body, label %L65_while_end

L65_while_body:
  %356 = load i32, i32* %i
  %357 = add i32 1, 0
  %358 = add i32 %356, %357
  store i32 %358, i32* %i
  %359 = load i32, i32* %j
  %360 = add i32 1, 0
  %361 = add i32 %359, %360
  store i32 %361, i32* %j
  %362 = load i32, i32* %i
  %363 = add i32 10, 0
  %364 = icmp eq i32 %362, %363
  br i1 %364, label %L67_if_then, label %L67_if_else

L67_if_then:
  %365 = load i32, i32* %j
  %366 = add i32 9, 0
  %367 = icmp eq i32 %365, %366
  br i1 %367, label %L68_if_then, label %L68_if_else

L68_if_then:
  br label %L68_if_end

L68_if_else:
  br label %L68_if_end

L68_if_end:
  br label %L67_if_end

L67_if_else:
  br label %L67_if_end

L67_if_end:
  br label %L65_while_cond

L65_while_end:
  br label %L64_while_cond

L64_while_end:
  br label %L63_while_cond

L63_while_end:
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

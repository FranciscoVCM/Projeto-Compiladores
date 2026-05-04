declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt_int = private constant [3 x i8] c"%d\00"
@.fmt_double = private constant [6 x i8] c"%.16e\00"
@.fmt_str = private constant [3 x i8] c"%s\00"
@.str_true = private constant [5 x i8] c"true\00"
@.str_false = private constant [6 x i8] c"false\00"

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
  %9 = sdiv i32 %7, %8
  %10 = add i32 6, 0
  %11 = mul i32 %9, %10
  %12 = sitofp i32 %11 to double
  %13 = fadd double %5, %12
  %14 = add i32 2, 0
  %15 = add i32 3, 0
  %16 = mul i32 %14, %15
  %17 = sitofp i32 %16 to double
  %18 = fadd double %13, %17
  %19 = add i32 3, 0
  %20 = add i32 4, 0
  %21 = mul i32 %19, %20
  %22 = sitofp i32 %21 to double
  %23 = fadd double %18, %22
  %24 = add i32 2, 0
  %25 = add i32 8, 0
  %26 = mul i32 %24, %25
  %27 = sitofp i32 %26 to double
  %28 = fadd double %23, %27
  %29 = add i32 5, 0
  %30 = add i32 9, 0
  %31 = mul i32 %29, %30
  %32 = sitofp i32 %31 to double
  %33 = fadd double %28, %32
  %34 = add i32 2, 0
  %35 = add i32 2, 0
  %36 = call i32 @_overload_int_int(i32 %34, i32 %35)
  %37 = sitofp i32 %36 to double
  %38 = fadd double %33, %37
  ret double %38
}

define i32 @_overload_double_double(double %b.param, double %b1.param) {
  %b = alloca double
  store double %b.param, double* %b
  %b1 = alloca double
  store double %b1.param, double* %b1
  %1 = add i32 2, 0
  %2 = load i32, i32* @overload
  %3 = add i32 %1, %2
  store i32 %3, i32* @overload
  %overload = alloca double
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
  %1 = sub i32 %args.argc, 1
  %2 = add i32 0, 0
  %3 = icmp sgt i32 %1, %2
  br i1 %3, label %L1_if_then, label %L1_if_else

L1_if_then:
  %4 = add i32 0, 0
  %5 = add i32 %4, 1
  %6 = sext i32 %5 to i64
  %7 = getelementptr inbounds i8*, i8** %args.argv, i64 %6
  %8 = load i8*, i8** %7
  %9 = call i32 @atoi(i8* %8)
  %10 = sitofp i32 %9 to double
  %11 = call double @_overload_double(double %10)
  br label %L1_if_end

L1_if_else:
  %12 = add i32 5, 0
  %13 = sitofp i32 %12 to double
  %14 = call double @_overload_double(double %13)
  br label %L1_if_end

L1_if_end:
  %15 = icmp ne i1 0, 0
  %16 = xor i1 %15, true
  br i1 %16, label %L2print_true, label %L2print_false

L2print_true:
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str_true, i32 0, i32 0))
  br label %L2print_end

L2print_false:
  %18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str_false, i32 0, i32 0))
  br label %L2print_end

L2print_end:
  %19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.4, i32 0, i32 0))
  %a = alloca i32
  %20 = add i32 2222222, 0
  store i32 %20, i32* %a
  %d = alloca double
  %21 = fadd double 2.32323320000000000e+08, 0.000000e+00
  store double %21, double* %d
  %b = alloca i32
  %22 = add i32 3, 0
  store i32 %22, i32* %b
  %23 = load i32, i32* %a
  %24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %23)
  %b1 = alloca i1
  %25 = icmp ne i1 1, 0
  store i1 %25, i1* %b1
  %26 = load i32, i32* %a
  %27 = load i32, i32* %a
  %28 = add i32 %26, %27
  %29 = load i32, i32* %a
  %30 = add i32 %28, %29
  %31 = add i32 8, 0
  %32 = add i32 2, 0
  %33 = srem i32 %31, %32
  %34 = add i32 %30, %33
  %35 = load double, double* %d
  %36 = add i32 3, 0
  %37 = sitofp i32 %36 to double
  %38 = fdiv double %35, %37
  %39 = sitofp i32 %34 to double
  %40 = fadd double %39, %38
  %41 = load i32, i32* %a
  %42 = load double, double* %d
  %43 = sitofp i32 %41 to double
  %44 = fmul double %43, %42
  %45 = fadd double %40, %44
  %46 = load double, double* %d
  %47 = fadd double %45, %46
  %48 = load i32, i32* %a
  %49 = sitofp i32 %48 to double
  %50 = fsub double %47, %49
  %51 = load i32, i32* %a
  %52 = load i32, i32* %b
  %53 = mul i32 %51, %52
  %54 = load double, double* %d
  %55 = sitofp i32 %53 to double
  %56 = fdiv double %55, %54
  %57 = load i32, i32* %a
  %58 = load i32, i32* %b
  %59 = mul i32 %57, %58
  %60 = load double, double* %d
  %61 = sitofp i32 %59 to double
  %62 = fdiv double %61, %60
  %63 = fmul double %56, %62
  %64 = fadd double %50, %63
  %65 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %66 = call double @_overload_double(double %65)
  %67 = fadd double %64, %66
  %68 = add i32 1, 0
  %69 = add i32 1, 0
  %70 = call i32 @_overload_int_int(i32 %68, i32 %69)
  %71 = sitofp i32 %70 to double
  store double %71, double* %d
  %72 = fadd double %67, %71
  %73 = add i32 5, 0
  %74 = call i32 @_main_int(i32 %73)
  %75 = sitofp i32 %74 to double
  %76 = fadd double %72, %75
  %77 = sub i32 %args.argc, 1
  %78 = add i32 1, 0
  %79 = sub i32 %77, %78
  %80 = add i32 %79, 1
  %81 = sext i32 %80 to i64
  %82 = getelementptr inbounds i8*, i8** %args.argv, i64 %81
  %83 = load i8*, i8** %82
  %84 = call i32 @atoi(i8* %83)
  %85 = sitofp i32 %84 to double
  %86 = fadd double %76, %85
  %87 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %86)
  %88 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.strlit.5, i32 0, i32 0))
  %89 = load i32, i32* %a
  %90 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %89)
  %91 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.strlit.6, i32 0, i32 0))
  %92 = load i32, i32* %a
  %93 = add i32 2, 0
  %94 = add i32 2, 0
  %95 = mul i32 %93, %94
  %96 = add i32 3, 0
  %97 = add i32 5, 0
  %98 = sdiv i32 %96, %97
  %99 = add i32 %95, %98
  %100 = add i32 5, 0
  %101 = call i32 @_main_int(i32 %100)
  %102 = add i32 %99, %101
  %103 = icmp sge i32 %92, %102
  br i1 %103, label %L3_if_then, label %L3_if_else

L3_if_then:
  %104 = load i32, i32* %a
  %105 = add i32 2, 0
  %106 = icmp sle i32 %104, %105
  br i1 %106, label %L4_if_then, label %L4_if_else

L4_if_then:
  %107 = add i32 2, 0
  %108 = load i32, i32* %a
  %109 = icmp sge i32 %107, %108
  br i1 %109, label %L5_if_then, label %L5_if_else

L5_if_then:
  %110 = add i32 2, 0
  %111 = load i32, i32* %a
  %112 = icmp sle i32 %110, %111
  br i1 %112, label %L6_if_then, label %L6_if_else

L6_if_then:
  %113 = load i32, i32* %a
  %114 = add i32 2, 0
  %115 = icmp eq i32 %113, %114
  br i1 %115, label %L7_if_then, label %L7_if_else

L7_if_then:
  %116 = add i32 2, 0
  %117 = load i32, i32* %a
  %118 = icmp eq i32 %116, %117
  br i1 %118, label %L8_if_then, label %L8_if_else

L8_if_then:
  %119 = load i32, i32* %a
  %120 = add i32 2, 0
  %121 = icmp sgt i32 %119, %120
  br i1 %121, label %L9_if_then, label %L9_if_else

L9_if_then:
  %122 = load i32, i32* %a
  %123 = add i32 2, 0
  %124 = icmp slt i32 %122, %123
  br i1 %124, label %L10_if_then, label %L10_if_else

L10_if_then:
  %125 = add i32 2, 0
  %126 = load i32, i32* %a
  %127 = icmp sgt i32 %125, %126
  br i1 %127, label %L11_if_then, label %L11_if_else

L11_if_then:
  %128 = add i32 2, 0
  %129 = load i32, i32* %a
  %130 = icmp slt i32 %128, %129
  br i1 %130, label %L12_if_then, label %L12_if_else

L12_if_then:
  %131 = load i32, i32* %a
  %132 = add i32 2, 0
  %133 = icmp ne i32 %131, %132
  br i1 %133, label %L13_if_then, label %L13_if_else

L13_if_then:
  %134 = add i32 2, 0
  %135 = load i32, i32* %a
  %136 = icmp ne i32 %134, %135
  br i1 %136, label %L14_if_then, label %L14_if_else

L14_if_then:
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
  br label %L7_if_end

L7_if_else:
  br label %L7_if_end

L7_if_end:
  br label %L6_if_end

L6_if_else:
  br label %L6_if_end

L6_if_end:
  br label %L5_if_end

L5_if_else:
  br label %L5_if_end

L5_if_end:
  br label %L4_if_end

L4_if_else:
  br label %L4_if_end

L4_if_end:
  br label %L3_if_end

L3_if_else:
  br label %L3_if_end

L3_if_end:
  %137 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.strlit.7, i32 0, i32 0))
  %138 = load double, double* %d
  %139 = add i32 2, 0
  %140 = sitofp i32 %139 to double
  %141 = fcmp oge double %138, %140
  br i1 %141, label %L15_if_then, label %L15_if_else

L15_if_then:
  %142 = load double, double* %d
  %143 = add i32 2, 0
  %144 = sitofp i32 %143 to double
  %145 = fcmp ole double %142, %144
  br i1 %145, label %L16_if_then, label %L16_if_else

L16_if_then:
  %146 = add i32 2, 0
  %147 = load double, double* %d
  %148 = sitofp i32 %146 to double
  %149 = fcmp oge double %148, %147
  br i1 %149, label %L17_if_then, label %L17_if_else

L17_if_then:
  %150 = add i32 2, 0
  %151 = load double, double* %d
  %152 = sitofp i32 %150 to double
  %153 = fcmp ole double %152, %151
  br i1 %153, label %L18_if_then, label %L18_if_else

L18_if_then:
  %154 = load double, double* %d
  %155 = add i32 2, 0
  %156 = sitofp i32 %155 to double
  %157 = fcmp oeq double %154, %156
  br i1 %157, label %L19_if_then, label %L19_if_else

L19_if_then:
  %158 = add i32 2, 0
  %159 = load double, double* %d
  %160 = sitofp i32 %158 to double
  %161 = fcmp oeq double %160, %159
  br i1 %161, label %L20_if_then, label %L20_if_else

L20_if_then:
  %162 = load double, double* %d
  %163 = add i32 2, 0
  %164 = sitofp i32 %163 to double
  %165 = fcmp ogt double %162, %164
  br i1 %165, label %L21_if_then, label %L21_if_else

L21_if_then:
  %166 = load double, double* %d
  %167 = add i32 2, 0
  %168 = sitofp i32 %167 to double
  %169 = fcmp olt double %166, %168
  br i1 %169, label %L22_if_then, label %L22_if_else

L22_if_then:
  %170 = add i32 2, 0
  %171 = load double, double* %d
  %172 = sitofp i32 %170 to double
  %173 = fcmp ogt double %172, %171
  br i1 %173, label %L23_if_then, label %L23_if_else

L23_if_then:
  %174 = add i32 2, 0
  %175 = load double, double* %d
  %176 = sitofp i32 %174 to double
  %177 = fcmp olt double %176, %175
  br i1 %177, label %L24_if_then, label %L24_if_else

L24_if_then:
  %178 = load double, double* %d
  %179 = add i32 2, 0
  %180 = sitofp i32 %179 to double
  %181 = fcmp one double %178, %180
  br i1 %181, label %L25_if_then, label %L25_if_else

L25_if_then:
  %182 = add i32 2, 0
  %183 = load double, double* %d
  %184 = sitofp i32 %182 to double
  %185 = fcmp one double %184, %183
  br i1 %185, label %L26_if_then, label %L26_if_else

L26_if_then:
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
  %186 = load double, double* %d
  %187 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %188 = fcmp oge double %186, %187
  br i1 %188, label %L27_if_then, label %L27_if_else

L27_if_then:
  %189 = load double, double* %d
  %190 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %191 = fcmp ole double %189, %190
  br i1 %191, label %L28_if_then, label %L28_if_else

L28_if_then:
  %192 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %193 = load double, double* %d
  %194 = fcmp oge double %192, %193
  br i1 %194, label %L29_if_then, label %L29_if_else

L29_if_then:
  %195 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %196 = load double, double* %d
  %197 = fcmp ole double %195, %196
  br i1 %197, label %L30_if_then, label %L30_if_else

L30_if_then:
  %198 = load double, double* %d
  %199 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %200 = fcmp oeq double %198, %199
  br i1 %200, label %L31_if_then, label %L31_if_else

L31_if_then:
  %201 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %202 = load double, double* %d
  %203 = fcmp oeq double %201, %202
  br i1 %203, label %L32_if_then, label %L32_if_else

L32_if_then:
  %204 = load double, double* %d
  %205 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %206 = fcmp ogt double %204, %205
  br i1 %206, label %L33_if_then, label %L33_if_else

L33_if_then:
  %207 = load double, double* %d
  %208 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %209 = fcmp olt double %207, %208
  br i1 %209, label %L34_if_then, label %L34_if_else

L34_if_then:
  %210 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %211 = load double, double* %d
  %212 = fcmp ogt double %210, %211
  br i1 %212, label %L35_if_then, label %L35_if_else

L35_if_then:
  %213 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %214 = load double, double* %d
  %215 = fcmp olt double %213, %214
  br i1 %215, label %L36_if_then, label %L36_if_else

L36_if_then:
  %216 = load double, double* %d
  %217 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %218 = fcmp one double %216, %217
  br i1 %218, label %L37_if_then, label %L37_if_else

L37_if_then:
  %219 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %220 = load double, double* %d
  %221 = fcmp one double %219, %220
  br i1 %221, label %L38_if_then, label %L38_if_else

L38_if_then:
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
  %222 = alloca i1
  %223 = alloca i1
  %224 = alloca i1
  %225 = alloca i1
  %226 = load i1, i1* %b1
  %227 = icmp ne i1 1, 0
  %228 = icmp eq i1 %226, %227
  br i1 %228, label %L43_and_right, label %L43_and_false

L43_and_right:
  %229 = load double, double* %d
  %230 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %231 = fcmp oge double %229, %230
  store i1 %231, i1* %225
  br label %L43_and_end

L43_and_false:
  store i1 0, i1* %225
  br label %L43_and_end

L43_and_end:
  %232 = load i1, i1* %225
  br i1 %232, label %L42_and_right, label %L42_and_false

L42_and_right:
  %233 = add i32 2, 0
  %234 = load double, double* %d
  %235 = sitofp i32 %233 to double
  %236 = fcmp oge double %235, %234
  store i1 %236, i1* %224
  br label %L42_and_end

L42_and_false:
  store i1 0, i1* %224
  br label %L42_and_end

L42_and_end:
  %237 = load i1, i1* %224
  br i1 %237, label %L41_and_right, label %L41_and_false

L41_and_right:
  %238 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %239 = load double, double* %d
  %240 = fcmp ole double %238, %239
  store i1 %240, i1* %223
  br label %L41_and_end

L41_and_false:
  store i1 0, i1* %223
  br label %L41_and_end

L41_and_end:
  %241 = load i1, i1* %223
  br i1 %241, label %L40_or_true, label %L40_or_right

L40_or_true:
  store i1 1, i1* %222
  br label %L40_or_end

L40_or_right:
  %242 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %243 = load double, double* %d
  %244 = fadd double 2.29999999999999982e+00, 0.000000e+00
  %245 = add i32 2, 0
  store i32 %245, i32* %a
  %246 = sitofp i32 %245 to double
  %247 = fadd double %244, %246
  %248 = add i32 2, 0
  %249 = sitofp i32 %248 to double
  store double %249, double* %d
  %250 = fadd double %247, %249
  store double %250, double* %d
  %251 = fadd double %243, %250
  %252 = fcmp oeq double %242, %251
  store i1 %252, i1* %222
  br label %L40_or_end

L40_or_end:
  %253 = load i1, i1* %222
  br i1 %253, label %L39_if_then, label %L39_if_else

L39_if_then:
  %254 = icmp ne i1 1, 0
  %255 = load i1, i1* %b1
  %256 = icmp eq i1 %254, %255
  br i1 %256, label %L44_if_then, label %L44_if_else

L44_if_then:
  %257 = load i1, i1* %b1
  %258 = icmp ne i1 1, 0
  %259 = icmp ne i1 %257, %258
  br i1 %259, label %L45_if_then, label %L45_if_else

L45_if_then:
  %260 = icmp ne i1 1, 0
  %261 = load i1, i1* %b1
  %262 = icmp ne i1 %260, %261
  br i1 %262, label %L46_if_then, label %L46_if_else

L46_if_then:
  br label %L46_if_end

L46_if_else:
  br label %L46_if_end

L46_if_end:
  br label %L45_if_end

L45_if_else:
  br label %L45_if_end

L45_if_end:
  br label %L44_if_end

L44_if_else:
  br label %L44_if_end

L44_if_end:
  br label %L39_if_end

L39_if_else:
  br label %L39_if_end

L39_if_end:
  %263 = alloca i1
  %264 = alloca i1
  %265 = alloca i1
  %266 = load i1, i1* %b1
  br i1 %266, label %L50_and_right, label %L50_and_false

L50_and_right:
  %267 = icmp ne i1 1, 0
  store i1 %267, i1* %265
  br label %L50_and_end

L50_and_false:
  store i1 0, i1* %265
  br label %L50_and_end

L50_and_end:
  %268 = load i1, i1* %265
  br i1 %268, label %L49_or_true, label %L49_or_right

L49_or_true:
  store i1 1, i1* %264
  br label %L49_or_end

L49_or_right:
  %269 = load i1, i1* %b1
  store i1 %269, i1* %264
  br label %L49_or_end

L49_or_end:
  %270 = load i1, i1* %264
  br i1 %270, label %L48_or_true, label %L48_or_right

L48_or_true:
  store i1 1, i1* %263
  br label %L48_or_end

L48_or_right:
  %271 = alloca i1
  %272 = icmp ne i1 1, 0
  br i1 %272, label %L51_and_right, label %L51_and_false

L51_and_right:
  %273 = load i1, i1* %b1
  %274 = xor i1 %273, true
  %275 = icmp ne i1 0, 0
  %276 = xor i1 %274, %275
  store i1 %276, i1* %271
  br label %L51_and_end

L51_and_false:
  store i1 0, i1* %271
  br label %L51_and_end

L51_and_end:
  %277 = load i1, i1* %271
  store i1 %277, i1* %263
  br label %L48_or_end

L48_or_end:
  %278 = load i1, i1* %263
  br i1 %278, label %L47_if_then, label %L47_if_else

L47_if_then:
  %279 = alloca i1
  %280 = alloca i1
  %281 = alloca i1
  %282 = icmp ne i1 1, 0
  br i1 %282, label %L55_and_right, label %L55_and_false

L55_and_right:
  %283 = load i1, i1* %b1
  store i1 %283, i1* %281
  br label %L55_and_end

L55_and_false:
  store i1 0, i1* %281
  br label %L55_and_end

L55_and_end:
  %284 = load i1, i1* %281
  br i1 %284, label %L54_or_true, label %L54_or_right

L54_or_true:
  store i1 1, i1* %280
  br label %L54_or_end

L54_or_right:
  %285 = icmp ne i1 1, 0
  store i1 %285, i1* %280
  br label %L54_or_end

L54_or_end:
  %286 = load i1, i1* %280
  br i1 %286, label %L53_or_true, label %L53_or_right

L53_or_true:
  store i1 1, i1* %279
  br label %L53_or_end

L53_or_right:
  %287 = alloca i1
  %288 = load i1, i1* %b1
  br i1 %288, label %L56_and_right, label %L56_and_false

L56_and_right:
  %289 = icmp ne i1 0, 0
  %290 = load i1, i1* %b1
  %291 = xor i1 %290, true
  %292 = xor i1 %289, %291
  store i1 %292, i1* %287
  br label %L56_and_end

L56_and_false:
  store i1 0, i1* %287
  br label %L56_and_end

L56_and_end:
  %293 = load i1, i1* %287
  store i1 %293, i1* %279
  br label %L53_or_end

L53_or_end:
  %294 = load i1, i1* %279
  br i1 %294, label %L52_if_then, label %L52_if_else

L52_if_then:
  br label %L52_if_end

L52_if_else:
  br label %L52_if_end

L52_if_end:
  br label %L47_if_end

L47_if_else:
  br label %L47_if_end

L47_if_end:
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
  br i1 %306, label %L57print_true, label %L57print_false

L57print_true:
  %307 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str_true, i32 0, i32 0))
  br label %L57print_end

L57print_false:
  %308 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str_false, i32 0, i32 0))
  br label %L57print_end

L57print_end:
  %309 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.10, i32 0, i32 0))
  %d1 = alloca double
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
  %335 = sdiv i32 %333, %334
  %336 = sitofp i32 %335 to double
  %337 = fadd double %332, %336
  store double %337, double* %d1
  %i = alloca i32
  %338 = add i32 0, 0
  store i32 %338, i32* %i
  %j = alloca i32
  %339 = add i32 0, 0
  store i32 %339, i32* %j
  %340 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.strlit.11, i32 0, i32 0))
  br label %L58_while_cond

L58_while_cond:
  %341 = load i32, i32* %i
  %342 = add i32 10, 0
  %343 = icmp slt i32 %341, %342
  br i1 %343, label %L58_while_body, label %L58_while_end

L58_while_body:
  br label %L59_while_cond

L59_while_cond:
  %344 = add i32 10, 0
  %345 = load i32, i32* %i
  %346 = icmp sgt i32 %344, %345
  br i1 %346, label %L59_while_body, label %L59_while_end

L59_while_body:
  br label %L60_while_cond

L60_while_cond:
  %347 = alloca i1
  %348 = add i32 20, 0
  %349 = load i32, i32* %j
  %350 = icmp sgt i32 %348, %349
  br i1 %350, label %L61_and_right, label %L61_and_false

L61_and_right:
  %351 = load i32, i32* %i
  %352 = add i32 10, 0
  %353 = icmp slt i32 %351, %352
  store i1 %353, i1* %347
  br label %L61_and_end

L61_and_false:
  store i1 0, i1* %347
  br label %L61_and_end

L61_and_end:
  %354 = load i1, i1* %347
  br i1 %354, label %L60_while_body, label %L60_while_end

L60_while_body:
  %355 = load i32, i32* %i
  %356 = add i32 1, 0
  %357 = add i32 %355, %356
  store i32 %357, i32* %i
  %358 = load i32, i32* %j
  %359 = add i32 1, 0
  %360 = add i32 %358, %359
  store i32 %360, i32* %j
  %361 = load i32, i32* %i
  %362 = add i32 10, 0
  %363 = icmp eq i32 %361, %362
  br i1 %363, label %L62_if_then, label %L62_if_else

L62_if_then:
  %364 = load i32, i32* %j
  %365 = add i32 9, 0
  %366 = icmp eq i32 %364, %365
  br i1 %366, label %L63_if_then, label %L63_if_else

L63_if_then:
  br label %L63_if_end

L63_if_else:
  br label %L63_if_end

L63_if_end:
  br label %L62_if_end

L62_if_else:
  br label %L62_if_end

L62_if_end:
  br label %L60_while_cond

L60_while_end:
  br label %L59_while_cond

L59_while_end:
  br label %L58_while_cond

L58_while_end:
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

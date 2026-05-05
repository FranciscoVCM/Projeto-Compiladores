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
  %37 = srem i32 %35, %36
  %38 = add i32 %34, %37
  %39 = load double, double* %d
  %40 = add i32 3, 0
  %41 = sitofp i32 %40 to double
  %42 = fdiv double %39, %41
  %43 = sitofp i32 %38 to double
  %44 = fadd double %43, %42
  %45 = load i32, i32* %a
  %46 = load double, double* %d
  %47 = sitofp i32 %45 to double
  %48 = fmul double %47, %46
  %49 = fadd double %44, %48
  %50 = load double, double* %d
  %51 = fadd double %49, %50
  %52 = load i32, i32* %a
  %53 = sitofp i32 %52 to double
  %54 = fsub double %51, %53
  %55 = load i32, i32* %a
  %56 = load i32, i32* %b
  %57 = mul i32 %55, %56
  %58 = load double, double* %d
  %59 = sitofp i32 %57 to double
  %60 = fdiv double %59, %58
  %61 = load i32, i32* %a
  %62 = load i32, i32* %b
  %63 = mul i32 %61, %62
  %64 = load double, double* %d
  %65 = sitofp i32 %63 to double
  %66 = fdiv double %65, %64
  %67 = fmul double %60, %66
  %68 = fadd double %54, %67
  %69 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %70 = call double @_overload_double(double %69)
  %71 = fadd double %68, %70
  %72 = add i32 1, 0
  %73 = add i32 1, 0
  %74 = call i32 @_overload_int_int(i32 %72, i32 %73)
  %75 = sitofp i32 %74 to double
  store double %75, double* %d
  %76 = fadd double %71, %75
  %77 = add i32 5, 0
  %78 = call i32 @_main_int(i32 %77)
  %79 = sitofp i32 %78 to double
  %80 = fadd double %76, %79
  %81 = sub i32 %args.argc, 1
  %82 = add i32 1, 0
  %83 = sub i32 %81, %82
  %84 = icmp sge i32 %83, 0
  %85 = add i32 %83, 1
  %86 = icmp slt i32 %85, %args.argc
  %87 = and i1 %84, %86
  br i1 %87, label %L4_parse_ok, label %L4_parse_bad

L4_parse_ok:
  %88 = sext i32 %85 to i64
  %89 = getelementptr inbounds i8*, i8** %args.argv, i64 %88
  %90 = load i8*, i8** %89
  br label %L4_parse_end

L4_parse_bad:
  br label %L4_parse_end

L4_parse_end:
  %91 = phi i8* [ %90, %L4_parse_ok ], [ getelementptr inbounds ([1 x i8], [1 x i8]* @.empty_str, i32 0, i32 0), %L4_parse_bad ]
  %92 = call i32 @atoi(i8* %91)
  %93 = sitofp i32 %92 to double
  %94 = fadd double %80, %93
  %95 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %94)
  %96 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.strlit.5, i32 0, i32 0))
  %97 = load i32, i32* %a
  %98 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_int, i32 0, i32 0), i32 %97)
  %99 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.strlit.6, i32 0, i32 0))
  %100 = load i32, i32* %a
  %101 = add i32 2, 0
  %102 = add i32 2, 0
  %103 = mul i32 %101, %102
  %104 = add i32 3, 0
  %105 = add i32 5, 0
  %106 = sdiv i32 %104, %105
  %107 = add i32 %103, %106
  %108 = add i32 5, 0
  %109 = call i32 @_main_int(i32 %108)
  %110 = add i32 %107, %109
  %111 = icmp sge i32 %100, %110
  br i1 %111, label %L5_if_then, label %L5_if_else

L5_if_then:
  %112 = load i32, i32* %a
  %113 = add i32 2, 0
  %114 = icmp sle i32 %112, %113
  br i1 %114, label %L6_if_then, label %L6_if_else

L6_if_then:
  %115 = add i32 2, 0
  %116 = load i32, i32* %a
  %117 = icmp sge i32 %115, %116
  br i1 %117, label %L7_if_then, label %L7_if_else

L7_if_then:
  %118 = add i32 2, 0
  %119 = load i32, i32* %a
  %120 = icmp sle i32 %118, %119
  br i1 %120, label %L8_if_then, label %L8_if_else

L8_if_then:
  %121 = load i32, i32* %a
  %122 = add i32 2, 0
  %123 = icmp eq i32 %121, %122
  br i1 %123, label %L9_if_then, label %L9_if_else

L9_if_then:
  %124 = add i32 2, 0
  %125 = load i32, i32* %a
  %126 = icmp eq i32 %124, %125
  br i1 %126, label %L10_if_then, label %L10_if_else

L10_if_then:
  %127 = load i32, i32* %a
  %128 = add i32 2, 0
  %129 = icmp sgt i32 %127, %128
  br i1 %129, label %L11_if_then, label %L11_if_else

L11_if_then:
  %130 = load i32, i32* %a
  %131 = add i32 2, 0
  %132 = icmp slt i32 %130, %131
  br i1 %132, label %L12_if_then, label %L12_if_else

L12_if_then:
  %133 = add i32 2, 0
  %134 = load i32, i32* %a
  %135 = icmp sgt i32 %133, %134
  br i1 %135, label %L13_if_then, label %L13_if_else

L13_if_then:
  %136 = add i32 2, 0
  %137 = load i32, i32* %a
  %138 = icmp slt i32 %136, %137
  br i1 %138, label %L14_if_then, label %L14_if_else

L14_if_then:
  %139 = load i32, i32* %a
  %140 = add i32 2, 0
  %141 = icmp ne i32 %139, %140
  br i1 %141, label %L15_if_then, label %L15_if_else

L15_if_then:
  %142 = add i32 2, 0
  %143 = load i32, i32* %a
  %144 = icmp ne i32 %142, %143
  br i1 %144, label %L16_if_then, label %L16_if_else

L16_if_then:
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
  %145 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.strlit.7, i32 0, i32 0))
  %146 = load double, double* %d
  %147 = add i32 2, 0
  %148 = sitofp i32 %147 to double
  %149 = fcmp oge double %146, %148
  br i1 %149, label %L17_if_then, label %L17_if_else

L17_if_then:
  %150 = load double, double* %d
  %151 = add i32 2, 0
  %152 = sitofp i32 %151 to double
  %153 = fcmp ole double %150, %152
  br i1 %153, label %L18_if_then, label %L18_if_else

L18_if_then:
  %154 = add i32 2, 0
  %155 = load double, double* %d
  %156 = sitofp i32 %154 to double
  %157 = fcmp oge double %156, %155
  br i1 %157, label %L19_if_then, label %L19_if_else

L19_if_then:
  %158 = add i32 2, 0
  %159 = load double, double* %d
  %160 = sitofp i32 %158 to double
  %161 = fcmp ole double %160, %159
  br i1 %161, label %L20_if_then, label %L20_if_else

L20_if_then:
  %162 = load double, double* %d
  %163 = add i32 2, 0
  %164 = sitofp i32 %163 to double
  %165 = fcmp oeq double %162, %164
  br i1 %165, label %L21_if_then, label %L21_if_else

L21_if_then:
  %166 = add i32 2, 0
  %167 = load double, double* %d
  %168 = sitofp i32 %166 to double
  %169 = fcmp oeq double %168, %167
  br i1 %169, label %L22_if_then, label %L22_if_else

L22_if_then:
  %170 = load double, double* %d
  %171 = add i32 2, 0
  %172 = sitofp i32 %171 to double
  %173 = fcmp ogt double %170, %172
  br i1 %173, label %L23_if_then, label %L23_if_else

L23_if_then:
  %174 = load double, double* %d
  %175 = add i32 2, 0
  %176 = sitofp i32 %175 to double
  %177 = fcmp olt double %174, %176
  br i1 %177, label %L24_if_then, label %L24_if_else

L24_if_then:
  %178 = add i32 2, 0
  %179 = load double, double* %d
  %180 = sitofp i32 %178 to double
  %181 = fcmp ogt double %180, %179
  br i1 %181, label %L25_if_then, label %L25_if_else

L25_if_then:
  %182 = add i32 2, 0
  %183 = load double, double* %d
  %184 = sitofp i32 %182 to double
  %185 = fcmp olt double %184, %183
  br i1 %185, label %L26_if_then, label %L26_if_else

L26_if_then:
  %186 = load double, double* %d
  %187 = add i32 2, 0
  %188 = sitofp i32 %187 to double
  %189 = fcmp one double %186, %188
  br i1 %189, label %L27_if_then, label %L27_if_else

L27_if_then:
  %190 = add i32 2, 0
  %191 = load double, double* %d
  %192 = sitofp i32 %190 to double
  %193 = fcmp one double %192, %191
  br i1 %193, label %L28_if_then, label %L28_if_else

L28_if_then:
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
  br label %L18_if_end

L18_if_else:
  br label %L18_if_end

L18_if_end:
  br label %L17_if_end

L17_if_else:
  br label %L17_if_end

L17_if_end:
  %194 = load double, double* %d
  %195 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %196 = fcmp oge double %194, %195
  br i1 %196, label %L29_if_then, label %L29_if_else

L29_if_then:
  %197 = load double, double* %d
  %198 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %199 = fcmp ole double %197, %198
  br i1 %199, label %L30_if_then, label %L30_if_else

L30_if_then:
  %200 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %201 = load double, double* %d
  %202 = fcmp oge double %200, %201
  br i1 %202, label %L31_if_then, label %L31_if_else

L31_if_then:
  %203 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %204 = load double, double* %d
  %205 = fcmp ole double %203, %204
  br i1 %205, label %L32_if_then, label %L32_if_else

L32_if_then:
  %206 = load double, double* %d
  %207 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %208 = fcmp oeq double %206, %207
  br i1 %208, label %L33_if_then, label %L33_if_else

L33_if_then:
  %209 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %210 = load double, double* %d
  %211 = fcmp oeq double %209, %210
  br i1 %211, label %L34_if_then, label %L34_if_else

L34_if_then:
  %212 = load double, double* %d
  %213 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %214 = fcmp ogt double %212, %213
  br i1 %214, label %L35_if_then, label %L35_if_else

L35_if_then:
  %215 = load double, double* %d
  %216 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %217 = fcmp olt double %215, %216
  br i1 %217, label %L36_if_then, label %L36_if_else

L36_if_then:
  %218 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %219 = load double, double* %d
  %220 = fcmp ogt double %218, %219
  br i1 %220, label %L37_if_then, label %L37_if_else

L37_if_then:
  %221 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %222 = load double, double* %d
  %223 = fcmp olt double %221, %222
  br i1 %223, label %L38_if_then, label %L38_if_else

L38_if_then:
  %224 = load double, double* %d
  %225 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %226 = fcmp one double %224, %225
  br i1 %226, label %L39_if_then, label %L39_if_else

L39_if_then:
  %227 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %228 = load double, double* %d
  %229 = fcmp one double %227, %228
  br i1 %229, label %L40_if_then, label %L40_if_else

L40_if_then:
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
  br label %L30_if_end

L30_if_else:
  br label %L30_if_end

L30_if_end:
  br label %L29_if_end

L29_if_else:
  br label %L29_if_end

L29_if_end:
  %230 = alloca i1
  %231 = alloca i1
  %232 = alloca i1
  %233 = alloca i1
  %234 = load i1, i1* %b1
  %235 = icmp ne i1 1, 0
  %236 = icmp eq i1 %234, %235
  br i1 %236, label %L45_and_right, label %L45_and_false

L45_and_right:
  %237 = load double, double* %d
  %238 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %239 = fcmp oge double %237, %238
  store i1 %239, i1* %233
  br label %L45_and_end

L45_and_false:
  store i1 0, i1* %233
  br label %L45_and_end

L45_and_end:
  %240 = load i1, i1* %233
  br i1 %240, label %L44_and_right, label %L44_and_false

L44_and_right:
  %241 = add i32 2, 0
  %242 = load double, double* %d
  %243 = sitofp i32 %241 to double
  %244 = fcmp oge double %243, %242
  store i1 %244, i1* %232
  br label %L44_and_end

L44_and_false:
  store i1 0, i1* %232
  br label %L44_and_end

L44_and_end:
  %245 = load i1, i1* %232
  br i1 %245, label %L43_and_right, label %L43_and_false

L43_and_right:
  %246 = fadd double 2.20000000000000018e+00, 0.000000e+00
  %247 = load double, double* %d
  %248 = fcmp ole double %246, %247
  store i1 %248, i1* %231
  br label %L43_and_end

L43_and_false:
  store i1 0, i1* %231
  br label %L43_and_end

L43_and_end:
  %249 = load i1, i1* %231
  br i1 %249, label %L42_or_true, label %L42_or_right

L42_or_true:
  store i1 1, i1* %230
  br label %L42_or_end

L42_or_right:
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
  store i1 %260, i1* %230
  br label %L42_or_end

L42_or_end:
  %261 = load i1, i1* %230
  br i1 %261, label %L41_if_then, label %L41_if_else

L41_if_then:
  %262 = icmp ne i1 1, 0
  %263 = load i1, i1* %b1
  %264 = icmp eq i1 %262, %263
  br i1 %264, label %L46_if_then, label %L46_if_else

L46_if_then:
  %265 = load i1, i1* %b1
  %266 = icmp ne i1 1, 0
  %267 = icmp ne i1 %265, %266
  br i1 %267, label %L47_if_then, label %L47_if_else

L47_if_then:
  %268 = icmp ne i1 1, 0
  %269 = load i1, i1* %b1
  %270 = icmp ne i1 %268, %269
  br i1 %270, label %L48_if_then, label %L48_if_else

L48_if_then:
  br label %L48_if_end

L48_if_else:
  br label %L48_if_end

L48_if_end:
  br label %L47_if_end

L47_if_else:
  br label %L47_if_end

L47_if_end:
  br label %L46_if_end

L46_if_else:
  br label %L46_if_end

L46_if_end:
  br label %L41_if_end

L41_if_else:
  br label %L41_if_end

L41_if_end:
  %271 = alloca i1
  %272 = alloca i1
  %273 = alloca i1
  %274 = load i1, i1* %b1
  br i1 %274, label %L52_and_right, label %L52_and_false

L52_and_right:
  %275 = icmp ne i1 1, 0
  store i1 %275, i1* %273
  br label %L52_and_end

L52_and_false:
  store i1 0, i1* %273
  br label %L52_and_end

L52_and_end:
  %276 = load i1, i1* %273
  br i1 %276, label %L51_or_true, label %L51_or_right

L51_or_true:
  store i1 1, i1* %272
  br label %L51_or_end

L51_or_right:
  %277 = load i1, i1* %b1
  store i1 %277, i1* %272
  br label %L51_or_end

L51_or_end:
  %278 = load i1, i1* %272
  br i1 %278, label %L50_or_true, label %L50_or_right

L50_or_true:
  store i1 1, i1* %271
  br label %L50_or_end

L50_or_right:
  %279 = alloca i1
  %280 = icmp ne i1 1, 0
  br i1 %280, label %L53_and_right, label %L53_and_false

L53_and_right:
  %281 = load i1, i1* %b1
  %282 = xor i1 %281, true
  %283 = icmp ne i1 0, 0
  %284 = xor i1 %282, %283
  store i1 %284, i1* %279
  br label %L53_and_end

L53_and_false:
  store i1 0, i1* %279
  br label %L53_and_end

L53_and_end:
  %285 = load i1, i1* %279
  store i1 %285, i1* %271
  br label %L50_or_end

L50_or_end:
  %286 = load i1, i1* %271
  br i1 %286, label %L49_if_then, label %L49_if_else

L49_if_then:
  %287 = alloca i1
  %288 = alloca i1
  %289 = alloca i1
  %290 = icmp ne i1 1, 0
  br i1 %290, label %L57_and_right, label %L57_and_false

L57_and_right:
  %291 = load i1, i1* %b1
  store i1 %291, i1* %289
  br label %L57_and_end

L57_and_false:
  store i1 0, i1* %289
  br label %L57_and_end

L57_and_end:
  %292 = load i1, i1* %289
  br i1 %292, label %L56_or_true, label %L56_or_right

L56_or_true:
  store i1 1, i1* %288
  br label %L56_or_end

L56_or_right:
  %293 = icmp ne i1 1, 0
  store i1 %293, i1* %288
  br label %L56_or_end

L56_or_end:
  %294 = load i1, i1* %288
  br i1 %294, label %L55_or_true, label %L55_or_right

L55_or_true:
  store i1 1, i1* %287
  br label %L55_or_end

L55_or_right:
  %295 = alloca i1
  %296 = load i1, i1* %b1
  br i1 %296, label %L58_and_right, label %L58_and_false

L58_and_right:
  %297 = icmp ne i1 0, 0
  %298 = load i1, i1* %b1
  %299 = xor i1 %298, true
  %300 = xor i1 %297, %299
  store i1 %300, i1* %295
  br label %L58_and_end

L58_and_false:
  store i1 0, i1* %295
  br label %L58_and_end

L58_and_end:
  %301 = load i1, i1* %295
  store i1 %301, i1* %287
  br label %L55_or_end

L55_or_end:
  %302 = load i1, i1* %287
  br i1 %302, label %L54_if_then, label %L54_if_else

L54_if_then:
  br label %L54_if_end

L54_if_else:
  br label %L54_if_end

L54_if_end:
  br label %L49_if_end

L49_if_else:
  br label %L49_if_end

L49_if_end:
  %303 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.strlit.8, i32 0, i32 0))
  %304 = load i32, i32* %a
  %305 = load double, double* %d
  %306 = fneg double %305
  %307 = sitofp i32 %304 to double
  %308 = fmul double %307, %306
  %309 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_double, i32 0, i32 0), double %308)
  %310 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.9, i32 0, i32 0))
  %311 = icmp ne i1 0, 0
  %312 = load i1, i1* %b1
  %313 = xor i1 %312, true
  %314 = xor i1 %311, %313
  br i1 %314, label %L59print_true, label %L59print_false

L59print_true:
  %315 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str_true, i32 0, i32 0))
  br label %L59print_end

L59print_false:
  %316 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str_false, i32 0, i32 0))
  br label %L59print_end

L59print_end:
  %317 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.strlit.10, i32 0, i32 0))
  %318 = sub i32 %args.argc, 1
  %319 = fadd double 1.10000000000000009e+00, 0.000000e+00
  %320 = sitofp i32 %318 to double
  %321 = fadd double %320, %319
  %322 = add i32 3, 0
  %323 = sitofp i32 %322 to double
  %324 = call double @_overload_double(double %323)
  %325 = fadd double %321, %324
  %326 = add i32 3, 0
  %327 = add i32 3, 0
  %328 = mul i32 %326, %327
  %329 = sitofp i32 %328 to double
  %330 = fadd double %325, %329
  %331 = add i32 2, 0
  %332 = sitofp i32 %331 to double
  %333 = fadd double %330, %332
  %334 = add i32 2, 0
  %335 = sitofp i32 %334 to double
  %336 = fadd double %333, %335
  %337 = add i32 2, 0
  %338 = sub i32 0, %337
  %339 = sitofp i32 %338 to double
  %340 = fadd double %336, %339
  %341 = add i32 3, 0
  %342 = add i32 3, 0
  %343 = sdiv i32 %341, %342
  %344 = sitofp i32 %343 to double
  %345 = fadd double %340, %344
  store double %345, double* %d1
  %346 = add i32 0, 0
  store i32 %346, i32* %i
  %347 = add i32 0, 0
  store i32 %347, i32* %j
  %348 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_str, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.strlit.11, i32 0, i32 0))
  br label %L60_while_cond

L60_while_cond:
  %349 = load i32, i32* %i
  %350 = add i32 10, 0
  %351 = icmp slt i32 %349, %350
  br i1 %351, label %L60_while_body, label %L60_while_end

L60_while_body:
  br label %L61_while_cond

L61_while_cond:
  %352 = add i32 10, 0
  %353 = load i32, i32* %i
  %354 = icmp sgt i32 %352, %353
  br i1 %354, label %L61_while_body, label %L61_while_end

L61_while_body:
  br label %L62_while_cond

L62_while_cond:
  %355 = alloca i1
  %356 = add i32 20, 0
  %357 = load i32, i32* %j
  %358 = icmp sgt i32 %356, %357
  br i1 %358, label %L63_and_right, label %L63_and_false

L63_and_right:
  %359 = load i32, i32* %i
  %360 = add i32 10, 0
  %361 = icmp slt i32 %359, %360
  store i1 %361, i1* %355
  br label %L63_and_end

L63_and_false:
  store i1 0, i1* %355
  br label %L63_and_end

L63_and_end:
  %362 = load i1, i1* %355
  br i1 %362, label %L62_while_body, label %L62_while_end

L62_while_body:
  %363 = load i32, i32* %i
  %364 = add i32 1, 0
  %365 = add i32 %363, %364
  store i32 %365, i32* %i
  %366 = load i32, i32* %j
  %367 = add i32 1, 0
  %368 = add i32 %366, %367
  store i32 %368, i32* %j
  %369 = load i32, i32* %i
  %370 = add i32 10, 0
  %371 = icmp eq i32 %369, %370
  br i1 %371, label %L64_if_then, label %L64_if_else

L64_if_then:
  %372 = load i32, i32* %j
  %373 = add i32 9, 0
  %374 = icmp eq i32 %372, %373
  br i1 %374, label %L65_if_then, label %L65_if_else

L65_if_then:
  br label %L65_if_end

L65_if_else:
  br label %L65_if_end

L65_if_end:
  br label %L64_if_end

L64_if_else:
  br label %L64_if_end

L64_if_end:
  br label %L62_while_cond

L62_while_end:
  br label %L61_while_cond

L61_while_end:
  br label %L60_while_cond

L60_while_end:
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main_StringArray(i32 %argc, i8** %argv)
  ret i32 0
}

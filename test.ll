; ModuleID = 'main'

@g = internal global i32 10
@g2 = internal constant i32 100
@.str = private constant [4 x i8] c"%s\0A\00"
@.str.1 = private constant [13 x i8] c"Lab2 Demo:\0A \00"
@.str.2 = private constant [4 x i8] c"%s\0A\00"
@.str.3 = private constant [16 x i8] c"Variable Types:\00"
@.str.4 = private constant [4 x i8] c"%s\0A\00"
@.str.5 = private constant [27 x i8] c"int double long char void \00"
@.str.6 = private constant [68 x i8] c"Long is partially supported and not all operations are valid on it\0A\00"
@.str.7 = private constant [9 x i8] c"int: %d\0A\00"
@.str.8 = private constant [12 x i8] c"double: %f\0A\00"
@.str.9 = private constant [12 x i8] c"long: %lld\0A\00"
@.str.10 = private constant [10 x i8] c"char: %c\0A\00"
@.str.11 = private constant [2 x i8] c"\0A\00"
@.str.12 = private constant [4 x i8] c"%s\0A\00"
@.str.13 = private constant [21 x i8] c"Variable Assignment:\00"
@.str.14 = private constant [4 x i8] c"%s\0A\00"
@.str.15 = private constant [57 x i8] c"Assingment of Double to Int, or Int to Double is handled\00"
@.str.16 = private constant [4 x i8] c"%s\0A\00"
@.str.17 = private constant [38 x i8] c"Assigning int a 10.20 and double b 10\00"
@.str.18 = private constant [8 x i8] c"a = %d\0A\00"
@.str.19 = private constant [8 x i8] c"b = %f\0A\00"
@.str.20 = private constant [2 x i8] c"\0A\00"
@.str.21 = private constant [4 x i8] c"%s\0A\00"
@.str.22 = private constant [21 x i8] c"Assignment Operator:\00"
@.str.23 = private constant [11 x i8] c"add:+= %d\0A\00"
@.str.24 = private constant [11 x i8] c"sub:-= %d\0A\00"
@.str.25 = private constant [12 x i8] c"muld:*= %d\0A\00"
@.str.26 = private constant [11 x i8] c"div:/= %d\0A\00"
@.str.27 = private constant [11 x i8] c"AND:&= %d\0A\00"
@.str.28 = private constant [10 x i8] c"OR:|= %d\0A\00"
@.str.29 = private constant [11 x i8] c"XOR:^= %d\0A\00"
@.str.30 = private constant [2 x i8] c"\0A\00"
@.str.31 = private constant [4 x i8] c"%s\0A\00"
@.str.32 = private constant [15 x i8] c"Unary Operator\00"
@.str.33 = private constant [10 x i8] c"a is: %d\0A\00"
@.str.34 = private constant [12 x i8] c"a++ is: %d\0A\00"
@.str.35 = private constant [14 x i8] c"a is now: %d\0A\00"
@.str.36 = private constant [12 x i8] c"++a is: %d\0A\00"
@.str.37 = private constant [2 x i8] c"\0A\00"
@.str.38 = private constant [4 x i8] c"%s\0A\00"
@.str.39 = private constant [12 x i8] c"While Loop:\00"
@.str.40 = private constant [4 x i8] c"%d \00"
@.str.41 = private constant [2 x i8] c"\0A\00"
@.str.42 = private constant [2 x i8] c"\0A\00"
@.str.43 = private constant [4 x i8] c"%s\0A\00"
@.str.44 = private constant [15 x i8] c"Do While Loop:\00"
@.str.45 = private constant [4 x i8] c"%d \00"
@.str.46 = private constant [2 x i8] c"\0A\00"
@.str.47 = private constant [2 x i8] c"\0A\00"
@.str.48 = private constant [4 x i8] c"%s\0A\00"
@.str.49 = private constant [35 x i8] c"For Loop: Progress in FOR statment\00"
@.str.50 = private constant [4 x i8] c"%d \00"
@.str.51 = private constant [2 x i8] c"\0A\00"
@.str.52 = private constant [4 x i8] c"%s\0A\00"
@.str.53 = private constant [35 x i8] c"For Loop: Pogress within the block\00"
@.str.54 = private constant [4 x i8] c"%d \00"
@.str.55 = private constant [2 x i8] c"\0A\00"
@.str.56 = private constant [4 x i8] c"%s\0A\00"
@.str.57 = private constant [41 x i8] c"For Loop: Expression for the declaration\00"
@.str.58 = private constant [4 x i8] c"%d \00"
@.str.59 = private constant [2 x i8] c"\0A\00"
@.str.60 = private constant [2 x i8] c"\0A\00"
@.str.61 = private constant [4 x i8] c"%s\0A\00"
@.str.62 = private constant [13 x i8] c"If Condition\00"
@.str.63 = private constant [11 x i8] c"ifv is 10\0A\00"
@.str.64 = private constant [4 x i8] c"%s\0A\00"
@.str.65 = private constant [42 x i8] c"Nested bloks supported. While within a IF\00"
@.str.66 = private constant [15 x i8] c"ifv is not 10\0A\00"
@.str.67 = private constant [14 x i8] c"Making it 10\0A\00"
@.str.68 = private constant [16 x i8] c"ifv is now: %d\0A\00"
@.str.69 = private constant [2 x i8] c"\0A\00"
@.str.70 = private constant [4 x i8] c"%s\0A\00"
@.str.71 = private constant [17 x i8] c"Global Variable:\00"
@.str.72 = private constant [15 x i8] c"Global g = %d\0A\00"
@.str.73 = private constant [22 x i8] c"const Global g2 = %d\0A\00"
@.str.74 = private constant [4 x i8] c"%s\0A\00"
@.str.75 = private constant [52 x i8] c"Changng const val will result in segmentation fault\00"
@.str.76 = private constant [2 x i8] c"\0A\00"
@.str.77 = private constant [4 x i8] c"%s\0A\00"
@.str.78 = private constant [25 x i8] c"Arithemetic Operations: \00"
@.str.79 = private constant [50 x i8] c"Value of arthimetic operation (2+(4*3)-8) is: %d\0A\00"
@.str.80 = private constant [50 x i8] c"Value of arthimetic operation (a+(b*c)-d) is: %d\0A\00"
@.str.81 = private constant [2 x i8] c"\0A\00"
@.str.82 = private constant [40 x i8] c"Function Declaration and Definition %s\0A\00"
@.str.83 = private constant [15 x i8] c"Function call\0A\00"
@.str.84 = private constant [19 x i8] c"bar(10,20) is: %d\0A\00"

declare i32 @printf(i8*, ...)

define internal i32 @bar(i32 %a1, i32 %b2) {
entry:
  %a = alloca i32
  store i32 %a1, i32* %a
  %b = alloca i32
  store i32 %b2, i32* %b
  %0 = load i32, i32* %a
  %1 = load i32, i32* %b
  %2 = load i32, i32* %b
  %3 = load i32, i32* %a
  %4 = add i32 %3, %2
  ret i32 %4
}

define internal i32 @main() {
entry:
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.1, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.3, i32 0, i32 0))
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.5, i32 0, i32 0))
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.6, i32 0, i32 0))
  %vti = alloca i32
  %4 = load i32, i32* %vti
  store i32 10, i32* %vti
  %vtd = alloca double
  %5 = load double, double* %vtd
  store double 1.020000e+01, double* %vtd
  %vtl = alloca i64
  %6 = load i64, i64* %vtl
  store i64 100000000000, i64* %vtl
  %vtc = alloca i8
  %7 = load i8, i8* %vtc
  store i8 99, i8* %vtc
  %8 = load i32, i32* %vti
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.7, i32 0, i32 0), i32 %8)
  %10 = load double, double* %vtd
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.8, i32 0, i32 0), double %10)
  %12 = load i64, i64* %vtl
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.9, i32 0, i32 0), i64 %12)
  %14 = load i8, i8* %vtc
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.10, i32 0, i32 0), i8 %14)
  %16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.11, i32 0, i32 0))
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.13, i32 0, i32 0))
  %18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([57 x i8], [57 x i8]* @.str.15, i32 0, i32 0))
  %19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.17, i32 0, i32 0))
  %a = alloca i32
  %20 = load i32, i32* %a
  store i32 10, i32* %a
  %b = alloca double
  %21 = load double, double* %b
  store double 1.000000e+01, double* %b
  %22 = load i32, i32* %a
  %23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.18, i32 0, i32 0), i32 %22)
  %24 = load double, double* %b
  %25 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.19, i32 0, i32 0), double %24)
  %26 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.20, i32 0, i32 0))
  %27 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.21, i32 0, i32 0), i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.22, i32 0, i32 0))
  %28 = load i32, i32* %a
  %29 = add i32 %28, 10
  store i32 %29, i32* %a
  %30 = load i32, i32* %a
  %31 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.23, i32 0, i32 0), i32 %30)
  %32 = load i32, i32* %a
  %33 = sub i32 %32, 10
  store i32 %33, i32* %a
  %34 = load i32, i32* %a
  %35 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.24, i32 0, i32 0), i32 %34)
  %36 = load i32, i32* %a
  %37 = mul i32 %36, 10
  store i32 %37, i32* %a
  %38 = load i32, i32* %a
  %39 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.25, i32 0, i32 0), i32 %38)
  %40 = load i32, i32* %a
  %41 = sdiv i32 %40, 10
  store i32 %41, i32* %a
  %42 = load i32, i32* %a
  %43 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.26, i32 0, i32 0), i32 %42)
  %44 = load i32, i32* %a
  %45 = and i32 %44, 10
  store i32 %45, i32* %a
  %46 = load i32, i32* %a
  %47 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.27, i32 0, i32 0), i32 %46)
  %48 = load i32, i32* %a
  %49 = or i32 %48, 10
  store i32 %49, i32* %a
  %50 = load i32, i32* %a
  %51 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.28, i32 0, i32 0), i32 %50)
  %52 = load i32, i32* %a
  %53 = xor i32 %52, 10
  store i32 %53, i32* %a
  %54 = load i32, i32* %a
  %55 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.29, i32 0, i32 0), i32 %54)
  %56 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.30, i32 0, i32 0))
  %57 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.31, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.32, i32 0, i32 0))
  %58 = load i32, i32* %a
  %59 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.33, i32 0, i32 0), i32 %58)
  %60 = load i32, i32* %a
  %61 = add i32 %60, 1
  store i32 %61, i32* %a
  %62 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.34, i32 0, i32 0), i32 %60)
  %63 = load i32, i32* %a
  %64 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.35, i32 0, i32 0), i32 %63)
  %65 = load i32, i32* %a
  %66 = add i32 %65, 1
  store i32 %66, i32* %a
  %67 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i32 0, i32 0), i32 %66)
  %68 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.37, i32 0, i32 0))
  %69 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.38, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.39, i32 0, i32 0))
  %whl = alloca i32
  %70 = load i32, i32* %whl
  store i32 0, i32* %whl
  br label %whlcond1

whlcond1:                                         ; preds = %whlloop, %entry
  %71 = load i32, i32* %whl
  %72 = icmp sle i32 %71, 10
  br i1 %72, label %whlloop, label %whlafter

whlloop:                                          ; preds = %whlcond1
  %73 = load i32, i32* %whl
  %74 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.40, i32 0, i32 0), i32 %73)
  %75 = load i32, i32* %whl
  %76 = add i32 %75, 1
  store i32 %76, i32* %whl
  br label %whlcond1

whlafter:                                         ; preds = %whlcond1
  %77 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.41, i32 0, i32 0))
  %78 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.42, i32 0, i32 0))
  %79 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.43, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.44, i32 0, i32 0))
  %do_whl = alloca i32
  %80 = load i32, i32* %do_whl
  store i32 5, i32* %do_whl
  br label %loop2

loop2:                                            ; preds = %cond, %whlafter
  %81 = load i32, i32* %do_whl
  %82 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.45, i32 0, i32 0), i32 %81)
  %83 = load i32, i32* %do_whl
  %84 = add i32 %83, 1
  store i32 %84, i32* %do_whl
  br label %cond

cond:                                             ; preds = %loop2
  %85 = load i32, i32* %do_whl
  %86 = icmp sle i32 %85, 10
  br i1 %86, label %loop2, label %after

after:                                            ; preds = %cond
  %87 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.46, i32 0, i32 0))
  %88 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.47, i32 0, i32 0))
  %89 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.48, i32 0, i32 0), i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.49, i32 0, i32 0))
  %fl = alloca i32
  %90 = load i32, i32* %fl
  store i32 0, i32* %fl
  br label %cond34

cond34:                                           ; preds = %progress, %after
  %91 = load i32, i32* %fl
  %92 = icmp sle i32 %91, 10
  br i1 %92, label %loop, label %after5

loop:                                             ; preds = %cond34
  %93 = load i32, i32* %fl
  %94 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.50, i32 0, i32 0), i32 %93)
  br label %progress

progress:                                         ; preds = %loop
  %95 = load i32, i32* %fl
  %96 = add i32 %95, 1
  store i32 %96, i32* %fl
  br label %cond34

after5:                                           ; preds = %cond34
  %97 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.51, i32 0, i32 0))
  %98 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.52, i32 0, i32 0), i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.53, i32 0, i32 0))
  %fl2 = alloca i32
  %99 = load i32, i32* %fl2
  store i32 0, i32* %fl2
  br label %cond67

cond67:                                           ; preds = %progress9, %after5
  %100 = load i32, i32* %fl2
  %101 = icmp sle i32 %100, 10
  br i1 %101, label %loop8, label %after10

loop8:                                            ; preds = %cond67
  %102 = load i32, i32* %fl2
  %103 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.54, i32 0, i32 0), i32 %102)
  %104 = load i32, i32* %fl2
  %105 = add i32 %104, 1
  store i32 %105, i32* %fl2
  br label %progress9

progress9:                                        ; preds = %loop8
  br label %cond67

after10:                                          ; preds = %cond67
  %106 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.55, i32 0, i32 0))
  %107 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.56, i32 0, i32 0), i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.57, i32 0, i32 0))
  %fl3 = alloca i32
  %108 = load i32, i32* %fl3
  store i32 0, i32* %fl3
  %109 = load i32, i32* %fl3
  store i32 5, i32* %fl3
  br label %cond1112

cond1112:                                         ; preds = %progress14, %after10
  %110 = load i32, i32* %fl3
  %111 = icmp sle i32 %110, 10
  br i1 %111, label %loop13, label %after15

loop13:                                           ; preds = %cond1112
  %112 = load i32, i32* %fl3
  %113 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.58, i32 0, i32 0), i32 %112)
  %114 = load i32, i32* %fl3
  %115 = add i32 %114, 1
  store i32 %115, i32* %fl3
  br label %progress14

progress14:                                       ; preds = %loop13
  br label %cond1112

after15:                                          ; preds = %cond1112
  %116 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.59, i32 0, i32 0))
  %117 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.60, i32 0, i32 0))
  %118 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.61, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.62, i32 0, i32 0))
  %ifv = alloca i32
  %119 = load i32, i32* %ifv
  store i32 0, i32* %ifv
  %120 = load i32, i32* %ifv
  %121 = icmp eq i32 %120, 10
  br i1 %121, label %then16, label %else

then16:                                           ; preds = %after15
  %122 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.63, i32 0, i32 0))
  br label %cont

else:                                             ; preds = %after15
  %123 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.64, i32 0, i32 0), i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.65, i32 0, i32 0))
  %124 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.66, i32 0, i32 0))
  %125 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.67, i32 0, i32 0))
  br label %whlcond17

whlcond17:                                        ; preds = %whlloop18, %else
  %126 = load i32, i32* %ifv
  %127 = icmp sle i32 %126, 10
  br i1 %127, label %whlloop18, label %whlafter19

whlloop18:                                        ; preds = %whlcond17
  %128 = load i32, i32* %ifv
  %129 = add i32 %128, 1
  store i32 %129, i32* %ifv
  %130 = load i32, i32* %ifv
  %131 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.68, i32 0, i32 0), i32 %130)
  br label %whlcond17

whlafter19:                                       ; preds = %whlcond17
  br label %cont

cont:                                             ; preds = %whlafter19, %then16
  %132 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.69, i32 0, i32 0))
  %133 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.70, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.71, i32 0, i32 0))
  %134 = load i32, i32* @g
  %135 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.72, i32 0, i32 0), i32 %134)
  %136 = load i32, i32* @g2
  %137 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.73, i32 0, i32 0), i32 %136)
  %138 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.74, i32 0, i32 0), i8* getelementptr inbounds ([52 x i8], [52 x i8]* @.str.75, i32 0, i32 0))
  %139 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.76, i32 0, i32 0))
  %140 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.77, i32 0, i32 0), i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.78, i32 0, i32 0))
  %a_arth = alloca i32
  %141 = load i32, i32* %a_arth
  store i32 2, i32* %a_arth
  %b_arth = alloca i32
  %142 = load i32, i32* %b_arth
  store i32 4, i32* %b_arth
  %c_arth = alloca i32
  %143 = load i32, i32* %c_arth
  store i32 3, i32* %c_arth
  %d_arth = alloca i32
  %144 = load i32, i32* %d_arth
  store i32 8, i32* %d_arth
  %arth = alloca i32
  %145 = load i32, i32* %arth
  %146 = mul i32 4, 3
  %147 = mul i32 4, 3
  %148 = add i32 2, %147
  %149 = mul i32 4, 3
  %150 = mul i32 4, 3
  %151 = add i32 2, %150
  %152 = sub i32 %151, 8
  store i32 %152, i32* %arth
  %153 = load i32, i32* %arth
  %154 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.79, i32 0, i32 0), i32 %153)
  %arth2 = alloca i32
  %155 = load i32, i32* %arth2
  %156 = load i32, i32* %a_arth
  %157 = load i32, i32* %b_arth
  %158 = load i32, i32* %c_arth
  %159 = load i32, i32* %c_arth
  %160 = load i32, i32* %b_arth
  %161 = mul i32 %160, %159
  %162 = load i32, i32* %b_arth
  %163 = load i32, i32* %c_arth
  %164 = load i32, i32* %c_arth
  %165 = load i32, i32* %b_arth
  %166 = mul i32 %165, %164
  %167 = load i32, i32* %a_arth
  %168 = add i32 %167, %166
  %169 = load i32, i32* %d_arth
  %170 = load i32, i32* %d_arth
  %171 = load i32, i32* %a_arth
  %172 = load i32, i32* %b_arth
  %173 = load i32, i32* %c_arth
  %174 = load i32, i32* %c_arth
  %175 = load i32, i32* %b_arth
  %176 = mul i32 %175, %174
  %177 = load i32, i32* %b_arth
  %178 = load i32, i32* %c_arth
  %179 = load i32, i32* %c_arth
  %180 = load i32, i32* %b_arth
  %181 = mul i32 %180, %179
  %182 = load i32, i32* %a_arth
  %183 = add i32 %182, %181
  %184 = sub i32 %183, %170
  store i32 %184, i32* %arth2
  %185 = load i32, i32* %arth2
  %186 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.80, i32 0, i32 0), i32 %185)
  %187 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.81, i32 0, i32 0))
  %188 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.82, i32 0, i32 0))
  %189 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.83, i32 0, i32 0))
  %190 = call i32 @bar(i32 10, i32 20)
  %191 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.84, i32 0, i32 0), i32 %190)
  ret i32 0
}

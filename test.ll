; ModuleID = 'test.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@ga = global i32 10, align 4
@gb = global i32 20, align 4
@gc = global i32 0, align 4
@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @addt(i32 %a, i32 %b) #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 %a, i32* %1, align 4
  store i32 %b, i32* %2, align 4
  %3 = load i32, i32* %1, align 4
  %4 = load i32, i32* %2, align 4
  %5 = add nsw i32 %3, %4
  ret i32 %5
}

; Function Attrs: nounwind uwtable
define i32 @add() #0 {
  %la = alloca i32, align 4
  %lb = alloca i32, align 4
  %lc = alloca i32, align 4
  %ld = alloca i32, align 4
  store i32 10, i32* %la, align 4
  store i32 20, i32* %lb, align 4
  %1 = load i32, i32* %la, align 4
  %2 = load i32, i32* %lb, align 4
  %3 = add nsw i32 %1, %2
  store i32 %3, i32* %lc, align 4
  %4 = load i32, i32* %la, align 4
  %5 = load i32, i32* %lb, align 4
  %6 = add nsw i32 %4, %5
  store i32 %6, i32* %ld, align 4
  %7 = load i32, i32* @ga, align 4
  %8 = load i32, i32* @gb, align 4
  %9 = add nsw i32 %7, %8
  store i32 %9, i32* @gc, align 4
  %10 = load i32, i32* @gc, align 4
  ret i32 %10
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %la = alloca i32, align 4
  %lb = alloca i32, align 4
  %lc = alloca i32, align 4
  %ld = alloca i32, align 4
  %le = alloca i32, align 4
  %sum = alloca i32, align 4
  %tmp = alloca i32, align 4
  %tmp2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 10, i32* %la, align 4
  store i32 20, i32* %lb, align 4
  %2 = load i32, i32* %la, align 4
  %3 = load i32, i32* %lb, align 4
  %4 = add nsw i32 %2, %3
  store i32 %4, i32* %lc, align 4
  %5 = load i32, i32* %la, align 4
  %6 = load i32, i32* %lb, align 4
  %7 = add nsw i32 %5, %6
  store i32 %7, i32* %ld, align 4
  %8 = load i32, i32* %lc, align 4
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %8)
  %10 = load i32, i32* %ld, align 4
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %10)
  store i32 30, i32* %la, align 4
  %12 = load i32, i32* %la, align 4
  %13 = load i32, i32* %lb, align 4
  %14 = add nsw i32 %12, %13
  store i32 %14, i32* %le, align 4
  %15 = load i32, i32* %le, align 4
  %16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %15)
  %17 = load i32, i32* %la, align 4
  %18 = load i32, i32* %lb, align 4
  %19 = call i32 @addt(i32 %17, i32 %18)
  store i32 %19, i32* %sum, align 4
  %20 = load i32, i32* %sum, align 4
  %21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %20)
  %22 = call i32 @add()
  %23 = load i32, i32* @ga, align 4
  %24 = load i32, i32* @gb, align 4
  %25 = add nsw i32 %23, %24
  store i32 %25, i32* %tmp, align 4
  %26 = load i32, i32* %tmp, align 4
  %27 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %26)
  store i32 10, i32* @ga, align 4
  %28 = load i32, i32* @ga, align 4
  %29 = load i32, i32* @gb, align 4
  %30 = add nsw i32 %28, %29
  store i32 %30, i32* %tmp2, align 4
  %31 = load i32, i32* %tmp2, align 4
  %32 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %31)
  ret i32 0
}

declare i32 @printf(i8*, ...) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"}

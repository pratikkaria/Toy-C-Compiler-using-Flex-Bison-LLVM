; ModuleID = 'temp_opt.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %la = alloca i32, align 4
  %lb = alloca i32, align 4
  %lc = alloca i32, align 4
  %ld = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 10, i32* %la, align 4
  store i32 20, i32* %lb, align 4
  %2 = load i32, i32* %la, align 4
  %3 = load i32, i32* %lb, align 4
  %4 = mul nsw i32 %3, 2
  %5 = add nsw i32 %2, %4
  %6 = sub nsw i32 %5, 2
  store i32 %6, i32* %lc, align 4
  %7 = load i32, i32* %la, align 4
  %8 = load i32, i32* %lb, align 4
  %9 = mul nsw i32 %8, 2
  %10 = add nsw i32 %7, %9
  %11 = sub nsw i32 %10, 2
  store i32 %11, i32* %ld, align 4
  %12 = load i32, i32* %lc, align 4
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %12)
  %14 = load i32, i32* %ld, align 4
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %14)
  ret i32 0
}

declare i32 @printf(i8*, ...) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"}

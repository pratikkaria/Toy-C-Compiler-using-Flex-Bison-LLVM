; ModuleID = 'temp_opt.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@ga = global i32 10, align 4
@gb = global i32 20, align 4
@gc = global i32 0, align 4

; Function Attrs: nounwind uwtable
define void @docomplex() #0 {
  %1 = load i32, i32* @ga, align 4
  %2 = load i32, i32* @gb, align 4
  %3 = add nsw i32 %1, %2
  store i32 %3, i32* @gc, align 4
  ret void
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  %d = alloca i32, align 4
  %e = alloca i32, align 4
  %f = alloca i32, align 4
  %tmp = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 10, i32* %a, align 4
  store i32 20, i32* %b, align 4
  %2 = load i32, i32* %a, align 4
  %3 = load i32, i32* %b, align 4
  %4 = add nsw i32 %2, %3
  store i32 %4, i32* %c, align 4
  %5 = load i32, i32* %a, align 4
  %6 = load i32, i32* %b, align 4
  %7 = add nsw i32 %5, %6
  store i32 %7, i32* %d, align 4
  %8 = load i32, i32* %a, align 4
  %9 = load i32, i32* %b, align 4
  %10 = mul nsw i32 %9, 2
  %11 = add nsw i32 %8, %10
  %12 = sub nsw i32 %11, 8
  store i32 %12, i32* %e, align 4
  %13 = load i32, i32* %a, align 4
  %14 = load i32, i32* %b, align 4
  %15 = mul nsw i32 %14, 2
  %16 = add nsw i32 %13, %15
  %17 = sub nsw i32 %16, 8
  store i32 %17, i32* %f, align 4
  %18 = load i32, i32* @ga, align 4
  %19 = load i32, i32* @gb, align 4
  %20 = add nsw i32 %18, %19
  store i32 %20, i32* %tmp, align 4
  ret i32 0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"}

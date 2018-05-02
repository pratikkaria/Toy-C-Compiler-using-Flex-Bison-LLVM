; ModuleID = 'temp_opt.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@ga = global i32 10, align 4
@gb = global i32 20, align 4
@gc = global i32 0, align 4
@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

; Function Attrs: nounwind uwtable
define void @docomplex() #0 {
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  %d = alloca i32, align 4
  store i32 10, i32* %a, align 4
  store i32 20, i32* %b, align 4
  %1 = load i32, i32* %a, align 4
  %2 = load i32, i32* %b, align 4
  %3 = add nsw i32 %1, %2
  store i32 %3, i32* %c, align 4
  %4 = load i32, i32* %a, align 4
  %5 = load i32, i32* %b, align 4
  %6 = add nsw i32 %4, %5
  store i32 %6, i32* %d, align 4
  %7 = load i32, i32* %c, align 4
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %7)
  %9 = load i32, i32* %d, align 4
  %10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %9)
  %11 = load i32, i32* @ga, align 4
  %12 = load i32, i32* @gb, align 4
  %13 = add nsw i32 %11, %12
  store i32 %13, i32* @gc, align 4
  ret void
}

declare i32 @printf(i8*, ...) #1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %b2 = alloca i32, align 4
  %c = alloca i32, align 4
  %d = alloca i32, align 4
  %e = alloca i32, align 4
  %f = alloca i32, align 4
  %tmp = alloca i32, align 4
  %l = alloca i32, align 4
  %k = alloca i32, align 4
  %m = alloca i32, align 4
  %i = alloca i32, align 4
  %lt = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @docomplex()
  store i32 10, i32* %a, align 4
  store i32 20, i32* %b, align 4
  store i32 20, i32* %b2, align 4
  %2 = load i32, i32* %a, align 4
  %3 = load i32, i32* %b, align 4
  %4 = add nsw i32 %2, %3
  store i32 %4, i32* %c, align 4
  %5 = load i32, i32* %a, align 4
  %6 = load i32, i32* %b, align 4
  %7 = add nsw i32 %5, %6
  store i32 %7, i32* %d, align 4
  %8 = load i32, i32* %c, align 4
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %8)
  %10 = load i32, i32* %d, align 4
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %10)
  %12 = load i32, i32* %a, align 4
  %13 = load i32, i32* %b, align 4
  %14 = mul nsw i32 %13, 2
  %15 = add nsw i32 %12, %14
  %16 = load i32, i32* %c, align 4
  %17 = sdiv i32 8, %16
  %18 = sub nsw i32 %15, %17
  store i32 %18, i32* %e, align 4
  %19 = load i32, i32* %a, align 4
  %20 = load i32, i32* %b, align 4
  %21 = mul nsw i32 %20, 2
  %22 = add nsw i32 %19, %21
  %23 = load i32, i32* %c, align 4
  %24 = sdiv i32 8, %23
  %25 = sub nsw i32 %22, %24
  store i32 %25, i32* %f, align 4
  %26 = load i32, i32* %e, align 4
  %27 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %26)
  %28 = load i32, i32* %f, align 4
  %29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %28)
  %30 = load i32, i32* @ga, align 4
  %31 = load i32, i32* @gb, align 4
  %32 = add nsw i32 %30, %31
  store i32 %32, i32* %tmp, align 4
  %33 = load i32, i32* %tmp, align 4
  %34 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %33)
  store i32 10, i32* %l, align 4
  %35 = load i32, i32* %l, align 4
  %36 = icmp slt i32 %35, 10
  br i1 %36, label %37, label %43

; <label>:37                                      ; preds = %0
  %38 = load i32, i32* %a, align 4
  %39 = load i32, i32* %b, align 4
  %40 = add nsw i32 %38, %39
  store i32 %40, i32* %k, align 4
  %41 = load i32, i32* %k, align 4
  %42 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %41)
  br label %49

; <label>:43                                      ; preds = %0
  %44 = load i32, i32* %a, align 4
  %45 = load i32, i32* %b2, align 4
  %46 = add nsw i32 %44, %45
  store i32 %46, i32* %m, align 4
  %47 = load i32, i32* %m, align 4
  %48 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %47)
  br label %49

; <label>:49                                      ; preds = %43, %37
  store i32 0, i32* %i, align 4
  br label %50

; <label>:50                                      ; preds = %59, %49
  %51 = load i32, i32* %i, align 4
  %52 = icmp slt i32 %51, 4
  br i1 %52, label %53, label %62

; <label>:53                                      ; preds = %50
  %54 = load i32, i32* %a, align 4
  %55 = load i32, i32* %b, align 4
  %56 = add nsw i32 %54, %55
  store i32 %56, i32* %lt, align 4
  %57 = load i32, i32* %lt, align 4
  %58 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %57)
  br label %59

; <label>:59                                      ; preds = %53
  %60 = load i32, i32* %i, align 4
  %61 = add nsw i32 %60, 1
  store i32 %61, i32* %i, align 4
  br label %50

; <label>:62                                      ; preds = %50
  ret i32 0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"}

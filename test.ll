; ModuleID = 'main'

@.str = private constant [4 x i8] c"%d\0A\00"
@.str.1 = private constant [4 x i8] c"%d\0A\00"
@.str.2 = private constant [4 x i8] c"%d\0A\00"
@.str.3 = private constant [4 x i8] c"%d\0A\00"
@.str.4 = private constant [4 x i8] c"%d\0A\00"

declare i32 @printf(i8*, ...)

define internal i32 @add(i32 %m1, i32 %n2) {
entry:
  %m = alloca i32
  store i32 %m1, i32* %m
  %n = alloca i32
  store i32 %n2, i32* %n
  %0 = load i32, i32* %n
  %1 = load i32, i32* %m
  %2 = add i32 %1, %0
  ret i32 %2
}

define internal i32 @main() {
entry:
  %mb = alloca i32
  %0 = load i32, i32* %mb
  store i32 0, i32* %mb
  %1 = load i32, i32* %mb
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %1)
  %sb = alloca i32
  %3 = load i32, i32* %sb
  store i32 23, i32* %sb
  %4 = load i32, i32* %sb
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i32 %4)
  %b = alloca i32
  %6 = load i32, i32* %b
  store i32 50, i32* %b
  %7 = load i32, i32* %b
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i32 %7)
  %d = alloca i32
  %9 = load i32, i32* %d
  store i32 0, i32* %d
  %10 = load i32, i32* %d
  %11 = icmp sle i32 %10, 10
  br label %whlcond1

whlcond1:                                         ; preds = %whlloop, %entry
  %12 = load i32, i32* %d
  %13 = icmp sle i32 %12, 10
  br i1 %13, label %whlloop, label %whlafter

whlloop:                                          ; preds = %whlcond1
  %14 = load i32, i32* %d
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i32 %14)
  %16 = load i32, i32* %d
  %17 = add i32 %16, 1
  store i32 %17, i32* %d
  br label %whlcond1

whlafter:                                         ; preds = %whlcond1
  %e = alloca i32
  %18 = load i32, i32* %e
  store i32 10, i32* %e
  %f = alloca i32
  %19 = load i32, i32* %f
  store i32 10, i32* %f
  %20 = load i32, i32* %f
  %21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i32 0, i32 0), i32 %20)
  %22 = call i32 @add(i32 10, i32 20)
  ret i32 0
}

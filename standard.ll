; ModuleID = 'standard.c'
source_filename = "standard.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca float, align 4
  store i32 0, i32* %1, align 4
  store i32 10, i32* %2, align 4
  store float 1.000000e+00, float* %3, align 4
  %4 = load i32, i32* %2, align 4
  %5 = sitofp i32 %4 to float
  %6 = load float, float* %3, align 4
  %7 = fadd float %5, %6
  %8 = fptosi float %7 to i32
  store i32 %8, i32* %2, align 4
  %9 = load i32, i32* %2, align 4
  %10 = sitofp i32 %9 to float
  %11 = load float, float* %3, align 4
  %12 = fmul float %10, %11
  %13 = fptosi float %12 to i32
  store i32 %13, i32* %2, align 4
  %14 = load i32, i32* %2, align 4
  %15 = sitofp i32 %14 to float
  %16 = load float, float* %3, align 4
  %17 = fdiv float %15, %16
  %18 = fptosi float %17 to i32
  store i32 %18, i32* %2, align 4
  %19 = load i32, i32* %2, align 4
  %20 = sitofp i32 %19 to float
  %21 = load float, float* %3, align 4
  %22 = fcmp olt float %20, %21
  %23 = zext i1 %22 to i32
  store i32 %23, i32* %2, align 4
  %24 = load i32, i32* %2, align 4
  %25 = sitofp i32 %24 to float
  %26 = load float, float* %3, align 4
  %27 = fcmp ole float %25, %26
  %28 = zext i1 %27 to i32
  store i32 %28, i32* %2, align 4
  %29 = load i32, i32* %2, align 4
  %30 = sitofp i32 %29 to float
  %31 = load float, float* %3, align 4
  %32 = fcmp ogt float %30, %31
  %33 = zext i1 %32 to i32
  store i32 %33, i32* %2, align 4
  %34 = load i32, i32* %2, align 4
  %35 = sitofp i32 %34 to float
  %36 = load float, float* %3, align 4
  %37 = fcmp oge float %35, %36
  %38 = zext i1 %37 to i32
  store i32 %38, i32* %2, align 4
  %39 = load i32, i32* %2, align 4
  %40 = sitofp i32 %39 to float
  %41 = load float, float* %3, align 4
  %42 = fcmp oeq float %40, %41
  %43 = zext i1 %42 to i32
  store i32 %43, i32* %2, align 4
  %44 = load i32, i32* %2, align 4
  %45 = sitofp i32 %44 to float
  %46 = load float, float* %3, align 4
  %47 = fcmp une float %45, %46
  %48 = zext i1 %47 to i32
  store i32 %48, i32* %2, align 4
  %49 = load float, float* %3, align 4
  %50 = fptosi float %49 to i32
  ret i32 %50
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.0-4ubuntu1 "}

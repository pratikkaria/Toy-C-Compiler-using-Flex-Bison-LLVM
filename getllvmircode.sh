clang -O0 -S -emit-llvm temp_opt.c -o $1; cat $1

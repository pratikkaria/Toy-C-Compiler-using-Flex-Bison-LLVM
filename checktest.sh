opt -load /home/sandeep/Downloads/llvm/build/lib/LLVMHello.so -ModulePassUtil -S test.ll > test.ir 2> /dev/null
diff working_test.ir test.ir
#vimdiff test.ll test.ir

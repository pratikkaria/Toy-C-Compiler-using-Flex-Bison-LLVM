./getllvmircode.sh test.c test.ll > /dev/null
./getllvmircode.sh partial_test.c partial_test.ll > /dev/null

opt -load /home/sandeep/Downloads/llvm/build/lib/LLVMHello.so -ModulePassUtil -S test.ll > test.ir 2> /dev/null
opt -load /home/sandeep/Downloads/llvm/build/lib/LLVMHello.so -ModulePassUtil -S partial_test.ll > partial_test.ir 2> /dev/null

diff working_test.ir test.ir
diff working_partial_test.ir partial_test.ir
#vimdiff test.ll test.ir

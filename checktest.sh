if [[  $# -ne 1 ]]
	then
	echo "Need a file name"
	exit 1
fi

./getllvmircode.sh $1.c $1.ll > /dev/null
# ./getllvmircode.sh partial_$1.c partial_$1.ll > /dev/null

opt -load /home/sandeep/Downloads/llvm/build/lib/LLVMHello.so -ModulePassUtil -S $1.ll > $1.ir 2> /dev/null
# opt -load /home/sandeep/Downloads/llvm/build/lib/LLVMHello.so -ModulePassUtil -S partial_$1.ll > partial_$1.ir 2> /dev/null

diff working_$1.ir $1.ir
echo "DONE"


if [[ $# -ne 2 ]]
then
echo "Need two args, input and output"
exit 1
fi

clang -O0 -S -emit-llvm $1 -o $2; cat $2

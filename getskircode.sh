if [[ $# -ne 2 ]]
then
echo "Need two args. Input c code file and the output file wher the generated IR code will be stored"
exit 1
fi
./cc $1 2> $2; cat $2

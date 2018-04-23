if [[ $# -ne 2 ]]
then
echo "Need two args"
exit 1
fi
make clean;
make build;
./cc $1 2> $2; cat $2

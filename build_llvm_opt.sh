tar_path="/home/sandeep/Downloads/llvm/llvm-3.8.0.src.tar.xz"
source_folder="/home/sandeep/Downloads/llvm/llvm-3.8.0.src"
parent_folder="/home/sandeep/Downloads/llvm"

curr_folder=$(pwd)

#tar -xf $tar_path -C $parent_folder


cp Hello_reg.cpp $source_folder/lib/Transforms/Hello/Hello.cpp
cp model.h $source_folder/lib/Transforms/Hello/model.h

cd $parent_folder
mkdir build
cd build
#cmake  $source_folder -DBUILD_SHARED_LIBS:BOOL=on  
make -j8
cd $curr_folder

#./checktest.sh test

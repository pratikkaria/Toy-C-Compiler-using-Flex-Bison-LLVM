##  Assignment: Compiler Lab4
Submitted by: Sandeep Kumar
ID: 2017ANZ8353

## Dependcies:
Flex  
Bison  
LLVM 3.8

## Things done
Global Constant Propagation  
Global Common sub expression elimination.

## Trying out LLVM optimization flags
 * Flag1 : constprop
 * Flag2: 
 
 To see available optimization flags use the command:
 ~~~
 opt--3.8 --help
 ~~~
 
 ### Constant Propagation flag:
 Use the flag:
 ~~~
 -constprop
 ~~~
 
 This by default works on byte code, to make it work on IR code use the flag -S.
 
 To generate llvm IR code use the command
 
 ~~~
 clang -O0 -S -emit-llvm temp_opt.c ;cat temp_opt.ll
 ~~~
 by default this saves the generated code in a file with the same name as the input with extension ll.
 
 Optimising the generated IR code using *opt* :
 
 ~~~
  opt-3.8 -constprop -S temp_opt.ir
 ~~~
 
 This basically take a flag of which optimization is to run  
 *constprop*
 then a flag -S telling this is the IR code and not that byte code
 and finally the IR code.
 
 Note: LLVM by default folds the constant. Hence the code generated using the command *emit-llvm* will be optimised. Hence we need to generate the code using
 our own old code which does no such thing. Using this we can see that constants like 10+20 is folder to 30. However if a variable is constant and then it is assigned
 to some other variable after adding to some constant, then it is not able to figure out that it is constant. May be some different flag is required for this.

##
cmake  <path to root> -DBUILD_SHARED_LIBS:BOOL=on
make -j8
make sure ll file is there
run ./check

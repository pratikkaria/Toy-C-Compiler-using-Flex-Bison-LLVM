CXX = clang++-6.0
CC = clang-6.0
CFLAGS = --std=c++14 

LLVM_SRC_PATH = /home/sandeep/Desktop/glamdring/llvm-project/llvm
LLVM_BUILD_PATH = $(LLVM_SRC_PATH)/build

LLVM_BIN_PATH = $(LLVM_SRC_PATH)/bin
LLVM_LIBS=core mc
LLVM_CONFIG_COMMAND = $(LLVM_SRC_PATH)/llvm-config 
LDFLAGS = `$(LLVM_CONFIG_COMMAND) --ldflags` -lpthread -ldl -lz -lncurses -rdynamic
CLANG_BUILD_FLAGS = -L$(LLVM_SRC_PATH)/lib -I$(LLVM_SRC_PATH)/include

CLANGLIBS = \
	-lclangFrontendTool -lclangFrontend -lclangDriver \
	-lclangSerialization -lclangCodeGen -lclangParse \
	-lclangSema -lclangStaticAnalyzerFrontend \
	-lclangStaticAnalyzerCheckers -lclangStaticAnalyzerCore \
	-lclangAnalysis -lclangARCMigrate -lclangRewrite \
	-lclangEdit -lclangAST -lclangLex -lclangBasic

# print:
# 	echo $(LLVM_SRC_PATH)
# 	echo $(LLVM_BUILD_PATH)
# 	echo $(LLVM_BIN_PATH)
# 	echo $(LLVM_LIBS)
# 	echo $(LLVM_CONFIG_COMMAND)
# 	echo "This: "$(CLANG_BUILD_FLAGS)
# 	echo "This: "$(CLANGLIBS)

all: rewritersample

rewritersample: rewritersample.cpp
	$(CXX) rewritersample.cpp $(CFLAGS) -o rewritersample $(CLANG_BUILD_FLAGS) $(LDFLAGS) $(CLANGLIBS) -v 1> /dev/null

clean:
	rm -rf *.o *.ll rewritersample
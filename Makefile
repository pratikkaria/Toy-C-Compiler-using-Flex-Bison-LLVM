all: check

OBJS = c.tab.o  \
       codegen.o  \
       cc.o    \
       c.lex.o  \

LLVMCONFIG = llvm-config
CPPFLAGS = `$(LLVMCONFIG) --cppflags` -std=c++11
LDFLAGS = `$(LLVMCONFIG) --ldflags` -lpthread -ldl -lz -lncurses -rdynamic
LIBS = `$(LLVMCONFIG) --libs`
CPPFLAGS += -MMD
SRC_FILES := $(*.cpp *.h)
SRC_DIR := .
OBJ_DIR := .
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

clean:
	$(RM) -rf c.tab.cpp c.tab.hpp cc c.lex.cpp $(OBJS) *.ll *.bc *.d

c.tab.cpp: c.y
	bison -d c.y -o c.tab.cpp

c.tab.hpp: c.tab.cpp

c.lex.cpp: c.l c.tab.hpp
	flex -o c.lex.cpp -l c.l

%.o: %.cpp %.h
	g++ -c $(CPPFLAGS) -o $@ $<


cc: $(OBJS)
	g++ -ggdb -g -O0 -o $@ $(OBJS) $(LIBS) $(LDFLAGS)

test: opt.c
	@ rm test.ll; make > /dev/null 2> /dev/null; ./cc opt.c 2> test.ll; lli test.ll;

check: cc opt.c
	./cc opt.c ;echo "To run the code with lli run \"make test\""

-include $(OBJ_FILES:.o=.d)
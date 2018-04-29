#include "llvm/IR/Value.h"

using namespace llvm;
class Binary_OP{
public:
    // operand 1
    std::string a;
    //operand 2
    std::string b;
    // assigned to
    std::string val;
    Value *value;
    std::string inst;
    int opcode;
    bool isvalid = true;



};


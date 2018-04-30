#include "llvm/IR/Value.h"
#include "llvm/IR/Instruction.h"

using namespace llvm;
class Binary_OP{
public:
    // operand 1
    std::string a;
    //operand 2
    std::string b;
    // assigned to
    std::string val;
    Instruction *inst;
    std::string inst_str;
    int opcode;
    bool isvalid = true;



};


#include "llvm/IR/Value.h"
#include "llvm/IR/Instruction.h"

using namespace llvm;
class Binary_OP{
public:
    std::string a;
    std::string b;
    std::string name;
    Instruction *inst;
    std::string inst_str;
    int opcode;
    bool isvalid = true;



};


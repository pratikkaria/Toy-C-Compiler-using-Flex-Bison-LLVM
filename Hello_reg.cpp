//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <vector>

using namespace llvm;

#define DEBUG_TYPE "hello"

STATISTIC(HelloCounter, "Counts number of functions greeted");

namespace {
struct ModulePassUtil : public ModulePass {
  static char ID;

  Module *module;

  std::vector<Binary_OP *> global_binary_op_list;

  std::vector<Binary_OP *> binary_op_list;
  std::map<std::string, Value *> locals;
  int tmp = 0;

  ModulePassUtil() : ModulePass(ID) {}

  std::string getNextTemp(){
    ++ tmp;
    return std::to_string(tmp);
  }

  void checkOpCode(int opcode){
     switch (opcode) {
    case Instruction::Add:
    errs()<<"Add opcode\n";
    break;
    case Instruction::Sub:
    errs()<<"Sub opcode\n";
    break;
    case Instruction::Mul:
    errs()<<"Mul opcode\n";
    break;
    case Instruction::SDiv:
    errs()<<"SDiv opcode\n";
    break;
    case Instruction::SRem:
    errs()<<"SRem opcode\n";
    break;
    case Instruction::And:
    errs()<<"And opcode\n";
    break;
    case Instruction::Or:
    errs()<<"Or opcode\n";
    break;
    case Instruction::Xor:
    errs()<<"Xor opcode\n";
    break;
    case Instruction::Load:
    errs()<<"Load opcode\n";
    break;
    case Instruction::Alloca:
    errs()<<"Alloca opcode\n";
    break;
    case Instruction::Store:
    errs()<<"Store opcode\n";
    break;
    default:
    errs()<<"Nothing matched\n";
    }
  }

  // Utils
  Binary_OP *isBinaryOpPresent(Binary_OP *binary_op) {
    errs()<<"Searching for a: "<<binary_op->a<<" b: "<<binary_op->b<<" opcode: "<<binary_op->opcode<<"\n";
    std::vector<Binary_OP *>::iterator it;
    for (it = binary_op_list.begin(); it != binary_op_list.end(); it++) {
      if (((*it)->a == binary_op->a) && ((*it)->b == binary_op->b) &&
          ((*it)->opcode == binary_op->opcode)) {
        errs() << "Found in Local. a: " << binary_op->a << " a: " << binary_op->b
               << " op: " << binary_op->opcode <<"\n";
               checkOpCode(binary_op->opcode);
        if ((*it)->isvalid) {
          return (*it);
        } else {
          errs() << "This is invalid\n";
        }
      }
    }

    // finding in global.
    for (it = global_binary_op_list.begin(); it != global_binary_op_list.end();
         it++) {
      if (((*it)->a == binary_op->a) && ((*it)->b == binary_op->b) &&
          ((*it)->opcode == binary_op->opcode) && (*it)->isvalid) {
        errs() << "Found in Global\n";
        return (*it);
      }
    }

    return nullptr;
  }

  void invalidateExpr(std::string name) {
    if (name.empty()) {
      return;
    }

    int typeVal = findVar(name);

    std::vector<Binary_OP *>::iterator it;

    for (it = binary_op_list.begin(); it != binary_op_list.end(); it++) {
      if (((*it)->a == name) || ((*it)->b == name)) {
        errs() << "Found in local and deleting: " << name << "\n";
        binary_op_list.erase(it);
        it--;
      }
    }

    if (typeVal == 2) {
      // do this for global also.
      for (it = global_binary_op_list.begin();
           it != global_binary_op_list.end(); it++) {
        if (((*it)->a == name) || ((*it)->b == name)) {
          errs() << "Found in global and deleting: " << name << "\n";
          global_binary_op_list.erase(it);
          it--;
        }
      }
    }
    return;
  }

  void addBinaryOp(Binary_OP *binary_op) {
    int reta = findVar(binary_op->a);
    int retb = findVar(binary_op->b);

    if (reta == 2 || retb == 2) {
      errs() << "Saving the expression in GLobal\n";
      global_binary_op_list.push_back(binary_op);
    } else {
      errs() << "Saving the expression in binary_local. a: "
      <<"Name: "<<binary_op->name<<" "
      <<binary_op->a<<" b: "<<binary_op->b<<" code: "<<binary_op->opcode<<"\n";
      binary_op_list.push_back(binary_op);
    }
  }

  int findVar(std::string name) {
    if (name.empty())
      return 4;
    // 0 for not found
    // 1 for local
    // 2 for global
    // 3 for constant
    // 4 for empty

    std::size_t found = name.find(" ");
    if (found != std::string::npos) {
      // errs() << "This is a constant." << name << "\n";
      return 4;
    }

    if (locals.find(name) != locals.end()) {
      return 1;
    } 

    GlobalVariable *gvar = module->getNamedGlobal(name);
    GlobalValue *gval = module->getNamedValue(name);

    if (gvar) {
      return 2;
    } else {
      errs() << "**** Error Undeclared Variable: " << name << "\n";
      return 0;
    }
  }



  // Function from here
  std::string processLoadInst(Instruction *inst) {
    std::string name = inst->getOperand(0)->getName();
    return name;
  }

  std::string processAllocaInst(Instruction *inst) {
    std::string var_name = inst->getName();
    if (!var_name.empty()) {
      locals[var_name] = inst;
    }
    return var_name;
  }

  std::string processStoreInst(Instruction *inst) {
    errs() << "processInstruction Store " << *inst << "\n";
    if (inst->getOpcode() != Instruction::Store) {
      errs() << "Return null\n";
      return "";
    }
    errs() << "Valid Store inst\n";
    std::string operand_name = inst->getOperand(1)->getName();
    errs() << "Returning: " << operand_name << "\n";
    return operand_name;
  }

  std::vector<std::string> getOperands(Instruction *inst) {
    std::vector<std::string> operand_list;
    for (Use &U : inst->operands()) {
      Value *v = U.get();
      if (Instruction *load_inst = dyn_cast<Instruction>(v)) {
        if (load_inst->getOpcode() == Instruction::Load) {
          std::string operandname = processLoadInst(load_inst);
          operand_list.push_back(operandname);
        } else {
          errs() << "This is a temp, must be calculated before:" << *load_inst << " \n";
          // errs() << "This must have been calculated before. Name is : "<<load_inst->getOpcode()<<" :\n";
          // search in tmp
          std::vector<std::string> ve = getOperands(load_inst);
          Binary_OP *check_tmp_local = new Binary_OP();
          check_tmp_local->a = ve[0];
          check_tmp_local->b = ve[1];
          check_tmp_local->opcode = load_inst->getOpcode();

          Binary_OP * res_local = isBinaryOpPresent(check_tmp_local);
          // if not then get a new tmp
          // std::string tmp_name = getNextTemp();
          // locals[tmp_name] = load_inst;
          operand_list.push_back(res_local->name);
        }
      } else if (Constant *c = dyn_cast<Constant>(v)) {

        std::string type_str;
        llvm::raw_string_ostream rso(type_str);
        c->print(rso);
        operand_list.push_back(rso.str());

      } else {
        errs() << "not a inst " << v->getValueName() << "\n   ";
      }
    }

    return operand_list;
  }

  void processBinaryInst(Instruction *inst, BasicBlock *pb,
                         BasicBlock::iterator &it2) {
    std::vector<std::string> operand_list;
    std::string type_str;
    llvm::raw_string_ostream rso(type_str);

    errs() << "Bin inst: " << *inst << "\n";
    operand_list = getOperands(inst);
  
    errs() << "Total operands: " << operand_list.size() << "\n";

    std::vector<std::string>::iterator it;
    for (it = operand_list.begin(); it != operand_list.end(); it++) {
      errs() << "Operand: " << *it << "\n";
    }

    Binary_OP *binary_op = new Binary_OP();
    binary_op->a = operand_list[0];
    binary_op->b = operand_list[1];
    binary_op->opcode = inst->getOpcode();
    binary_op->isvalid = true;
    binary_op->inst = inst;
    inst->print(rso);
    binary_op->inst_str = rso.str();

    binary_op->name = getNextTemp();


    // Binary_OP *temp = findTargetVariable(binary_op, pb, it2);
    // if (temp == nullptr) {
    //   return;
    // }
    // errs()<<"findTargetVariable: a: "<<temp->a<<" b: "<<temp->b<<" code: "<<temp->opcode<<"\n";
    // binary_op->isvalid = temp->isvalid;
    Binary_OP *binary_op_check = isBinaryOpPresent(binary_op);

    if (binary_op_check != nullptr) {
      errs() << "Eliminating with  inst: " << *(binary_op_check->inst) << "\n";
      // int ret = findVar(binary_op_check->val);
      // errs() << "ret is: " << ret << " for " << binary_op_check->inst_str <<
      // "\n";

      Value *value;

      // if (ret == 2) {
      //   value = module->getNamedValue(binary_op_check->val);
      //   LoadInst *newLoad = new LoadInst(value);
      //   errs()<<"Loading: "<<*value<<"\n";
      //   pb->getInstList().insert(it2, newLoad);
      //   value = newLoad;
      // } else

      if (binary_op_check->inst == nullptr) {
        goto savetheins;
      } else {
        value = binary_op_check->inst;
      }

      // LoadInst *newLoad = new LoadInst(value);
      // pb->getInstList().insert(it2, newLoad);
      // it2++;
      // errs() << "new load inst: " << *newLoad << "\n";

      errs() << "Replacing users\n";
      for (User *U : inst->users()) {
        U->replaceUsesOfWith(inst, value);
      }
      // errs() << "Replacing users DONE\n";
      errs() << "Replacing "<<*inst <<" with: " << *value << "\n";
      inst->replaceAllUsesWith(value);
      errs() << "Replacing inst done\n";

      errs() << "Removing operands\n";
      for (Use &U : inst->operands()) {
        Value *v = U.get();
        errs() << "Operand: " << *v << "\n";
        if (Instruction *load_inst = dyn_cast<Instruction>(v)) {
          if (load_inst->getOpcode() == Instruction::Load) {
            load_inst->eraseFromParent();
            // it2--;
            errs() << "Erased " << (*it2) << "\n";
          } else {
            errs() << "not a load\n";
          }
        } else if (Constant *c = dyn_cast<Constant>(v)) {
          errs() << "Constant\n";
          // it2--;
        }
      }
      it2--;
      // it2--;

      errs() << "Replacing operands Done\n";

      inst->eraseFromParent();
      errs() << "Erased\n";
      it2--;
      // it2--;
      return;
    }

  savetheins:
    // This is a new expression. Save this to the cache.
    addBinaryOp(binary_op);
  }

  void processInstruction(Instruction *inst, BasicBlock &function_iterator,
                          BasicBlock::iterator &it) {
    bool nothing_matched = false;
    switch (inst->getOpcode()) {
    case Instruction::Add:
    case Instruction::Sub:
    case Instruction::Mul:
    case Instruction::SDiv:
    case Instruction::SRem:
    case Instruction::And:
    case Instruction::Or:
    case Instruction::Xor:

      processBinaryInst(inst, &function_iterator, it);
      errs() << "\n---------\n";
      break;

    case Instruction::Load:
      processLoadInst(inst);
      errs() << "\n---------\n";
      break;

    case Instruction::Alloca: {
      std::string name = processAllocaInst(inst);
      errs() << "Allocating: " << name << "\n";
      break;
    }

    case Instruction::Store: {
      std::string sname = processStoreInst(inst);
      if (!sname.empty()) {
        errs() << "Store to: " << sname << "\n";
        invalidateExpr(sname);
      }
      break;
    }
    default:
      nothing_matched = true;
    }
  }

  llvm::LLVMContext *context;
  bool runOnModule(Module &M) override {
    std::map<std::string, int> opcode_map;
    llvm::LLVMContext &context2 = M.getContext();
    context = &context2;
    module = &M;
    for (Module::iterator module_iterator = M.begin(), ee = M.end();
         module_iterator != ee; module_iterator++) {

      // This will be called for each function
      for (Function::iterator function_iterator = module_iterator->begin(),
                              e = module_iterator->end();
           function_iterator != e; function_iterator++) {
        for (BasicBlock::iterator basic_iterator = function_iterator->begin();
             basic_iterator != function_iterator->end(); basic_iterator++) {
          Instruction *inst = dyn_cast<Instruction>(basic_iterator);
          processInstruction(inst, *function_iterator, basic_iterator);
        }

        // clearing out the local value of theold functions.
        binary_op_list.clear();
        locals.clear();
        tmp= 0;
      }
    }

    return false;
  }
};
}

char ModulePassUtil::ID = 0;
static RegisterPass<ModulePassUtil> X("ModulePassUtil",
                                      "ModulePassUtilHello World Pass");
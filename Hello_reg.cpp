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
  std::map<std::string, std::string> pre_locals;

  ModulePassUtil() : ModulePass(ID) {}

  // Utils
  Binary_OP *isBinaryOpPresent(Binary_OP *binary_op) {
    std::vector<Binary_OP *>::iterator it;

    for (it = binary_op_list.begin(); it != binary_op_list.end(); it++) {
      if (((*it)->a == binary_op->a) && ((*it)->b == binary_op->b) &&
          ((*it)->opcode == binary_op->opcode)) {
        errs() << "Found in Local. " << binary_op->a << " " << binary_op->b
               << " " << binary_op->opcode << "\n";
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
    errs() << "Adding a binary op\n";
    int reta = findVar(binary_op->a);
    int retb = findVar(binary_op->b);

    if (reta == 2 || retb == 2) {
      errs() << "Saving the expression in GLobal\n";
      global_binary_op_list.push_back(binary_op);
    } else {
      errs() << "Saving the expression in local\n";
      binary_op_list.push_back(binary_op);
    }

    pre_locals[binary_op->inst_str] = binary_op->val;
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
      errs() << "This is a constant." << name << "\n";
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

  Binary_OP *findTargetVariable(Binary_OP *binary_op, BasicBlock *pb,
                                BasicBlock::iterator &it2) {
    Binary_OP *binary_op_tmp = new Binary_OP();
    Instruction *inst = binary_op->inst;
    Instruction *store_inst;
    for (User *U : inst->users()) {
      if (store_inst = dyn_cast<Instruction>(U)) {
        if (store_inst->getOpcode() == Instruction::Store) {
          std::string stor_val = processStoreInst(store_inst);
          if (!stor_val.empty()) {
            errs() << "Final Saving to: " << stor_val << "\n";
            binary_op_tmp->val = stor_val;
            binary_op_tmp->isvalid = true;
            return binary_op_tmp;
          } else {
            errs() << "No store operand found\n";
            // create a new variable and store the value there.
          }
        } else {
          errs() << "This is not store. main " << *inst << "\n";
          errs() << "THis is not store. operans inst" << *store_inst << "\n";

          // If this is the return statement then there is no need to create
          // extra temo variable
          if (store_inst->getOpcode() == Instruction::Ret) {
            return nullptr;
          }
          binary_op_tmp->inst = store_inst;
          binary_op_tmp = findTargetVariable(binary_op_tmp, pb, it2);
          binary_op_tmp->val = "tmp_" + binary_op_tmp->val;

          // check here
          Binary_OP *search_binary_op = isBinaryOpPresent(binary_op);
          if (search_binary_op == nullptr) {
            // AllocaInst *pa = new AllocaInst(llvm::Type::getInt32Ty(*context),
            // 0,
            //                                 binary_op_tmp->val);
            // processAllocaInst(pa);
            // LoadInst *newLoad = new LoadInst(pa);
            // inst->replaceAllUsesWith(newLoad);
            // StoreInst *sa = new StoreInst(inst, pa);

            // errs() << "Alloc inst: " << *pa << "\n";
            // errs() << "Store inst: " << *sa << "\n";

            // errs() << "it2 at alloc insertion is: " << (*it2) << "\n";
            // pb->getInstList().insert(it2, pa);
            // it2++;

            // errs() << "it2 at of store insertion is: " << (*it2) << "\n";
            // pb->getInstList().insert(it2, sa);
            // // it2++;

            // errs() << "it2 at load insertion is: " << (*it2) << "\n";
            // pb->getInstList().insert(it2, newLoad);
            // it2--;
            return binary_op_tmp;

          } else {
            return search_binary_op;
          }
        }
      } else {
        errs() << "This is not instructio. save\n";
      }
    }
    return binary_op_tmp;
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
    errs() << "Checking " << *inst << "\n";
    if (inst->getOpcode() != Instruction::Store) {
      errs() << "Return null\n";
      return "";
    }
    errs() << "Valid Store inst\n";
    std::string operand_name = inst->getOperand(1)->getName();
    errs() << "Returning: " << operand_name << "\n";
    return operand_name;
  }

  void processBinaryInst(Instruction *inst, BasicBlock *pb,
                         BasicBlock::iterator &it2) {
    std::vector<std::string> operand_list;
    std::string type_str;
    llvm::raw_string_ostream rso(type_str);

    errs() << "Bin inst: " << *inst << "\n";

    for (Use &U : inst->operands()) {
      Value *v = U.get();
      if (Instruction *load_inst = dyn_cast<Instruction>(v)) {
        if (load_inst->getOpcode() == Instruction::Load) {
          std::string operandname = processLoadInst(load_inst);
          operand_list.push_back(operandname);
        } else {
          errs() << "Some other inst (expecting Load):" << *load_inst << " \n";
          errs() << "This must have been calculated before.\n";
          load_inst->print(rso);
          if (pre_locals.find(rso.str()) != pre_locals.end()) {
            errs() << "FOUND store in " << pre_locals[rso.str()] << "\n";
            operand_list.push_back(pre_locals[rso.str()]);
          } else {
            errs() << "NOT FOUND\n";
            return;
          }
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

    Binary_OP *temp = findTargetVariable(binary_op, pb, it2);
    if (temp == nullptr) {
      return;
    }
    binary_op->val = temp->val;
    binary_op->isvalid = temp->isvalid;

    Binary_OP *binary_op_check = isBinaryOpPresent(binary_op);

    if (binary_op_check != nullptr) {
      errs() << "Eliminating with " << binary_op_check->val
             << " inst: " << *(binary_op_check->inst) << "\n";
      int ret = findVar(binary_op_check->val);
      errs() << "ret is: " << ret << " for " << binary_op_check->val << "\n";
      // if (ret == 4) {
      //   // this was a temp. We are dealing with something wierd here;
      //   // look into binary op for oprans match.
      //   errs() << "Working on this one"
      //          << "\n";
      //   errs() << *inst << "\n";
      //   errs() << binary_op_check->a << "\n";
      //   errs() << binary_op_check->b << "\n";
      // }
      Value *value;

      if (ret == 2) {
        value = module->getNamedValue(binary_op_check->val);
        LoadInst *newLoad = new LoadInst(value);
        errs()<<"Loading: "<<*value<<"\n";
        pb->getInstList().insert(it2, newLoad);
        value = newLoad;
        // it2++;
        // value = newLoad;
      } else if(binary_op_check->inst==nullptr){
         goto savetheins;
      }else{
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
      errs()<<"Replacing with: "<<*value<<"\n";
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
          it2--;
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
        pre_locals.clear();
      }
    }

    return false;
  }
};
}

char ModulePassUtil::ID = 0;
static RegisterPass<ModulePassUtil> X("ModulePassUtil",
                                      "ModulePassUtilHello World Pass");
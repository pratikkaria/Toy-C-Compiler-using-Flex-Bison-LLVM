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

#include <vector>
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

#include "model.h"
#include "../../../include/llvm/IR/Instructions.h"
// #include "../../../include/llvm/Support/raw_ostream.h"
// #include "../../../include/llvm/IR/BasicBlock.h"
// #include "../../../include/llvm/IR/Instruction.h"
// #include "../../../include/llvm/IR/Use.h"
// #include "../../../include/llvm/ADT/Statistic.h"
// #include "../../../include/llvm/Pass.h"
// #include "../../../include/llvm/PassSupport.h"
// #include "../../../include/llvm/IR/Instructions.h"

using namespace llvm;

#define DEBUG_TYPE "hello"

STATISTIC(HelloCounter,
"Counts number of functions greeted");

namespace {
    // Hello - The first implementation, without getAnalysisUsage.
    struct Hello : public FunctionPass {
        static char ID; // Pass identification, replacement for typeid
        Hello() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            ++HelloCounter;
            errs() << "Hello: ";
            errs().write_escaped(F.getName()) << '\n';
            return false;
        }
    };
}

char Hello::ID = 0;
static RegisterPass <Hello> X("hello", "Hello World Pass");

namespace {

    std::vector<Binary_OP *> binary_op_list;
    std::map<std::string, Value *> locals;

    // Hello2 - The second implementation with getAnalysisUsage implemented.
    struct Hello2 : public FunctionPass {
        static char ID; // Pass identification, replacement for typeid
        Hello2() : FunctionPass(ID) {}

        Binary_OP *isBinaryOpPresent(Binary_OP *binary_op) {
            std::vector<Binary_OP *>::iterator it;
            for (it = binary_op_list.begin(); it != binary_op_list.end(); it++) {
                if (((*it)->a == binary_op->a)
                    && ((*it)->b == binary_op->b)
                    && ((*it)->opcode == binary_op->opcode)) {
                    return (*it);
                }
            }
            return nullptr;
        }

        std::string processLoadInst(Instruction *inst) {
            // int total = 0;
            // errs()<<"Processing Load Instruction: \n";
            // errs()<<*inst<<"\n";
            std::string name = inst->getOperand(0)->getName();
            // errs()<<"Load var: "<<name<<"\n";
            return name;

        }

        void processAllocaInst(Instruction *inst) {
            // errs()<<"This is Alloca. This is: "<<inst->getOpcode()<<"\n";
            std::string var_name = inst->getName();
            if (!var_name.empty()) {
                errs() << "Variable Name: " << var_name << "\n";
                locals[var_name] = inst;
            }
            // errs()<<"Type: "<<inst->getType()->isIntegerTy()<<"\n";
            // errs()<<"Inst: "<<*i<<"\n\n";
        }

        std::string processStoreInst(Instruction *inst) {
            errs() << "Store. Inst: " << *inst << "\n";
            std::string operand_name = inst->getOperand(1)->getName();
            errs() << "Operand: " << operand_name << "\n";
            return operand_name;
            //   for(Use &U : inst->operands()){
            //   Value *v = U.get();
            //   errs()<<*v<<"\n";
            // }
            // for (auto op = inst->op_begin(); op != inst->op_end(); op++) {
            //     Value* v = op->get();
            //     StringRef name = v->getName();
            //     errs()<<"==>: "<<name<<"\n";
            //   }

        }

        void processAddInst(Instruction *inst, BasicBlock *pb, BasicBlock::iterator &it2, llvm::LLVMContext &context) {
            // errs()<<"This is Add. This is: "<<inst->getOpcode()<<"\n";
            std::vector<std::string> operand_list;
            errs() << "Add inst: " << *inst << "\n";
            for (Use &U : inst->operands()) {
                Value * v = U.get();
                if (Instruction * Inst = dyn_cast<Instruction>(v)) {
                    if (Inst->getOpcode() == Instruction::Load) {
                        std::string operandname = processLoadInst(Inst);
                        // if (!operandname.empty()) {
                        operand_list.push_back(operandname);
                        // }
                    }
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
            binary_op->value = inst;
            Instruction * store_inst;
            for (User *U: inst->users()) {
                if (store_inst = dyn_cast<Instruction>(U)) {
                    std::string stor_val = processStoreInst(store_inst);
                    binary_op->val = stor_val;
                }
            }

            Binary_OP *binary_op_check = isBinaryOpPresent(binary_op);

            if (binary_op_check != nullptr) {
                errs() << "THIS IS ALREADY PRESENT and the value can be found in " << binary_op_check->val << "\n";
                errs() << *inst << "\n";
                Value * value = locals[binary_op_check->val];
                Value * tmp;

                // for (Use &U : inst->operands()) {
                //     Value * v = U.get();
                //     if (Instruction * load_inst = dyn_cast<Instruction>(v)) {
                //       errs()<<"Trying to remove: "<<*load_inst<<"\n";
                //         if (load_inst->getOpcode() == Instruction::Load) {
                //           errs()<<"Trying to remove: "<<*load_inst<<"\n";
                //             ReplaceInstWithValue(load_inst->getParent()->getInstList(), it2, tmp);
                //             it2--;
                //         }else{
                //           errs()<<"THIS IS NOT LOADTrying to remove: "<<*load_inst<<"\n";
                //         }
                //     }else{
                //           errs()<<"THIS IS NOT Instruction"<<"\n";
                //     }
                // }

                // IRBuilder<> builder(context);
                // LoadInst *loadInst = builder.CreateLoad(value, "ff");
                // Value *inci;
                // builder.CreateStore(inci, dyn_cast<Value>(binary_op_check->value));

                // auto *newAlloc = new AllocaInst(llvm::Type::getInt32Ty(context), 0, "indexLoc");

                LoadInst *newLoad = new LoadInst(value);
                pb->getInstList().insert(it2, newLoad);
                // it2++; // this is requried
                // StoreInst * storeInst = new StoreInst(newLoad, locals[binary_op->val]);
                // pb->getInstList().insert(it2, storeInst);

                it2++;

                // errs() << "New store inst\n";
                // errs() << *storeInst << "\n";

                // BasicBlock::iterator ii3(inst);
                // ReplaceInstWithValue(pb->getInstList(), it2,
                //      value);
                // inst->replaceAllUsesWith(newLoad);
                // errs() << *inst << "\n";

                // ReplaceInstWithValue(inst->getParent()->getInstList(), it2, value);
                // ReplaceInstWithInst(inst->getParent()->getInstList(), it2, newLoad);

                // StoreInst *storeInst = new StoreInst(newLoad, locals[binary_op->val]);
                // pb->getInstList().insert(it2, storeInst);
                // it2++;
                // inst->eraseFromParent();
                // inst->removeFromParent();

                // it2--;
                // this has to be here as it cannot be before instruction using this.


                for (User *U: inst->users()) {
                    U->replaceUsesOfWith(inst, newLoad);
                    // if (store_inst = dyn_cast<Instruction>(U)) {
                    //     errs() << "Usage of inst:\n";
                    //     errs() << *store_inst << "\n";
                    //     // ReplaceInstWithValue(store_inst->getParent()->getInstList(), it2, tmp);
                    //     // store_inst->eraseFromParent();
                    //     // it2--;
                    //     //
                    // }
                }

                inst->replaceAllUsesWith(value);

                // ReplaceInstWithValue(inst->getParent()->getInstList(), it2, tmp);
                // ReplaceInstWithValue(inst->getParent()->getInstList(), it2, value);
                
                // errs()<<"Here: "<<dyn_cast<Instruction>(inst->getOperand(0))<<"\n";



                for (Use &U : inst->operands()) {
                    Value * v = U.get();
                    if (Instruction * load_inst = dyn_cast<Instruction>(v)) {
                        errs() << "Trying to remove: " << *load_inst << "\n";
                        if (load_inst->getOpcode() == Instruction::Load) {
                            errs() << "Trying to remove: " << *load_inst << "\n";
                            // ReplaceInstWithValue(load_inst->getParent()->getInstList(), it2, tmp);
                            load_inst->eraseFromParent();
                            it2--;
                        } else {
                            errs() << "THIS IS NOT LOADTrying to remove: " << *load_inst << "\n";
                        }
                    } else {
                        errs() << "THIS IS NOT Instruction" << "\n";
                    }
                }

                inst->eraseFromParent();
                it2--;

                // inst->removeFromParent();

            } else {
                errs() << "THIS IS NOT FOUND\n";
                binary_op_list.push_back(binary_op);

            }


        }

        void
        processInstruction(Instruction *inst, BasicBlock &bb, BasicBlock::iterator &it, llvm::LLVMContext &context) {
            switch (inst->getOpcode()) {
                case Instruction::Add:
                    processAddInst(inst, &bb, it, context);
                    break;
                case Instruction::Load:
                    processLoadInst(inst);
                    break;
                case Instruction::Alloca:
                    processAllocaInst(inst);
                    break;
                case Instruction::Store:
                    processStoreInst(inst);
                    break;
                default:
                    errs() << "Instruction OPCODE not supported\n";
            }
        }


        bool runOnFunction(Function &F) override {

            ++HelloCounter;
            std::map<std::string, int> opcode_map;
            llvm::LLVMContext &context = F.getContext();
            for (Function::iterator bb = F.begin(), e = F.end(); bb != e; bb++) {
                for (BasicBlock::iterator i = bb->begin(), i2 = bb->end(); i != i2; i++) {
                    // Processing this instruction
                    // Processing each of the instruction.
                    Instruction * inst = dyn_cast<Instruction>(i);
                    processInstruction(inst, *bb, i, context);
                }
            }

            return false;

        }
    };
}

char Hello2::ID = 0;
static RegisterPass <Hello2>
        Y("hello2", "Hello World Pass (with getAnalysisUsage implemented)");

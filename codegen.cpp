#include "node.h"
#include "codegen.h"
#include "c.tab.hpp"
#include <llvm/IR/Verifier.h>

using namespace std;

extern void yyerror(const char *);

bool secondpass = false;

void CodeGenContext::generateCode(BlockNode &rootNode) {
    cout << "Generating code for ROOT..." << endl;
    rootNode.codeGen(*this);

    secondpass = true;
    int pass = 0;
    while (pass) {
        cout << "##################SECOND PASS#################" << endl;
        module = new Module("main", llvmContext);
        rootNode.codeGen(*this);
        pass--;
    }

    module->dump();
}

static Type *typeOf(const IdentiferNode &type, bool isPtr) {
    if (type.name.compare("long") == 0) {
        if (isPtr)
            return Type::getInt64PtrTy(llvmContext);
        return Type::getInt64Ty(llvmContext);
    } else if (type.name.compare("int") == 0) {
        if (isPtr)
            return Type::getInt32PtrTy(llvmContext);
        return Type::getInt32Ty(llvmContext);
    } else if ((type.name.compare("double") == 0)) {
        if (isPtr)
            return Type::getDoublePtrTy(llvmContext);
        return Type::getDoubleTy(llvmContext);
    } else if (type.name.compare("char") == 0) {
        if (isPtr)
            return Type::getInt8PtrTy(llvmContext);
        return Type::getInt8Ty(llvmContext);
    } else if (type.name.compare("void") == 0) {
        return Type::getVoidTy(llvmContext);
    } else if (type.name.compare("_Bool") == 0) {
        return Type::getInt1Ty(llvmContext);
    }
    return Type::getVoidTy(llvmContext);
}


static int findInConstant(CodeGenContext &context, string name) {
    if (context.const_locals().find(name) != context.const_locals().end()) {
        return context.const_locals()[name];
    }
}

static int findInConstant(CodeGenContext &context, ASTNode *node) {
    if (context.const_locals().find(((IdentiferNode *) node)->name) != context.const_locals().end()) {
        return context.const_locals()[((IdentiferNode *) node)->name];
    } else if (dynamic_cast<IntNode *>(node)) {
        return ((IntNode *) node)->value;
    }
}

static bool isThisConstant(CodeGenContext &context, ASTNode *node) {
//    cout<<"#### isthisconstant: "<<endl;
    if (dynamic_cast<IdentiferNode *>(node)) {
//        cout<<"This is an identifer: "<<((IdentiferNode *)node)->name<<endl;
        if (context.const_locals().find(((IdentiferNode *) node)->name) != context.const_locals().end()) {
//            cout<<"Found it"<<endl;
            return context.const_locals()[((IdentiferNode *) node)->name];
        }
    } else if (dynamic_cast<IntNode *>(node)) {
//        cout<<"This is an int node"<<endl;
        return true;
    }
    return false;
}

static bool isThisConstant(CodeGenContext &context, string name) {
    if (context.const_locals().find(name) != context.const_locals().end()) {
        return context.const_locals()[name];
    }
    return false;
}


static bool isThisVariableUsed(CodeGenContext &context, string name) {
    if (context.variable_use().find(name) != context.variable_use().end()) {
        return true;
    }
    return false;
}

static Value *findIdentifierValue(CodeGenContext &context, string name) {
    if (context.isBlocksEmpty()) {
        goto checkglobal;
    } else if (context.locals().find(name) != context.locals().end()) {
        return context.locals()[name];
    } else {
        // Search in parent block.
        CodeGenBlock *parentBlock = context.currentCgenBlock();
        while (parentBlock->parent != nullptr) {
            if (parentBlock->parent->locals.find(name) !=
                parentBlock->parent->locals.end()) {
                return parentBlock->parent->locals[name];
            }
            parentBlock = parentBlock->parent;

        }
    }
    checkglobal:
    GlobalVariable *gvar = context.module->getNamedGlobal(name);
    GlobalValue *gval = context.module->getNamedValue(name);

    if (gvar) {
        return gval;
    } else {
        cerr << "**** Error Undeclared Variable: " << name << endl;
        return nullptr;
    }
}


/* -- Code Generation -- */
Value *BlockNode::codeGen(CodeGenContext &context) {
    cout << "Generating code for Block" << endl;
    StatementList::const_iterator it;
    Value *last = NULL;

    if (!secondpass) {
        for (it = statements.begin(); it != statements.end(); it++) {
            cout << "\nGenerating code for " << typeid(**it).name() << endl;
            last = (**it).codeGen(context);
        }

        cout << "***************" << endl;
//    cout<<"2 Size: "<<context.variable_use().size()<<endl;

        for (it = statements.begin(); it != statements.end(); it++) {
            cout << "\nPrinting usage for " << typeid(**it).name() << ": ";
            if (dynamic_cast<VariableDeclaration *>(*it)) {
                cout << ((VariableDeclaration *) (*it))->id->name
                     << " used: " << isThisVariableUsed(context, ((VariableDeclaration *) (*it))->id->name)
                     << " isconstant: " << isThisConstant(context, ((VariableDeclaration *) (*it))->id->name)
                     << endl;
            } else {
                cout << endl;
            }
        }
        cout << "***************" << endl;
    } else {


        for (it = statements.begin(); it != statements.end(); it++) {
            cout << "\nGenerating code for " << typeid(**it).name() << endl;
            if (dynamic_cast<VariableDeclaration *>(*it)) {
                if (!isThisVariableUsed(context, ((VariableDeclaration *) (*it))->id->name)) {
                    cout << ((VariableDeclaration *) (*it))->id->name
                         << " used: " << isThisVariableUsed(context, ((VariableDeclaration *) (*it))->id->name)
                         << " isconstant: " << isThisConstant(context, ((VariableDeclaration *) (*it))->id->name)
                         << endl;
                    cout << "SKIPPING" << endl;
                    continue;
                }
            }
            cout << "Generating" << endl;
            last = (**it).codeGen(context);
        }
    }
    return last;
}

//Push Style

Value *ForLoopNode::codeGen(CodeGenContext &context) {
    cout << "Creating code for loop: " << endl;
    Function *function = context.currentBlock()->getParent();
    // declaration
    if (declaration != NULL)
        declaration->codeGen(context);
    else if (expr_dec != NULL)
        expr_dec->codeGen(context);

    BasicBlock *CondBB = BasicBlock::Create(llvmContext, "cond", function);
    BasicBlock *LoopBB = BasicBlock::Create(llvmContext, "loop");
    BasicBlock *ProgressBB = BasicBlock::Create(llvmContext, "progress");
    BasicBlock *AfterBB = BasicBlock::Create(llvmContext, "after");

    function->getBasicBlockList().push_back(CondBB);
    function->getBasicBlockList().push_back(LoopBB);
    function->getBasicBlockList().push_back(ProgressBB);
    function->getBasicBlockList().push_back(AfterBB);


    BranchInst::Create(CondBB, context.currentBlock());

    //cond
    context.pushBlock(CondBB);
    Value *startval = condition->codeGen(context);
    BranchInst::Create(LoopBB, AfterBB, startval, context.currentBlock());
    context.popBlock();

    //loopblock
    context.pushBlock(LoopBB);
    Value *loopval = block->codeGen(context);
    BranchInst::Create(ProgressBB, context.currentBlock());
    context.popBlock();
    //---------

    //progress
    context.pushBlock(ProgressBB);
    if (progress != NULL)
        progress->codeGen(context);
    BranchInst::Create(CondBB, context.currentBlock());
    context.popBlock();

    //afterbb
    context.pushBlock(AfterBB);
//    context.currentCgenBlock()->pending_blocks++;
//    context.popBlock();

    return NULL;

}

Value *DoWhileLoopNode::codeGen(CodeGenContext &context) {
    cout << "Creating code forDo while: " << endl;
    Function *function = context.currentBlock()->getParent();

    BasicBlock *LoopBB = BasicBlock::Create(llvmContext, "loop", function);
    BasicBlock *CondBB = BasicBlock::Create(llvmContext, "cond");
    BasicBlock *AfterBB = BasicBlock::Create(llvmContext, "after");

    function->getBasicBlockList().push_back(LoopBB);
    function->getBasicBlockList().push_back(CondBB);
    function->getBasicBlockList().push_back(AfterBB);

    BranchInst::Create(LoopBB, context.currentBlock());

    // cond block
    context.pushBlock(CondBB);
    Value *startval = cond->codeGen(context);
    BranchInst::Create(LoopBB, AfterBB, startval, context.currentBlock());
    context.popBlock();

    //loopblock
    context.pushBlock(LoopBB);
    Value *loopval = block->codeGen(context);
    BranchInst::Create(CondBB, context.currentBlock());
    context.popBlock();
    //---------

    //afterbb
    context.pushBlock(AfterBB);

    return NULL;

}

Value *WhileLoopNode::codeGen(CodeGenContext &context) {
    cout << "Creating code for: While loop" << endl;
    Function *function = context.currentBlock()->getParent();
    Value *condValue = cond->codeGen(context);

//    if(context.optimization_phase) {
//        if (cond->isConstant && cond->const_value == 0) {
//            return NULL;
//        }
//    }


    BasicBlock *CondBB = BasicBlock::Create(llvmContext, "whlcond", function);
    BasicBlock *LoopBB = BasicBlock::Create(llvmContext, "whlloop");
    BasicBlock *AfterBB = BasicBlock::Create(llvmContext, "whlafter");

    function->getBasicBlockList().push_back(CondBB);
    function->getBasicBlockList().push_back(LoopBB);
    function->getBasicBlockList().push_back(AfterBB);

    BranchInst::Create(CondBB, context.currentBlock());

    //comnd
    context.pushBlock(CondBB);
    Value *startval = cond->codeGen(context);
    BranchInst::Create(LoopBB, AfterBB, startval, context.currentBlock());
    context.popBlock();

    //loopblock
    context.pushBlock(LoopBB);
    Value *loopval = block->codeGen(context);
    BranchInst::Create(CondBB, context.currentBlock());
    context.popBlock();
    //---------

    //afterbb
    context.pushBlock(AfterBB);

    return NULL;

}

Value *IfNode::codeGen(CodeGenContext &context) {
    cout << "Creating IF Statement" << endl;
    Function *function = context.currentBlock()->getParent();
    Value *condValue = cond->codeGen(context);
//    if(context.optimization_phase) {
//
//        if (cond->isConstant) {
//            if (debug)
//                cout << "in the IF block and this is constant" << endl;
//            if (cond->const_value == 1) {
//                Value *thenValue = truecond->codeGen(context);
//            } else {
//                falsecond->codeGen(context);
//            }
//
//            return NULL;
//        }
//    }


    BasicBlock *thenBlock = BasicBlock::Create(llvmContext, "then", function);
    BasicBlock *elseBlock = BasicBlock::Create(llvmContext, "else");
    BasicBlock *mergeBlock = BasicBlock::Create(llvmContext, "cont");

    cout << "Blocks created" << endl;

    function->getBasicBlockList().push_back(thenBlock);


    if (falsecond != nullptr) {
        BranchInst::Create(thenBlock, elseBlock, condValue, context.currentBlock());
    } else {
        BranchInst::Create(thenBlock, mergeBlock, condValue, context.currentBlock());
    }

    // This is required so the the variables can be matched.
    context.pushBlock(thenBlock);
    Value *thenValue = truecond->codeGen(context);
    BranchInst::Create(mergeBlock, context.currentBlock());
    context.popBlock();

    // create else block
    if (falsecond != nullptr) {
        function->getBasicBlockList().push_back(elseBlock);
        // This is required so the the variables can be matched.
        context.pushBlock(elseBlock);
        Value *elseValue = falsecond->codeGen(context);
        BranchInst::Create(mergeBlock, context.currentBlock());
        context.popBlock();
    }

    // create PHI node
    function->getBasicBlockList().push_back(mergeBlock);
    context.pushBlock(mergeBlock);


    return NULL;
}

Value *VariableDeclaration::codeGen(CodeGenContext &context) {

    cout << "Creating code for Variable declaration: " << endl;
    if (debug) {
        cout << "Var: Type: " << storageType->type->name << endl;
        cout << "Var: Name: " << id->name << endl;
    }

    //checking const


    if (!context.isBlocksEmpty()) {
        // Local
        AllocaInst *alloc = new AllocaInst(typeOf(*(storageType->type), isPtr), id->name.c_str(),
                                           context.currentBlock());
        if (context.locals().find(id->name) == context.locals().end()) {
            context.locals()[id->name] = alloc;
        } else {
            yyerror("Variable Already defined");
        }
//        if (isThisConstant(context, id->name) && context.optimization_phase) {
//            return context.const_values()[id->name];
//        }
        if (assignmentExpr != NULL) {
            AssignmentNode assn(*id, assignmentExpr, isPtr);
            Value *val = assn.codeGen(context);
//            if (assignmentExpr->isConstant) {

            cout << "++++++++Marking " << id->name << " constant" << endl;
            context.const_locals()[id->name] = true;
                context.const_values()[id->name] = alloc;

//                isConstant = true;
//                const_value = assignmentExpr->const_value;

//                id->isConstant = true;
//                id->const_value = const_value;
//            } else {
//                if (debug)
//                    cout << "========>This is not constant" << endl;
//            }
        }
        return alloc;
    } else {
        context.module->getOrInsertGlobal(id->name, typeOf(*(storageType->type), isPtr));
        GlobalVariable *gVar = context.module->getNamedGlobal(id->name);

        if (!storageType->storage) {
            gVar->setLinkage(GlobalValue::InternalLinkage);
        } else {
            gVar->setLinkage(GlobalValue::ExternalLinkage);
        }

        if (storageType && storageType->qualifier) {
//            if (storageType->qualifier->name.compare("const") == 0) {
            gVar->setConstant(true);
//            }
        }

        if (assignmentExpr != NULL) {
            AssignmentNode assn(*id, assignmentExpr, isPtr);
            assn.codeGen(context);
        }
        return NULL;
    }

}

Value *AssignmentNode::codeGen(CodeGenContext &context) {
    cout << "Creating assignment for AssignmentNode " << endl;
    if (debug) {
        cout << "Name: " << getId().name << endl;
    }
    Value *id_val;

    if (context.isBlocksEmpty()) {
        GlobalVariable *gvar = context.module->getNamedGlobal(getId().name);
        id_val = context.module->getNamedValue(getId().name);
        if (gvar) {
            if (debug)
                cout << "It is global" << endl;
            if (!gvar->hasInitializer()) {
                cout << assignmentExpr << endl;
                if (!isPtr) {
                    gvar->setInitializer(dyn_cast<Constant>(assignmentExpr->codeGen(context)));
                } else {
                    const char *constValue = ((IdentiferNode *) assignmentExpr)->name.c_str();;
                    llvm::Constant *format_const =
                            llvm::ConstantDataArray::getString(llvmContext, constValue);
                    llvm::GlobalVariable *var =
                            new llvm::GlobalVariable(
                                    *context.module, llvm::ArrayType::get(llvm::IntegerType::get(llvmContext, 8),
                                                                          strlen(constValue) + 1),
                                    true, llvm::GlobalValue::PrivateLinkage, format_const, ".str");


                    gvar->setInitializer(var);
                }
                return gvar;
            } else {
                if (debug)
                    cout << "The global has already been has been initialized" << endl;
            }
        } else {
            std::cerr << "undeclared variable " << id.name << endl;
            return NULL;
        }
    }

    id_val = findIdentifierValue(context, getId().name);

    if (id_val == nullptr)
        return NULL;
    IRBuilder<> builder(context.currentBlock());
    LoadInst *loadInst = builder.CreateLoad(id_val, "");
    Value *inci;
    switch (op) {
        case ADD_ASSIGN: {
            if (debug)
                cout << "This is ADD Assign ********\n";
            Value *tmp = assignmentExpr->codeGen(context);
            IRBuilder<> builder(context.currentBlock());
            inci = builder.CreateAdd(loadInst, tmp, "");
            builder.CreateStore(inci, id_val);
            cout << "+++++++Marking " << getId().name << " NOT constant" << endl;
            context.const_locals()[getId().name] = false;
            return inci;
        }
        case SUB_ASSIGN:
            if (debug)
                cout << "This is SUB Assign ********\n";
            inci = builder.CreateSub(loadInst, assignmentExpr->codeGen(context), "");
            builder.CreateStore(inci, id_val);
            return inci;
        case MUL_ASSIGN:
            if (debug)
                cout << "This is MUL Assign ********\n";
            inci = builder.CreateMul(loadInst, assignmentExpr->codeGen(context), "");
            builder.CreateStore(inci, id_val);
            return inci;
        case DIV_ASSIGN:
            if (debug)
                cout << "This is DIV Assign ********\n";
            inci = builder.CreateSDiv(loadInst, assignmentExpr->codeGen(context), "");
            builder.CreateStore(inci, id_val);
            return inci;
        case MOD_ASSIGN:
            if (debug)
                cout << "This is MOD Assign ********\n";
            inci = builder.CreateSRem(loadInst, assignmentExpr->codeGen(context), "");
            builder.CreateStore(inci, id_val);
            return inci;
        case OR_ASSIGN:
            if (debug)
                cout << "This is OR Assign ********\n";
            inci = builder.CreateOr(loadInst, assignmentExpr->codeGen(context), "");
            builder.CreateStore(inci, id_val);
            return inci;
        case AND_ASSIGN:
            if (debug)
                cout << "This is AND Assign ********\n";
            inci = builder.CreateAnd(loadInst, assignmentExpr->codeGen(context), "");
            builder.CreateStore(inci, id_val);
            return inci;
        case XOR_ASSIGN:
            if (debug)
                cout << "This is XOR Assign ********\n";
            inci = builder.CreateXor(loadInst, assignmentExpr->codeGen(context), "");
            builder.CreateStore(inci, id_val);
            return inci;
//        case '=':
//            goto normaalassig;
//        default:
//            cout<<"Assign: Not Supported: "<<op<<endl;

    }
    // THi is the normal assignment, example a =10;
    Value *assig_val = assignmentExpr->codeGen(context);
    if (dynamic_cast<BinaryOperatorNode *>(assignmentExpr)) {
        cout << "got the constant value:" << ((BinaryOperatorNode *) assignmentExpr)->isConstant << endl;
        if (!((BinaryOperatorNode *) assignmentExpr)->isConstant) {
            cout << "+++++++Marking " << getId().name << " NOT constant" << endl;
            context.const_locals()[getId().name] = false;
        } else {
            cout << "+++++++Marking " << getId().name << " constant" << endl;
            context.const_locals()[getId().name] = true;
        }
    } else {
        cout << "ERROR " << endl;
    }

    return new StoreInst(assig_val,
                         id_val, false, context.currentBlock());


}

//----------------

Value *LongNode::codeGen(CodeGenContext &context) {
    cout << "Creating code for: Long" << endl;
    return ConstantInt::get(Type::getInt64Ty(llvmContext), value, true);
}

Value *CharNode::codeGen(CodeGenContext &context) {
    cout << "Creating code for: Char" << endl;
    return ConstantInt::get(Type::getInt8Ty(llvmContext), value, true);
}

Value *IntNode::codeGen(CodeGenContext &context) {
    cout << "Creating code for: int" << endl;
    return ConstantInt::get(Type::getInt32Ty(llvmContext), value, true);
}

Value *BoolNode::codeGen(CodeGenContext &context) {
    cout << "Creating code for: bool" << endl;
    IRBuilder<> builder(context.currentBlock());
    if (value)
        return builder.getTrue();
    else
        return builder.getFalse();
//    return ConstantInt::get(Type::getInt1Ty(llvmContext), value, true);
}

Value *DoubleNode::codeGen(CodeGenContext &context) {
    cout << "Creating code for: double" << endl;
    return ConstantFP::get(Type::getDoubleTy(llvmContext), value);
}

Value *StringNode::codeGen(CodeGenContext &context) {
    cout << "String code gen: " << value << endl;


    size_t pos = value.find("\\n");
    if (pos != string::npos) {
        value.replace(pos, 2, 1, '\n');
    }
    pos = value.find("\"");
    if (pos != string::npos)
        value.erase(pos, 1);
    pos = value.find("\"");
    if (pos != string::npos)
        value.erase(pos, 1);


//    cout << "String code gen: " << value << endl;
    const char *constValue = value.c_str();

    llvm::Constant *format_const =
            llvm::ConstantDataArray::getString(llvmContext, constValue);
    llvm::GlobalVariable *var =
            new llvm::GlobalVariable(
                    *context.module, llvm::ArrayType::get(llvm::IntegerType::get(llvmContext, 8),
                                                          strlen(constValue) + 1),
                    true, llvm::GlobalValue::PrivateLinkage, format_const, ".str");

    llvm::Constant *zero =
            llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(llvmContext));

    std::vector < llvm::Constant * > indices;
    indices.push_back(zero);
    indices.push_back(zero);
    llvm::Constant *var_ref = llvm::ConstantExpr::getGetElementPtr(
            llvm::ArrayType::get(llvm::IntegerType::get(llvmContext, 8), strlen(constValue) + 1),
            var, indices);

    return var_ref;
}

//---------------

Value *IdentiferNode::codeGen(CodeGenContext &context) {
    cout << "=================Creating identifier reference: " << name << endl;
    context.variable_use()[name] = true;
    Value *ident_ptr = findIdentifierValue(context, name);
    if (ident_ptr == nullptr) {
        cerr << "Error: Variable is not defined" << endl;
        return NULL;
    }
    return new LoadInst(ident_ptr, "", false, context.currentBlock());
}

Value *FunctionCallNode::codeGen(CodeGenContext &context) {
    cout << "Generating for Function Call for " << id.name << " args Size " << arguments.size() << endl;
    Function *function = context.module->getFunction(id.name.c_str());
    if (function == NULL) {
        std::cerr << "no such function " << id.name << endl;
        return NULL;
    }
    std::vector < Value * > args;
    ExpressionList::const_iterator it;
    for (it = arguments.begin(); it != arguments.end(); it++) {
        args.push_back((**it).codeGen(context));

    }
    CallInst *call = CallInst::Create(function, makeArrayRef(args), "",
                                      context.currentBlock());
    std::cout << "Creating method call: " << id.name << endl;
    return call;
}

Value *UnaryOperatorNode::codeGen(CodeGenContext &context) {
    std::cout << "****Creating unary operation " << op << endl;

    switch (op) {
        case INC_OP: {
            if (debug)
                cout << "INC_OP" << endl;
            Value *lhsvali = lhs.codeGen(context);
            IRBuilder<> builder(context.currentBlock());
            Value *inci = builder.CreateAdd(lhsvali, builder.getInt32(1), "");
            Value *stri = builder.CreateStore(inci, findIdentifierValue(context, ((IdentiferNode *) &lhs)->name));
            cout << "+++++++Marking " << ((IdentiferNode *) &lhs)->name << " NOT constant in unary" << endl;
            lhs.isConstant = false;
            context.const_locals()[((IdentiferNode *) &lhs)->name] = false;
            if (onleft)
                return inci;
            return lhsvali;
        }
        case DEC_OP: {
            if (debug)
                cout << "DEC_OP" << endl;
            Value *lhsvald = lhs.codeGen(context);
            IRBuilder<> builder(context.currentBlock());
            Value *incd = builder.CreateSub(lhsvald, builder.getInt32(1), "");
            Value *strd = builder.CreateStore(incd, findIdentifierValue(context, ((IdentiferNode *) &lhs)->name));
            if (onleft)
                return incd;
            return lhsvald;

        }
        default:
            cerr << "UNARY OPERATOR NOT SUPPORTED" << endl;
    }
    return NULL;
}

Value *BinaryOperatorNode::codeGen(CodeGenContext &context) {
    std::cout << "Creating binary operation " << op << endl;
    if (isThisConstant(context, lhs) && isThisConstant(context, rhs)) {
        cout << "+++++++++" << "This binary op is constant" << endl;
        this->isConstant = true;
        isConstant = true;
    }
//    if (dynamic_cast<IdentiferNode *>(lhs)) {
//        if (isThisConstant(context, ((IdentiferNode *) lhs)->name) && context.optimization_phase) {
//            int lhs_val = findInConstant(context, ((IdentiferNode *) lhs)->name);
//            lhs->isConstant = true;
//            lhs->const_value = lhs_val;
//        }
//    }
//
//    if (dynamic_cast<IdentiferNode *>(rhs)) {
//        if (isThisConstant(context, ((IdentiferNode *) rhs)->name)) {
//            int rhs_val = findInConstant(context, ((IdentiferNode *) rhs)->name);
//            rhs->isConstant = true;
//            rhs->const_value = rhs_val;
//        }
//    }

    IRBuilder<> builder(context.currentBlock());
    Instruction::BinaryOps instr;
    switch (op) {
        case '+':
            if (debug)
                cout << "This is Add" << endl;
            instr = Instruction::Add;
            goto math;
        case '-':
            if (debug)
                cout << "This is Sub" << endl;
            instr = Instruction::Sub;
            goto math;
        case '*':
            if (debug)
                cout << "This is Mul" << endl;
            instr = Instruction::Mul;
            goto math;
        case '/':
            instr = Instruction::SDiv;
            goto math;
        case '%':
            instr = Instruction::SRem;
            goto math;

        case '&':
            instr = Instruction::And;
            goto math;
        case '|':
            instr = Instruction::Or;
            goto math;
        case '^':
            instr = Instruction::Xor;
            goto math;
        case NE_OP:
//            if (lhs->isConstant && rhs->isConstant) {
//                if (debug)
//                    cout << "THis is CONSTANT" << endl;
//                isConstant = true;
//
//                if (lhs->const_value != rhs->const_value) {
//                    const_value = 1;
//                    return ConstantInt::get(Type::getInt1Ty(llvmContext), 1, true);
//                } else {
//                    const_value = 0;
//                    return ConstantInt::get(Type::getInt1Ty(llvmContext), 0, true);
//
//                }
//            }

            return builder.CreateICmpNE(lhs->codeGen(context), rhs->codeGen(context), "");
        case EQ_OP:
//            if (lhs->isConstant && rhs->isConstant && context.optimization_phase) {
//                isConstant = true;
//
//                if (lhs->const_value == rhs->const_value) {
//                    const_value = 1;
//                    return ConstantInt::get(Type::getInt1Ty(llvmContext), 1, true);
//                } else {
//                    const_value = 0;
//                    return ConstantInt::get(Type::getInt1Ty(llvmContext), 0, true);
//
//                }
//            }
            // return ConstantInt::get(Type::getInt32Ty(llvmContext), value, true);
            return builder.CreateICmpEQ(lhs->codeGen(context), rhs->codeGen(context), "");
        case LE_OP:
//            if (lhs->isConstant && rhs->isConstant && context.optimization_phase) {
//                isConstant = true;
//
//                if (lhs->const_value <= rhs->const_value) {
//                    const_value = 1;
//                    return ConstantInt::get(Type::getInt1Ty(llvmContext), 1, true);
//                } else {
//                    const_value = 0;
//                    return ConstantInt::get(Type::getInt1Ty(llvmContext), 0, true);
//
//                }
//            }
            return builder.CreateICmpSLE(lhs->codeGen(context), rhs->codeGen(context), "");
        case GE_OP:
            return builder.CreateICmpSGE(lhs->codeGen(context), rhs->codeGen(context), "");
        case '>':
            return builder.CreateICmpSGT(lhs->codeGen(context), rhs->codeGen(context), "");
        case '<':
            return builder.CreateICmpSLT(lhs->codeGen(context), rhs->codeGen(context), "");
        default:
            cerr << "BINARY OPERATOR NOT SUPPORTED" << endl;
    }
    math:
    if (debug)
        cout << "Creating instruction: " << op << endl;
//    if (lhs->isConstant && rhs->isConstant && context.optimization_phase) {
//        int val;
//        switch (op) {
//            case '+':
//                val = lhs->const_value + rhs->const_value;
//                break;
//            case '-':
//                val = lhs->const_value - rhs->const_value;
//                break;
//            case '*':
//                val = lhs->const_value * rhs->const_value;
//                break;
//            default:
//                goto no_const;
//        }
//        isConstant = true;
//        const_value = val;
//        IntNode *intNode = new IntNode(val);
//        return intNode->codeGen(context);
//    }

    no_const:

    Value *ret = BinaryOperator::Create(instr, lhs->codeGen(context),
                                        rhs->codeGen(context), "", context.currentBlock());
        cout << "Inst Created" << endl;
    return ret;
}

Value *FunctionDeclarationNode::codeGen(CodeGenContext &context) {
    cout << "Function Declaration" << endl;
    if (debug) {
        cout << "==Name: " << id.name << endl;
        cout << "==Type: " << storageType->type->name << endl;
        cout << "==isPtr: " << isPtr << endl;
    }
    vector < Type * > argTypes;
    VariableList::const_iterator it;
    for (it = arguments.begin(); it != arguments.end(); it++) {
        argTypes.push_back(typeOf(*(**it).storageType->type, (**it).isPtr));
    }
    FunctionType *ftype = FunctionType::get(typeOf(*(storageType->type), isPtr),
                                            makeArrayRef(argTypes), hasEllipsis);
    GlobalValue::LinkageTypes lt;
    if (storageType->storage)
        lt = GlobalValue::ExternalLinkage;
    else
        lt = GlobalValue::InternalLinkage;
    Function *function = Function::Create(ftype, lt, id.name.c_str(), context.module);
    function->setCallingConv(llvm::CallingConv::C);
    return function;
}

Value *FunctionDefinitionNode::codeGen(CodeGenContext &context) {
    cout << "Function Definition" << endl;
    if (debug) {
        cout << "Name: " << id.name << endl;
        cout << "Type: " << storageType->type->name << endl;
    }
    VariableList::const_iterator it;
    Function *function = context.module->getFunction(id.name.c_str());
    if (function == NULL) {
        vector < Type * > argTypes;

        for (it = arguments.begin(); it != arguments.end(); it++) {
            argTypes.push_back(typeOf(*(**it).storageType->type, (**it).isPtr));
        }
        FunctionType *ftype = FunctionType::get(typeOf(*(storageType->type), isPtr),
                                                makeArrayRef(argTypes), hasEllipsis);
        function = Function::Create(ftype,
                                    GlobalValue::InternalLinkage,
                                    id.name.c_str(), context.module);
    }


    BasicBlock *bblock = BasicBlock::Create(llvmContext, "entry", function, 0);
    context.pushBlock(bblock);

    Function::arg_iterator argsValues = function->arg_begin();
    Value *argumentValue;

    for (it = arguments.begin(); it != arguments.end(); it++) {
        (**it).codeGen(context);
        argumentValue = &*argsValues++;
        argumentValue->setName((*it)->id->name.c_str());
        StoreInst *inst = new StoreInst(argumentValue, context.locals()[(*it)->id->name],
                                        false, bblock);

    }
    block.codeGen(context);
    ReturnInst::Create(llvmContext, context.getCurrentReturnValue(), context.currentBlock());
    context.popBlock();

//    verifyFunction(*function);

    return function;
}

Value *ReturnStatementNode::codeGen(CodeGenContext &context) {
    std::cout << "Generating RETURN code " << endl;
    if (expression != NULL) {
        Value *returnValue = expression->codeGen(context);
        context.setCurrentReturnValue(returnValue);
        return returnValue;
    } else
        return NULL;

}




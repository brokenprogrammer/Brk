#include "expression.hpp"

llvm::Value* IdentifierExpression::codegen() {
    return nullptr;
}

llvm::Value* IntegerExpression::codegen() {
    switch(this->m_type) {
        case TOKEN_UINT32:
            return llvm::ConstantInt::get(TheContext, llvm::APInt(32, this->m_value, false));
        case TOKEN_INT32:
            return llvm::ConstantInt::get(TheContext, llvm::APInt(32, this->m_value, true));
        case TOKEN_UINT64:
            return llvm::ConstantInt::get(TheContext, llvm::APInt(64, this->m_value, false));
        case TOKEN_INT64:
            return llvm::ConstantInt::get(TheContext, llvm::APInt(64, this->m_value, true));
        default:
            return nullptr; //TODO: Error logging or something similar? Oskar Mendel 2018-04-10
    }
}

llvm::Value* FloatingExpression::codegen() {
    if (this->m_isFloat) {
        return llvm::ConstantFP::get(TheContext, llvm::APFloat(this->m_value.m_float));
    } else {
        return llvm::ConstantFP::get(TheContext, llvm::APFloat(this->m_value.m_double));
    }
}

llvm::Value* StringExpression::codegen() {
    return nullptr;
}

llvm::Value* PostIncrementExpression::codegen() {
    return nullptr;
}

llvm::Value* PostDecrementExpression::codegen() {
    return nullptr;
}

llvm::Value* CallExpression::codegen() {
    return nullptr;
}

llvm::Value* ArrayExpression::codegen() {
    return nullptr;
}

llvm::Value* NotExpression::codegen() {
    return nullptr;
}

llvm::Value* ComplementExpression::codegen() {
    return nullptr;
}

llvm::Value* NegativeExpression::codegen() {
    llvm::Value* value = this->e->codegen();
    llvm::Value* negativeOne;

    if (!value) {
        return nullptr;
    }

    if (value->getType()->isFloatTy() || value->getType()->isDoubleTy()) {
        negativeOne = llvm::ConstantFP::get(TheContext, llvm::APFloat(-1.0));
        return Builder.CreateFMul(value, negativeOne);
    } else if (value->getType()->isIntegerTy()) {
        negativeOne = llvm::ConstantInt::get(TheContext, llvm::APInt(32, -1, true));
        return Builder.CreateMul(value, negativeOne);
    }

    return nullptr;
}

llvm::Value* PointerExpression::codegen() {
    return nullptr;
}

llvm::Value* AddressExpression::codegen() {
    return nullptr;
}

llvm::Value* CastExpression::codegen() {
    return nullptr;
}

llvm::Value* MultExpression::codegen() {
    llvm::Value* L = this->LHS->codegen();
    llvm::Value* R = this->RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
        return Builder.CreateFMul(L, R);
    } else {
        return Builder.CreateMul(L, R);
    }
}

llvm::Value* DivideExpression::codegen() {
    llvm::Value* L = this->LHS->codegen();
    llvm::Value* R = this->RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
        return Builder.CreateFDiv(L, R);
    } else {
        return Builder.CreateUDiv(L, R);
    }
}

llvm::Value* ModExpression::codegen() {
    llvm::Value* L = this->LHS->codegen();
    llvm::Value* R = this->RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
        return Builder.CreateFRem(L, R);
    } else {
        return Builder.CreateURem(L, R);
    }
}

llvm::Value* AddExpression::codegen() {
    llvm::Value* L = this->LHS->codegen();
    llvm::Value* R = this->RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
        return Builder.CreateFAdd(L, R);
    } else {
        return Builder.CreateAdd(L, R);
    }
}

llvm::Value* SubExpression::codegen() {
    llvm::Value* L = this->LHS->codegen();
    llvm::Value* R = this->RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
        return Builder.CreateFSub(L, R);
    } else {
        return Builder.CreateSub(L, R);
    }
}

llvm::Value* ShrExpression::codegen() {
    llvm::Value* L = this->LHS->codegen();
    llvm::Value* R = this->RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    //TODO: Create support for logical right shift and left shift. (>>>) in java. Oskar Mendel 2018-03-30
    if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
        //TODO: Error or not supported? Oskar Mendel 2018-04-10
        return nullptr;
    } else {
        return Builder.CreateAShr(L, R);
    }
}

llvm::Value* ShlExpression::codegen() {
    llvm::Value* L = this->LHS->codegen();
    llvm::Value* R = this->RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
        //TODO: Error or not supported? Oskar Mendel 2018-04-10
        return nullptr;
    } else {
        return Builder.CreateShl(L, R);
    }
}

llvm::Value* EqualityExpression::codegen() {
    llvm::Value* L = this->LHS->codegen();
    llvm::Value* R = this->RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    //TODO: If one of L & R is floating and other is integer the R have to be converted to same as the L. Oskar Mendel 2018-04-10

    switch(this->m_type) {
        case TOKEN_ISEQUAL:
            if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
                return Builder.CreateFCmpUEQ(L, R);
            } else {
                return Builder.CreateICmpEQ(L, R);
            }
            break;
        case TOKEN_NOTEQUAL:
            if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
                return Builder.CreateFCmpUNE(L, R);
            } else {
                return Builder.CreateICmpNE(L, R);
            }
            break;
        case TOKEN_LOWERTHAN:
            if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
                return Builder.CreateFCmpULT(L, R);
            } else {
                return Builder.CreateICmpULT(L, R);
            }
        case TOKEN_GREATERTHAN:
            if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
                return Builder.CreateFCmpUGT(L, R);
            } else {
                return Builder.CreateICmpUGT(L, R);
            }
            break;
        case TOKEN_LOWEROREQUALS:
            if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
                return Builder.CreateFCmpULE(L, R);
            } else {
                return Builder.CreateICmpULE(L, R);
            }
            break;
        case TOKEN_GREATEROREQUALS:
            if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
                return Builder.CreateFCmpUGE(L, R);
            } else {
                return Builder.CreateICmpUGE(L, R);
            }
            break;
        default:
            //TODO: Error or not supported? Oskar Mendel 2018-04-10
            break;
    }

    return nullptr;
}

llvm::Value* AndExpression::codegen() {
    llvm::Value* L = this->LHS->codegen();
    llvm::Value* R = this->RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
        //TODO: Error or not supported? Oskar Mendel 2018-04-10
        return nullptr;
    } else {
        return Builder.CreateAnd(L, R);
    }
}

llvm::Value* XorExpression::codegen() {
    llvm::Value* L = this->LHS->codegen();
    llvm::Value* R = this->RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
        //TODO: Error or not supported? Oskar Mendel 2018-04-10
        return nullptr;
    } else {
        return Builder.CreateXor(L, R);
    }
}

llvm::Value* OrExpression::codegen() {
    llvm::Value* L = this->LHS->codegen();
    llvm::Value* R = this->RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
        //TODO: Error or not supported? Oskar Mendel 2018-04-10
        return nullptr;
    } else {
        return Builder.CreateOr(L, R);
    }
}

llvm::Value* LogicalAndExpression::codegen() {
    llvm::Value* L = this->LHS->codegen();
    llvm::Value* R = this->RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    if (!L->getType()->isFloatingPointTy()) {
        //TODO: Convert L to floating. Oskar Mendel 2018-04-10
    }

    if (!R->getType()->isFloatingPointTy()) {
        //TODO: Convert L to floating. Oskar Mendel 2018-04-10
    }

    L = Builder.CreateFCmpONE(L, llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0)));
    if (!llvm::dyn_cast<llvm::ConstantInt>(L)->getValue().getBoolValue()) {
        return L;
    }
    
    R = Builder.CreateFCmpONE(R, llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0)));
    return R;
}

llvm::Value* LogicalOrExpression::codegen() {
    llvm::Value* L = this->LHS->codegen();
    llvm::Value* R = this->RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    if (!L->getType()->isFloatingPointTy()) {
        //TODO: Convert L to floating. Oskar Mendel 2018-04-10
    }

    L = Builder.CreateFCmpONE(L, llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0)));
    if (llvm::dyn_cast<llvm::ConstantInt>(L)->getValue().getBoolValue()) {
        return L;
    } else {

        if (!R->getType()->isFloatingPointTy()) {
            //TODO: Convert L to floating. Oskar Mendel 2018-04-10
        }

        R = Builder.CreateFCmpONE(R, llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0)));
        return R;
    }
}

llvm::Value* ConditionalExpression::codegen() {
    llvm::Value* Cond = this->m_cond->codegen();

    if (!Cond) {
        return nullptr;
    }

    if (!Cond->getType()->isFloatingPointTy()) {
        //TODO: Convert L to floating. Oskar Mendel 2018-04-10
    }

    Cond = Builder.CreateFCmpONE(Cond, llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0)));
    if (llvm::dyn_cast<llvm::ConstantInt>(Cond)->getValue().getBoolValue()) {
        llvm::Value* L = this->LHS->codegen();

        if (!L) {
            return nullptr;
        }

        return L;
    } else {
        llvm::Value* R = this->RHS->codegen();

        if (!R) {
            return nullptr;
        }

        return R;
    }
}

llvm::Value* AssignExpression::codegen() {
    return nullptr;
}

llvm::Value* AddAssignExpression::codegen() {
    return nullptr;
}

llvm::Value* SubAssignExpression::codegen() {
    return nullptr;
}

llvm::Value* MulAssignExpression::codegen() {
    return nullptr;
}

llvm::Value* DivAssignExpression::codegen() {
    return nullptr;
}

llvm::Value* ModAssignExpression::codegen() {
    return nullptr;
}

llvm::Value* AndAssignExpression::codegen() {
    return nullptr;
}

llvm::Value* OrAssignExpression::codegen() {
    return nullptr;
}

llvm::Value* XorAssignExpression::codegen() {
    return nullptr;
}

llvm::Value* ShlAssignExpression::codegen() {
    return nullptr;
}

llvm::Value* ShrAssignExpression::codegen() {
    return nullptr;
}

llvm::Value* CommaExpression::codegen() {
    return nullptr;
}
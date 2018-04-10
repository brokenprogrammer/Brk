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
    return nullptr;
}

llvm::Value* XorExpression::codegen() {
    return nullptr;
}

llvm::Value* OrExpression::codegen() {
    return nullptr;
}

llvm::Value* LogicalAndExpression::codegen() {
    return nullptr;
}

llvm::Value* LogicalOrExpression::codegen() {
    return nullptr;
}

llvm::Value* ConditionalExpression::codegen() {
    return nullptr;
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
#include "expression.hpp"

llvm::Value* IdentifierExpression::codegen() {
    return nullptr;
}

llvm::Value* IntegerExpression::codegen() {
    //TODO: Add support for different bit sizes for ints when types are implemented.
        // Oskar Mendel 2018-03-30
     return llvm::ConstantInt::get(TheContext, llvm::APInt(64, this->m_value, true));
}

llvm::Value* FloatingExpression::codegen() {
    return llvm::ConstantFP::get(TheContext, llvm::APFloat(this->m_value));;
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
    return nullptr;
}

llvm::Value* DivideExpression::codegen() {
    return nullptr;
}

llvm::Value* ModExpression::codegen() {
    return nullptr;
}

llvm::Value* AddExpression::codegen() {
    return nullptr;
}

llvm::Value* SubExpression::codegen() {
    return nullptr;
}

llvm::Value* ShrExpression::codegen() {
    return nullptr;
}

llvm::Value* ShlExpression::codegen() {
    return nullptr;
}

llvm::Value* EqualityExpression::codegen() {
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
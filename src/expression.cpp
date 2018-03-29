#include "expression.hpp"

llvm::Value* IntegerExpression::codegen() {
     return llvm::ConstantFP::get(TheContext, llvm::APFloat(this->m_value));
}
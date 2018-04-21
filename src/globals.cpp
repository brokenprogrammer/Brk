#include "globals.hpp"

// LLVM core data structures
llvm::LLVMContext TheContext;

// Object to help generate LLVM instructions
llvm::IRBuilder<> Builder(TheContext);

// LLVM construct that contains functions and global variables
std::unique_ptr<llvm::Module> TheModule;

// This map to track of which values are defined in the current scope
std::map<std::string, llvm::Value *> NamedValues;
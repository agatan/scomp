#ifndef SCOMP_CODEGEN_CONTEXT_HPP_
#define SCOMP_CODEGEN_CONTEXT_HPP_

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

namespace scomp {
  namespace codegen {

    struct context final {
      llvm::IRBuilder<> builder;
      llvm::LLVMContext& llvm_context;

      context(llvm::LLVMContext& ctx): builder(ctx), llvm_context(ctx) {}
    };

  } // namespace codegen
} // namespace scomp

#endif

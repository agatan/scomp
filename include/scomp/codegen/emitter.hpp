#ifndef SCOMP_CODEGEN_EMITTER_HPP_
#define SCOMP_CODEGEN_EMITTER_HPP_

#include <unordered_map>

#include <scomp/ast/ast.hpp>
#include <scomp/ast/module.hpp>
#include <scomp/codegen/context.hpp>

namespace scomp {
  namespace codegen {

    std::unique_ptr<llvm::Module> emit_llvm_ir(ast::module const&, context&);

  } // namespace codegen
} // namespace scomp

#endif

#include <scomp/codegen/type_emitter.hpp>

#include <scomp/internal_error.hpp>

namespace scomp {
  namespace codegen {

    llvm::Type* type_emitter::emit(semantics::builtin_type const& t) {
      if (t->name() == "int") {
        return llvm::Type::getInt64Ty(ctx.llvm_context);
      } else if (t->name() == "bool") {
        return llvm::Type::getInt1Ty(ctx.llvm_context);
      } else if (t->name() == "void") {
        // TODO: void type representation...
        return llvm::Type::getInt1Ty(ctx.llvm_context);
      }
      SCOMP_INTERNAL_ERROR();
      return nullptr;
    }

  } // namespace codegen
} // namespace scomp

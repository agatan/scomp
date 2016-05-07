#ifndef SCOMP_CODEGEN_TYPE_EMITTER_HPP_
#define SCOMP_CODEGEN_TYPE_EMITTER_HPP_

#include <scomp/internal_error.hpp>
#include <scomp/codegen/context.hpp>
#include <scomp/semantics/type.hpp>

namespace scomp {
  namespace codegen {

    struct type_emitter {
      explicit type_emitter(context& ctx) : ctx(ctx) {}

      llvm::Type* emit(semantics::type const& ty) {
        return boost::apply_visitor([this](auto&& t) { return this->emit(t); },
                                    ty);
      }

      llvm::Type* emit(semantics::dummy_type const&) {
        SCOMP_INTERNAL_ERROR();
      }
      llvm::Type* emit(semantics::builtin_type const&);

    private:
      context& ctx;
    };

  } // namespace codegen
} // namespace scomp

#endif

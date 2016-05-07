#include <scomp/semantics/analyze.hpp>
#include <scomp/semantics/forward_collector.hpp>
#include <scomp/semantics/type_check.hpp>

namespace scomp {
  namespace semantics {

    scope_ptr analyze(ast::module const& module) {
      auto global_scope = std::make_shared<scomp::semantics::scope>();
      forward_collect(module, global_scope);
      type_check(module, module.filename(), global_scope);
      return global_scope;
    }

  } // namespace semantics
} // namespace scomp

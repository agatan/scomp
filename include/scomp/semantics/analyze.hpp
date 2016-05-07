#ifndef SCOMP_SEMANTICS_ANALYZE_HPP_
#define SCOMP_SEMANTICS_ANALYZE_HPP_

#include <scomp/ast/module.hpp>
#include <scomp/semantics/scope.hpp>

namespace scomp {
  namespace semantics {
    scope_ptr analyze(ast::module const&);
  } // namespace semantics
} // namespace scomp

#endif

#ifndef SCOMP_SEMANTICS_FORWARD_COLLECTOR_HPP_
#define SCOMP_SEMANTICS_FORWARD_COLLECTOR_HPP_

#include <scomp/ast/module.hpp>
#include <scomp/semantics/scope.hpp>

namespace scomp {
  namespace semantics {

    void forward_collect(ast::module const&, scope_ptr const&);

  } // namespace semantics
} // namespace scomp

#endif

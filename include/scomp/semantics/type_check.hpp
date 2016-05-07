#ifndef SCOMP_SEMANTICS_TYPE_CHECK_HPP_
#define SCOMP_SEMANTICS_TYPE_CHECK_HPP_

#include <scomp/ast/module.hpp>
#include <scomp/semantics/scope.hpp>

namespace scomp {
  namespace semantics {

    void type_check(ast::module&, scope_ptr const&);

  } // namespace semantics
} // namespace scomp

#endif

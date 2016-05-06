#ifndef SCOMP_SEMANTICS_TRANSLATE_TYPE_HPP_
#define SCOMP_SEMANTICS_TRANSLATE_TYPE_HPP_

#include <boost/optional.hpp>

#include <scomp/ast/ast_fwd.hpp>
#include <scomp/semantics/type_fwd.hpp>
#include <scomp/semantics/scope.hpp>

namespace scomp {
  namespace semantics {
    boost::optional<semantics::type> translate_type(ast::type const&,
                                                    scope_ptr const&);
  } // namespace semantics
} // namespace scomp

#endif

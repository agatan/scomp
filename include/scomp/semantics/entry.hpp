#ifndef SCOMP_SEMANTICS_ENTRY_HPP_
#define SCOMP_SEMANTICS_ENTRY_HPP_

#include <string>
#include <vector>

#include <boost/variant.hpp>

#include <scomp/semantics/type.hpp>
#include <scomp/semantics/entry_fwd.hpp>
#include <scomp/semantics/scope.hpp>

namespace scomp {
  namespace semantics {

    namespace entry_node {
      struct var_entry {
        std::string name;
        semantics::type type;

        var_entry() = default;
        var_entry(std::string name, semantics::type const& t)
            : name(std::move(name)), type(t) {}
        var_entry(std::string name, semantics::type&& t)
            : name(std::move(name)), type(std::move(t)) {}
      };

      struct fun_entry {
        std::string name;
        using param_type = std::pair<std::string, semantics::type>;
        std::vector<param_type> params;
        semantics::type return_type;
        scope fun_scope;
      };
    } // namespace entry_node

  } // namespace semantics
} // namespace scomp

#endif

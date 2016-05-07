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
        scope_ptr fun_scope;


        fun_entry() = default;
        fun_entry(std::string name, std::vector<param_type> const& params,
                  semantics::type const& return_type,
                  enclosing_scope_ptr&& enclosing)
            : name(std::move(name)),
              params(params),
              return_type(return_type),
              fun_scope(std::make_shared<scope>(std::move(enclosing))) {
          for (auto&& param : this->params) {
            fun_scope->define_symbol(
                param.first,
                std::make_shared<var_entry>(param.first, param.second));
          }
        }
        fun_entry(std::string name, std::vector<param_type>&& params,
                  semantics::type&& return_type,
                  enclosing_scope_ptr&& enclosing)
            : name(std::move(name)),
              params(std::move(params)),
              return_type(std::move(return_type)),
              fun_scope(std::make_shared<scope>(std::move(enclosing))) {
          for (auto&& param : this->params) {
            fun_scope->define_symbol(param.first,
                                     std::make_shared<var_entry>(
                                         param.first, std::move(param.second)));
          }
        }
      };
    } // namespace entry_node

  } // namespace semantics
} // namespace scomp

#endif

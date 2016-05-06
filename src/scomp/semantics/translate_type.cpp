#include <scomp/semantics/translate_type.hpp>

#include <scomp/ast/type.hpp>
#include <scomp/semantics/type.hpp>

namespace scomp {
  namespace semantics {
    namespace detail {

      struct trans_type_visitor
          : boost::static_visitor<boost::optional<semantics::type>> {

        explicit trans_type_visitor(scope_ptr const& scope) : scope(scope) {}

        result_type operator()(ast::primary_type const& t) const {
          auto builtin = get_builtin_type(t->name);
          if (builtin) {
            return builtin;
          }
          return boost::none;
        }

      private:
        scope_ptr const& scope;
      };

    } // namespace detail

    boost::optional<semantics::type> translate_type(ast::type const& ast_type,
                                                    scope_ptr const& scope) {
      return boost::apply_visitor(detail::trans_type_visitor{scope}, ast_type);
    }

  } // namespace semantics
} // namespace scomp

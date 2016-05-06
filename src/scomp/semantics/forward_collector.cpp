#include <scomp/semantics/forward_collector.hpp>

#include <scomp/internal_error.hpp>
#include <scomp/ast/ast.hpp>

namespace scomp {
  namespace semantics {

    struct forward_collect_visitor {
      explicit forward_collect_visitor(scope_ptr const& s) : scope(s) {}

      void operator()(ast::val_def const& valdef) const {
      }

      void operator()(ast::fun_def const& fundef) const {

      }

    private:
      scope_ptr const& scope;
    };

    void forward_collect(ast::module const& mod, scope_ptr const& scope) {
      for (auto&& d: mod.defs()) {
        boost::apply_visitor(forward_collect_visitor{scope}, d);
      }
    }

  } // namespace semantics
} // namespace scomp

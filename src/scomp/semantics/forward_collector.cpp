#include <scomp/semantics/forward_collector.hpp>

#include <scomp/internal_error.hpp>
#include <scomp/ast/ast.hpp>
#include <scomp/semantics/error.hpp>
#include <scomp/semantics/entry.hpp>
#include <scomp/semantics/translate_type.hpp>

namespace scomp {
  namespace semantics {

    struct forward_collect_visitor {
      explicit forward_collect_visitor(scope_ptr const& s,
                                       std::string const& file)
          : scope(s), filename(file) {}

      void operator()(ast::val_def const& valdef) const {
        auto typ = translate_type(valdef->typ, scope);
        if (typ) {
          scope->define_symbol(valdef->name,
                               std::make_shared<entry_node::var_entry>(
                                   valdef->name, std::move(*typ)));
          return;
        }
        throw error(filename, ast::position(valdef->typ), "No such type");
      }

      void operator()(ast::fun_def const& fundef) const {
        type return_type = builtin_void();
        if (fundef->return_type) {
          if (auto typ = translate_type(*fundef->return_type, scope)) {
            return_type = *typ;
          } else {
            throw error(filename, ast::position(*fundef->return_type), "No such type");
          }
        }
        std::vector<std::pair<std::string, type>> params;
        for (auto&& param : fundef->params) {
          if (auto typ = translate_type(param.second, scope)) {
            params.emplace_back(param.first, *typ);
          } else {
            throw error(filename, ast::position(param.second), "No such type");
          }
        }
        fun_entry entry = std::make_shared<entry_node::fun_entry>(
            fundef->name, std::move(params), std::move(return_type), scope);
        scope->define_symbol(fundef->name, std::move(entry));
      }

    private:
      scope_ptr const& scope;
      std::string const& filename;
    };

    void forward_collect(ast::module const& mod, scope_ptr const& scope) {
      for (auto&& d: mod.defs()) {
        boost::apply_visitor(forward_collect_visitor(scope, mod.name()), d);
      }
    }

  } // namespace semantics
} // namespace scomp

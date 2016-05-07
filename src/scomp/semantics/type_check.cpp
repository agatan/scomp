#include <scomp/semantics/type_check.hpp>

#include <algorithm>
#include <numeric>
#include <functional>

#include <boost/format.hpp>
#include <boost/range/combine.hpp>

#include <scomp/helper/get.hpp>
#include <scomp/internal_error.hpp>
#include <scomp/ast/ast.hpp>
#include <scomp/semantics/type.hpp>
#include <scomp/semantics/entry.hpp>
#include <scomp/semantics/error.hpp>

namespace scomp {
  namespace semantics {

    void check_statement(ast::statement const&, std::string const&,
                         scope_ptr const&);
    void check_expression(ast::expression const&, std::string const&,
                         scope_ptr const&);
    void check_definition(ast::definition const&, std::string const&,
                         scope_ptr const&);


    struct expr_type_checker : boost::static_visitor<type> {
      explicit expr_type_checker(std::string const& filename,
                                 scope_ptr const& scope)
          : filename(filename), scope(scope) {}

      type operator()(ast::literal_expr const& lit) const {
        struct literal_type_visitor {
          type operator()(int) const {
            return builtin_int();
          }
          type operator()(bool) const {
            return builtin_bool();
          }
        };

        auto ty = boost::apply_visitor(literal_type_visitor{}, lit->value);
        lit->type(ty);
        return ty;
      }

      type operator()(ast::binop_expr const& binop) const {
        SCOMP_INTERNAL_ERROR_MSG("binop_expr is not implemented yet.");
      }

      type operator()(ast::parens_expr const& parens) const {
        auto ty = boost::apply_visitor(*this, parens->expr);
        parens->type(ty);
        return ty;
      }

      type operator()(ast::apply_expr const& app) const {
        auto callee_opt = helper::get<ast::var_expr>(app->callee);
        if (!callee_opt) {
          SCOMP_INTERNAL_ERROR_MSG("functional object is not supported yet...");
        }
        auto callee = *callee_opt;
        auto function_opt = scope->find(callee->name);
        if (!function_opt || !helper::get<fun_entry>(*function_opt)) {
          throw error(filename, ast::position(callee),
                      "No such function: " + callee->name);
        }
        auto funentry = helper::get<fun_entry>(*function_opt, helper::no_option);

        // argument type construction...
        std::vector<type> args_type;
        for (auto const& arg: app->args) {
          args_type.emplace_back(boost::apply_visitor(*this, arg));
        }

        // argument number check...
        if (funentry->params.size() != args_type.size()) {
          throw error(
              filename, ast::position(app),
              (boost::format(
                   "Illegal number of arguments: expected %d, have %d") %
               funentry->params.size() % args_type.size())
                  .str());
        }

        // argument type check...
        for (decltype(args_type)::size_type i = 0; i < funentry->params.size();
             ++i) {
          if (!match(args_type[i], funentry->params[i].second)) {
            throw error(filename, ast::position(app->args[i]), "Type mismatch");
          }
        }

        // return type registration
        app->type(funentry->return_type);
        return funentry->return_type;
      }

      type operator()(ast::block_expr const& blk) const {
        if (blk->body.empty()) {
          blk->type(builtin_void());
          return builtin_void();
        }
        for (auto&& stmt: blk->body) {
          check_statement(stmt, filename, scope);
        }
        auto last_elem = helper::get<ast::expr_stmt>(blk->body.back());
        if (last_elem) {
          auto last_type = boost::apply_visitor(
              [](auto&& e) { return e->type(); }, (*last_elem)->expr);
          blk->type(last_type);
          return last_type;
        } else {
          blk->type(builtin_void());
          return blk->type();
        }
      }

      template <typename T>
      type operator()(T) const {
        SCOMP_INTERNAL_ERROR();
      }

    private:
      std::string const& filename;
      scope_ptr const& scope;
    };

  } // namespace semantics
} // namespace scomp

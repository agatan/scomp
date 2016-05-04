#ifndef SCOMP_AST_EXPRESSION_HPP_
#define SCOMP_AST_EXPRESSION_HPP_

#include <scomp/ast/ast_fwd.hpp>

#include <memory>
#include <vector>
#include <sstream>
#include <string>

#include <boost/variant.hpp>

#include <scomp/ast/node_base.hpp>
#include <scomp/ast/stringize.hpp>

namespace scomp {
  namespace ast {
    namespace node {

      struct literal_expr : node_base {
        using value_type = boost::variant<int, bool>;
        value_type value;

        explicit literal_expr(value_type&& v)
            : node_base(), value(std::move(v)) {}
        literal_expr(pos_type const& p, value_type&& v)
            : node_base(p), value(std::move(v)) {}

        std::string to_string() const;
      };

      struct var_expr : node_base {
        std::string name;

        explicit var_expr(std::string name)
            : node_base(), name(std::move(name)) {}
        var_expr(pos_type const& p, std::string name)
            : node_base(p), name(std::move(name)) {}

        std::string to_string() const {
          return name;
        }
      };

      struct binop_expr : node_base {
        std::string op;
        expression lhs;
        expression rhs;

        binop_expr() = default;

        binop_expr(pos_type const& p, std::string op, expression&& lhs,
                   expression&& rhs)
            : node_base(p),
              op(std::move(op)),
              lhs(std::move(lhs)),
              rhs(std::move(rhs)) {}

        binop_expr(pos_type const& p, std::string op, expression const& lhs,
                   expression const& rhs)
            : node_base(p), op(std::move(op)), lhs(lhs), rhs(rhs) {}

        std::string to_string() const;
      };

      struct parens_expr : node_base {
        expression expr;

        parens_expr(pos_type const& p, expression&& expr)
            : node_base(p), expr(std::move(expr)) {}
        parens_expr(pos_type const& p, expression const& expr)
            : node_base(p), expr(expr) {}

        std::string to_string() const {
          return "(" + stringize(expr) + ")";
        }
      };

      struct apply_expr : node_base {
        expression callee;
        std::vector<expression> args;

        apply_expr(pos_type const& p, expression&& f,
                   std::vector<expression>&& a)
            : node_base(p), callee(std::move(f)), args(std::move(a)) {}
        apply_expr(pos_type const& p, expression const& f,
                   std::vector<expression> const& a)
            : node_base(p), callee(f), args(a) {}

        std::string to_string() const;
      };

      struct block_expr :node_base {
        std::vector<statement> body;

        block_expr(pos_type const& p, std::vector<statement>&& b)
            : node_base(p), body(std::move(b)) {}
        block_expr(pos_type const& p, std::vector<statement> const& b)
            : node_base(p), body(b) {}

        std::string to_string() const;
      };

    } // namespace node
  } // namespace ast
} // namespace scomp

#endif

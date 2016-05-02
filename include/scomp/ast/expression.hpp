#ifndef SCOMP_AST_EXPRESSION_HPP_
#define SCOMP_AST_EXPRESSION_HPP_

#include <scomp/ast/ast_fwd.hpp>

#include <memory>
#include <vector>
#include <sstream>
#include <string>

#include <boost/variant.hpp>

#include <scomp/ast/stringize.hpp>

namespace scomp {
  namespace ast {
    namespace node {

      struct literal_expr {
        using value_type = boost::variant<int, bool>;
        value_type value;

        explicit literal_expr(value_type&& v) : value(std::move(v)) {}

        std::string to_string() const;
      };

      struct var_expr {
        std::string name;

        explicit var_expr(std::string name) : name(std::move(name)) {}

        std::string to_string() const {
          return name;
        }
      };

      struct binop_expr {
        std::string op;
        expression lhs;
        expression rhs;

        binop_expr(std::string op, expression&& lhs, expression&& rhs)
            : op(std::move(op)), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

        binop_expr(std::string op, expression const& lhs, expression const& rhs)
            : op(std::move(op)), lhs(lhs), rhs(rhs) {}

        std::string to_string() const;
      };

      struct parens_expr {
        expression expr;

        explicit parens_expr(expression&& expr) : expr(std::move(expr)) {}
        explicit parens_expr(expression const& expr) : expr(expr) {}

        std::string to_string() const {
          return "(" + stringize(expr) + ")";
        }
      };

      struct apply_expr {
        expression function;
        std::vector<expression> args;

        apply_expr(expression&& f, std::vector<expression>&& a)
            : function(std::move(f)), args(std::move(a)) {}
        apply_expr(expression const& f, std::vector<expression> const& a)
            : function(f), args(a) {}

        std::string to_string() const;
      };

      struct block_expr {
        std::vector<statement> body;

        explicit block_expr(std::vector<statement>&& b) : body(std::move(b)) {}
        explicit block_expr(std::vector<statement> const& b) : body(b) {}

        std::string to_string() const;
      };

    } // namespace node
  } // namespace ast
} // namespace scomp

#endif

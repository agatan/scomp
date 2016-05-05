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
#include <scomp/semantics/type.hpp>

namespace scomp {
  namespace ast {
    namespace node {

      struct expr_base : node_base {
        expr_base() = default;
        explicit expr_base(pos_type const& p) : node_base(p) {}

        semantics::type const& type() const & {
          return type_;
        }
        semantics::type type() && {
          return std::move(type_);
        }
        void type(semantics::type const& t) {
          type_ = t;
        }
        void type(semantics::type&& t) {
          type_ = std::move(t);
        }
      private:
        semantics::type type_;
      };

      struct literal_expr : expr_base {
        using value_type = boost::variant<int, bool>;
        value_type value;

        explicit literal_expr(value_type&& v)
            : expr_base(), value(std::move(v)) {}
        literal_expr(pos_type const& p, value_type&& v)
            : expr_base(p), value(std::move(v)) {}

        std::string to_string() const;
      };

      struct var_expr : expr_base {
        std::string name;

        explicit var_expr(std::string name)
            : expr_base(), name(std::move(name)) {}
        var_expr(pos_type const& p, std::string name)
            : expr_base(p), name(std::move(name)) {}

        std::string to_string() const {
          return name;
        }
      };

      struct binop_expr : expr_base {
        std::string op;
        expression lhs;
        expression rhs;

        binop_expr() = default;

        binop_expr(pos_type const& p, std::string op, expression&& lhs,
                   expression&& rhs)
            : expr_base(p),
              op(std::move(op)),
              lhs(std::move(lhs)),
              rhs(std::move(rhs)) {}

        binop_expr(pos_type const& p, std::string op, expression const& lhs,
                   expression const& rhs)
            : expr_base(p), op(std::move(op)), lhs(lhs), rhs(rhs) {}

        std::string to_string() const;
      };

      struct parens_expr : expr_base {
        expression expr;

        parens_expr(pos_type const& p, expression&& expr)
            : expr_base(p), expr(std::move(expr)) {}
        parens_expr(pos_type const& p, expression const& expr)
            : expr_base(p), expr(expr) {}

        std::string to_string() const {
          return "(" + stringize(expr) + ")";
        }
      };

      struct apply_expr : expr_base {
        expression callee;
        std::vector<expression> args;

        apply_expr(pos_type const& p, expression&& f,
                   std::vector<expression>&& a)
            : expr_base(p), callee(std::move(f)), args(std::move(a)) {}
        apply_expr(pos_type const& p, expression const& f,
                   std::vector<expression> const& a)
            : expr_base(p), callee(f), args(a) {}

        std::string to_string() const;
      };

      struct block_expr :expr_base {
        std::vector<statement> body;

        block_expr(pos_type const& p, std::vector<statement>&& b)
            : expr_base(p), body(std::move(b)) {}
        block_expr(pos_type const& p, std::vector<statement> const& b)
            : expr_base(p), body(b) {}

        std::string to_string() const;
      };

    } // namespace node
  } // namespace ast
} // namespace scomp

#endif

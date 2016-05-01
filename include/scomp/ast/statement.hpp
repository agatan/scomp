#ifndef SCOMP_AST_STATEMENT_HPP_
#define SCOMP_AST_STATEMENT_HPP_

#include <scomp/ast/ast_fwd.hpp>

#include <string>

#include <boost/optional.hpp>

#include <scomp/ast/stringize.hpp>

namespace scomp {
  namespace ast {
    namespace node {

      struct expr_stmt {
        expression expr;

        explicit expr_stmt() = default;
        explicit expr_stmt(expression&& e) : expr(std::move(e)) {}
        explicit expr_stmt(expression const& e) : expr(e) {}

        std::string to_string() const {
          return stringize(expr);
        }
      };

      struct valdef_stmt {
        std::string name;
        boost::optional<type> typ;
        expression value;

        explicit valdef_stmt() = default;
        explicit valdef_stmt(std::string name, type&& t, expression&& v)
            : name(std::move(name)), typ(std::move(t)), value(std::move(v)) {}
        explicit valdef_stmt(std::string name, type const& t,
                             expression const& v)
            : name(std::move(name)), typ(t), value(v) {}

        explicit valdef_stmt(std::string name, expression&& v)
            : name(std::move(name)), typ(boost::none), value(std::move(v)) {}
        explicit valdef_stmt(std::string name, expression const& v)
            : name(std::move(name)), typ(boost::none), value(v) {}

        std::string to_string() const;
      };

      struct return_stmt {
        boost::optional<expression> expr = boost::none;

        explicit return_stmt() = default;
        explicit return_stmt(expression&& e) : expr(std::move(e)) {}
        explicit return_stmt(expression const& e) : expr(e) {}

        std::string to_string() const;
      };

    } // namespace node
  } // namespace ast
} // namespace scomp

#endif

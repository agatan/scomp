#ifndef SCOMP_AST_STATEMENT_HPP_
#define SCOMP_AST_STATEMENT_HPP_

#include <scomp/ast/ast_fwd.hpp>

#include <string>

#include <boost/optional.hpp>

#include <scomp/ast/node_base.hpp>
#include <scomp/ast/stringize.hpp>

namespace scomp {
  namespace ast {
    namespace node {

      struct expr_stmt : node_base {
        expression expr;

        expr_stmt() = default;
        explicit expr_stmt(pos_type const& p, expression&& e)
            : node_base(p), expr(std::move(e)) {}
        explicit expr_stmt(pos_type const& p, expression const& e)
            : node_base(p), expr(e) {}

        std::string to_string() const {
          return stringize(expr);
        }
      };

      struct valdef_stmt : node_base {
        std::string name;
        boost::optional<type> typ;
        expression value;

        explicit valdef_stmt() = default;
        explicit valdef_stmt(pos_type const& p, std::string name,
                             boost::optional<type>&& t, expression&& v)
            : node_base(p),
              name(std::move(name)),
              typ(std::move(t)),
              value(std::move(v)) {}
        explicit valdef_stmt(pos_type const& p, std::string name,
                             boost::optional<type> const& t,
                             expression const& v)
            : node_base(p), name(std::move(name)), typ(t), value(v) {}

        // explicit valdef_stmt(std::string name, type&& t, expression&& v)
        //     : name(std::move(name)), typ(std::move(t)), value(std::move(v)) {}
        // explicit valdef_stmt(std::string name, type const& t,
        //                      expression const& v)
        //     : name(std::move(name)), typ(t), value(v) {}
        //
        // explicit valdef_stmt(std::string name, expression&& v)
        //     : name(std::move(name)), typ(boost::none), value(std::move(v)) {}
        // explicit valdef_stmt(std::string name, expression const& v)
        //     : name(std::move(name)), typ(boost::none), value(v) {}

        std::string to_string() const;
      };

      struct return_stmt : node_base {
        boost::optional<expression> expr = boost::none;

        explicit return_stmt() = default;
        explicit return_stmt(pos_type const& p, expression&& e)
            : node_base(p), expr(std::move(e)) {}
        explicit return_stmt(pos_type const& p, expression const& e)
            : node_base(p), expr(e) {}

        std::string to_string() const;
      };

    } // namespace node
  } // namespace ast
} // namespace scomp

#endif

#ifndef SCOMP_AST_AST_FWD_HPP_
#define SCOMP_AST_AST_FWD_HPP_

#include <memory>

#include <boost/variant.hpp>

namespace scomp {
  namespace ast {
    namespace node {
      // expressions
      struct literal_expr;
      struct var_expr;
      struct binop_expr;
      struct parens_expr;
      struct apply_expr;
      struct block_expr;

      // statements
      struct expr_stmt;
      struct valdef_stmt;
      struct return_stmt;

      // definitions
      struct val_def;
      struct fun_def;

      // types
      struct primary_type;
    } // namespace node

    // expressions
    using literal_expr = std::shared_ptr<node::literal_expr>;
    using var_expr = std::shared_ptr<node::var_expr>;
    using binop_expr = std::shared_ptr<node::binop_expr>;
    using parens_expr = std::shared_ptr<node::parens_expr>;
    using apply_expr = std::shared_ptr<node::apply_expr>;
    using block_expr = std::shared_ptr<node::block_expr>;

    using expression =
        boost::variant<literal_expr, var_expr, binop_expr, parens_expr,
                       apply_expr, block_expr>;

    // statements
    using expr_stmt = std::shared_ptr<node::expr_stmt>;
    using valdef_stmt = std::shared_ptr<node::valdef_stmt>;
    using return_stmt = std::shared_ptr<node::return_stmt>;

    using statement = boost::variant<expr_stmt, valdef_stmt, return_stmt>;

    // definitions
    using val_def = std::shared_ptr<node::val_def>;
    using fun_def = std::shared_ptr<node::fun_def>;

    using definition = boost::variant<val_def, fun_def>;

    // types
    using primary_type = std::shared_ptr<node::primary_type>;

    using type = boost::variant<primary_type>;

  } // namespace ast
} // namespace scomp

#endif

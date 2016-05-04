#ifndef SCOMP_AST_AST_HPP_
#define SCOMP_AST_AST_HPP_

#include <scomp/ast/ast_fwd.hpp>
#include <scomp/ast/expression.hpp>
#include <scomp/ast/statement.hpp>
#include <scomp/ast/definition.hpp>
#include <scomp/ast/type.hpp>
#include <scomp/ast/module.hpp>

namespace scomp {
  namespace ast {

    template <typename T, typename... Args>
    expression make_expression(Args&&... args) {
      return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    statement make_statement(Args&&... args) {
      return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    definition make_definition(Args&&... args) {
      return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    type make_type(Args&&... args) {
      return std::make_shared<T>(std::forward<Args>(args)...);
    }

  } // namespace ast
} // namespace scomp

#endif

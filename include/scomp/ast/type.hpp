#ifndef SCOMP_AST_TYPE_HPP_
#define SCOMP_AST_TYPE_HPP_

#include <scomp/ast/ast_fwd.hpp>

#include <string>
#include <memory>

#include <scomp/ast/node_base.hpp>
#include <scomp/ast/stringize.hpp>

namespace scomp {
  namespace ast {
    namespace node {

      struct primary_type : node_base {
        std::string name;

        explicit primary_type() = default;
        explicit primary_type(pos_type const& p, std::string name)
            : node_base(p), name(std::move(name)) {}

        std::string to_string() const {
          return name;
        }
      };

    } // namespace node
  } // namespace ast
} // namespace scomp

#endif

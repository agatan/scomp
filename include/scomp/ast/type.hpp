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

      struct unknown_type : node_base {
        type *ref = nullptr;

        explicit unknown_type() = default;
        explicit unknown_type(pos_type const& p, type* r)
            : node_base(p), ref(r) {}

        std::string to_string() const {
          if (!ref) {
            return "unknown_type";
          }
          return "unknown_type(" + stringize(*ref) + ")";
        }
      };

    } // namespace node
  } // namespace ast
} // namespace scomp

#endif

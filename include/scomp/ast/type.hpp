#ifndef SCOMP_AST_TYPE_HPP_
#define SCOMP_AST_TYPE_HPP_

#include <scomp/ast/ast_fwd.hpp>

#include <string>
#include <memory>

#include <scomp/ast/stringize.hpp>

namespace scomp {
  namespace ast {
    namespace node {

      struct primary_type {
        std::string name;

        explicit primary_type() = default;
        explicit primary_type(std::string name) : name(std::move(name)) {}

        std::string to_string() const {
          return name;
        }
      };

      struct unknown_type {
        type *ref = nullptr;

        explicit unknown_type() = default;
        explicit unknown_type(type *r) : ref(r) {}

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

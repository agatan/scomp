#include <scomp/ast/expression.hpp>

#include <boost/format.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>

#include <scomp/ast/statement.hpp>

namespace scomp {
  namespace ast {
    namespace node {

      std::string literal_expr::to_string() const {
        struct visitor {
          std::string operator()(int i) const {
            return std::to_string(i);
          }

          std::string operator()(bool b) const {
            return b ? "true" : "false";
          }
        };
        return boost::apply_visitor(visitor{}, value);
      }

      std::string binop_expr::to_string() const {
        return (boost::format("%s %s %s") % stringize(lhs) % op % stringize(rhs)).str();
      }

      std::string apply_expr::to_string() const {
        return (boost::format("%s(%s)") % stringize(function) %
                boost::algorithm::join(
                    args | boost::adaptors::transformed(
                               [](auto const& e) { return stringize(e); }),
                    ", "))
            .str();
      }

      std::string block_expr::to_string() const {
        return (boost::format("{ %s }") %
                boost::algorithm::join(
                    body | boost::adaptors::transformed(
                               [](auto const& e) { return stringize(e); }),
                    "; "))
            .str();
      }

    } // namespace node
  } // namespace ast
} // namespace scomp

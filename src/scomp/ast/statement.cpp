#include <scomp/ast/statement.hpp>

#include <sstream>

#include <scomp/ast/expression.hpp>
#include <scomp/ast/type.hpp>

namespace scomp {
  namespace ast {
    namespace node {

      std::string valdef_stmt::to_string() const {
        std::stringstream ss;
        ss << "val " << name;
        if (typ) {
          ss << ": " << stringize(*typ);
        }
        ss << " = " << stringize(value);
        return ss.str();
      }

      std::string return_stmt::to_string() const {
        if (expr) {
          return "return " + stringize(*expr);
        }
        return "return";
      }

    } // namespace node
  } // namespace ast
} // namespace scomp

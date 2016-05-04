#include <scomp/ast/definition.hpp>

#include <sstream>

#include <boost/format.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>

#include <scomp/ast/expression.hpp>
#include <scomp/ast/type.hpp>

namespace scomp {
  namespace ast {
    namespace node {

      std::string val_def::to_string() const {
        std::stringstream ss;
        ss << "val " << name;
        ss << ": " << stringize(typ);
        ss << " = " << stringize(value);
        return ss.str();
      }

      std::string fun_def::to_string() const {
        return (boost::format("%s(%s)%s = %s") % name %
                boost::algorithm::join(
                    params | boost::adaptors::transformed([](auto const& p) {
                      return p.first + ": " + stringize(p.second);
                    }),
                    ", ") %
                (return_type ? ": " + stringize(*return_type) : "") %
                stringize(body))
            .str();
      }

    } // namespace node
  } // namespace ast
} // namespace scomp

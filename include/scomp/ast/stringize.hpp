#ifndef SCOMP_AST_STRINGIZE_HPP_
#define SCOMP_AST_STRINGIZE_HPP_

#include <string>

#include <boost/variant.hpp>

namespace scomp {
  namespace ast {

    template <typename... Args>
    std::string stringize(boost::variant<Args...> const& v) {
      return boost::apply_visitor([](auto const& p) { return p->to_string(); },
                                  v);
    }

    template <typename T>
    std::string stringize(T const& v) {
      return v->to_string();
    }

  } // namespace ast
} // namespace scomp

#endif

#ifndef SCOMP_SEMANTICS_TYPE_FWD_HPP_
#define SCOMP_SEMANTICS_TYPE_FWD_HPP_

#include <memory>

#include <boost/variant.hpp>

namespace scomp {
  namespace semantics {
    namespace type_node {
      struct builtin_type;
    } // namespace type_node

    using builtin_type = std::shared_ptr<type_node::builtin_type>;

    using type = boost::variant<builtin_type>;

  } // namespace semantics
} // namespace scomp

#endif

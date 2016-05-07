#ifndef SCOMP_SEMANTICS_TYPE_FWD_HPP_
#define SCOMP_SEMANTICS_TYPE_FWD_HPP_

#include <memory>

#include <boost/variant.hpp>

namespace scomp {
  namespace semantics {
    namespace type_node {
      struct dummy_type;
      struct builtin_type;
    } // namespace type_node

    using dummy_type = std::shared_ptr<type_node::dummy_type>;
    using builtin_type = std::shared_ptr<type_node::builtin_type>;

    using type = boost::variant<dummy_type, builtin_type>;

  } // namespace semantics
} // namespace scomp

#endif

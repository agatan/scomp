#ifndef SCOMP_SEMANTICS_ENTRY_FWD_HPP_
#define SCOMP_SEMANTICS_ENTRY_FWD_HPP_

#include <memory>

#include <boost/variant.hpp>

namespace scomp {
  namespace semantics {
    namespace entry_node {
      struct var_entry;
      struct fun_entry;
    } // namespace entry_node

    using var_entry = std::shared_ptr<entry_node::var_entry>;
    using fun_entry = std::shared_ptr<entry_node::fun_entry>;

    using entry = boost::variant<var_entry, fun_entry>;

  } // namespace semantics
} // namespace scomp

#endif

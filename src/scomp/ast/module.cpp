#include <scomp/ast/module.hpp>

namespace scomp {
  namespace ast {

    void module::add_definition(definition const& def) {
      defs_.push_back(def);
    }
    void module::add_definition(definition&& def) {
      defs_.emplace_back(std::move(def));
    }

  } // namespace ast
} // namespace scomp

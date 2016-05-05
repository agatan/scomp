#include <scomp/semantics/scope.hpp>

namespace scomp {
  namespace semantics {

    boost::optional<entry> scope::find(std::string const& key) const {
      auto it = table.find(key);
      if (it == table.end()) {
        if (auto parent = enclosing.lock()) {
          return parent->find(key);
        }
        return boost::none;
      }
      return it->second;
    }

    void scope::define_symbol(std::string const& key, entry const& ent) {
      table.insert({key, ent});
    }

  } // namespace semantics
} // namespace scomp

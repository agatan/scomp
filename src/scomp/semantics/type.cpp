#include <scomp/semantics/type.hpp>

#include <unordered_map>

namespace scomp {
  namespace semantics {

    static type& builtin_int() {
      static type i = std::make_shared<type_node::builtin_type>("int");
      return i;
    }

    static type& builtin_bool() {
      static type b = std::make_shared<type_node::builtin_type>("bool");
      return b;
    }

    boost::optional<type> get_builtin_type(std::string const& name) {
      static std::unordered_map<std::string, type> builtin_types{
          {"int", builtin_int()}, {"bool", builtin_bool()}};

      auto it = builtin_types.find(name);
      if (it != builtin_types.end()) {
        return it->second;
      }
      return boost::none;
    }

  } // namespace semantics
} // namespace scomp

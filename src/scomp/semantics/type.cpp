#include <scomp/internal_error.hpp>
#include <scomp/semantics/type.hpp>

#include <unordered_map>

namespace scomp {
  namespace semantics {

    builtin_type& builtin_int() {
      static builtin_type i = std::make_shared<type_node::builtin_type>("int");
      return i;
    }

    builtin_type& builtin_bool() {
      static builtin_type b = std::make_shared<type_node::builtin_type>("bool");
      return b;
    }

    builtin_type& builtin_void() {
      static builtin_type v = std::make_shared<type_node::builtin_type>("void");
      return v;
    }

    boost::optional<builtin_type> get_builtin_type(std::string const& name) {
      static std::unordered_map<std::string, builtin_type> builtin_types{
          {"int", builtin_int()},
          {"bool", builtin_bool()},
          {"void", builtin_void()}};

      auto it = builtin_types.find(name);
      if (it != builtin_types.end()) {
        return it->second;
      }
      return boost::none;
    }

    struct match_visitor : boost::static_visitor<bool> {
      template <typename T, typename U>
      bool operator()(T const&, U const&) const {
        return false;
      }

      bool operator()(dummy_type const&, dummy_type const&) const {
        SCOMP_INTERNAL_ERROR_MSG("dummy type should not be checked");
      }

      template <typename T>
      bool operator()(dummy_type const&, T const&) const {
        SCOMP_INTERNAL_ERROR_MSG("dummy type should not be checked");
      }

      template <typename T>
      bool operator()(T const&, dummy_type const&) const {
        SCOMP_INTERNAL_ERROR_MSG("dummy type should not be checked");
      }

      bool operator()(builtin_type const& lhs, builtin_type const& rhs) const {
        return lhs == rhs;
      }
    };

    bool match(type const& lhs, type const& rhs) {
      return boost::apply_visitor(match_visitor{}, lhs, rhs);
    }

  } // namespace semantics
} // namespace scomp

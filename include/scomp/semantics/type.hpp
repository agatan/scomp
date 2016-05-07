#ifndef SCOMP_SEMANTICS_TYPE_HPP_
#define SCOMP_SEMANTICS_TYPE_HPP_

#include <scomp/semantics/type_fwd.hpp>

#include <string>

#include <boost/optional.hpp>

namespace scomp {
  namespace semantics {

    builtin_type& builtin_int();
    builtin_type& builtin_bool();
    builtin_type& builtin_void();

    boost::optional<builtin_type> get_builtin_type(std::string const&);

    bool match(type const&, type const&);

    namespace type_node {

      struct builtin_type final {
        builtin_type() = default;
        explicit builtin_type(std::string name) noexcept
            : name_(std::move(name)) {}

        std::string const& name() const& noexcept { return name_; }
        std::string name() && noexcept { return std::move(name_); }

       private:
        std::string name_;
      };

    } // namespace type_node

  } // namespace semantics
} // namespace scomp

#endif

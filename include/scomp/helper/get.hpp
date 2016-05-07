#ifndef SCOMP_HELPER_GET_HPP_
#define SCOMP_HELPER_GET_HPP_

#include <boost/variant.hpp>
#include <boost/optional.hpp>

#include <scomp/helper/no_option.hpp>

namespace scomp {
  namespace helper {

    template <typename T, typename... Args>
    boost::optional<T> get(boost::variant<Args...> const& variant) {
      auto p = boost::get<T>(&variant);
      if (p) {
        return *p;
      }
      return boost::none;
    }

    template <typename T, typename... Args>
    T get(boost::variant<Args...> const& variant, no_option_t) {
      return boost::get<T>(variant);
    }

  } // namespace helper
} // namespace scomp

#endif

#ifndef SCOMP_INTERNAL_ERROR_HPP_
#define SCOMP_INTERNAL_ERROR_HPP_

#include <iostream>

namespace scomp {
  [[noreturn]] inline void internal_error(char const* const file,
                                          char const* const function,
                                          std::size_t line,
                                          std::string const& msg = "") {
    std::cerr << "Internal compile error occurs: at " << file << ":" << function
              << ":" << line << ": " << msg << std::endl;
    std::abort();
  }
} // namespace scomp

#define SCOMP_INTERNAL_ERROR_MSG(s) \
  ::scomp::internal_error(__FILE__, __func__, __LINE__, (s))

#define SCOMP_INTERNAL_ERROR() \
  SCOMP_INTERNAL_ERROR_MSG("")


#endif

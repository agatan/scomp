#ifndef SCOMP_SEMANTICS_ERROR_HPP_
#define SCOMP_SEMANTICS_ERROR_HPP_

#include <scomp/ast/node_base.hpp>

namespace scomp {
  namespace semantics {

    struct error {
      error() = default;
      error(std::string filename, ast::node::pos_type const& pos,
            std::string message = "")
          : filename_(std::move(filename)),
            pos_(pos),
            message_(std::move(message)) {}

      std::string const& filename() const & {
        return filename_;
      }
      std::string filename() && {
        return std::move(filename_);
      }

      ast::node::pos_type const& pos() const & {
        return pos_;
      }
      ast::node::pos_type pos() && {
        return std::move(pos_);
      }

      std::string const& message() const & {
        return message_;
      }
      std::string message() && {
        return std::move(message_);
      }

     private:
      std::string filename_;
      ast::node::pos_type pos_;
      std::string message_;
    };

  } // namespace semantics
} // namespace scop

#endif

#ifndef SCOMP_SYNTAX_HELPER_HPP_
#define SCOMP_SYNTAX_HELPER_HPP_

#include <coco/combix.hpp>

#include <scomp/syntax/config.hpp>

namespace scomp {
  namespace syntax {

    namespace cbx = coco::combix;

    namespace parser {

      template <typename Parser>
      auto lex(Parser&& parser) {
        return cbx::skip(std::forward<Parser>(parser), cbx::spaces());
      }

      cbx::parser<std::string, stream_type> reserved();

      cbx::parser<std::string, stream_type> keyword(std::string const& s);

      cbx::parser<std::string, stream_type> varname();

    } // namespace parser
  } // namespace syntax
} // namespace scomp

#endif

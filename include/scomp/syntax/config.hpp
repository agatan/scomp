#ifndef SCOMP_SYNTAX_CONFIG_HPP_
#define SCOMP_SYNTAX_CONFIG_HPP_

#include <coco/combix/parse_result.hpp>
#include <coco/combix/parser.hpp>
#include <coco/combix/iterator_stream.hpp>

namespace scomp {
  namespace syntax {
    namespace parser {

      using stream_type =
          coco::combix::iterator_stream<std::string::const_iterator>;

      template <typename T>
      using parser_type = coco::combix::parser<T, stream_type>;

    } // namespace parser
  } // namespace syntax
} // namespace scomp

#endif

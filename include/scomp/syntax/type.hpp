#ifndef SCOMP_SYNTAX_TYPE_HPP_
#define SCOMP_SYNTAX_TYPE_HPP_

#include <coco/combix/parse_result.hpp>
#include <boost/optional.hpp>

#include <scomp/ast/ast_fwd.hpp>
#include <scomp/syntax/config.hpp>

namespace scomp {
  namespace syntax {

    namespace parser {
      parser_type<ast::type> type();
      parser_type<ast::type> type_spec();
      parser_type<boost::optional<ast::type>> optional_type_spec();
    } // namespace parser

    coco::combix::parse_result<ast::type, parser::stream_type>
    parse_type(std::string const&);

  } // namespace syntax
} // namespace scomp

#endif

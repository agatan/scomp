#ifndef SCOMP_SYNTAX_EXPRESSION_HPP_
#define SCOMP_SYNTAX_EXPRESSION_HPP_

#include <coco/combix/parse_result.hpp>

#include <scomp/ast/ast_fwd.hpp>
#include <scomp/syntax/config.hpp>

namespace scomp {
  namespace syntax {

    namespace parser {
      parser_type<ast::expression> expression();
    } // namespace parser

    coco::combix::parse_result<ast::expression, parser::stream_type>
    parse_expression(std::string const&);

  } // namespace syntax
} // namespace scomp

#endif

#ifndef SCOMP_SYNTAX_STATEMENT_HPP_
#define SCOMP_SYNTAX_STATEMENT_HPP_

#include <coco/combix/parse_result.hpp>

#include <scomp/ast/ast_fwd.hpp>
#include <scomp/syntax/config.hpp>

namespace scomp {
  namespace syntax {

    namespace parser {
      parser_type<ast::statement> statement();
    } // namespace parser

    coco::combix::parse_result<ast::statement, parser::stream_type>
    parse_statement(std::string const&);

  } // namespace syntax
} // namespace scomp

#endif

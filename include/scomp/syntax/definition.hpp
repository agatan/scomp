#ifndef SCOMP_SYNTAX_DEFINITION_HPP_
#define SCOMP_SYNTAX_DEFINITION_HPP_

#include <coco/combix/parse_result.hpp>

#include <scomp/ast/ast_fwd.hpp>
#include <scomp/syntax/config.hpp>

namespace scomp {
  namespace syntax {

    namespace parser {
      parser_type<ast::definition> definition();
    } // namespace parser

    coco::combix::parse_result<ast::definition, parser::stream_type>
    parse_definition(std::string const&);

  } // namespace syntax
} // namespace scomp

#endif

#ifndef SCOMP_SYNTAX_PARSER_HPP_
#define SCOMP_SYNTAX_PARSER_HPP_

#include <vector>
#include <string>

#include <scomp/syntax/config.hpp>
#include <scomp/ast/ast_fwd.hpp>

namespace scomp {
  namespace syntax {

    namespace parser {
      parser_type<std::vector<ast::definition>> toplevel();
    } // namespace parser

    coco::combix::parse_result<std::vector<ast::definition>,
                               parser::stream_type>
    parse_toplevel(std::string const&);

  } // namespace syntax
} // namespace scomp

#endif

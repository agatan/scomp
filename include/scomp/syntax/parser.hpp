#ifndef SCOMP_SYNTAX_PARSER_HPP_
#define SCOMP_SYNTAX_PARSER_HPP_

#include <vector>
#include <string>

#include <scomp/syntax/config.hpp>
#include <scomp/ast/module.hpp>

namespace scomp {
  namespace syntax {

    namespace parser {
      parser_type<ast::module> module();
    } // namespace parser

    // parse_module(file_name, source)
    coco::combix::parse_result<ast::module, parser::stream_type> parse_module(
        std::string const&, std::string const&);

  } // namespace syntax
} // namespace scomp

#endif

#include <scomp/syntax/statement.hpp>

#include <coco/combix.hpp>

#include <scomp/ast/ast.hpp>
#include <scomp/syntax/helper.hpp>
#include <scomp/syntax/expression.hpp>

namespace scomp {
  namespace syntax {

    namespace cbx = coco::combix;

    namespace parser {

      parser_type<ast::statement> expr_statement() {
        return cbx::map(cbx::lazy_fun(expression), [](auto&& e) {
          return ast::make_statement < ast::node::expr_stmt > (std::move(e));
        });
      }

      parser_type<ast::statement> statement() {
        return expr_statement();
      }

    } // namespace parser

    cbx::parse_result<ast::statement, parser::stream_type> parse_statement(
        std::string const& s) {
      auto stream = cbx::range_stream(s);
      auto const p =
          cbx::between(cbx::spaces(), cbx::seq(cbx::spaces(), cbx::eof()),
                       parser::statement());
      return cbx::parse(p, stream);
    }

  } // namespace syntax
} // namespace scomp

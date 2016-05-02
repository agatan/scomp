#include <scomp/syntax/statement.hpp>

#include <coco/combix.hpp>

#include <scomp/ast/ast.hpp>
#include <scomp/syntax/helper.hpp>
#include <scomp/syntax/expression.hpp>
#include <scomp/syntax/type.hpp>

namespace scomp {
  namespace syntax {

    namespace cbx = coco::combix;

    namespace parser {

      static parser_type<ast::statement> expr_statement() {
        return cbx::map(cbx::lazy_fun(expression), [](auto&& e) {
          return ast::make_statement < ast::node::expr_stmt > (std::move(e));
        });
      }

      static parser_type<ast::statement> valdef_statement() {
        auto const p = cbx::skip_seq(cbx::spaces())(
            keyword("val"), varname(), optional_type_spec(), cbx::token('='),
            cbx::lazy_fun(expression));
        return cbx::map(p, [](auto&& t) {
          auto&& name = std::get<1>(t);
          auto&& ty = std::get<2>(t);
          auto&& value = std::get<4>(t);
          return ast::make_statement<ast::node::valdef_stmt>(
              std::move(name), std::move(ty), std::move(value));
        });
      }

      static parser_type<ast::statement> return_statement() {
        auto const p =
            cbx::skip_seq(cbx::spaces())(keyword("return"), expression());
        return cbx::map(p, [](auto&& t) {
          return ast::make_statement<ast::node::return_stmt>(
              std::get<1>(std::move(t)));
        });
      }

      parser_type<ast::statement> statement() {
        return cbx::choice(return_statement(), valdef_statement(),
                           expr_statement());
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

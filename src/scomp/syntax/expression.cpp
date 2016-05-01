#include <scomp/syntax/expression.hpp>

#include <coco/combix.hpp>

#include <scomp/ast/ast.hpp>
#include <scomp/syntax/helper.hpp>

namespace scomp {
  namespace syntax {

    namespace cbx = coco::combix;

    namespace parser {

      parser_type<ast::expression> expression();

      // primary
      parser_type<int> integer() {
        return cbx::map(cbx::many1(cbx::digit()), [](auto&& is) {
          int acc = 0;
          for (auto c : is) {
            acc = acc * 10 + static_cast<int>(c) - '0';
          }
          return acc;
        });
      }

      parser_type<bool> boolean() {
        return cbx::choice(
            cbx::map(keyword("true"), [](auto) { return true; }),
            cbx::map(keyword("false"), [](auto) { return false; }));
      }

      parser_type<ast::expression> literal() {
        return cbx::expected(
            cbx::choice(
                cbx::map(integer(),
                         [](auto i) {
                           return ast::make_expression<ast::node::literal_expr>(
                               i);
                         }),
                cbx::map(boolean(),
                         [](auto i) {
                           return ast::make_expression<ast::node::literal_expr>(
                               i);
                         })),
            "literal expression");
      }

      parser_type<ast::expression> variable() {
        return cbx::map(varname(), [](auto&& s) {
          return ast::make_expression<ast::node::var_expr>(
              std::forward<decltype(s)>(s));
        });
      }

      parser_type<ast::expression> parens() {
        return cbx::map(cbx::between(lex(cbx::token('(')), lex(cbx::token(')')),
                                     lex(cbx::lazy_fun(expression))),
                        [](auto&& e) {
                          return ast::make_expression<ast::node::parens_expr>(
                              std::forward<decltype(e)>(e));
                        });
      }

      parser_type<ast::expression> primary() {
        return cbx::choice(variable(), literal(), parens());
      }

      parser_type<std::vector<ast::expression>> args() {
        return cbx::map(
            cbx::sep_by(lex(cbx::lazy_fun(expression)), lex(cbx::token(','))),
            [](auto&& es) {
              std::vector<ast::expression> result;
              std::move(es.begin(), es.end(), std::back_inserter(result));
              return result;
            });
      }

      parser_type<ast::expression> apply() {
        return cbx::map(
            cbx::skip_seq(cbx::spaces())(
                primary(), cbx::between(lex(cbx::token('(')),
                                         lex(cbx::token(')')), args())),
            [](auto&& t) {
              return ast::make_expression<ast::node::apply_expr>(
                  std::get<0>(std::forward<decltype(t)>(t)),
                  std::get<1>(std::forward<decltype(t)>(t)));
            });
      }

      parser_type<ast::expression> expression() {
        return cbx::expected(cbx::choice(cbx::try_(apply()), primary()), "expression");
      }

    } // namespace parser

    cbx::parse_result<ast::expression, parser::stream_type> parse_expression(
        std::string const& s) {
      auto stream = cbx::range_stream(s);
      auto const p =
          cbx::between(cbx::spaces(), cbx::seq(cbx::spaces(), cbx::eof()),
                       parser::expression());
      return cbx::parse(p, stream);
    }

  } // namespace syntax
} // namespace scomp

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
        return cbx::choice(parens(), literal(), variable());
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
        auto const applicative_parser = cbx::skip_seq(cbx::spaces())(
            primary(), cbx::many(cbx::between(lex(cbx::token('(')),
                                              lex(cbx::token(')')), args())));
        return cbx::map(applicative_parser, [](auto&& t) {
          ast::expression res = std::get<0>(t);
          std::deque<std::vector<ast::expression>> args_list = std::get<1>(t);
          for (auto&& args : std::move(args_list)) {
            res = ast::make_expression<ast::node::apply_expr>(std::move(res),
                                                              std::move(args));
          }
          return res;
        });
      }

      parser_type<ast::expression> multiplicative() {
        auto const op = cbx::map(
            lex(cbx::choice(cbx::token('*'), cbx::token('/'))), [](auto c) {
              return [c](auto&& lhs, auto&& rhs) {
                return ast::make_expression<ast::node::binop_expr>(
                    std::string(1, c), std::forward<decltype(lhs)>(lhs),
                    std::forward<decltype(rhs)>(rhs));
              };
            });
        return cbx::chainl1(lex(apply()), op);
      }

      parser_type<ast::expression> additive() {
        auto const op = cbx::map(
            lex(cbx::choice(cbx::token('+'), cbx::token('-'))), [](auto c) {
              return [c](auto&& lhs, auto&& rhs) {
                return ast::make_expression<ast::node::binop_expr>(
                    std::string(1, c), std::forward<decltype(lhs)>(lhs),
                    std::forward<decltype(rhs)>(rhs));
              };
            });
        return cbx::chainl1(lex(multiplicative()), op);
      }

      parser_type<ast::expression> expression() {
        return cbx::expected(additive(), "expression");
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

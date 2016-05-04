#include <scomp/syntax/definition.hpp>

#include <coco/combix.hpp>

#include <scomp/ast/ast.hpp>
#include <scomp/syntax/helper.hpp>
#include <scomp/syntax/expression.hpp>
#include <scomp/syntax/type.hpp>

namespace scomp {
  namespace syntax {

    namespace cbx = coco::combix;

    namespace parser {

      static parser_type<ast::definition> val_definition() {
        auto const p =
            cbx::skip_seq(cbx::spaces())(keyword("val"), varname(), type_spec(),
                                         cbx::token('='), expression());
        return cbx::map(cbx::positioned(p), [](auto&& p) {
          auto&& pos = p.first;
          auto&& t = p.second;
          auto&& name = std::get<1>(t);
          auto&& ty = std::get<2>(t);
          auto&& value = std::get<4>(t);
          return ast::make_definition<ast::node::val_def>(
              pos, std::move(name), std::move(ty), std::move(value));
        });
      }

      static parser_type<std::pair<std::string, ast::type>> param() {
        return cbx::map(cbx::skip_seq(cbx::spaces())(varname(), type_spec()),
                        [](auto&& t) {
                          return std::make_pair(std::get<0>(std::move(t)),
                                                std::get<1>(std::move(t)));
                        });
      }

      static parser_type<std::vector<std::pair<std::string, ast::type>>> params() {
        return cbx::map(
            cbx::sep_by(param(), lex(cbx::token(','))), [](auto&& ps) {
              std::vector<std::pair<std::string, ast::type>> pvs;
              std::move(ps.begin(), ps.end(), std::back_inserter(pvs));
              return pvs;
            });
      }

      static parser_type<ast::definition> fun_definition() {
        auto const p = cbx::skip_seq(cbx::spaces())(
            keyword("def"), varname(),
            cbx::between(lex(cbx::token('(')), lex(cbx::token(')')), params()),
            optional_type_spec(), cbx::token('='), expression());

        return cbx::map(cbx::positioned(p), [](auto&& p) {
          auto&& pos = p.first;
          auto&& t = p.second;

          std::string const& name = std::get<1>(t);

          std::vector<std::pair<std::string, ast::type>> const& params =
              std::get<2>(t);

          boost::optional<ast::type> const& ret = std::get<3>(t);

          ast::expression const& e = std::get<5>(t);

          return ast::make_definition<ast::node::fun_def>(
              pos, std::move(name), std::move(params), std::move(ret),
              std::move(e));
        });
      }

      parser_type<ast::definition> definition() {
        return cbx::choice(
            cbx::expected(fun_definition(), "function definition"),
            cbx::expected(val_definition(), "variable definition"));
      }

    } // namespace parser

    cbx::parse_result<ast::definition, parser::stream_type> parse_definition(
        std::string const& s) {
      auto stream =
          cbx::make_positioned<cbx::source_position>(cbx::range_stream(s));
      auto const p =
          cbx::between(cbx::spaces(), cbx::seq(cbx::spaces(), cbx::eof()),
                       parser::definition());
      return cbx::parse(p, stream);
    }

  } // namespace syntax
} // namespace scomp

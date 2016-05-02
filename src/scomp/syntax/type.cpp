#include <scomp/syntax/type.hpp>

#include <coco/combix.hpp>

#include <scomp/ast/ast.hpp>
#include <scomp/syntax/helper.hpp>

namespace scomp {
  namespace syntax {

    namespace cbx = coco::combix;

    namespace parser {

      static parser_type<ast::type> primary_type() {
        return cbx::map(varname(), [](auto&& s) {
          return ast::make_type<ast::node::primary_type>(std::move(s));
        });
      }

      parser_type<ast::type> type() {
        return cbx::expected(primary_type(), "type");
      }

      parser_type<ast::type> type_spec() {
        return cbx::expected(
            cbx::map(cbx::skip_seq(cbx::spaces())(cbx::token(':'), type()),
                     [](auto&& t) { return std::get<1>(std::move(t)); }),
            "type specifier");
      }

      parser_type<boost::optional<ast::type>> optional_type_spec() {
        return cbx::option(type_spec());
      }

    } // namespace parser

    cbx::parse_result<ast::type, parser::stream_type> parse_type(
        std::string const& s) {
      auto stream = cbx::range_stream(s);
      auto const p =
          cbx::between(cbx::spaces(), cbx::seq(cbx::spaces(), cbx::eof()),
                       parser::type());
      return cbx::parse(p, stream);
    }

  } // namespace syntax
} // namespace scomp

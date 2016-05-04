#include <scomp/syntax/parser.hpp>

#include <coco/combix.hpp>

#include <scomp/syntax/helper.hpp>
#include <scomp/syntax/definition.hpp>

namespace scomp {
  namespace syntax {

    namespace parser {

      namespace cbx = coco::combix;

      parser_type<ast::module> module(std::string filename) {
        auto const sep = cbx::many(lex(cbx::token(';')));
        auto const p = cbx::sep_by(definition(), sep);
        return cbx::map(p, [filename = std::move(filename)](auto&& ds) {
          std::vector<ast::definition> dvs;
          std::move(ds.begin(), ds.end(), std::back_inserter(dvs));
          return ast::module(std::move(filename), std::move(dvs));
        });
      }

    } // namespace parser

    coco::combix::parse_result<ast::module, parser::stream_type>
    parse_module(std::string const& filename, std::string const& s) {
      auto stream =
          cbx::make_positioned<cbx::source_position>(cbx::range_stream(s));
      auto const p =
          cbx::between(cbx::spaces(), cbx::seq(cbx::spaces(), cbx::eof()),
                       parser::module(filename));
      return cbx::parse(p, stream);
    }

  } // namespace syntax
} // namespace scomp

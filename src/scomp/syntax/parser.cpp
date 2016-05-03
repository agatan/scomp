#include <scomp/syntax/parser.hpp>

#include <coco/combix.hpp>

#include <scomp/syntax/helper.hpp>
#include <scomp/syntax/definition.hpp>

namespace scomp {
  namespace syntax {

    namespace parser {

      namespace cbx = coco::combix;

      parser_type<std::vector<ast::definition>> toplevel() {
        auto const sep = cbx::many(lex(cbx::token(';')));
        auto const p = cbx::sep_by(definition(), sep);
        return cbx::map(p, [](auto&& ds) {
          std::vector<ast::definition> dvs;
          std::move(ds.begin(), ds.end(), std::back_inserter(dvs));
          return dvs;
        });
      }

    } // namespace parser

    coco::combix::parse_result<std::vector<ast::definition>, parser::stream_type>
    parse_toplevel(std::string const& s) {
      auto stream =
          cbx::make_positioned<cbx::source_position>(cbx::range_stream(s));
      auto const p =
          cbx::between(cbx::spaces(), cbx::seq(cbx::spaces(), cbx::eof()),
                       parser::toplevel());
      return cbx::parse(p, stream);
    }

  } // namespace syntax
} // namespace scomp

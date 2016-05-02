#include <scomp/syntax/helper.hpp>

namespace scomp {
  namespace syntax {

    namespace cbx = coco::combix;

    namespace parser {

      cbx::parser<std::string, stream_type> reserved() {
        return cbx::choice(cbx::string("val"), cbx::string("true"),
                           cbx::string("false"), cbx::string("def"));
      }

      cbx::parser<std::string, stream_type> keyword(std::string const& s) {
        return lex(cbx::skip(
            cbx::string(s), cbx::not_followed_by(cbx::choice(
                                cbx::digit(), cbx::alpha(), cbx::token('_')))));
      }

      cbx::parser<std::string, stream_type> varname() {
        auto lead = cbx::choice(cbx::alpha(), cbx::token('_'));
        auto tail = cbx::map(
            cbx::many(cbx::choice(cbx::alpha(), cbx::digit(), cbx::token('_'))),
            [](auto&& cs) { return std::string(cs.begin(), cs.end()); });
        auto const var = cbx::map(cbx::seq(lead, tail), [](auto&& s) {
          return std::get<0>(std::forward<decltype(s)>(s)) +
                 std::get<1>(std::forward<decltype(s)>(s));
        });
        return cbx::map(cbx::seq(cbx::not_followed_by(reserved()), var),
                        [](auto&& t) { return std::get<1>(std::move(t)); });
      }

    } // namespace parser
  } // namespace syntax
} // namespace scomp

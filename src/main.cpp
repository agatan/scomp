#include <iostream>

#include <boost/property_tree/json_parser.hpp>

#include <scomp/ast/ast.hpp>
#include <scomp/ast/stringize.hpp>
#include <scomp/ast/dump.hpp>
#include <scomp/syntax/parser.hpp>

int main() {
  std::string line;
  std::string src;
  while (std::getline(std::cin, line)) {
    src += line + '\n';
  }

  auto res = scomp::syntax::parse_toplevel(src);
  if (res) {
    boost::property_tree::ptree root;
    for (auto&& d: *res) {
      scomp::ast::dump_definition(root, d);
    }
    boost::property_tree::write_json(std::cout, root);
  } else {
    auto&& pos = res.unwrap_error().position();
    std::cerr << "Parse error at line: " << pos.line << ", column: " << pos.column << "\n";
    std::cerr << res.unwrap_error() << std::endl;
  }
}

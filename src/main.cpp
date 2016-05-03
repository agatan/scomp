#include <iostream>

#include <scomp/ast/ast.hpp>
#include <scomp/ast/stringize.hpp>
#include <scomp/syntax/parser.hpp>

int main() {
  std::string line;
  std::string src;
  while (std::getline(std::cin, line)) {
    src += line + '\n';
  }

  auto res = scomp::syntax::parse_toplevel(src);
  if (res) {
    for (auto&& d: *res) {
      std::cout << scomp::ast::stringize(d) << std::endl;
    }
  } else {
    auto&& pos = res.unwrap_error().position();
    std::cerr << "Parse error at line: " << pos.line << ", column: " << pos.column << "\n";
    std::cerr << res.unwrap_error() << std::endl;
  }
}

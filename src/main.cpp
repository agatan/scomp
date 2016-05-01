#include <iostream>

#include <scomp/ast/ast.hpp>
#include <scomp/ast/stringize.hpp>
#include <scomp/syntax/expression.hpp>

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    auto res = scomp::syntax::parse_expression(line);
    if (res) {
      std::cout << scomp::ast::stringize(*res) << std::endl;
    } else {
      std::cerr << res.unwrap_error() << std::endl;
    }
  }
}

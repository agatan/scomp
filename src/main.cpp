#include <iostream>

#include <boost/property_tree/json_parser.hpp>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/ADT/Triple.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/Target/TargetMachine.h>

#include <scomp/ast/ast.hpp>
#include <scomp/ast/stringize.hpp>
#include <scomp/ast/dump.hpp>
#include <scomp/syntax/parser.hpp>
#include <scomp/semantics/error.hpp>
#include <scomp/semantics/analyze.hpp>
#include <scomp/codegen/context.hpp>
#include <scomp/codegen/emitter.hpp>

void initialize_llvm() {
  LLVMInitializeX86TargetInfo();
  LLVMInitializeX86Target();
  LLVMInitializeX86TargetMC();
  LLVMInitializeX86AsmPrinter();
  LLVMInitializeX86AsmParser();
}

int main() {
  std::string line;
  std::string src;
  while (std::getline(std::cin, line)) {
    src += line + '\n';
  }

  auto res = scomp::syntax::parse_module("<stdin>", src);
  if (res) {
    boost::property_tree::ptree root;
    scomp::ast::dump_module(root, res.unwrap());
    boost::property_tree::write_json(std::cout, root);

    try {
      auto scope = scomp::semantics::analyze(*res);
      assert(static_cast<bool>(scope));
      initialize_llvm();
      scomp::codegen::context ctx(llvm::getGlobalContext());
      auto mod = scomp::codegen::emit_llvm_ir(*res, ctx);
      mod->dump();
    } catch (scomp::semantics::error const& err) {
      std::cerr << err.filename() << ":" << err.line() << ":" << err.column()
                << ": " << err.message() << std::endl;
    }

  } else {
    auto&& pos = res.unwrap_error().position();
    std::cerr << "Parse error at line: " << pos.line << ", column: " << pos.column << "\n";
    std::cerr << res.unwrap_error() << std::endl;
  }
}

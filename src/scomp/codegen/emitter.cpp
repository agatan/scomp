#include <scomp/codegen/emitter.hpp>

#include <llvm/IR/Verifier.h>

#include <scomp/helper/get.hpp>
#include <scomp/semantics/entry.hpp>
#include <scomp/codegen/type_emitter.hpp>

namespace scomp {
  namespace codegen {

    struct emitter final {
      explicit emitter(context& ctx, std::unique_ptr<llvm::Module>&& mod)
          : ctx(ctx), ty_emitter(ctx), module(std::move(mod)), table() {}

      std::unique_ptr<llvm::Module> get_module() && {
        return std::move(module);
      }

      template <typename... Args>
      auto emit(boost::variant<Args...> const& v) {
        return boost::apply_visitor([&](auto&& t) { return emit(t); }, v);
      }

      void emit(ast::module const& module) {
        for (auto&& d: module.defs()) {
          if (auto f = helper::get<ast::fun_def>(d)) {
            proto(*f);
          }
        }
        for (auto&& d: module.defs()) {
          emit(d);
        }
      }

      // expressions {{{
      llvm::Value* emit(ast::literal_expr const& lit) {
        struct visitor {
          context& ctx;
          type_emitter& ty_e;

          visitor(context& ctx, type_emitter& ty_e): ctx(ctx), ty_e(ty_e) {}

          llvm::Value* operator()(int n) const {
            return llvm::ConstantInt::get(ty_e.emit(semantics::builtin_int()),
                                          n, true /* signed */);
          }

          llvm::Value* operator()(bool b) const {
            return llvm::ConstantInt::get(ty_e.emit(semantics::builtin_bool()),
                                          b);
          }
        };
        return boost::apply_visitor(visitor(ctx, ty_emitter), lit->value);
      }

      llvm::Value* emit(ast::var_expr const& v) {
        return find(v->name);
      }

      llvm::Value* emit(ast::binop_expr const&) {
        SCOMP_INTERNAL_ERROR_MSG("binop_expr is not supported yet");
      }

      llvm::Value* emit(ast::parens_expr const& p) {
        return emit(p->expr);
      }

      llvm::Value* emit(ast::apply_expr const& app) {
        auto callee = helper::get<ast::var_expr>(app->callee, helper::no_option);
        auto callee_f = module->getFunction(callee->name);
        std::vector<llvm::Value*> args;
        for (auto&& arg: app->args) {
          args.push_back(emit(arg));
        }
        return ctx.builder.CreateCall(callee_f, args, "calltmp");
      }

      llvm::Value* emit(ast::block_expr const& blk) {
        llvm::Value* last = nullptr;
        for (auto&& stmt: blk->body) {
          last = emit(stmt);
        }
        return last;
      }
      // }}}

      // statements {{{
      llvm::Value* emit(ast::expr_stmt const& es) {
        return emit(es->expr);
      }

      llvm::Value* emit(ast::valdef_stmt const& valdef) {
        auto value = emit(valdef->value);
        define_value(valdef->name, value);
        return nullptr;
      }

      llvm::Value* emit(ast::return_stmt const&) {
        SCOMP_INTERNAL_ERROR_MSG("return statement is not implemented yet");
      }
      // }}}

      // definitions {{{
      llvm::Value* emit(ast::val_def const& valdef) {
        SCOMP_INTERNAL_ERROR_MSG("global variable is not implemented yet");
      }

      llvm::Value* emit(ast::fun_def const& fundef) {
        // TODO: prototype declaration
        auto f = module->getFunction(fundef->name);
        if (!f) {
          SCOMP_INTERNAL_ERROR_MSG("function should be declared here");
        }

        auto bb = llvm::BasicBlock::Create(ctx.llvm_context, "entry", f);
        ctx.builder.SetInsertPoint(bb);

        for (auto&& arg: f->args()) {
          define_value(arg.getName(), &arg);
        }

        auto value = emit(fundef->body);
        ctx.builder.CreateRet(value);
        llvm::verifyFunction(*f);
        return f;
      }

      void proto(ast::fun_def const& fundef) {
        std::vector<llvm::Type*> params_ty;
        for (auto&& t: fundef->entry->params) {
          params_ty.push_back(ty_emitter.emit(t.second));
        }
        auto ret = ty_emitter.emit(fundef->entry->return_type);
        auto ft = llvm::FunctionType::get(ret, params_ty, false /* variadic */ );
        auto f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage,
                                        fundef->name, &*module);
        unsigned idx = 0;
        for (auto& arg: f->args()) {
          arg.setName(fundef->entry->params[idx++].first);
        }
      }
      // }}}

    private:
      context& ctx;
      type_emitter ty_emitter;
      std::unique_ptr<llvm::Module> module;
      std::unordered_map<std::string, llvm::Value*> table;

      void define_value(std::string const& key, llvm::Value* value) {
        table.insert({key, value});
      }
      llvm::Value* find(std::string const& key) {
        auto it = table.find(key);
        if (it == table.end()) {
          return nullptr;
        }
        return it->second;
      }
    };

    std::unique_ptr<llvm::Module> emit_llvm_ir(ast::module const& mod, context& ctx) {
      auto module = llvm::make_unique<llvm::Module>(mod.name(), ctx.llvm_context);
      auto e = emitter(ctx, std::move(module));
      e.emit(mod);
      return std::move(e).get_module();
    }

  } // namespace codegen
} // namespace scomp

#include <scomp/ast/dump.hpp>

#include <boost/property_tree/ptree.hpp>

#include <scomp/ast/ast.hpp>

namespace scomp {
  namespace ast {

    namespace ptree = boost::property_tree;

    namespace detail {

      void dump_position(ptree::ptree& parent, node::pos_type const& pos) {
        auto& tree = parent.put("position", "");
        tree.put("line", pos.line);
        tree.put("column", pos.column);
      }

      struct type_visitor {
        explicit type_visitor(ptree::ptree& p) : parent(p) {}

        void operator()(primary_type const& p) const {
          parent.put("primary_type", p->name);
        }

        void operator()(unknown_type const& p) const {
          ptree::ptree& t = parent.add("unknown_type", "");
          if (p->ref != nullptr) {
            dump_type(t, *p->ref);
          }
        }

      private:
        ptree::ptree& parent;
      };

      struct def_visitor {
        explicit def_visitor(ptree::ptree& p) : parent(p) {}

        void operator()(val_def const& valdef) const {
          ptree::ptree& child = parent.add("val_def", "");
          dump_position(child, position(valdef));
          child.add("name", valdef->name);
          dump_type(child.add("type", ""), valdef->typ);
          dump_expression(child.add("value", ""), valdef->value);
        }

        void operator()(fun_def const& fundef) const {
          ptree::ptree& child = parent.add("fun_def", "");
          dump_position(child, position(fundef));
          child.add("name", fundef->name);

          ptree::ptree& params = child.add("params", "");
          for (auto&& p: fundef->params) {
            ptree::ptree tree;
            tree.add("name", p.first);
            dump_type(tree.add("type", ""), p.second);
            params.push_back(std::make_pair("", tree));
          }

          if (fundef->return_type) {
            dump_type(child.add("return_type", ""), *fundef->return_type);
          }

          dump_expression(child.add("body", ""), fundef->body);
        }
      private:
        ptree::ptree& parent;
      };

      struct expr_visitor {
        explicit expr_visitor(ptree::ptree& p) : parent(p) {}

        void operator()(literal_expr const& lit) const {
          struct value_stringizer {
            std::string operator()(int i) const {
              return std::to_string(i);
            }
            std::string operator()(bool b) const {
              if (b) {
                return "true";
              } else {
                return "false";
              }
            }
          };

          ptree::ptree& child = parent.add("literal_expr", "");
          dump_position(child, position(lit));
          child.add("value",
                    boost::apply_visitor(value_stringizer{}, lit->value));
        }

        void operator()(var_expr const& var) const {
          ptree::ptree& child = parent.add("var_expr", "");
          dump_position(child, position(var));
          child.add("name", var->name);
        }

        void operator()(binop_expr const& binop) const {
          ptree::ptree& child = parent.add("binop_expr", "");
          dump_position(child, position(binop));
          child.add("operator", binop->op);
          dump_expression(child.add("lhs", ""), binop->lhs);
          dump_expression(child.add("rhs", ""), binop->rhs);
        }

        void operator()(parens_expr const& p) const {
          ptree::ptree& child = parent.add("parens_expr", "");
          dump_position(child, position(p));
          dump_expression(child, p->expr);
        }

        void operator()(apply_expr const& app) const {
          ptree::ptree& child = parent.add("apply_expr", "");
          dump_position(child, position(app));
          dump_expression(child.add("callee", ""), app->callee);
          ptree::ptree& args = child.add("arguments", "");
          for (auto&& arg: app->args) {
            ptree::ptree tree;
            dump_expression(tree, arg);
            args.push_back(std::make_pair("", tree));
          }
        }

        void operator()(block_expr const& blk) const {
          ptree::ptree& child = parent.add("block_expr", "");
          dump_position(child, position(blk));
          ptree::ptree& ss = child.add("body", "");
          for (auto&& s: blk->body) {
            ptree::ptree tree;
            dump_statement(tree, s);
            ss.push_back(std::make_pair("", tree));
          }
        }
      private:
        ptree::ptree& parent;
      };

      struct stmt_visitor {
        explicit stmt_visitor(ptree::ptree& p) : parent(p) {}

        void operator()(expr_stmt const& es) const {
          ptree::ptree& child = parent.add("expr_stmt", "");
          dump_position(child, position(es));
          dump_expression(child.add("expression", ""), es->expr);
        }

        void operator()(valdef_stmt const& valdef) const {
          ptree::ptree& child = parent.add("valdef_stmt", "");
          dump_position(child, position(valdef));
          child.add("name", valdef->name);
          if (valdef->typ) {
            dump_type(child.add("type", ""), *valdef->typ);
          }
          dump_expression(child.add("value", ""), valdef->value);
        }

        void operator()(return_stmt const& ret) const {
          ptree::ptree& child = parent.add("return_stmt", "");
          dump_position(child, position(ret));
          if (ret->expr) {
            dump_expression(child.add("value", ""), *ret->expr);
          }
        }
      private:
        ptree::ptree& parent;
      };

    } // namespace detail

    void dump_module(ptree::ptree& tree, module const& mod) {
      ptree::ptree& mod_tree = tree.add("module", "");
      mod_tree.add("name", mod.name());
      ptree::ptree& defs = mod_tree.add("definitions", "");
      for (auto&& d: mod.defs()) {
        ptree::ptree child;
        dump_definition(child, d);
        defs.push_back(std::make_pair("", child));
      }
    }

    void dump_type(ptree::ptree& tree, type const& typ) {
      boost::apply_visitor(detail::type_visitor(tree), typ);
    }

    void dump_definition(ptree::ptree& tree, definition const& def) {
      boost::apply_visitor(detail::def_visitor(tree), def);
    }

    void dump_expression(ptree::ptree& tree, expression const& expr) {
      boost::apply_visitor(detail::expr_visitor(tree), expr);
    }

    void dump_statement(ptree::ptree& tree, statement const& stmt) {
      boost::apply_visitor(detail::stmt_visitor(tree), stmt);
    }

  } // namespace ast
} // namespace scomp

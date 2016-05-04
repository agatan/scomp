#ifndef SCOMP_AST_MODULE_HPP_
#define SCOMP_AST_MODULE_HPP_

#include <string>
#include <vector>

#include <scomp/ast/ast_fwd.hpp>

namespace scomp {
  namespace ast {

    struct module {
      module() = default;

      explicit module(std::string name): name_(std::move(name)), defs_() {}
      module(std::string name, std::vector<definition> const& defs)
          : name_(std::move(name)), defs_(defs) {}
      module(std::string name, std::vector<definition>&& defs)
          : name_(std::move(name)), defs_(std::move(defs)) {}

      module(module const&) = delete;
      module(module&&) = default;

      module& operator=(module const&) = delete;
      module& operator=(module&&) = default;

      std::string const& name() const & {
        return name_;
      }
      std::string name() && {
        return std::move(name_);
      }
      void name(std::string name) {
        name_ = std::move(name);
      }

      std::vector<definition> const& defs() const & {
        return defs_;
      }
      std::vector<definition>& defs() & {
        return defs_;
      }
      std::vector<definition> defs() && {
        return std::move(defs_);
      }

      void add_definition(definition const& def);
      void add_definition(definition&& def);

    private:
      std::string name_;
      std::vector<definition> defs_;
    };

  } // namespace ast
} // namespace scomp

#endif

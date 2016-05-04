#ifndef SCOMP_AST_DEFINITION_HPP_
#define SCOMP_AST_DEFINITION_HPP_

#include <scomp/ast/ast_fwd.hpp>

#include <string>
#include <vector>
#include <utility>

#include <boost/optional.hpp>

#include <scomp/ast/node_base.hpp>

namespace scomp {
  namespace ast {
    namespace node {

      struct val_def : node_base {
        std::string name;
        type typ;
        expression value;

        explicit val_def() = default;
        explicit val_def(pos_type const& p, std::string name, type&& t,
                         expression&& v)
            : node_base(p),
              name(std::move(name)),
              typ(std::move(t)),
              value(std::move(v)) {}
        explicit val_def(pos_type const& p, std::string name, type const& t,
                         expression const& v)
            : node_base(p), name(std::move(name)), typ(t), value(v) {}

        std::string to_string() const;
      };

      struct fun_def : node_base {
        std::string name;
        std::vector<std::pair<std::string, type>> params;
        boost::optional<type> return_type;
        expression body;

        explicit fun_def() = default;
        fun_def(pos_type const& p, std::string name,
                std::vector<std::pair<std::string, type>> const& params,
                boost::optional<type> const& ret, expression const& body)
            : node_base(p),
              name(std::move(name)),
              params(params),
              return_type(ret),
              body(body) {}
        fun_def(pos_type const& p, std::string name,
                std::vector<std::pair<std::string, type>>&& params,
                boost::optional<type>&& ret, expression&& body)
            : node_base(p),
              name(std::move(name)),
              params(std::move(params)),
              return_type(std::move(ret)),
              body(std::move(body)) {}

        std::string to_string() const;
      };

    } // namespace node
  } // namespace ast
} // namespace scomp

#endif

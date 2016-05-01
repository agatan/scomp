#ifndef SCOMP_AST_DEFINITION_HPP_
#define SCOMP_AST_DEFINITION_HPP_

#include <scomp/ast/ast_fwd.hpp>

#include <string>
#include <vector>
#include <utility>

#include <boost/optional.hpp>

namespace scomp {
  namespace ast {
    namespace node {

      struct val_def {
        std::string name;
        boost::optional<type> typ;
        expression value;

        explicit val_def() = default;
        explicit val_def(std::string name, type&& t, expression&& v)
            : name(std::move(name)), typ(std::move(t)), value(std::move(v)) {}
        explicit val_def(std::string name, type const& t,
                             expression const& v)
            : name(std::move(name)), typ(t), value(v) {}

        explicit val_def(std::string name, expression&& v)
            : name(std::move(name)), typ(boost::none), value(std::move(v)) {}
        explicit val_def(std::string name, expression const& v)
            : name(std::move(name)), typ(boost::none), value(v) {}

        std::string to_string() const;
      };

      struct fun_def {
        std::string name;
        std::vector<std::pair<std::string, type>> params;
        boost::optional<type> return_type;
        expression body;

        explicit fun_def() = default;
        fun_def(std::string name,
                std::vector<std::pair<std::string, type>> const& params,
                expression const& body)
            : name(std::move(name)),
              params(params),
              return_type(boost::none),
              body(body) {}
        fun_def(std::string name,
                std::vector<std::pair<std::string, type>>&& params,
                expression&& body)
            : name(std::move(name)),
              params(std::move(params)),
              return_type(boost::none),
              body(std::move(body)) {}
        fun_def(std::string name,
                std::vector<std::pair<std::string, type>> const& params,
                type const& ret,
                expression const& body)
            : name(std::move(name)),
              params(params),
              return_type(ret),
              body(body) {}
        fun_def(std::string name,
                std::vector<std::pair<std::string, type>>&& params,
                type&& ret,
                expression&& body)
            : name(std::move(name)),
              params(std::move(params)),
              return_type(std::move(ret)),
              body(std::move(body)) {}

        std::string to_string() const;
      };

    } // namespace node
  } // namespace ast
} // namespace scomp

#endif

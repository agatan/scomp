#ifndef SCOMP_AST_NODE_BASE_HPP_
#define SCOMP_AST_NODE_BASE_HPP_

#include <boost/variant.hpp>
#include <coco/combix/source_position.hpp>

namespace scomp {
  namespace ast {
    namespace node {

      using pos_type = coco::combix::source_position;

      struct node_base {
        node_base() = default;
        explicit node_base(pos_type const& pos)
            : position_(pos) {}
        explicit node_base(pos_type&& pos)
            : position_(std::move(pos)) {}

        pos_type const& position() const {
          return position_;
        }

        void position(pos_type const& pos) {
          position_ = pos;
        }

        void position(pos_type&& pos) {
          position_ = std::move(pos);
        }

       private:
        pos_type position_;
      };

    } // namespace node

    template <typename T>
    auto postiion(T const& t) -> decltype(t.position()) {
      return t.position();
    }

    template <typename T>
    auto position(std::shared_ptr<T> const& t) -> decltype(t->position()) {
      return t->position();
    }

    template <typename... Args>
    auto position(boost::variant<Args...> const& t) {
      return boost::apply_visitor([](auto&& v) { return position(v); }, t);
    }

  } // namespace ast
} // namespace scomp

#endif

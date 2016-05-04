#ifndef SCOMP_AST_NODE_BASE_HPP_
#define SCOMP_AST_NODE_BASE_HPP_

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
  } // namespace ast
} // namespace scomp

#endif

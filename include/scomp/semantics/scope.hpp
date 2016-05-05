#ifndef SCOMP_SEMANTICS_SCOPE_HPP_
#define SCOMP_SEMANTICS_SCOPE_HPP_

#include <string>
#include <unordered_map>

#include <boost/optional.hpp>

#include <scomp/semantics/entry_fwd.hpp>

namespace scomp {
  namespace semantics {

    struct scope;

    using scope_ptr = std::shared_ptr<scope>;
    using enclosing_scope_ptr = std::weak_ptr<scope>;

    using table_type = std::unordered_map<std::string, entry>;

    struct scope final : std::enable_shared_from_this<scope> {
      scope() = default;
      explicit scope(enclosing_scope_ptr&& e)
          : enclosing(std::move(e)) {}

      boost::optional<entry> find(std::string const&) const;

      void define_symbol(std::string const&, entry const&);

     private:
      table_type table;
      enclosing_scope_ptr enclosing;
    };


  } // namespace semantics
} // namespace scomp

#endif

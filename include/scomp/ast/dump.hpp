#ifndef SCOMP_AST_DUMP_HPP_
#define SCOMP_AST_DUMP_HPP_

#include <boost/property_tree/ptree.hpp>

#include <scomp/ast/ast_fwd.hpp>

namespace scomp {
  namespace ast {

    void dump_type(boost::property_tree::ptree&, type const&);
    void dump_definition(boost::property_tree::ptree&, definition const&);
    void dump_expression(boost::property_tree::ptree&, expression const&);
    void dump_statement(boost::property_tree::ptree&, statement const&);

  } // namespace ast
} // namespace scomp

#endif

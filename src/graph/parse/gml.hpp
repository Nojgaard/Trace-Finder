#ifndef GRAPH_PARSE_GML_H
#define GRAPH_PARSE_GML_H
#include <iostream>
#include "../base.hpp"

namespace graph {
namespace parse {
namespace gml {

void read(std::istream &s, graph_t &g);
void write (std::ostream &s, const graph_t &g);

}//gml
}//parse
}//graph
#endif

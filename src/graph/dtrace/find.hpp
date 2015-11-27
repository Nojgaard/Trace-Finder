#ifndef GRAPH_DTRACE_FIND_H
#define GRAPH_DTRACE_FIND_H
#include "../base.hpp"
#include <vector>

namespace graph {
namespace dtrace {

void find(const graph_t &g, std::vector<vertex> &out);

}//dtrace
}//graph
#endif

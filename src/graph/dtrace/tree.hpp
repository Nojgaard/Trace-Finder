#ifndef GRAPH_DTRACE_H
#define GRAPH_DTRACE_H
#include "../base.hpp"
#include "rule.hpp"

namespace graph {
namespace dtrace {
int full_trace_size(const graph_t &g);
void traverse_bfs(const graph_t &g, const ruleset &rules,
		std::vector<vertex> &out);
}//dtrace
}//graph
#endif

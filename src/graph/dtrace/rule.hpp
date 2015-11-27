#ifndef GRAPH_DTRACE_RULE_H
#define GRAPH_DTRACE_RULE_H
#include "../base.hpp"

namespace graph {
namespace dtrace {

typedef std::vector<bool (*)(const std::vector<vertex> &, const graph_t &)> ruleset;

bool has_one_repetition(const std::vector<vertex> &t, const graph_t &g);
bool is_canon(const std::vector<vertex> &t, const graph_t &g);

}//dtrace
}//graph
#endif

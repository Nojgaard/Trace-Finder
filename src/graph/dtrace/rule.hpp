#ifndef GRAPH_DTRACE_RULE_H
#define GRAPH_DTRACE_RULE_H
#include "../base.hpp"
#include "trace.hpp"

namespace graph {
namespace dtrace {

typedef std::vector<bool (*)(const trace &)> ruleset;

bool has_one_repetition(const trace &t);
bool is_canon(const trace &t);

}//dtrace
}//graph
#endif

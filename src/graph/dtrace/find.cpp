#include "tree.hpp"
#include "rule.hpp"
#include "../base.hpp"

using namespace std;

namespace graph {
namespace dtrace {

void find(const graph_t &g, vector<vertex> &out) {
	ruleset rules;
	rules.push_back(&has_one_repetition);
	rules.push_back(&has_two_repetition);
	rules.push_back(&is_canon);
	traverse_bfs(g,rules,out);
}

}//dtrace
}//graph

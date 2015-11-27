#include <vector>
#include "../base.hpp"
#include "tree.hpp"
#include <iostream>

namespace graph {
namespace dtrace {
using namespace std;

bool has_one_repetition(const vector<vertex> &trace, const graph_t &g) {
	if (trace.size() <= 1) return true;
	if (trace.back()== trace[trace.size()-3]) return false;
	int current_size = trace.size();
	if (full_trace_size(g)+1 == current_size){
		auto p = boost::edge(trace[0],trace[1],g);
		assert(p.second);
		edge e_first = p.first;
		p = boost::edge(trace[current_size-2],trace.back(),g);
		assert(p.second);
		edge e_last = p.first;
		if (e_last == e_first) return false;
	}
	return true;
}

bool is_canon(const vector<vertex> &trace, const graph_t &g) {
	if (trace.size() == 0) return true;
	if (trace[0] != trace.back()) return true;
	
	vertex minv = trace[0];
	vector<int> pp;
	for (size_t i = 0; i < trace.size(); i++) {
		if (i != 0 && trace[i] == minv) {
			pp.push_back(i);
		}
	}
	for (int p : pp) {
		//check backward
		for (size_t i = 0; i < trace.size(); i++) {
			int j = p-i;
			if (j <= 0) j = abs(j-1);
			if (trace[i] < trace[j]) {
				break;
			} else if (trace[i] > trace[j]) {
				return false;
			}
		}
		if (p == (int)trace.size()-1) continue;
		//check forward
		for (size_t i = 0; i < trace.size(); i++) {
			int j = (p+i);
			if (j >= (int)trace.size()) {
				j = (j+1)%trace.size();
			}
			if (trace[i] < trace[j]) {
				break;
			} else if (trace[i] > trace[j]) {
				return false;
			}
		}
	}
	return true;
}

}//dtrace
}//graph

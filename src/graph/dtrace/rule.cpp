#include <vector>
#include "../base.hpp"
#include "rule.hpp"
#include "trace.hpp"
#include "tree.hpp"
#include <iostream>

namespace graph {
namespace dtrace {
using namespace std;

bool has_one_repetition(const trace &t) {
	if (t.size() <= 1) return true;
	if (t.back()== t[t.size()-2]) return false;
	if (t.tar_size()== t.size()){
		if (t[0] == t.back()) return false;
	}
	return true;
}

bool is_canon(const trace &t) {
	if (t.size() == 0) return true;
	if (t.tail_vertex() != t.head_vertex()) return true;
	
	vector<vertex> vt = t.get_vertex_trace();
	vertex minv = vt[0];
	vector<int> pp;
	for (size_t i = 0; i < vt.size(); i++) {
		if (i != 0 && vt[i] == minv) {
			pp.push_back(i);
		}
	}
	for (int p : pp) {
		//check backward
		for (size_t i = 0; i < vt.size(); i++) {
			int j = p-i;
			if (j <= 0) j = abs(j-1);
			if (vt[i] < vt[j]) {
				break;
			} else if (vt[i] > vt[j]) {
				return false;
			}
		}
		if (p == (int)vt.size()-1) continue;
		//check forward
		for (size_t i = 0; i < vt.size(); i++) {
			int j = (p+i);
			if (j >= (int)vt.size()) {
				j = (j+1)%vt.size();
			}
			if (vt[i] < vt[j]) {
				break;
			} else if (vt[i] > vt[j]) {
				return false;
			}
		}
	}
	return true;
}

}//dtrace
}//graph

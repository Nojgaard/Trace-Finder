#include <vector>
#include <map>
#include <cassert>
#include <cmath>
#include <iostream>
#include "../base.hpp"
#include "../morphism/vf2.hpp"
#include "../morphism/canonicalize.hpp"
#include "../../range.hpp"
#include "rule.hpp"
#include "trace.hpp"
#include "embedded_trace.hpp"

namespace graph {
namespace dtrace {

using namespace std;

vertex min_vertex(const graph_t &g) {
	vertex minv;
	bool mindef = false;
	for (auto v : as_range(vertices(g))) {
		if (!mindef || minv > v) {
			mindef = true;
			minv = v;
		}
	}
	return minv;
}

bool does_exist(const embedded_trace &t, 
		const vector<embedded_trace> &tv) {
	bool ex = false;
	for (auto &ta : tv) {
		if (t == ta) {
			ex = true;
			break;
		}
	}
	return ex;
}

bool is_valid(const embedded_trace &t, const ruleset &rules) {
	for (auto r : rules) {
		if (!r(t.get_trace())) {
			return false;
		}
	}
	return true;
}

void print_level_info(int level, const vector<embedded_trace> &nl,
		int invalid, int pruned) {
	cout << "------------------------" << endl;
	cout << "Level       " << level << endl;
	cout << "Found       " << nl.size() << " unique traces."<<endl;
	cout << "Pruned      " << pruned << " traces." << endl;
	cout << "Invalidated " << invalid << " traces." << endl;
}

void traverse_bfs(const graph_t &g, const ruleset &rules, 
		vector<vertex> &out) {
	assert(num_vertices(g) > 0);
	vector<embedded_trace> curr_level,next_level;
	int level = 0;
	curr_level.push_back(embedded_trace(min_vertex(g),g));
	int tar_level = curr_level[0].get_trace().tar_size();
	int pruned = 0, invalid = 0;
	size_t next = 0;
	while (level < tar_level && next < curr_level.size()) {
		embedded_trace &t = curr_level[next];
		next++;
		for (auto e : t.children()) {
			if (t.is_full(e)) continue;

			embedded_trace et(e, t.get_trace(), g);
			
			bool valid = is_valid(et,rules);
			if (!valid) {
				invalid++;
				continue;
			}
			et.canonicalize();
			//et.print();
			bool exists = false;
			exists = does_exist(et,next_level);
			if (!exists) {
				next_level.push_back(et);
			} else {
				pruned++;
			}
		}
		if (next >= curr_level.size() && !next_level.empty()) {
			print_level_info(level, next_level,invalid,pruned);
			swap(curr_level,next_level);
			next_level.clear();
			level++; pruned = 0; invalid = 0;
			next = 0;
		}
	}
	
	cout << "--------------------\n";
	cout << "Traversal complete!\n";
	cout << "Found " << curr_level.size() << " traces.\n";
}

}//dtrace
}//graph

#include <vector>
#include <map>
#include <cassert>
#include <cmath>
#include "../base.hpp"
#include "../morphism/vf2.hpp"
#include "../../range.hpp"

namespace graph {
namespace dtrace {

using namespace std;


int full_trace_size(const graph_t &g) {
	return (2*num_edges(g));
}

struct embedded_trace {
public:
	embedded_trace(vertex v, const graph_t &g):host_g(g) {
		trace.push_back(v);
		compute_embedding();
	}

	embedded_trace(vertex v, const vector<vertex> &t, 
		const graph_t &g):host_g(g) {
		trace = t;
		trace.push_back(v);
		compute_embedding();
	}

	range<boost::graph_traits<graph_t>::adjacency_iterator> children() {
		return as_range(adjacent_vertices(trace.back(),host_g));
	}

	const vector<vertex> & get_trace() {
		return trace;
	}

	bool is_full(vertex tar) {
		vertex src = trace.back();
		auto p = boost::edge(src,tar,host_g);
		assert(p.second);
		edge e = p.first;
		return (embedding[e] <= 0);
	}

	bool operator == (const embedded_trace &rhs) const {
		using namespace morphism::vf2;
		always_true_pred vp;
		label_pred<edge,int> ep(embedding, rhs.embedding);
		return (is_isomorphic(host_g,rhs.host_g,vp,ep));
	}

private:
	void compute_embedding() {
		for (size_t i = 1; i < trace.size(); i++) {
			edge e = boost::edge(trace[i-1],trace[i],host_g).first;
			if (embedding.find(e) == embedding.end()) {
				embedding[e] = i*-1;
				assert(embedding[e] < 0);
				continue;
			}
			int j = embedding[e] * -1;
			int gap_f = i-j;
			assert(gap_f > 0);
			int gap_b = (full_trace_size(host_g)-i)+j;
			assert(gap_b > 0);
			int gap = (gap_f > gap_b)?gap_b:gap_f;
			embedding[e] = gap;
		}
		for (auto e : as_range(edges(host_g))) {
			if (embedding.find(e) == embedding.end()) {
				embedding[e] = 0;
			} else if (embedding[e] < 0) {
				int df = embedding[e] * -1;
				int db = trace.size()-df+1;
				embedding[e] = (df < db)?df*-1:db*-1;
				assert(embedding[e] < 0);
			}
		}
	}

	vector<vertex> trace;
	map<edge, int> embedding;
	const graph_t &host_g;
};

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

void traverse_bfs(const graph_t &g, vector<vertex> &out) {
	assert(num_vertices(g) > 0);
	vector<embedded_trace> curr_level,next_level;
	int level = 0;
	curr_level.push_back(embedded_trace(min_vertex(g),g));
	int tar_level = full_trace_size(g);
	int pruned = 0, invalid = 0;
	size_t next = 0;
	while (level < tar_level && next < curr_level.size()) {
		embedded_trace &t = curr_level[next];
		next++;
		for (auto v : t.children()) {
			if (t.is_full(v)) continue;

			embedded_trace et(v, t.get_trace(), g);
			bool exists = does_exist(et,next_level);
			if (!exists) {
				next_level.push_back(et);
			} else {
				pruned++;
			}
		}
		if (next >= curr_level.size() && !next_level.empty()) {
			swap(curr_level,next_level);
			next_level.clear();
			level++; pruned = 0; invalid = 0;
		}
	}
}

}//dtrace
}//graph
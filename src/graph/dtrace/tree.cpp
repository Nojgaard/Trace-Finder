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

	bool is_full(vertex src, vertex tar) {
		auto p = boost::edge(src,tar,host_g);
		assert(p.second);
		edge e = p.first;
		return (embedding[e] <= 0);
	}

	bool operator == (const embedded_trace &rhs) {
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

void traverse_bfs() {
}

}//dtrace
}//graph

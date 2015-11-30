#include "embedded_trace.hpp"
#include "../morphism/vf2.hpp"
#include "../morphism/canonicalize.hpp"
#include <iostream>
#include <cassert>

using namespace std;

namespace graph  {
namespace dtrace {

embedded_trace::embedded_trace(vertex v, const graph_t &g)
	:t(v,g),host_g(g) {
	compute_embedding();
}

embedded_trace::embedded_trace(edge e, const trace &pt, 
	const graph_t &g):t(pt),host_g(g) {
	t.extend(e);
	compute_embedding();
}

embedded_trace::children_t embedded_trace::children() const {
	return as_range(out_edges(t.head_vertex(),host_g));
}

const trace & embedded_trace::get_trace() const {
	return t;
}

bool embedded_trace::is_full(edge e) const {
	return (embedding.at(e) > 0);
}

void embedded_trace::canonicalize() {
	morphism::label_less<edge,int> el(embedding,embedding);
	graph::morphism::canonizalise(host_g, el);
}

bool embedded_trace::operator == (const embedded_trace &rhs) const {
	using namespace morphism::vf2;
	always_true_pred vp;
	label_pred<edge,int> ep(embedding, rhs.embedding);
	
	return (is_isomorphic(host_g,rhs.host_g,vp,ep));
}

void embedded_trace::print() const {
	cout << "Trace: ";
	/*for (size_t i = 0; i < trace.size(); i++) {
		cout << trace[i] << " ";
	}*/
	cout << endl;
	cout << "Embedding: ";
	for (auto e : as_range(edges(host_g))) {
		auto src = source(e,host_g);
		auto tar = target(e,host_g);
		cout << "|(" << src << ", " << tar << "): ";
		cout << embedding.at(e) << " ";
	}
	cout << endl;
}

void embedded_trace::compute_embedding() {
	for (size_t i = 0; i < t.size(); i++) {
		edge e = t[i];
		if (embedding.find(e) == embedding.end()) {
			embedding[e] = (i+1)*-1;
			assert(embedding[e] < 0);
			continue;
		}
		assert(embedding[e] < 0);
		int j = embedding[e] * -1;
		int gap_f = (i+1)-j;
		assert(gap_f > 0);
		int gap_b = (t.tar_size()-(i+1))+j;
		assert(gap_b > 0);
		int gap = (gap_f > gap_b)?gap_b:gap_f;
		embedding[e] = gap;
	}
	for (auto e : as_range(edges(host_g))) {
		if (embedding.find(e) == embedding.end()) {
			embedding[e] = 0;
		} else if (embedding[e] < 0) {
			int df = embedding[e] * -1;
			int db = t.size()-(df-1);
			embedding[e] = (df < db)?df*-1:db*-1;
			assert(embedding[e] < 0);
		}
	}
}



}//dtrace
}//graph


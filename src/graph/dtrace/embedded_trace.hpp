#ifndef GRAPH_DTRACE_EMBEDDED_TRACE_H
#define GRAPH_DTRACE_EMBEDDED_TRACE_H
#include "../base.hpp"
#include "../../range.hpp"
#include "trace.hpp"
#include <vector>
#include <map>
#include "../morphism/canonicalize.hpp"

namespace graph  {
namespace dtrace {

class embedded_trace {
public:
	using children_t = range<boost::graph_traits<graph_t>::out_edge_iterator>;
	
	//embedded_trace(const embedded_trace &et);
	embedded_trace(vertex v, const graph_t &g);
	embedded_trace(edge e, const trace &pt, const graph_t &g);
	children_t children() const;
	const trace & get_trace() const;
	bool is_full(edge e) const;
	void canonicalize();
	bool operator == (const embedded_trace &rhs) const;
	void print() const;
private:
	void compute_embedding();

	trace t;
	std::map<edge,int> embedding;
	const graph_t &host_g;
	std::shared_ptr<const morphism::canon::canonicalized_graph> canon_graph;
};

}//dtrace
}//graph

#endif

#ifndef GRAPH_BASE_H
#define GRAPH_BASE_H

#include<boost/graph/adjacency_list.hpp>

namespace graph {

typedef boost::adjacency_list<boost::vecS, boost::vecS,
			boost::undirectedS> graph_t;
typedef boost::graph_traits<graph_t>::vertex_descriptor vertex;
typedef boost::graph_traits<graph_t>::edge_descriptor edge;

} //namespace graph

#endif

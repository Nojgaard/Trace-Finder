#include <iostream>
#include "util.hpp"
#include "../base.hpp"
#include <map>
#include <stdexcept>
#include <string>
#include "../../range.hpp"

namespace graph {
namespace parse {
namespace gml {
using namespace std;

void read_node(istream &s, graph_t &g,map<int,vertex> &idx_map) {
	eat(s, "[");
	vertex v = add_vertex(g);
	string token;
	while ((s >> token)) {
		if (token == "]") {
			return;
		} else if (token == "id") {
			int id = eat_int(s);
			if (idx_map.find(id) != idx_map.end()) {
				string str_id = to_string(id);
				throw runtime_error(
						"Node id "+str_id+"declared twice.\n");
			}
			
			idx_map[id] = v;
		}
	}
	throw runtime_error("Reached EOF while parsing node.\n");
}

void read_edge(istream &s, graph_t &g, map<int,vertex> &idx_map) {
	eat(s, "[");
	vertex src,tar;
	bool bsrc = false,btar = false;
	string token;
	while ((s >> token)) {
		if (token == "]") {
			if (!bsrc || !btar) {
				throw runtime_error("Target/source has not been declared while parsing edge.\n");
			}
			add_edge(src,tar,g);
			return;
		} else if (token == "source") {
			if (bsrc)
				throw runtime_error("Source already declared.\n");
			int id = eat_int(s);
			if (idx_map.find(id) == idx_map.end())
				throw runtime_error("Source node not declared.\n");
			src = idx_map[id];
			bsrc = true;
		} else if (token == "target") {
			if (btar)
				throw runtime_error("Target already declared.\n");
			int id = eat_int(s);
			if (idx_map.find(id) == idx_map.end())
				throw runtime_error("Target node not declared.\n");
			tar = idx_map[id];
			btar = true;
		} else {
			throw runtime_error("Unexpected symbol '"+token+"' while parsing edge.\n");
		}
	}
	throw runtime_error("Reached EOF while parsing edge.\n");

}

void read_graph(istream &s, graph_t &g) {
	eat(s, "graph");
	eat(s, "[");
	string token;
	map<int,vertex> idx_map;
	while ((s >> token)) {
		if (token == "]") {
			return;
		} else if (token == "node") {
			read_node(s,g,idx_map);
		} else if (token == "edge") {
			read_edge(s,g,idx_map);
		} else {
			throw runtime_error("Unexpected symbol '"+token+"' while reading graph.\n");
		}
	}
	throw runtime_error("Reached EOF while reading graph.\n");
}

void read(istream &s, graph_t &g) {
	read_graph(s,g);
}

void write(ostream &s, const graph_t &g) {
	s << "graph [" << endl;
	for (vertex v : as_range(vertices(g))) {
		s << "  node [ id " << v << " ]" << endl; 
	}
	for (auto e : as_range(edges(g))) {
		auto src = source(e,g);
		auto tar = target(e,g);
		s << "  edge [ source " << src << " target " << tar << 
			" ] " << endl;
	}
	s << "]";
}



}//gml
}//parse 
}//graph


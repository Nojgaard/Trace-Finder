#ifndef GRAPH_MORPHISM_CANONICALIZE_H
#define GRAPH_MORPHISM_CANONICALIZE_H
#include "../base.hpp"
#include <graph_canon/canonicalization.hpp>
#include <graph_canon/canonicalization_util.hpp>
#include <graph_canon/ordered_graph.hpp>
#include <graph_canon/util.hpp>
#include <graph_canon/compare.hpp>
#include <iostream>

namespace graph {
namespace morphism {

template <typename ve, typename ltype>
struct label_less {
	label_less (const std::map<ve,ltype> &pl,
				const std::map<ve,ltype> &pr) :pl(pl),pr(pr){}
	bool operator () (ve lhs, ve rhs) const {
		return (pl.at(lhs) < pr.at(rhs));
	}
private:
	const std::map<ve,ltype> &pl,&pr;

};

template <typename ve, typename ltype>
struct label_equal {
	label_equal (const std::map<ve,ltype> &pl,
				const std::map<ve,ltype> &pr) :pl(pl),pr(pr){}
	bool operator () (ve lhs, ve rhs) const {
		return (pl.at(lhs) == pr.at(rhs));
	}
private:
	const std::map<ve,ltype> &pl,&pr;
};

template<typename eless>
void canonizalise(const graph_t &g, eless el) {
	using namespace graph_canonicalization;
	canonicalizer<std::size_t, 
		edge_invariant_all_equal<std::size_t>,
		traversal_bfsExpS,
		target_cell_select_first_largest> canon;
	simple_automorphism_visitor<std::size_t> visitor;
	vertex_less_all_equivalent vless;
	auto idx = canon(g, get(boost::vertex_index_t(),g)
			,vless,visitor);
	auto idx_map = boost::make_iterator_property_map(idx.cbegin()
			, get(boost::vertex_index_t(), g));
	boost::ordered_graph<graph_t, decltype(idx_map)> canon_graph(g,idx_map,always_false());


}
}//morphism
}//graph
#endif

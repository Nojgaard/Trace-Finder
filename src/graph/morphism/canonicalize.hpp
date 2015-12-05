#ifndef GRAPH_MORPHISM_CANONICALIZE_H
#define GRAPH_MORPHISM_CANONICALIZE_H
#include "../base.hpp"
#include <graph_canon/canonicalization.hpp>
#include <graph_canon/canonicalization_util.hpp>
#include <graph_canon/ordered_graph.hpp>
#include <graph_canon/util.hpp>
#include <graph_canon/compare.hpp>
#include <iostream>
#include <vector>
#include <map>
#include "../../range.hpp"
#include <algorithm>
#include <cassert>

namespace graph {
namespace morphism {
namespace canon {

template <typename ve, typename ltype>
struct label_less {
	label_less (const std::map<ve,ltype> &p) :p(p){}
	bool operator () (ve lhs, ve rhs) const {
		return (p.at(lhs) < p.at(rhs));
	}
private:
	const std::map<ve,ltype> &p;

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


template <typename edge_pred>
struct vertex_less_edge_pred {
	vertex_less_edge_pred(const std::map<edge, edge_pred> &p,
						  const graph_t &g)
		:p(p),g(g){}

	bool operator () (vertex vl, vertex vr) {
		std::vector<edge_pred> lhs, rhs;
		for (auto e : as_range(out_edges(vl,g))) {
			lhs.push_back(p.at(e));
		}
		for (auto e : as_range(out_edges(vr,g))) {
			rhs.push_back(p.at(e));
		}
		if (lhs.size() < rhs.size()) return true;
		if (lhs.size() > rhs.size()) return false;
		std::sort(lhs.begin(), lhs.end());
		std::sort(rhs.begin(), rhs.end());
		for (size_t i = 0; i < lhs.size(); i++) {
			if (lhs[i] < rhs[i]) return true;
			if (lhs[i] > rhs[i]) return false;
		}
		return false;
	}
private:
	const std::map<edge,edge_pred> &p;
	const graph_t &g;
};

typedef boost::iterator_property_map<__gnu_cxx::__normal_iterator<const unsigned int*, std::vector<unsigned int> >, boost::vec_adj_list_vertex_id_map<boost::no_property, unsigned int>, unsigned int, const unsigned int&> idx_map_t;

typedef graph_canonicalization::canonicalizer<size_t,
		graph_canonicalization::edge_invariant_all_equal<size_t>,
		graph_canonicalization::traversal_bfsExpS,
		graph_canonicalization::target_cell_select_first_largest> canonicalizer_t;

struct canonicalized_graph {
public:
	template<typename visitor, typename vless, typename eless>
	canonicalized_graph(canonicalizer_t &c, const graph_t &g, 
			visitor vis, vless vl, eless el)
		: perm(c(g,get(boost::vertex_index_t(),g),vl,vis)), 
		  cg(g, boost::make_iterator_property_map(perm.cbegin(), 
					  get(boost::vertex_index_t(),g)),el) {}

	template<typename edge_equal>
	bool is_equal(const canonicalized_graph &rhs, 
			edge_equal eeq) const {
		using namespace graph_canonicalization;
		return ordered_graph_equal(cg,rhs.cg,always_true(),
				eeq,graph_compare_null_visitor());
	}

private:
	const canonicalizer_t::Permutation perm;
	const boost::ordered_graph<graph_t, idx_map_t> cg;

};

template<typename vertex_less, typename edge_less>
std::shared_ptr<canonicalized_graph> canonicalize(
		const graph_t &g,vertex_less vl, edge_less el) {
	using namespace graph_canonicalization;
	
	canonicalizer_t canon;
	simple_automorphism_visitor<std::size_t> visitor;
	//vertex_less_all_equivalent vlessaq;
	canonicalized_graph cg(canon,g,visitor,vl,el);
	return std::make_shared<canonicalized_graph>(canon,g,visitor,
			vl,el);

}

}//canon
}//morphism
}//graph
#endif

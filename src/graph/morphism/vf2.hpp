#ifndef GRAPH_MORPHISM_VF2_H
#define GRAPH_MORPHISM_VF2_H
#include <map>
#include <boost/graph/vf2_sub_graph_iso.hpp>

namespace graph {
namespace morphism {
namespace vf2 {

struct always_true_pred {
	template<typename ve>
	bool operator () (ve,ve) const {
		return true;
	}
};

template <typename ve, typename ltype>
struct label_pred {
	label_pred (const std::map<ve,ltype> &pl,
				const std::map<ve,ltype> &pr) :pl(pl),pr(pr){}
	bool operator () (ve lhs, ve rhs) const {
		return (pl.at(lhs) == pr.at(rhs));
	}
private:
	const std::map<ve,ltype> &pl,&pr;
};

struct iso_callback {
	iso_callback(bool &iso):iso(iso){
		iso = false;
	}

	template <typename map_lr, typename map_rl>
	bool operator () (map_lr, map_rl) {
		iso = true;
		return false;
	}

private:
	bool &iso;
};

template <typename graph, typename vpred, typename epred>
bool is_isomorphic(
		const graph &g_left,
		const graph &g_right,
		const vpred vp,
		const epred ep) {
	auto v_order_left = boost::vertex_order_by_mult(g_left);
	bool iso;
	iso_callback cb(iso);
	boost::vf2_graph_iso(g_left,g_right,cb,
			get(boost::vertex_index_t(), g_left),
			get(boost::vertex_index_t(), g_right),
			v_order_left, ep, vp);
	return iso;
}

}//vf2
}//morphism
}//graph
#endif

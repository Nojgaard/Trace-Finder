#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <stdexcept>
#include "base.hpp"
#include "parse/gml.hpp"

namespace graph {
namespace io {
namespace file {
using namespace std;
void read(string p, graph_t &g) {
	string ext = boost::filesystem::extension(p);
	if (ext == ".gml") {
		boost::filesystem::ifstream s(p);
		parse::gml::read(s,g);
	} else {
		throw runtime_error("Unknown file format.\n");
	}
}
}//file
}//io
}//graph

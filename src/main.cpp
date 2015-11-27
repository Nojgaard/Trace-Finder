#include <iostream>
#include <boost/program_options.hpp>
#include "graph/base.hpp"
#include "graph/io.hpp"
#include "graph/dtrace/find.hpp"
#include <exception>

using namespace std;
using namespace graph;
namespace po = boost::program_options;

int main(int argc, char **argv) {
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "Generate help message.")
		("input,i", po::value<string>()->required(),
		 	"Path of the input file.")
	;
	po::variables_map vm;
	po::store(po::parse_command_line(argc,argv,desc),vm);

	if (vm.count("help")) {
		cout << desc << endl;
		return 0;
	}
	string file_path = vm["input"].as<string>();
	graph_t g;
	try {
		io::file::read(file_path, g);
	} catch (exception &e) {
		cout << e.what() << endl;
		return 0;
	}
	vector<vertex> traces;
	dtrace::find(g,traces);

	return 0;
}

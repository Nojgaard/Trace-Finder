#include <iostream>
#include <stdexcept>

namespace graph {
namespace parse {
using namespace std;

void eat(istream &s, string exp) {
	string token;
	if (!(s >> token)) {
		throw runtime_error("Expected '"+exp+"' but found EOF.\n");
	} else if (token != exp) {
		throw runtime_error("Expected '"+exp+"' but found '"
				+ token + "'.\n");
	}
}

int eat_int(istream &s) {
	string token;
	if (!(s >> token)) {
		throw runtime_error("Reached EOF but expected int.\n");
	}
	return stoi(token);
}

}
}

#ifndef GRAPH_PARSE_UTIL_H
#define GRAPH_PARSE_UTIL_H
#include <iostream>
namespace graph {
namespace parse {
void eat(std::istream &s, std::string exp);
int  eat_int(std::istream &s);
}
}
#endif

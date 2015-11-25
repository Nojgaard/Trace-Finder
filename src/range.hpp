#ifndef RANGE_H
#define RANGE_H
#include <utility>
template<typename Iter>
struct range : std::pair<Iter, Iter> {

	range(const std::pair<Iter, Iter> &x) 
		: std::pair<Iter, Iter>(x) { }

	Iter begin() const {
		return this->first;
	}

	Iter end() const {
		return this->second;
	}
};

template<typename Iter>
inline range<Iter> as_range(const std::pair<Iter, Iter> &x) {
	return range<Iter>(x);
}
#endif

#pragma once

#include <map>
#include <unordered_map>

using namespace std;

class c11 {
public:
	void test() {
		// key is const
		// at(key): out_of_range

		map<int, int> m; // or unordered_map<int, int> m;
		m[1]; // insert({1, 0})

		// equal_range [lower_bound, upper_bound)

		// unordered_*: bucket
	}
};
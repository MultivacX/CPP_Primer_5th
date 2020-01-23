#pragma once

#include <numeric>
#include <vector>

using namespace std;

class c10 {
public:
	void test() {
		vector<double> vd{ 1, 2, 3 };
		auto sum = accumulate(vd.begin(), vd.end(), 0);

		vector<string> vc{ "1", "2", "3" };
		// auto str = accumulate(vc.begin(), vc.end(), ""); // const char* 没有定义+运算符

		vector<int> vi;
		fill_n(vi.begin(), 10, 0); // UB ERROR
		fill_n(back_inserter(vi), 10, 0);

		// copy
		// replace replace_copy
		// unique
		// stable_sort
		// find_if for_each

		// lambda 捕获列表只用于局部非static变量
		// bind: placeholders 参数占位符; 绑定引用参数 ref(param)

	}
};
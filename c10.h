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
		// auto str = accumulate(vc.begin(), vc.end(), ""); // const char* û�ж���+�����

		vector<int> vi;
		fill_n(vi.begin(), 10, 0); // UB ERROR
		fill_n(back_inserter(vi), 10, 0);

		// copy
		// replace replace_copy
		// unique
		// stable_sort
		// find_if for_each

		// lambda �����б�ֻ���ھֲ���static����
		// bind: placeholders ����ռλ��; �����ò��� ref(param)

	}
};
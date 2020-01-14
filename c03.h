#pragma once

#include <iostream>
#include <vector>

using namespace std;

class c03 {
public:
	static void test() {
		const vector<int> v{ 0, 1, 2 };
		//v[0] = 1; error

		int a = 0, b = 1, c = 2;
		int arr[3] = { 0, 1, 2 };
		int* pArr[3] = { &a, &b, &c };
		//int& rArr[3] = /* error */;
		int (*parr)[3] = &arr;
		int (&rarr)[3] = arr;
		
		auto firstElementAddr(arr);
		decltype(arr) new_arr = { 3, 4, 5 };
		
		int* arrBegin = arr; // begin(arr)
		int* arrEnd = &arr[4]; // end(arr)

		int* p = arr + 1;
		int val = p[-1]; // arr[0]

		const char* str = "012";
		char chars[4] = { '0', '1', '2', '\0' };

		auto& refArr = arr;
		auto addrArr1stElement = arr;

		return;
	}
};
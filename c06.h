#pragma once

#include <iostream>
#include <vector>

using namespace std;

// constexpr objects are const and are initialized with values known during compilation
constexpr size_t scale(int s) { return s * 2; }

int print_arr(int(&r)[10], int i) {
	cout << "ref: " << r[i] << endl;
	return r[i];
}

//int print_arr(int (*p)[10], int i) {
//	return (*p)[i];
//}

int print_arr(int p[][10], int i) {
	cout << "ptr: " << (*p)[i] << endl;
	return (*p)[i];
}

class c06 {
public:
	void fcn(const int i) { /*i = 2;*/ }
	// void fcn(int i) {} // ERROR: 重复定义, 同上, 当用实参初始化形参时会忽略掉顶层 const

	void print(const int*) {}
	// void print(const int[]) {} // ERROR: 重复定义, 同上
	// void print(const int[10]) {} // ERROR: 重复定义, 同上

	void print(int(*matrix)[10], int row) {}
	// void print(int matrix[][10], int row) {} // ERROR: 重复定义, 同上

	void test() {
		int matrix[3][5] = { 
			{1, 2, 3, 4, 5},
			{11, 12, 13, 14, 15},
			{21, 22, 23, 24, 25},
		};

		int (&r)[3][5] = matrix;
		int (*p)[5] = matrix;
		// int a[][5] = matrix; // ERROR
		// int a[3][5] = matrix; // ERROR: no copy
		int (&rr)[5] = matrix[1];
		int (*pp)[5] = &matrix[1];

		auto s = scale(3);
		int arr[scale(3)];
		constexpr auto len = scale(4);
		int arr2[len];
		int i = 2;
		auto j = scale(i);

		// 函数类型/指向函数的指针
		int f(int*, int);
		using F = int(int*, int);
		typedef int F1(int*, int);
		using FP = int(*)(int*, int);
		typedef int (*FP1)(int*, int);
		// 返回函数指针
		{ F *f1(string s); }
		{ FP f1(string s); }
		{ int (*f1(string s))(int*, int); }
		{ auto f1(string s)->int(*)(int*, int); }
		{ auto f1(string s)->FP; }
		{ decltype(f) *f1(string s); }

		{
			int arr[10] = { 10, 11, 12, 13 };
			print_arr(arr, 2);
			print_arr(&arr, 2);
			int matrix[2][10] = { { 10, 11, 12, 13 }, { 20, 21, 22, 23 } };
			print_arr(matrix[0], 2);
			print_arr(matrix[1], 2);
			print_arr(&matrix[0], 2);
			print_arr(matrix, 2);
			print_arr(&matrix[1], 2);
			print_arr(matrix + 1, 2);
		}
	}

	int(*func(int i))[10]{ return nullptr; }
	// auto func(int i) -> int(*)[10]{ return nullptr; } // 同上
	// int a[10] = {0}; decltype(a) *func(int i){ return nullptr; } // 同上
};
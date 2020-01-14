#pragma once

#include <iostream>
#include <vector>

using namespace std;

constexpr size_t scale(int s) { return s * 2; }

class c06 {
public:
	void fcn(const int i) {}
	// void fcn(int i) {} // ERROR: �ظ�����, ͬ��, ����ʵ�γ�ʼ���β�ʱ����Ե����� const

	void print(const int*) {}
	// void print(const int[]) {} // ERROR: �ظ�����, ͬ��
	// void print(const int[10]) {} // ERROR: �ظ�����, ͬ��

	void print(int(*matrix)[10], int row) {}
	// void print(int matrix[][10], int row) {} // ERROR: �ظ�����, ͬ��

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
		int i = 2;
		auto j = scale(i);

		// ��������/ָ������ָ��
		int f(int*, int);
		using F = int(int*, int);
		typedef int F1(int*, int);
		using FP = int(*)(int*, int);
		typedef int (*FP1)(int*, int);
		// ���غ���ָ��
		{ F *f1(string s); }
		{ FP f1(string s); }
		{ int (*f1(string s))(int*, int); }
		{ auto f1(string s)->int(*)(int*, int); }
		{ auto f1(string s)->FP; }
		{ decltype(f) *f1(string s); }
	}

	int(*func(int i))[10]{ return nullptr; }
	// auto func(int i) -> int(*)[10]{ return nullptr; } // ͬ��
	// int a[10] = {0}; decltype(a) *func(int i){ return nullptr; } // ͬ��
};
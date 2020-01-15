#pragma once

#include <iostream>
#include <vector>

using namespace std;

int height = 0;

class c07 {
public:
	// 默认构造函数
	c07() = default; // 合成的默认构造函数
	// c07() : _cnt(0), _change(0) {} // 初始化列表
	// c07()/* : _cnt(0), _change(0) */ { _cnt = 0; _change = 0; } // 赋值
	// c07(int v = 0, int c = 0) : _cnt(v), _change(c) {} // 初始化列表

	// explicit 抑制隐式转换
	explicit c07(int cnt) : _cnt(cnt), _change(0) { cout << "c07 int " << cnt << endl;  }
	// 委托构造
	c07(char c) : c07((int)(c - '0')) { cout << "c07 char " << c << endl; }

	int count() { return _cnt; } // int count(c07 *const this) { return this->_cnt; }
	int count() const { return _cnt; } // int count(const c07 *const this) { return this->_cnt; }

	void some_member() const { ++::height;  ++_change; }

	c07& self() { return *this; }
	const c07& self() const { return *this; } // ERROR: c07& self() const { return *this; }

private:
	int _cnt = 0;
	mutable int _change = 0;

	static const int time = 0;
	static constexpr int day = 1;
	// static int month = 3; // ERROR
	static int month;
};

int c07::month = 3;

c07 func(); // func
c07 obj; // default
c07 obji(8); // explicit c07(int cnt)
c07 obj0 = 66; // c07(char c)
c07 objc = 'a'; // c07(char c)

// public members
// 没有构造函数
// 没有类内初始值
// 没有基类 没有虚函数
struct AggregateClassA {
	int val;
	char s;
};

AggregateClassA aca = { 19, 'S' };

// 字面值常量类
// constexpr 构造函数
// 字面值 members
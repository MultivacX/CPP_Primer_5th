#pragma once

#include <functional>

int add(int i, int j) { return i + j; }
string add(const string& i, const string& j) { return i + j; }
auto mod = [](int i, int j) { return i % j; };
class divide {
public:
	int operator()(int i, int j) { return i / j; }
};

class c14 {
public:
	// 不能重载 ::    .*    .    ? :

	// 使用重载的运算符本质上是一次函数调用 无法保证运算对象的求值顺序

	// 一般不应该重载逗号、取地址、逻辑与、逻辑或

	// 使用与内置类型一致的含义

	// 成员
	// 必须是成员 赋值、下标[]、调用()、成员访问->
	// 应该是成员 复合赋值
	// 改变对象状态/与给定类型密切相关

	// -> 只能重载为获取某个对象的成员

	// 函数对象 lambda 
	// mutable : auto f = [val] () mutable { return ++val; }

	// 可调用对象：函数、函数指针、lambda、bind、重载了函数调用符的类
	// function<T>

	// 对象的成员指针	a.*b
	// 指针的成员指针	a->*b

	static void test() {
		string s = "world";
		string t = s + "X";
		string u = "Y" + s; // + 不是 string 的成员

		c14 obj0;
		obj0.cnt = 1;
		c14 obj1;
		obj1.cnt = 99;

		obj0 = obj1;
		obj0 = 199;

		cout << 3.5 + obj0 << endl;
		cout << 3.5 + static_cast<double>(obj0) << endl;

		c14* p0 = new c14;
		*p0 = 43;
		auto obj2 = *p0;
		 auto cnt0 = p0->operator*();
		// cout << (*p0) << endl;
		delete p0;

		unordered_map<string, int(*)(int, int)> m0{
			{"+", add},
			//{"%", mod}, // ERROR
			//{"/", divide()}, // ERROR
			//{"*", multiplies<int>()}, // ERROR
		};
		unordered_map<string, function<int(int, int)>> m{
			//{"+", add}, // ERROR
			{"+", [](int i, int j) { return add(i, j); }},
			{"%", mod},
			{"/", divide()},
			{"*", multiplies<int>()},
		};

		cout << endl;
	}

	void operator=(const c14& rhs) {
		cnt += rhs.cnt;
	}

	void operator=(int i) {
		cnt = i;
	}

	c14& operator++() {
		++cnt;
		return *this;
	}

	c14 operator++(int) {
		c14 c = *this;
		++*this;
		return c;
	}

	int& operator*() {
		return cnt;
	}

	// bad examples
	// 类型转换
	operator int() const { return cnt; }
	operator const int*() const { return &cnt; }
	// 用作条件的时候编译器会对 explicit 转换做自动转换
	explicit operator double() const { return cnt; }

private:
	int cnt{42};
};


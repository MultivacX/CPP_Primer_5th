#pragma once

#include <string>

using namespace std;

/*
T& T(const T&);
T& operator=(const T&);
T& T(T&&); // T& T(T&&) noexcept;
T& operator=(T&&); // T& operator=(T&&) noexcept;
T& operator=(T);

~T();
*/

class c13 {
	friend void swap(c13&, c13&);
public:
	c13() : ps(new string), i(0) {}
	~c13() { if (ps) delete ps; }
	//~c13() = delete; // ERROR: c13 obj;

	c13(const c13& rhs) : ps(new string(*rhs.ps)), i(rhs.i) {}

	c13& operator=(const c13& rhs) {
		auto new_str = new string(*rhs.ps);
		delete ps;
		ps = new_str;
		i = rhs.i;
		return *this;
	}

	// copy & swap
	c13& operator=(c13 rhs) {
		swap(*this, rhs);
		return *this;
	}

	// why noexcept : 13.6.2
	c13(c13&& c) noexcept : ps(c.ps), i(c.i) { c.ps = nullptr; }
	c13& operator=(c13&& c) noexcept {
		if (this != &c) {
			ps = c.ps;
			i = c.i;
			c.ps = nullptr;
		}
		return *this;
	}

	static c13 getObj() {
		return c13();
	}

	static void test() {
		int i = 1;
		int j = 2;
		int& k = i;
		k = j;

		// 左值持久 右值短暂
		// 左值引用 
		// 右值引用 只能绑定到一个即将要销毁的对象；也不过是某个对象的另一个名字而已

		// 变量是左值
		c13&& rr1 = getObj();
		// c13&& rr2 = rr1; // ERROR
		c13&& rr2 = std::move(rr1);
		// 此后不能使用 rr1 的值

		// 移后源对象必须可析构

		// 移动右值，拷贝左值
		// 如果没有移动构造函数，右值也被拷贝

		// 区分移动和拷贝的重载函数通常为
		// X f(const T&);
		// X f(T&&);

		c13 ff;
		(*ff.ps) = "ff";
		c13&& ffr = ff.f(100);
		c13 ffl = ff.f(101);
		ff.retFoo().f(102);
		ff.retVal().f(103);

		const c13 ff2;
		c13 ff2l = ff2.f("const c13 ff2");

		cout << endl;
	}

	c13& retFoo() { return *this; }
	c13 retVal() { return *this; }

	c13 f(int i) && { 
		cout << "c13 f(int i) &&" << i << endl; 
		this->i = i; 
		return *this; }
	c13 f(int i) const & { 
		cout << "c13 f(int i) const &" << i << endl;
		c13 ret(*this); 
		ret.i = i; 
		return ret; 
	}
	// c13 f(int i) const; // ERROR
	// c13 f(int i); // ERROR
	c13 f(string s) { 
		cout << "c13 f(string s)" << s << endl;
		*ps = s; 
		return *this; 
	}
	c13 f(string s) const { 
		cout << "c13 f(string s) const" << s << endl;
		*ps = s; 
		// delete ps; // delete const is OK
		// ps = nullptr; // ERROR
		// ++i; // ERROR
		return *this; 
	}

private:
	// int& ref;
	string* ps;
	int i;
};

void swap(c13& lhs, c13& rhs) {
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
}
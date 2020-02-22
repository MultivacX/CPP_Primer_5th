#pragma once

template<typename T>
int compare(const T& t1, const T& t2) {
	return t1 < t2;
}

// 非类型模板参数
// 模板实参必须是常量表达式
template<unsigned M, unsigned N>
int compare(const char (&r1)[M], const char(&r2)[N]) {
	return strcmp(r1, r2);
}

template<unsigned M, unsigned N>
int compare(const char(*p1)[M], const char(*p2)[N]) {
	return strcmp(*p1, *p2);
}

template<typename T> class c16t;
template<typename T> void friend_c16t(const c16t<T>& t) {}
template<typename T> class Pal;

template<typename T = int>
class c16t {
	// 内部 c16t<T> 可以省略 <T>
public:
	c16t();
	// 成员模板
	template<typename U> c16t(U u);

	void f() {}
	void useless() {}

	friend void friend_c16t<T>(const c16t<T>& t);
	friend class Pal<c16t<T>>;
	friend class Pal<T>;
	template<typename T> friend class Pal2;
	friend class Pal3;
	// firend T;

	static int si;
};

template<typename T>
c16t<T>::c16t() {

}

template<typename T>
template<typename U>
c16t<T>::c16t(U u) {

}

template<typename T>
int c16t<T>::si = 0;

template<typename T> using twin = pair<int, int>;

/* template argument deduction */

// 自动应用的类型转换
// 1. const
// 2. 数组到指针
// 3. 函数到指针

// 指定显示模板实参
// template<typename T1, typename T2, typename T3> T1 sum(T2, T3);
// auto val = sum<int>(2, 3);
// auto val = sum<int, int, int>(2, 3);

// 尾置返回
template<typename It>
auto fcn(It beg, It end) -> decltype(*beg) {
	return *beg;
}

// type transformation
template<typename It>
auto fcn2(It beg, It end) -> typename remove_reference<decltype(*beg)>::type {
	return *beg;
}

// T is int
int (*pf1)(const int&, const int&) = compare;

// 实参只能是左值
template<typename T> void f1(T&) {}
// 实参可以是右值
template<typename T> void f2(const T&) {}
template<typename T> void f3(T&& val) {
	T t = val;
	cout << val << endl;
}

template<typename T> void f4(T&& val) {
	T t = val;
	cout << val << endl;
}
template<typename T> void f4(const T& val) {
	T t = val;
	cout << val << endl;
}

template<typename F, typename T1, typename T2> 
void flip(F f, T1&& t1, T2&& t2) {
	// f(std::forward<T1>(t1), std::forward<T2>(t2)); // ERROR
	f(std::forward<T2>(t2), std::forward<T1>(t1));
}

void g1(int&& i, int& j) {
	cout << i << " " << j << endl;
}

// 重载与模板
// 非模板函数

// 可变参数模板
template<typename T, typename... Args>
void foo(const T& t, const Args& ... rest) {
	cout << sizeof...(Args) << endl;
	cout << sizeof...(rest) << endl;
}

// 模板特化不是重载

// 只能部分特化类模板

class c16 {
public:
	// 成员模板不能是虚函数
	template<typename T> void print(const T& t) {
		cout << "c16 print" << t << endl;
	}

	static void test() {
		// 函数模板推断参数类型
		compare("", "a");
		const char str0[2] = {'1', '\0'};
		const char str1[3] = { 'a', 'b', '\0' };
		compare(&str0, &str1);

		// 类模板不能推断
		// 对于一个实例化了的类模板，其成员只有在使用时才被实例化
		c16t<int> c16int; // c16t<int>::useless 没有被实例化
		c16int.f(); 

		// 类静态成员 T::static_mem
		// 类类型成员 typename T::type_mem

		// 默认模板实参
		c16t<> c16int_;

		// 成员模板
		c16 objc16;
		objc16.print(0);
		objc16.print(0.1);
		// 成员模板
		c16t<double> c16df(1.0f);

		// 模板在使用时才会实例化，所以相同的实例可能出现在多个对象文件中，这会导致实例化多个相同模板的开销太大
		// 通过显式实例化来避免这种开销
		// extern template declaration; // 实例化声明
		// template declaration;        // 实例化定义 会实例化所有成员

		// 指向引用的引用

		// 右值引用
		f3(42); // T -> int
		// 引用折叠
		int i = 0;
		f3(i); // T -> int&
		const int ci = 3;
		f3(ci); // T -> const int&

		f4(42); // T -> int
		f4(i); // T -> int&
		f4(ci); // T -> const int&

		// 右值引用不能绑定左值表达式
		// 函数参数与其他任何变量一样，都是左值表达式
		flip(g1, i, 42);
	}
};
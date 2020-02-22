#pragma once

template<typename T>
int compare(const T& t1, const T& t2) {
	return t1 < t2;
}

// ������ģ�����
// ģ��ʵ�α����ǳ������ʽ
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
	// �ڲ� c16t<T> ����ʡ�� <T>
public:
	c16t();
	// ��Աģ��
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

// �Զ�Ӧ�õ�����ת��
// 1. const
// 2. ���鵽ָ��
// 3. ������ָ��

// ָ����ʾģ��ʵ��
// template<typename T1, typename T2, typename T3> T1 sum(T2, T3);
// auto val = sum<int>(2, 3);
// auto val = sum<int, int, int>(2, 3);

// β�÷���
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

// ʵ��ֻ������ֵ
template<typename T> void f1(T&) {}
// ʵ�ο�������ֵ
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

// ������ģ��
// ��ģ�庯��

// �ɱ����ģ��
template<typename T, typename... Args>
void foo(const T& t, const Args& ... rest) {
	cout << sizeof...(Args) << endl;
	cout << sizeof...(rest) << endl;
}

// ģ���ػ���������

// ֻ�ܲ����ػ���ģ��

class c16 {
public:
	// ��Աģ�岻�����麯��
	template<typename T> void print(const T& t) {
		cout << "c16 print" << t << endl;
	}

	static void test() {
		// ����ģ���ƶϲ�������
		compare("", "a");
		const char str0[2] = {'1', '\0'};
		const char str1[3] = { 'a', 'b', '\0' };
		compare(&str0, &str1);

		// ��ģ�岻���ƶ�
		// ����һ��ʵ�����˵���ģ�壬���Աֻ����ʹ��ʱ�ű�ʵ����
		c16t<int> c16int; // c16t<int>::useless û�б�ʵ����
		c16int.f(); 

		// �ྲ̬��Ա T::static_mem
		// �����ͳ�Ա typename T::type_mem

		// Ĭ��ģ��ʵ��
		c16t<> c16int_;

		// ��Աģ��
		c16 objc16;
		objc16.print(0);
		objc16.print(0.1);
		// ��Աģ��
		c16t<double> c16df(1.0f);

		// ģ����ʹ��ʱ�Ż�ʵ������������ͬ��ʵ�����ܳ����ڶ�������ļ��У���ᵼ��ʵ���������ͬģ��Ŀ���̫��
		// ͨ����ʽʵ�������������ֿ���
		// extern template declaration; // ʵ��������
		// template declaration;        // ʵ�������� ��ʵ�������г�Ա

		// ָ�����õ�����

		// ��ֵ����
		f3(42); // T -> int
		// �����۵�
		int i = 0;
		f3(i); // T -> int&
		const int ci = 3;
		f3(ci); // T -> const int&

		f4(42); // T -> int
		f4(i); // T -> int&
		f4(ci); // T -> const int&

		// ��ֵ���ò��ܰ���ֵ���ʽ
		// ���������������κα���һ����������ֵ���ʽ
		flip(g1, i, 42);
	}
};
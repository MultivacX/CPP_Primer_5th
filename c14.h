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
	// �������� ::    .*    .    ? :

	// ʹ�����ص��������������һ�κ������� �޷���֤����������ֵ˳��

	// һ�㲻Ӧ�����ض��š�ȡ��ַ���߼��롢�߼���

	// ʹ������������һ�µĺ���

	// ��Ա
	// �����ǳ�Ա ��ֵ���±�[]������()����Ա����->
	// Ӧ���ǳ�Ա ���ϸ�ֵ
	// �ı����״̬/����������������

	// -> ֻ������Ϊ��ȡĳ������ĳ�Ա

	// �������� lambda 
	// mutable : auto f = [val] () mutable { return ++val; }

	// �ɵ��ö��󣺺���������ָ�롢lambda��bind�������˺������÷�����
	// function<T>

	// ����ĳ�Աָ��	a.*b
	// ָ��ĳ�Աָ��	a->*b

	static void test() {
		string s = "world";
		string t = s + "X";
		string u = "Y" + s; // + ���� string �ĳ�Ա

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
	// ����ת��
	operator int() const { return cnt; }
	operator const int*() const { return &cnt; }
	// ����������ʱ���������� explicit ת�����Զ�ת��
	explicit operator double() const { return cnt; }

private:
	int cnt{42};
};


#pragma once

// auto p = new string
// 1. operator new/operator new[] �����ڴ�
// 2. ���ù��캯��
// 3. ����ָ��

// �������� void *operator new(size_t, void*)

// placement new
// ��һ���ض��ġ�Ԥ�ȷ�����ڴ��ַ�Ϲ������

// �����������������ٶ��󣬵������ͷ��ڴ�

// dynamic_cast ת��ָ������ʧ�ܷ���0��ת����������ʧ���׳�bad_cast

// ������Ա����ָ��ʱ��Ҫ���ǳ�Ա�����Ƿ�������
// function mem_fn

// enum class

// nested class
// ���ͳ�Ա ��̬��Ա ��Ա���� ��Ա����

// union
// https://stackoverflow.com/questions/4788965/when-would-anyone-use-a-union-is-it-a-remnant-from-the-c-only-days

// local class

class BaseNoVirtual {
public:
	BaseNoVirtual () {}
	~BaseNoVirtual () {}

	int i;
};

class D1NoVirtual : public BaseNoVirtual {
public:
	D1NoVirtual() {}
	~D1NoVirtual() {}

	int i;
};

class c19Base {
public:
	virtual ~c19Base()	{

	}
};

class BitField {
public:
	unsigned int mode : 2;
	unsigned int modified : 1;
};

class c19 : public c19Base {
public:
	static void test() {
		c19 obj;
		obj.testDynamicCast();

		c19* pd = &obj;
		c19Base* pb = &obj;

		// c19Base*
		// ��̬����
		decltype(pb) x;
		cout << "x:" << typeid(x).name() << endl;
		auto& t = typeid(pd);
		cout << "t:" << t.name() << endl;
		auto& t0 = typeid(pb);
		cout << "t0:" << t0.name() << endl;
		// ����ʱ��ֵ
		auto& t1 = typeid(*pd);
		cout << "t1:" << t1.name() << endl;
		auto& t2 = typeid(*pb);
		cout << "t2:" << t2.name() << endl;

		c19Base* p = nullptr;
		auto& t3 = typeid(p);
		cout << "t3:" << t3.name() << endl;
		// auto& t4 = typeid(*p); // ���麯������Чָ������ʱ��ֵ: std::bad_typeid 

		if (t1 == t2) cout << "same class" << endl;

		BitField bf;
		bf.mode = 3;
		bf.modified = 0;

		volatile c19 vobj;
		vobj.change_vi();

		cout << endl;
	}

	void testDynamicCast() {
		D1NoVirtual d;
		BaseNoVirtual* pb = &d;
		// D1NoVirtual* pd = dynamic_cast<D1NoVirtual*>(pb); // ERROR

		cout << endl;
	}

	// volatile ȷ�к���������й�
	// �ϳɵĿ����� volatile ������Ч
	volatile int vi{ 0 };
	int* volatile vip;
	volatile int* ivp;
	volatile int* volatile vivp;

	void change_vi() volatile {
		++vi;
	}
};

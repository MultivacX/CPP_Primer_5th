#pragma once

// auto p = new string
// 1. operator new/operator new[] 分配内存
// 2. 调用构造函数
// 3. 返回指针

// 不能重载 void *operator new(size_t, void*)

// placement new
// 在一个特定的、预先分配的内存地址上构造对象

// 调用析构函数会销毁对象，但不会释放内存

// dynamic_cast 转换指针类型失败返回0；转换引用类型失败抛出bad_cast

// 声明成员函数指针时需要考虑成员函数是否有重载
// function mem_fn

// enum class

// nested class
// 类型成员 静态成员 成员变量 成员函数

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
		// 静态类型
		decltype(pb) x;
		cout << "x:" << typeid(x).name() << endl;
		auto& t = typeid(pd);
		cout << "t:" << t.name() << endl;
		auto& t0 = typeid(pb);
		cout << "t0:" << t0.name() << endl;
		// 运行时求值
		auto& t1 = typeid(*pd);
		cout << "t1:" << t1.name() << endl;
		auto& t2 = typeid(*pb);
		cout << "t2:" << t2.name() << endl;

		c19Base* p = nullptr;
		auto& t3 = typeid(p);
		cout << "t3:" << t3.name() << endl;
		// auto& t4 = typeid(*p); // 有虚函数，无效指针运行时求值: std::bad_typeid 

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

	// volatile 确切含义与机器有关
	// 合成的拷贝对 volatile 对象无效
	volatile int vi{ 0 };
	int* volatile vip;
	volatile int* ivp;
	volatile int* volatile vivp;

	void change_vi() volatile {
		++vi;
	}
};

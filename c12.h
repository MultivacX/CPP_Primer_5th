#pragma once

#include <memory>

using namespace std;

class c12 {
public:
	static void test() {
		// 静态内存：局部 static 对象、类 static 数据成员、定义在任何函数之外的变量
		// 栈内存
		// free store / heap

		// weak_ptr 指向 shared_ptr 所管理的对象

		shared_ptr<string> p1;
		// p1 = new string; // ERROR: 接受指针参数的智能指针构造函数是 explicit 的
		p1.reset(new string);
		p1 = make_shared<string>();
		(*p1).length();
		p1->length();
		shared_ptr<string> f(); // 函数声明
		shared_ptr<string> p2(new string);
		shared_ptr<string> p3;
		p3 = p1;

		// 使用动态内存的三个原因
		// 1 不知道需要使用多少对象 比如容器类
		// 2 不知道使用对象的准确类型 比如多态
		// 3 需要在多个对象间共享数据 

		int* pi1 = new int; // 默认初始化 2.2.1，内置类型或组合类型的对象的值是未定义的
		int* pi2 = new int(); // 值初始化为 0

		const int* pci = new const int;
		auto pic_tmp = pci;
		delete pci;
		pci = nullptr;
		// pic_tmp : dangling pointer
		const int* pci0 = new const int();
		int* pci00 = const_cast<int*>(pci0);
		*pci00 = 2;
		const int* pci2 = new int();
		int* pci02 = const_cast<int*>(pci2);
		*pci02 = 2;
		pci2 = nullptr;

		int* p4 = new (nothrow) int; // placement new; 分配失败返回 nullptr

		// release 放弃控制权
		// reset 释放当前指向的对象
		unique_ptr<string> up0;
		up0.reset(new string);
		auto up0_raw = up0.release();
		delete up0_raw;

		// 可以拷贝或赋值一个将要被销毁的 unique_ptr：比如返回一个 unique_ptr

		// 为什么智能指针的删除器不一样？

		// weak.lock() 返回对应的 shared_ptr 或者 空shared_ptr

		int* pia = new int[10]{1, 2, 3, 4};
		int pia0 = *pia;
		int pia1 = *(pia + 1);
		delete[] pia;
		unique_ptr<int[]> upia(new int[5] {1, 2, 3, 4});
		upia.reset();
		// shared_ptr 不支持 T[]
		shared_ptr<int> spia(new int[5]{ 1, 2, 3, 4 }, [](int* p) { delete[] p; });
		spia.reset();

		// new 1.分配内存 2.构造对象
		// delete 1.析构对象 2.释放内存

		cout << "c12" << endl;
	}
};
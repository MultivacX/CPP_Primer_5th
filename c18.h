#pragma once

// stack unwinding
// ���캯��
// ��������
// noexcept

// ���ڽ���������ʵ�εĺ�����˵�������ֲ��ҽ���ʵ���������������ռ����

// virtual destructor
// Effiective C++ 3rd edition. 
//     Item 7: Declare destructors virtual in polymorphic base classes.
// C++ Coding Standards : 101 Rules, Guidelines, and Best Practices 
//     Item 50 : Make base class destructors public and virtual, or protected and nonvirtual.
// https://www.zhihu.com/question/41538182

// ���ؼ̳� ��Ա������
// ��̳� ����� ��ŵԸ�⹲�������


void recoup(int) noexcept {}
void coup(int) {}

void test_noexcept() {
	// ERROR: typedef void (*FuncType0)(int) noexcept;
	typedef void (*FuncType0)(int);
	FuncType0 p0 = &recoup;

	// ERROR: using FuncType1 = void (*)(int) noexcept;
	using FuncType1 = void (*)(int);
	FuncType1 p1 = &recoup;

	void (*p2)(int) noexcept;
	p2 = &recoup;
	// ERROR: p2 = &coup; // p2 is noexcept but coup is NOT noexcept

	void (*p3)(int);
	p3 = &recoup; // p3 is NOT noexcept
	p3 = &coup;
}

class c18Base {
public:
	virtual void f1(int) noexcept {}
	virtual void f2(int) noexcept(false) {}
	virtual void f3(int) {}
};

class c18
: public c18Base {
public:
	c18(vector<int>& v) 
	try :
	data(new vector<int>(v)) {

	} catch (const std::bad_alloc & e) { 
		// 
	} catch (...) {

	}

	vector<int>* data;

	void g() noexcept {} // void g() noexcept(true) {}
	void f() noexcept(noexcept(g())) {} // noexcept(g()) == true, void f() noexcept(true) {}

	virtual void f1(int) noexcept {} // ERROR: virtual void f1(int) {}
	virtual void f2(int) noexcept(true) {} // virtual void f2(int) noexcept(false) {}
	virtual void f3(int) noexcept {} // virtual void f3(int) {}
};
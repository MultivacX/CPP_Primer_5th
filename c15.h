#pragma once

// ��Ԫ ��Ա
// ֱ�ӻ���/������
// ��Ԫ��ϵ���ܴ���Ҳ���ܼ̳�

// ��̬���� ��̬����

// ���ֲ����������ͼ��

// �̳еĹ��캯�� using

class c15_base {
public:
	virtual ~c15_base() {}

	virtual void fv() {}
	virtual c15_base* fv1() { return this; }
	virtual int fd(int i = 42) { return i; }
	virtual int fd(string s) { return 1; }

	void fh() {}

protected:
	int bi;

private:
	virtual void fv_private() {}
	int pri;
};

class c15_abstract_base {
public:
	virtual void fpv() = 0;
	virtual void fpv1() = 0;
};

void c15_abstract_base::fpv1() {}

class c15_no_derive final {

};

class c15_derive : public c15_base, c15_abstract_base {
public:
	// virtual
	virtual void fv() { c15_base::fv(); }
	//void fv() {}
	//void fv() override {}
	//virtual void fv() override {}
	virtual c15_derive* fv1() override { return this; }
	// ���������ϣ�����е����ذ汾���������ɼ�����Ҫô�������а汾��Ҫô��������
	using c15_base::fd; // �������а汾�����ֻ���� fd(int) �� fd(string) ���ɼ�
	int fd(int i = 43) { return i; } // �����ض��汾

	// pure virtual
	void fpv() {}
	void fpv1() {}

	// hide
	// void fh() {}
	void fh(int hide_too) {}

	// ������ĳ�Ա����Ԫֻ��ͨ����������������ʻ�����ܱ�����Ա
	// void f_protected(c15_base& c) { cout << c.bi << endl; } // ERROR
	void f_protected(c15_derive& c) { cout << c.bi << endl; }

	virtual void fv_private() override {}
	// virtual void fv_private() override { c15_base::fv_private();  } // ERROR
};

class c15_derive_protected : protected c15_base {
public:
	void f() { cout << bi << endl; }
};

class c15_derive_private : private c15_base {
public:
	using c15_base::bi;
	// using c15_base::pri; // ERROR
	void f() { 
		cout << bi << endl; 

		c15_derive_private derive_private;
		c15_base* p_b2derive_private = &derive_private;
		p_b2derive_private->fv();
	}
	friend void f_private();
};

void f_private() {
	c15_derive_private derive_private;
	c15_base* p_b2derive_private = &derive_private;
	p_b2derive_private->fv();
}

class c15 {
public:
	static void test() {
		c15_base base;
		c15_derive derived;
		c15_base& rb2d = derived;
		c15_base* pb2d = &derived;
		// ָ��������Ļ���ָ������ã����ú�������ʹ�û����ж����Ĭ��ʵ��
		cout << base.fd() << ", " << derived.fd() << ", " << pb2d->fd() << endl;
		derived.fd("");

		c15_derive_protected derive_protected;
		// c15_base* p_b2derive_protected = &derive_protected; // ERROR
		// derive_protected.fv(); // ERROR
		// p_b2derive_protected->fv(); // ERROR
		c15_derive_private derive_private;
		// c15_base* p_b2derive_private = &derive_private; // ERROR
		// derive_private.fv(); // ERROR
		// p_b2derive_private->fv(); // ERROR
		// ������ֻ��Ϊ��Щ�����Է��ʵ������ṩ using ����
		derive_private.bi;
	}
};
#pragma once

#include <memory>

using namespace std;

class c12 {
public:
	static void test() {
		// ��̬�ڴ棺�ֲ� static ������ static ���ݳ�Ա���������κκ���֮��ı���
		// ջ�ڴ�
		// free store / heap

		// weak_ptr ָ�� shared_ptr ������Ķ���

		shared_ptr<string> p1;
		// p1 = new string; // ERROR: ����ָ�����������ָ�빹�캯���� explicit ��
		p1.reset(new string);
		p1 = make_shared<string>();
		(*p1).length();
		p1->length();
		shared_ptr<string> f(); // ��������
		shared_ptr<string> p2(new string);
		shared_ptr<string> p3;
		p3 = p1;

		// ʹ�ö�̬�ڴ������ԭ��
		// 1 ��֪����Ҫʹ�ö��ٶ��� ����������
		// 2 ��֪��ʹ�ö����׼ȷ���� �����̬
		// 3 ��Ҫ�ڶ������乲������ 

		int* pi1 = new int; // Ĭ�ϳ�ʼ�� 2.2.1���������ͻ�������͵Ķ����ֵ��δ�����
		int* pi2 = new int(); // ֵ��ʼ��Ϊ 0

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

		int* p4 = new (nothrow) int; // placement new; ����ʧ�ܷ��� nullptr

		// release ��������Ȩ
		// reset �ͷŵ�ǰָ��Ķ���
		unique_ptr<string> up0;
		up0.reset(new string);
		auto up0_raw = up0.release();
		delete up0_raw;

		// ���Կ�����ֵһ����Ҫ�����ٵ� unique_ptr�����緵��һ�� unique_ptr

		// Ϊʲô����ָ���ɾ������һ����

		// weak.lock() ���ض�Ӧ�� shared_ptr ���� ��shared_ptr

		int* pia = new int[10]{1, 2, 3, 4};
		int pia0 = *pia;
		int pia1 = *(pia + 1);
		delete[] pia;
		unique_ptr<int[]> upia(new int[5] {1, 2, 3, 4});
		upia.reset();
		// shared_ptr ��֧�� T[]
		shared_ptr<int> spia(new int[5]{ 1, 2, 3, 4 }, [](int* p) { delete[] p; });
		spia.reset();

		// new 1.�����ڴ� 2.�������
		// delete 1.�������� 2.�ͷ��ڴ�

		cout << "c12" << endl;
	}
};
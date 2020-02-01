#pragma once

#include <vector>
#include <list>
#include <unordered_set>

using namespace std;

class c09 {
public:
	void static test() {
		// deque []
		// list : double linked list

		// https://stackoverflow.com/questions/6954906/does-c11-allow-vectorconst-t

		const vector<int> cv{ 10, 11, 12 };
		// cv[0] = 5; // ERROR
		// cv.push_back(0); // ERROR
		int cv0 = cv[0];
		
		// vector<const int> ce{ 10, 11, 12 }; // ERROR
		vector<const int*> cep{ &cv0 };
		// vector<const int* const> cecp{ &cv0 }; // ERROR
		auto cit = cep.cbegin();
		++cit;

		// ���� ��ֵ assign
		list<int> l{ 1, 2, 3 };
		vector<int> vl(l.begin(), l.end());
		vector<int> v2 = vl;
		// vector<double> v3 = vl; // ERROR
		vector<double> v4(l.begin(), l.end());
		vector<double> v5(v2.begin(), v2.end());
		vector<double> v6;
		v6.assign(l.begin(), l.end());

		// swap
		// ���� string����������ָ�롢���ò���ʧЧ���������ڲ�ͬ��������

		// vector/deque/string ����Ԫ�ػᵼ�µ�������ָ�롢����ʧЧ
		// ɾ��Ԫ�������ʧЧȡ���ڱ�ɾ����Ԫ��λ��

		// ����Ԫ���ǿ���

		// emplace ��������ֱ�ӹ���Ԫ��

		// resize ��ɾ����������Ӧ��������Ԫ��

		// to_string sto*

		unordered_multiset<int> ms{2, 2, 2};
		// ms.erase(2); // remove all 2
		ms.erase(ms.begin()); // remove the 1st 2

		cout << endl;
	}
};
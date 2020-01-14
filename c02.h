#ifndef CPPPRIMER_C02_H
#define CPPPRIMER_C02_H

#include <iostream>

extern int c02i;
int c02i = 5;

extern int c02j = 5;

class c02 {
public:
    static void test() {
        /*0*/
        // -42 不是字面量

        /*1*/
        //列表初始化
        double d = 3.1415926;
        //int a{d}; // error

        /*2*/
        //int i; // 不会初始化，值未定义
        //std::cout << i << std::endl;

        /*3*/
        // error
        // c02i = 5;
        // extern int c02j = 5;

        /*4*/
        // 静态类型语言，在编译阶段检查类型

        const int &r1 = 42;
        // const int *p1 = 42;
        double d1 = 3.14;
        const int &r2 = d1;
        // int &r2 = d1;
        int i1 = 0;
        const int &r3 = i1;
        i1 = 100;
        std::cout << r3 << std::endl;

        // 指针是对象 引用是别名
        // top-level const
        // low-level const
        // constexpr int *p == int *const p
        int v = 99;
        int *const p = &v;
        auto p0 = p;
        *p0 = 20;

        typedef char *pstring;
        const pstring cstr = 0; 
        // == char* const cstr
        // != const char *cstr = 0;

        // auto : ignore top-level const or &

        // decltype(*p0) *p0 是解引用，此处类型是 int&
        // decltype((var)) 此处是引用
    }

    static int tc;
    static int testConst() {
        return tc;
    }

    void testConst(int i) {
        const int j = i;
    }
};

int c02::tc = 0;
const int tc = c02::testConst();

#endif //CPPPRIMER_C02_H

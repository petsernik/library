#include<iostream>
using namespace std;
struct A {
    struct B {
        int x;
    };
    B *b = {};
    A() {
        b = new B{ 10 };
    }
    void print() {
        cout << b->x << "\n";
    }
};

//struct A::B {
//    int x;
//};

int main()
{
    A a;
    a.print();
}

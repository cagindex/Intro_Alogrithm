#include<iostream>
using namespace std;

class A{
    public:
        int x;
        A(int x_):x(x_){cout << x << "constructor called " << endl;}
        A(const A& a){
            x = 2 + a.x;cout << "copy called" << endl;
        }
        // A(const A&& a){
        //     cout << "move constructor called" << endl;
        // }
        ~A(){ cout << x << "destructor called" << endl;}

        // A& operator=(const A& a){
        //     cout << "operator = called" << endl;
        //     memcpy(this, &a, sizeof(a));
        //     return *this;
        // }
};

A f(){ A b(10); return b;}

int main(){
    A a(1);
    a = f();
    A b(f());

    return 0;
}

/**
 * 1 g++使用了rvo优化导致f()中return b并没有调用copy;
 * 2 a = f()调用系统默认的=赋值操作符;
 * 3 move constructor
*/
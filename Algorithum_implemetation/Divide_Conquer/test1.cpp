#include<iostream>
using namespace std;

struct st{
    int x;

    st(int x_):x(x_){cout << "constructor called" << endl;}
    st(const st& s):x(s.x){cout << "copy constructor called" << endl;}
    st(st&& s):x(s.x){cout << "move constructor called" << endl;}
    ~st(){cout << "Destructor called" << endl;}
};

st testtest(){
    struct st tmp(2);
    return tmp;
}
/**
 * pesudo code:
 * struct st tmp;
 * __inner_tmp = tmp;
 * return;
 * destructor tmp;
*/

int main(){
    struct st a(2);
    struct st b = st(2);
    struct st c = testtest();
    return 0;
}

#include<iostream>
using namespace std;

class a{
    private:
        int s;
        int* p;
    public:
        a(){
            cout << "a() called" << endl;
            p = new int;
            cout << "p: " << p << endl;
        }

        ~a(){
            cout << "~a() called" << endl;
            //delete p; // 不能delete同一个内存地址2遍
        }
};

int* testtest(){
    int* a = new int[10];
    cout << a << endl;
    return a;
}

a ttt(){
    return a();
}

int main(){
    a test1;
    //a test2 = test1;
    //这里因为是浅copy所以会导致两边的p都指向同一个位置
    //本来是没什么事的，但是main结束后，会调用析构函数，在析构函数～a里面，我们delete了p，首先会delete test2，这个时候p地址已经delete了
    //该程序对此地址没有访问和执行权限，之后会delete test1对p，因为是浅拷贝，test1 的p也是这个地址，此时程序没有这个地址对权限，所以报错.
    a test2 = ttt();
    return 0;
}
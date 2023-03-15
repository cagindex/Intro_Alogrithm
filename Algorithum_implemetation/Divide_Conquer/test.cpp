#include<iostream>
using namespace std;


int main(){
    int a = 3;
    int& b = a;
    const int* p1 = &a;
    int* const p2 = &a;
    b = 2;
    return 0;
}
// int main(){
//     int a = 0;
//     const int a1 = 20;
//     const int &&b1 = a + a1; // 两个左值相加的结果会返回，返回的值是一个右值！！
//     return 0;
// }
// int main(){
//     int a = 3;
//     //常指针
//     const int* p = &a;
//     //指针常量
//     int* const pp = &a;
//     cout << p << endl;
//     cout << *p << endl;
//     return 0;
// }
// int main(){
//     int a = 5;
//     int& b = a;
//     cout << "The a position at : " << &a << endl;
//     cout << "The b position at : " << &b << endl;
//     return 0;
// }
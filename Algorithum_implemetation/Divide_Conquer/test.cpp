#include<iostream>
using namespace std;

int ss(){
    bool a = true;
    return a<<2;
}

typedef struct ARR{
    int * a;
    int len;
}arr;

arr t(){
    int* a = new int[5];
    int s = 5;
    arr bb;
    bb.a = a;
    bb.len = s;
    return bb;
}

int main(){
    for(int i = 0; i < 5 ; i++){
        cout << rand()%2 << endl;
    }
    cout << "endl" << endl;
    bool a = true;
    cout << (a == 0) << endl;
    cout << ss() << endl;

    cout << "ARR test" << endl;
    arr s = t();
    cout << s.a[0] << endl;
    return 0;
}
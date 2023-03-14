#include<iostream>
using namespace std;

int ss(){
    bool a = true;
    return a<<2;
}

int main(){
    for(int i = 0; i < 5 ; i++){
        cout << rand()%2 << endl;
    }
    cout << "endl" << endl;
    bool a = true;
    cout << (a == 0) << endl;
    cout << ss() << endl;
    return 0;
}
#include<iostream>
#include<typeinfo>
using namespace std;

struct tt{

    int a;
    double b;

    tt():a(10),b(1.11){cout << "structor constructor called at: " << this << endl;}

    tt(const tt& c){ //为什么这个const这么重要？
        cout << "struct copy constructor called at: " << this << endl;
        a = c.a;
        b = c.b;
    }

    ~tt(){cout << "structor destructor called at: " << this << endl;}
};

class class_tt{
    public:
        int a;
        double b;

        class_tt():a(10),b(1.11){cout << "class constructor called at: " << this << endl;}

        class_tt(const class_tt& c){ // 为什么这个const这么重要?
            cout << "Class copy constructor called at: " << this << endl;
            a = c.a;
            b = c.b;
        }

        ~class_tt(){cout << "Class destructor called at: " << this << endl;}
};

tt rere(){
    struct tt a;
    cout << "In rere function a at: " << &a << endl;
    return a;
}

class_tt class_re(){
    class_tt s;
    cout << "In class_re function s at: " << &s << endl;
    return s;
}

int main(){
    struct tt c = rere();
    cout << "In main function c at: " << &c << endl;
    
    class_tt cc = class_re();
    cout << "In main function cc at: " << &cc << endl;
    return 0;
}

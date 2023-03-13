#include<iostream>
using namespace std;

class chip{
    private:
        bool quality;
    public:
        int tmp;
        chip():quality(false),tmp(3){}

        int Check(chip other){
            /**
             * return int for good or not
             * there are four situations : 00 01 10 11
             * the first bit stands for the quality of the this chip
             * the second bit stands for the qulity of the tested chip
             * but it may useless or may not allowed to distinguish this.
            */
            int thisReport, otherReport;
            cout << this->quality << endl;
            return 1;
        }
};

int main(){
    chip a;
    a.Check(chip());
    cout << a.tmp << endl;
    cout << (void *)a << endl;
    return 0;
}
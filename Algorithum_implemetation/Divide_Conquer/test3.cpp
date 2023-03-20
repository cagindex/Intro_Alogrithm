#include<iostream>
using namespace std;

class A{
	public:
		int x;
		A(int x_):x(x_){}

		int operator^(const A& othera){
			return x*(othera.x);
		}
};

int main(){
	A a1(3);
	int res = a1^A(4);

	int t = 3;
	cout << t/4 << endl;
	cout << t%4 << endl;
	cout << sizeof(long long) << endl;
	return 0;
}

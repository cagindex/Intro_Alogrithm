#include<iostream>
using namespace std;

int main(){
	int a = 3;
	int a2 = 4;
	int& b = a;
	b = 3;
	int* const p = &a;
	const int* s = &a;
	*s = 3;
	*p = 3;
	p = &a2;
	return 0;
}

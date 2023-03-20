#include<iostream>
using namespace std;

class load{
	public:
		load(){}
		load(int va, int wei):value(va),weight(wei){}
		int GetValue() const {return value;}
		int GetWeight() const {return weight;}
		void ChangeValue(int i) {value = i;}
		void ChangeWeight(int i) {weight = i;}
	private:
		int value;
		int weight;
};

load* GetInput(int num){
	int value, weight;
	load* res = new load[num];
	for(int i = 0; i < num; i++){
		cin >> value >> weight;
		res[i].ChangeValue(value);
		res[i].ChangeWeight(weight);
	}
	return res;
}

void Dp_Algorithm(load* loadsPtr, int** dp, short** dpNote, int num, int weight){
	/**
	 * Fn(0) = 0; F0(k) = 0
	*/
	int i, j, a1, a2;
	for(i = 0; i < num + 1; i++){
		dpNote[i][0] = 0;
		dp[i][0] = 0;
	}
	for(i = 0;i < weight + 1; i++){
		dpNote[0][i] = 0;
		dp[0][i] = 0;
	}

	/**
	 * dp from buttom to up
	*/
	for(i = 1; i < num + 1; i++){
		for(j = 1; j < weight + 1; j++){
			a1 = dp[i-1][j];
			if((j - loadsPtr[i-1].GetWeight()) >= 0){
				a2 = dp[i-1][j-loadsPtr[i-1].GetWeight()] + loadsPtr[i-1].GetValue();
			}
			else{
				a2 = 0;
			}

			if(a1 > a2){
				dp[i][j] = a1;
				dpNote[i][j] = 0;
			}
			else{
				dp[i][j] = a2;
				dpNote[i][j] = 1;
			}
		}
	}
}

void print(int** dp, int num, int weight){
	int i, j;
	for(i = 0; i < num + 1; i++){
		for(j = 0; j < weight + 1; j++){
			printf("%d  ", dp[i][j]);
		}
		printf("\n");
	}
}

void print(short** dp, int num, int weight){
	int i, j;
	for(i = 0; i < num + 1; i++){
		for(j = 0; j < weight + 1; j++){
			printf("%d  ", dp[i][j]);
		}
		printf("\n");
	}
}

void print_res(int** dp, short** dpNote, int num, int weight, load* loadsPtr){
	int i, j;
	i = num;
	j = weight;

	while((i > 0) && (j > 0)){
		if(dpNote[i][j] == 1){
			printf("%d ", i);
			j -= loadsPtr[i - 1].GetWeight();
		}
		i --;
	}
	printf("\n");
}

int main(){
	int num, weight, i;
	cin >> num >> weight;
	load* loadsPtr = GetInput(num);
	int** dp = new int* [num+1];
	short** dpNote = new short* [num+1];
	for(i = 0; i < num + 1; i++){
		dp[i] = new int[weight + 1];
		dpNote[i] = new short[weight + 1];
	}

	Dp_Algorithm(loadsPtr, dp, dpNote, num, weight);
	print(dp, num, weight);
	cout << " . " << endl;
	print(dpNote, num, weight);
	cout << "print result" << endl;
	print_res(dp, dpNote, num, weight, loadsPtr);
	return 0;
}

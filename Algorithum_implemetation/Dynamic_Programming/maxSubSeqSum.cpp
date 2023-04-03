#include<iostream>
using namespace std;

int maxSubSeqSum(int* arr, int length){
    int i, maxRes = 0;
    int* dp = new int[length];
    memset(dp, 0, sizeof(int)*length);

    dp[0] = arr[0];
    for (i = 1; i < length; i++){
        dp[i] = (arr[i] > (arr[i] + dp[i-1])) ? arr[i] : (arr[i] + dp[i-1]);
    }
    for (i = 0; i < length; i++){
        maxRes = (maxRes < dp[i]) ? dp[i] : maxRes;
    }
    return maxRes;
}

int main(){
    int length, maxSum, n = 0;
    cin >> length;
    int* arr = new int[length];
    while (n < length){
        cin >> arr[n];
        n++;
    }
    
    maxSum = maxSubSeqSum(arr, length);
    cout << "The max sub sum is : " << maxSum << endl;
    return 0;
}
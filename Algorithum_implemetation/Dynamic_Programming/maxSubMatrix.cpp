#include<iostream>
using namespace std;

int max(int a, int b){ return (a > b) ? a : b; }
int sum(int** arr, int i, int j, int k){
    int res = 0;
    int index;
    for (index = j; index <= k; index ++){
        res += arr[i][index];
    }
    return res;
}
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

int maxSubMatrix(int** arr, int rowLength, int columnLength){
    int i, j, k, ans = 0;
    int* res = new int[columnLength];
    int** dp = new int*[rowLength];
    for(i = 0; i < rowLength; i++){
        dp[i] = new int[columnLength];
        memcpy(dp[i], arr[i], sizeof(int)*columnLength);
    }

    for(i = 1; i < rowLength; i++){
        for(j = 0; j < columnLength; j++){
            dp[i][j] += dp[i-1][j];
        }
    }

    for(i = 0; i < rowLength; i++){
        for(j = i; j < rowLength; j++){
            for(k = 0; k < columnLength; k++){
                if (0 == i){
                    res[k] = dp[j][k]; 
                }
                else{
                    res[k] = dp[j][k] - dp[i-1][k];
                }
            }
            int midValue = maxSubSeqSum(res, columnLength);
            ans = max(ans, midValue);
        }
    }

    return ans;
}

int main(){
    int rowLength, columnLength;
    cin >> rowLength >> columnLength;
    int n = 0, m = 0, contain;

    int** arr = new int*[rowLength]; 
    for(int i = 0; i < rowLength; i++){
        arr[i] = new int[columnLength];
    }

    n = 0;
    while(n < rowLength){
        m = 0;
        while(m < columnLength){
            cin >> contain;
            arr[n][m] = contain;
            m++;
        }
        n++;
    }

    int maxSub = maxSubMatrix(arr, rowLength, columnLength);
    cout << "The max Sub maxtrix is: " << maxSub << endl;
    return 0;
}
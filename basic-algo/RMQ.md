
### 描述

RMQ, 区间最大值/最小值查询。

### 方法

RMQ是一种利用动态规划思想解决区间最值问题的方法， 其中dp[i][j]表示从i开始长度为2^j的区间的最值，

而长度为2^j的区间又可分为两半，[i, i + 2^(j-1) - 1] 和 [i + 2^(j-1), i + 2^j - 1], 长度都为2^(j-1)

那么转移方程为 dp[i][j] = max(dp[i][j-1], dp[i + 2^(j-1)][j-1]);

查询[l,r]时，先求出覆盖[l,r]区间的最小幂k，例如[2,8], k = 2， 即将[2,8]分为长度相等都为2^k两部分

那么查询结果为 max(dp[l][k], dp[l + 2^k - 1][k]).

### 模板

``` c++

const int N = 1e5+10;
int a[N], n;

// ##### RMQ

int dp[N][20];

void initRMQ(){
    for(int i=0; i<n; i++) dp[i][0] = a[i];
    for(int j=1; j<=20; j++){
        for(int i=0; i<n; i++){
            if(i + (1<<(j)) - 1 < n){
                dp[i][j] = max(dp[i][j-1], dp[i + (1<<(j-1))][j-1]);
            }
        }
    }
}

int RMQ(int l, int r){
    int k = 0;
    while( (1 << (k+1)) < (r - l + 1)) k++;
    return max(dp[l][k], dp[r - (1 << (k)) + 1][k]);
}

```

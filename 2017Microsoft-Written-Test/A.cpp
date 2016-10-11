/*
题目链接：http://hihocoder.com/problemset/problem/1399
给一个数列，若相邻两个数和为奇数则可以删除这两个数，问最后剩下最少数的个数。

分析：
最后剩下的结果肯定都是奇数或全部都是偶数！
所以答案就是奇数偶数个数的绝对值。
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <stack>
#include <algorithm>
#include <functional>
#include <cmath>
#include <bitset>
using namespace std;
#define MP make_pair
#define FI first
#define SE second

const int inf = 1 << 28;
const int maxn = 2e6+10;

int n, a[maxn];
int ans;

int main(){

    while(~scanf("%d", &n)){
        for(int i=0;i<n;i++) {
            scanf("%d", &a[i]);
            if(a[i] & 1) ans ++;
            else ans--;
        }

        cout << abs(ans) << endl;
    }
    return 0;
}


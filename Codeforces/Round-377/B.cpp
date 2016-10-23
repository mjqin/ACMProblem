// 让一个序列的所有相邻数的和都等于K 
// http://codeforces.com/contest/732/problem/B
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

int a[510];

int main(){
    int n, k;
    cin >> n >> k;
    for(int i=0;i<n;i++){
        scanf("%d", &a[i]);
    }
    int sum = 0;
    for(int i=1;i<n;i++){
        if(a[i] + a[i-1] < k){
            sum += (k - a[i] - a[i-1]);
            a[i] += (k - a[i] - a[i-1]);
        }
    }

    printf("%d\n", sum);
    for(int i=0;i<n;i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}

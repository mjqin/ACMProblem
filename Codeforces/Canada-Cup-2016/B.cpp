// http://codeforces.com/contest/725/problem/B
// 飞机上送餐问题
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

long long n;
char c;
int t[] = {4, 5, 6, 3, 2, 1};

int main(){
    scanf("%I64d%c", &n, &c);
    long long ans = ( n / 4) * 16;
    n %= 4;
    if(n == 0){
        ans -= 16;
        cout << ans + 7 + t[c - 'a'] << endl;
        return 0;
    }
    if(n == 1 || n == 3) {
        cout << ans + t[c - 'a'] << endl;
        return 0;
    }
    if(n == 2){
        cout << ans + 7 + t[c - 'a'] << endl;
    }
    return 0;
}

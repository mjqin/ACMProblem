// http://codeforces.com/contest/725/problem/A
// 
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

char s[maxn];

int main(){
    int n;
    cin >> n;
    scanf("%s", s);
    int ans = 0;
    for(int i=0;i<n;i++){
        if(s[i] == '<') ans++;
        else break;
    }
    for(int i=n-1;i>=0;i--){
        if(s[i] == '>') ans++;
        else break;
    }
    cout << ans << endl;
    return 0;
}

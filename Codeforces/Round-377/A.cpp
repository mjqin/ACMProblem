// http://codeforces.com/contest/732/problem/A
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

int main(){
    int k, r;
    cin >> k >> r;
    int ans;
    for(ans=1; 1 ;ans++){
        if(ans * k % 10 == r || (ans * k % 10 == 0)) break;
    }
    cout << ans << endl;
}

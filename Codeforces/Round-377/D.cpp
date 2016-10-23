// http://codeforces.com/contest/732/problem/D
// 有n们课程需要考试，每门课只能在特定的某些天考才能通过，并且每门课都需要一定的复习时间，求最小通过所有考试的时间。
// 单调性：时间越长能通过的课程数肯定越多。所以二分时间即可。
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

const int N = 1e5+10;
int n, m;
int d[N], a[N];
map<int,int> mp;

bool check(int k){
    mp.clear();
    int cnt = 0;
    for(int i=k;i>=1;i--){
        if(d[i] && mp[d[i]] == 0) {
            mp[d[i]] = i;
            cnt ++;
        }
    }
    if(cnt < m) return false;

    int sum = 0;
    for(int i=1;i<=k;i++){
        if(mp[d[i]] == i) {
            if(sum >= a[d[i]]) sum -= a[d[i]];
            else return false;
        }
        else sum++;
    }
    return true;
}

int main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++) scanf("%d", &d[i]);
    for(int i=1;i<=m;i++) scanf("%d", &a[i]);
    int l=1, r = n+1;
    while( l < r){
        int mid = (l + r) >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    if(l == n+1) printf("-1\n");
    else printf("%d\n", l);
    return 0;
}

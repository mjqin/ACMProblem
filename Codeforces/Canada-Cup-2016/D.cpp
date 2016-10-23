// http://codeforces.com/contest/725/problem/D
// 贪心模拟。

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
int n;
long long t[maxn], w[maxn];

struct Node{
    long long w, t;
    Node(long long a=0, long long b=0){
        t = a;
        w = b;
    }
    friend bool operator < (Node a, Node b){
        if( (a.w - a.t) == (b.w - b.t)) return a.t > b.t;
        return (a.w - a.t) > (b.w - b.t);
    }
}node[maxn];

priority_queue<pair<long long,long long> > q1;
priority_queue<Node> q2;

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++) {
        scanf("%I64d%I64d", &node[i].t, &node[i].w);
        if(i == 0) continue;
        if(node[i].t > node[0].t){
            q2.push(node[i]);
        }else{
            q1.push(MP(node[i].t, node[i].w));
        }
    }

    int ans = q2.size() + 1;
    long long sum = node[0].t;
    Node tmp;
    pair<long long, long long> pa;
    while(!q2.empty() && sum > 0){
        tmp = q2.top();
        q2.pop();
       // cout << "mv:" << tmp.t << " " << tmp.w << endl;
        sum -= (tmp.w - tmp.t + 1);
        //cout << "sum:" << sum << endl;
        if(sum < 0) break;
        while(!q1.empty()){
            pa = q1.top();
            if(sum < pa.FI){
                q2.push(Node(pa.FI, pa.SE));
                q1.pop();
            }else break;
        }
        //cout << "q2:" << q2.size() << endl;
        ans = min(ans, (int)q2.size() + 1);
    }

    cout << ans << endl;
    return 0;
}

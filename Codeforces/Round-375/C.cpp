/*
给n首歌，和每首歌表演的乐队序号，现在要改变一些歌的表演乐队，使得前m个乐队中表演歌曲数目的最小值最大。
输出最小值和改变次数。

分析：
最小值ans1 = n / m
改变策略和以贪心，每次将当前表演歌曲数>ans1的乐队变为当前表演数目最小的乐队。
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <functional>
#include <cmath>
#include <bitset>
using namespace std;

const int inf = 1 << 28;
const int maxn = 10010;

int n, m;
int a[maxn], mp[maxn];
int ans1, ans2;

struct Node{
    int t, v;
    Node(int a=0, int b=0){
        t = a;
        v = b;
    }
    friend bool operator < (Node a, Node b){
        return a.t > b.t;
    }
};

int main(){
    scanf("%d%d", &n, &m);
    for(int i=0;i<n;i++) {
        scanf("%d", &a[i]);
        if(a[i] <= m) mp[a[i]]++;
    }
    ans1 = n / m;
    priority_queue<Node> que;
    Node node;
    for(int i=1;i<=m;i++) que.push(Node(mp[i], i));
    for(int i=0;i<n;i++){
        if(que.top().t == ans1) break;
        if(a[i] > m || (a[i] <= m && mp[a[i]] > ans1)) {
            node = que.top();
            que.pop();
            if(a[i] <= m) mp[a[i]]--;
            a[i] = node.v;
            node.t ++;
            mp[node.v]++;
            que.push(node);
            ans2++;
        }
    }

    printf("%d %d\n", ans1, ans2);
    for(int i=0;i<n;i++) printf("%d%c", a[i], i == n-1 ? '\n' : ' ');
    return 0;
}

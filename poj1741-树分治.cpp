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

int n, k;
int head[maxn], cnt;
bool vis[maxn];

vector<int> V1, V2;
int sum[maxn], Max[maxn], tot;

struct Edge{
    int to, next, w;
}e[maxn<<1];

void init(){
    cnt = 0;
    memset(head, -1, sizeof(head));
    memset(vis, false, sizeof(vis));
}

// 前向星加边
void addEdge(int u, int v, int w){
    e[cnt].to = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt++;
}

// 求出以u为根节点所有子树的大小，以及最大子树的节点数
void dfs1(int u, int fa){
    sum[u] = 1;
    Max[u] = 0;
    tot++;
    for(int i=head[u]; i!=-1; i=e[i].next){
        int v = e[i].to;
        if(v == fa || vis[v]) continue;
        dfs1(v, u);
        sum[u] += sum[v];
        Max[u] = max(Max[u], sum[v]);
    }
    V1.push_back(Max[u]);
    V2.push_back(u);
}

// 求重心
int getWP(int u){
    V1.clear(), V2.clear();
    tot = 0;
    dfs1(u, -1);
    int Min = inf, ans, tmp;
    for(int i=0;i<V1.size();i++){
        tmp = max(V1[i], tot - sum[V2[i]]);
        if(tmp < Min){
            ans = V2[i];
            Min = tmp;
        }
    }
    return ans;
}

// 求出所有点到u的距离，保存到V1中
void getDis(int u, int fa, int d){
    V1.push_back(d);
    for(int i=head[u]; i!=-1; i=e[i].next){
        int v = e[i].to;
        if(v == fa || vis[v]) continue;
        getDis(v, u, d + e[i].w);
    }
}

// 计算以u为根节点到父节点距离为d满足条件的节点对数
int calc(int u, int d){
    int ret = 0;
    V1.clear();
    getDis(u, -1, d);
    // 求数列中两点值之和小于固定值K的点对数，采用两端逼近的方法
    sort(V1.begin(), V1.end());
    int l=0, r=V1.size()-1;
    while(l < r){
        if(V1[l] + V1[r] <= k){
            ret += (r - l);
            l++;
        }else r--;
    }
    return ret;
}

// 先计算以u为根节点所有满足条件的点对数，然后减去在同一个子树中的，然后递归在加上子树中满足条件的点对数
int dfs(int u){
    int ans = 0;
    int rt = getWP(u);
    ans += calc(rt, 0);
    vis[rt] = true;
    for(int i=head[rt]; i!=-1; i=e[i].next){
        int v = e[i].to;
        if(!vis[v]){
            ans -= calc(v, e[i].w);
            ans += dfs(v);
        }
    }
    return ans;
}


int main(){
    int u, v, w;
    while( ~scanf("%d%d", &n, &k) && (n + k !=0)){
        init();
        for(int i=0;i<n-1;i++){
            scanf("%d%d%d", &u, &v, &w);
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        cout << dfs(1) << endl;
    }
    return 0;
}

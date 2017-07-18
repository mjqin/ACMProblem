
### 描述

LCA，求树上任意两点的最近公共祖先。

### 方法

#### 1 dfs序 + RMQ

所谓dfs序就是使用dfs遍历树的时候节点访问的先后顺序，例如给一棵树

5

1 2

1 3

2 4

2 5

对应的dfs序就应该是： 1 2 4 2 5 2 1 3 1， 从根节点出发遍历完所有节点然后再回到根。

这样任意两个节点之间就构成了一段连续的区间。

同时记录下每个节点第一次被访问时的下标。 **这地方其实不是第一次被访问的也可以， 因为两个点之间肯定要遍历到LCA**

最后用RMQ查询的是两个节点对应区间的最小深度，就是LCA， 当然这里求的是下标，还需要转化为节点编号。

所以还需要记录每个节点对应的深度。 

当然，最后一个还可以重新给每个节点从上到下，从左到右按顺序重新编号也可以， 这样就用新的编号代替深度。


``` c++

// ###### LCA  dfs + RMQ
int dis[N], id[N*2], idx[N], dep[N*2], tot1, dp[N*2][20];

void dfs(int u, int fa, int h){
    id[++tot1] = u; idx[u] = tot1; dep[tot1] = h;
    for(int i=head[u]; i!=-1; i = e[i].next){
        int v = e[i].to;
        if(v == fa) continue;
        dis[v] = dis[u] + e[i].w;
        dfs(v, u, h+1);
        id[++tot1] = u;
        dep[tot1] = h;
    }
}

void initLCA(){
    for(int i=1;i<=tot1;i++) dp[i][0] = i;
    for(int j=1;j<=20;j++){
        for(int i=1; i + (1<<j) - 1 <= tot1; i++){
            int a = dp[i][j-1], b = dp[i + (1 << (j-1))][j-1];
            dp[i][j] = dep[a] < dep[b] ? a:b;
        }
    }
}

int LCA(int u, int v){
    int k = 0;
    int l = idx[u], r = idx[v];
    if(l > r) swap(l, r);
    while( (1 << (k+1) ) < (r - l + 1) ) k++;
    int a = dp[l][k], b = dp[r - (1<<k) + 1][k];
    return id[dep[a] < dep[b] ? a: b];
}

```

#### 2 树上倍增 (Binary lifting)

树上倍增的思想其实和暴力查找LCA差不多，但进行了一些优化，采用二进制的方法来枚举步长。

首先，对于任意两个节点u，v，我们如果暴力找两者的LCA的话，肯定先比较两者的深度，先将节点深度大的跳到和深度小的节点同一深度，

然后两个节点再同时往上走，直到到达同一个节点，就是他们的LCA。

而倍增的思想就是将原来往上需要查找的深度进行二进制枚举，从而将复杂度有O(N)降为O(logN)。

其中一个关键的变量就是up[i][j]，表示从节点i开始往上跳2^j个节点到达哪个节点。

有了这个数组，我们就可以直接枚举j，从而进行“暴力”搜索的步骤。

``` c++

// ######## LCA  Binary lifting 
int up[N][25], fa[N], dep[N];

void dfs(int u, int pre, int h){
    fa[u] = pre; dep[u] = h;
    for(int i=head[u]; i!=-1; i=e[i].next){
        int v = e[i].to;
        if(v == pre) continue;
        dfs(v, u, h+1);
    }
}

void initLCA(){
    dfs(1, 0, 0);
    for(int i=1;i<=n;i++) up[i][0] = fa[i];
    for(int j=1;j<=20;j++){
        for(int i=1;i<=n;i++){
            up[i][j] = up[up[i][j-1]][j-1];
        }
    }
}

int LCA(int u, int v){
    if(dep[u] < dep[v]) swap(u, v);
    int c = dep[u] - dep[v];
    for(int i=0;i<=20;i++){
        if(c & (1<<i)) u = up[u][i];
    }
    if(u == v) return v;
    for(int i=20; i>=0; i--){
        if(up[u][i] != up[v][i]){
            u = up[u][i];
            v = up[v][i];
        }
    }
    return fa[u];
}

```

由于倍增的本质其实就是暴力枚举， 所以我们也可以在枚举的时候维护各种变量，例如任意两个节点之间边的最大值/最小值等等。

#### 3 Tarjan

Tarjan的思想是根据遍历节点的先后顺序来寻找规律。

如果我们要求(u,v)两个节点的LCA，当我们通过dfs来遍历树上各个节点的时候，假如先遍历到节点u，然后回溯，直到节点v，

那么节点(u,v)的LCA必然是遍历到v时节点u回溯到深度最低的节点。

基于这个观察规律，我们可以在回溯是更新节点的父亲节点，用并查集来维护，那么(u,v)的LCA就是遍历到v时的_find(u)，假设先遍历u节点。

``` c++

int fa[N];
vector<VI> g;
vector<PII> query;
map<PII,int> lca;
int dis[N];

void initLCA(){
    for(int i=1;i<=n;i++){
        fa[i] = i;
        vis[i] = false;
    }
    g.clear();
    g.resize(n+1);
}

int _find(int x){
    return x == fa[x] ? x :  _find(fa[x]);
}

int Tarjan(int u, int pre){
    for(int i=head[u]; i!=-1;i=e[i].next){
        int v = e[i].to;
        if(v == pre) continue;
        Tarjan(v, u);
        fa[v] = u;
        vis[v] = true;
    }
    for(auto v: g[u]){
        if(vis[v]){
            lca[MP(u, v)] = _find(v);
            lca[MP(v, u)] = _find(v);
        }
    }
}

```



### 描述

最短路径， 包括两种情况，单源和任意两点之间的最短路径，主要有一下五种方法。

测试链接： http://acm.hdu.edu.cn/showproblem.php?pid=2544

Johnson算法测试: http://hihocoder.com/problemset/problem/1089

### 方法

#### 1 Floyd-Warshall

Floyd使用动态规划的思想，枚举所有点判断通过该点是否能优化其他两点之间的距离，所以计算的也是任意两点之间的最短路径。
算法实现也最为简单。

效率：O(n^3)

``` c++

// Shortest path - floyd
int n, m;
int dis[N][N]; // dis要初始化为无穷大

void floyd(){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
}

```

#### 2 Dijkstra

Dijkstra是求单源最短路径最经典的算法，算法主要思想是维护两个集合S,U，分别记录已经求出最短路径的点和未求出最短路径的点。

S初始化为源点， U初始化为除源点以外其他点。

每次在当前U中找出dis最小值的点，加入S，并用这个点作为中间节点更新其他所有节点的dis。

直到所有节点都加入S，算法结束。

效率：O(n^2)

``` c++

// Shortest path - Dijkstra
int n, m;
int g[N][N];  //要初始化为inf
int dis[N];
bool vis[N];

void dijkstra(int k){
    for(int i=1;i<=n;i++) dis[i] = g[k][i];
    memset(vis, 0, sizeof(vis));
    vis[k] = 1;
    for(int i=1;i<n;i++){
        int tmp = inf, id;
        for(int j=1;j<=n;j++){
            if(!vis[j] && dis[j] < tmp){
                tmp = dis[j];
                id = j;
            }
        }
        vis[id] = 1;
        for(int j=1;j<=n;j++){
            dis[j] = min(dis[j], dis[id] + g[id][j]);
        }
    }
}

```

Dijkstra还能使用优先队列进行优化，用优先队列直接维护当前已经求出的路径最小的点。

复杂度： O((n+m)*log(m)) 适用于边数较小的稀疏图

``` c++

// Shortest path - dijkstra 优先队列优化
int n, m;
int dis[N];

struct Edge{
    int to,w;
    friend bool operator < (Edge a, Edge b){
        return a.w > b.w;
    }
};

vector<Edge> e[N];

void dijkstra(int k){
    for(int i=1;i<=n;i++) dis[i] = inf;
    dis[k] = 0;
    priority_queue<Edge> q;
    q.push(Edge{k, 0});
    while(!q.empty()){
        Edge t = q.top(); q.pop();
        for(auto it: e[t.to]){
            if(dis[it.to] > t.w + it.w){
                dis[it.to] = t.w + it.w;
                q.push(Edge{it.to, dis[it.to]});
            }
        }
    }
}
```

#### 3 Bellman-Ford

Bellman-Ford是使用边去更新点的距离，方法也比较简单，就是枚举所有的边，看使用该边能否更新两个断点的距离。

而由于路径最长的边数总和不会超过n-1，所以最多更新n-1次就可以就出所有点到源点的最短路径。

Bellman-Ford还能判断途中是否存在负环， 方法是继续枚举一遍所有的边，还是否还存在节点还能继续松弛。

复杂度： O(n*m)

``` c++

// Shortest path - Bellman ford
int n;
int dis[N];

struct Edge{
    int u,v,w;
};

vector<Edge> e;  // 双向边要加两次

bool bellman_ford(int k){
    for(int i=1;i<=n;i++) dis[i] = inf;
    dis[k] = 0;
    for(int i=1;i<n;i++){
        for(auto it: e){
            dis[it.v] = min(dis[it.v], dis[it.u] + it.w);
        }
    }
    for(auto it: e){
        if(dis[it.v] > dis[it.u] + it.w) return false;
    }
    return true;
}

```

#### 4 spfa

spfa是对bellman-ford的一种优化，在bellman-ford中我们选择了最多的次数进行循环，但实际上不用循环n-1次就已经不会在更新了。

所以spfa使用了一个队列维护需要更新的所有节点， 直到所有节点都无法更新完毕，也就是队列为空时退出循环。

但spfa需要使用邻接表维护当前结点的所有邻接节点。

复杂度: O(=_=)

``` c++

// Shortest path - spfa
int n;
int dis[N];

struct Edge{
    int to,w;
};

vector<Edge> e[N];
bool vis[N];  // 记录节点是否在队列中

bool spfa(int k){
    for(int i=1;i<=n;i++) dis[i] = inf;
    dis[k] = 0;
    queue<int> q;
    q.push(k);
    vis[k] = 1;
    int cnt = 0;
    while(!q.empty()){
        int u = q.front(); q.pop();
        vis[u] = 0;
        if(cnt > n*m) return false;
        for(int i=0;i<e[u].size();i++){
            int v = e[u][i].to;
            if(dis[v] > dis[u] + e[u][i].w){
                dis[v] = dis[u] + e[u][i].w;
                if(!vis[v]){
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
        cnt++;
    }
    return true;
}

```

#### 5 Johnson算法

Johnson算法是目前计算所有节点间最短路径的效率最高的算法，主要步骤是：

* 首先用Bellman-Ford计算出1（或任意点）到其他所有点的最短距离。
* 对每条边进行重赋值， 使得每条边的权重都为非负值，从而使优先队列优化后的dijkstra的效率达到最高。
* 使用优先队列优化的dijkstra计算所有点之间的最短路径。

效率： O(n*n*log(n) + n*m)

``` c++

int n, m;
int d[N][N];

struct Edge{
    int u, v, w;
    friend bool operator < (Edge a, Edge b){
        return a.w > b.w;
    }
};

vector<Edge> e[N];

void dijkstra(int k, int dis[]){
    for(int i=1;i<=n;i++) dis[i] = inf;
    dis[k] = 0;
    priority_queue<Edge> q;
    q.push(Edge{k, 0, 0});
    while(!q.empty()){
        Edge t = q.top(); q.pop();
        for(auto it: e[t.u]){
            if(dis[it.v] > t.w + it.w){
                dis[it.v] = t.w + it.w;
                q.push(Edge{it.v, 0, dis[it.v]});
            }
        }
    }
}

bool bellman_ford(int k, int dis[]){
    for(int i=1;i<=n;i++) dis[i] = inf;
    dis[k] = 0;
    for(int i=1;i<n;i++){
        for(int j=1;j<=n;j++){
            for(auto it: e[j]){
                dis[it.v] = min(dis[it.v], dis[it.u] + it.w);
            }
        }
    }

    for(int j=1;j<=n;j++){
        for(auto it: e[j]){
            if(dis[it.v] > dis[it.u] + it.w) return false;
        }
    }
    return true;
}

bool johnson(){
    if(bellman_ford(1, d[1])){
            // reweighting
        for(int i=1;i<=n;i++){
            for(auto it: e[i]){
                it.w += d[1][i] - d[1][it.v];
            }
        }

        for(int i=2;i<=n;i++) dijkstra(i, d[i]);

        // recover weight
        for(int i=1;i<=n;i++){
            for(auto it: e[i]){
                it.w -= d[1][i] - d[1][it.v];
            }
        }
        return true;
    }
    return false; // 存在负环
}

```


### 描述

最大流算法，求一个给定网络中从起点到汇点的最大流量，通常包括以下几种算法。

### 方法

#### 1 Edmond Karp

常称为EK，通过不断寻找增广路径（即从起点到终点所有边长度都大于0的路径）来增加当前的最大流量，直到最后增广路径不存在时算法结束，对应的
流量就是最大流量。

为了使某条边的流量能够回退， 增加反向边流量的概念。

``` c++

// ###### Maxflow - EK
int n, m;
int pre[N];
int f[N][N];  // 两点之间的容量
bool vis[N];
int dis[N];

int bfs(int src, int dest){
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(src);
    dis[src] = inf;
    vis[src] = 1;
    while(!q.empty()){
        int x = q.front(); q.pop();
        if(x == dest) return dis[x];
        for(int i=1;i<=n;i++){
            if(f[x][i] > 0 && !vis[i]){
                pre[i] = x;
                vis[i] = 1;
                q.push(i);
                dis[i] = min(dis[x], f[x][i]);
            }
        }
    }
    return -1;
}

int EK(int src, int dest){
    int maxflow = 0;
    while( 1 ){
        int k = bfs(src, dest);
        if(k == -1) break;
        int tmp = dest;
        while(tmp != src){
            int x = pre[tmp];
            f[x][tmp] -= k;
            f[tmp][x] += k;
            tmp = x;
        }
        maxflow += k;
    }
    return maxflow;
}

```

#### 2 Ford Fulkerson

原理和EK一样，不同的地方是将寻找增广路径算法由bfs换成了dfs，写法上简单很多。

``` c++

// ####### Maxflow - Ford Fulkerson
int n, m;
int f[N][N];
bool vis[N];

int dfs(int u, int dest, int t){
    if(u == dest) return t;
    for(int i=1;i<=n;i++){
        if(!vis[i] && f[u][i] > 0){
            vis[u] = true;
            int x = dfs(i, dest, min(t, f[u][i]));
            if(x > 0){
                f[u][i] -= x;
                f[i][u] += x;
                return x;
            }
        }
    }
    return 0;
}

int ford_fulkerson(int src, int dest){
    int maxflow = 0;
    while( 1 ){
        memset(vis, 0, sizeof(vis));
        int k = dfs(src, dest, inf);
        if(k == 0) break;
        maxflow += k;
    }
    return maxflow;
}

```

#### 3 Dinic

Dinic算法相当于对ford fulkerson进行了优化， 将原网络按照到源点的距离（注意这里的距离指的是隔了几个点， 而不是容量）进行分层，
分层的原因是从源点到终点的路径中，同一层的点不可能在同一条路径上，并且只有下一层的点才可能在路径上，这样在dfs的时候又加了一个判断条件，
提高了dfs的效率。

``` c++

//###### Maxflow - Dinic
int n, m;
int f[N][N], h[N];
bool vis[N];

int bfs(int src, int dest){
    memset(h, -1, sizeof(h));
    queue<int> q;
    q.push(src);
    h[src] = 0;
    while(!q.empty()){
        int t = q.front(); q.pop();
        if(t == dest) return 1;
        for(int i=1;i<=n;i++){
            if(f[t][i] > 0 && h[i] == -1){
                h[i] = h[t]+1;
                q.push(i);
            }
        }
    }
    return 0;
}

int dfs(int u, int dest, int t){
    if(u == dest) return t;
    for(int i=1;i<=n;i++){
        if(!vis[i] && f[u][i] > 0 && h[i] == h[u] + 1){
            vis[u] = true;
            int x = dfs(i, dest, min(t, f[u][i]));
            if(x > 0){
                f[u][i] -= x;
                f[i][u] += x;
                return x;
            }
        }
    }
    return 0;
}

int Dinic(int src, int dest){
    int maxflow = 0;
    while(bfs(src, dest)){
        while( 1 ){
            memset(vis, 0, sizeof(vis));
            int k = dfs(src, dest, inf);
            if(k == 0) break;
            maxflow += k;
        }
    }
    return maxflow;
}

```

/*
给一个无向图，无自环无重边，再给两个点s和t，求一个生成树使得s和t的度数分别不超过ds，dt。

分析：
并查集维护连通性，具体构造步骤如代码。
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
#define MP make_pair
#define FI first
#define SE second

const int inf = 1 << 28;
const int maxn = 2e5+10;

int n, m, s, t, ds, dt;
vector<pair<int,int> > edge;
vector<pair<int,int> > ans;
int fa[maxn];
bool vs[maxn], vt[maxn]; // 记录所有和s, t相连的连通块

void init(){
    for(int i=0;i<=n;i++) {
        fa[i] = i;
        vs[i] = vt[i] = 0;
    }
}

// 并查集路径压缩
int find_root(int x){
    int t = x, z;
    while( t!= fa[t] ) t = fa[t];
    while(x != fa[x]){
        z = fa[x];
        fa[x] = t;
        x = z;
    }
    return t;
}

int union_set(int x, int y){
    int a = find_root(x), b = find_root(y);
   // printf("##:%d %d %d %d\n", x, y, a, b);
    if(a == b) return 0;
    fa[a] = b;
    if(vs[a] || vs[b]) vs[b] = true;
    if(vt[a] || vt[b]) vt[b] = true; // 更新和s,t相连的连通块
    return 1;
}

int main(){
    scanf("%d%d", &n, &m);
    int u, v;
    init();
    for(int i=0;i<m;i++){
        scanf("%d%d", &u, &v);
        edge.push_back(MP(u, v));
    }
    scanf("%d%d%d%d", &s, &t, &ds, &dt);

    // 先将所有不和s，t相连的连通块求出来
    for(int i=0;i<m;i++){
        u = edge[i].FI;
        v = edge[i].SE;
        if(u == s || v == s) vs[u] = vs[v] = true;
        if(u == t || v == t) vt[u] = vt[v] = true;
        if ( !(u == s || u == t || v == s || v == t) ) {
            if(union_set(u, v)) ans.push_back(MP(u, v));
        }
    }

    // 然后求从s连向不和t相连的连通块
    for(int i=0;i<m;i++){
        u = edge[i].FI;
        v = edge[i].SE;
        if( (u == s && !vt[v] ) || (v == s && !vt[u] ) ) {
            if(union_set(u, v)) ans.push_back(MP(u, v));
        }
    }

// 从t连向不和s相连的连通块
    for(int i=0;i<m;i++){
        u = edge[i].FI;
        v = edge[i].SE;
        if( (u == t && !vs[v]) || (v == t && !vs[u]) ) {
            if(union_set(u, v)) ans.push_back(MP(u, v));
        }
    }

// 更新当前s，t的度数
    for(int i=0;i<ans.size();i++){
        u = ans[i].FI;
        v = ans[i].SE;
        //printf("##:%d %d\n", u, v);
        if(u == s || v == s) ds--;
        if(u == t || v == t) dt--;
    }

//将s剩余的度数连向所有除t以外所有的边
    for(int i=0;i<m;i++){
        u = edge[i].FI;
        v = edge[i].SE;
        if(ds == 0 ) break;
        if( ( (u == s && v!= t) || (v == s && u != t) ) && ds > 0) {
            if(union_set(u, v)) {
                ds--;
                //puts("222");
                ans.push_back(MP(u, v));
            }
        }
    }

//将t剩余的度数连向所有除s以外所有的边
    for(int i=0;i<m;i++){
        u = edge[i].FI;
        v = edge[i].SE;
        if(dt == 0) break;
        if( ((u == t && v!= s) || (v == t && u != s) ) && dt > 0) {
            if(union_set(u, v)) {
                dt--;
               // puts("111");
                ans.push_back(MP(u, v));
            }
        }
    }

// 最后连s和t之间的边
    for(int i=0;i<m;i++){
        u = edge[i].FI;
        v = edge[i].SE;
        if( (u == s && v == t) || (v == s && u == t) ) {
            if(union_set(u, v)) {
                dt--;
                ds--;
               // puts("111");
                ans.push_back(MP(u, v));
            }
        }
    }

// 判断当前度数是否满足条件
    if(ds < 0 || dt < 0){
        //printf("%d %d\n", ds, dt);
        puts("No");
        return 0;
    }

// 检查是否是生成树
    int t = find_root(1);
    for(int i=1;i<=n;i++){
        if(t != find_root(i)){
            puts("No");
            return 0;
        }
    }

// 输出解
    puts("Yes");
    for(int i=0;i<ans.size();i++){
        printf("%d %d\n", ans[i].FI, ans[i].SE);
    }
    return 0;
}

/*
给一个无向图，无重边，无自环，现在要给每条边加一个方向使得入度等于出度的点的数量最多，输出策略。

分析：
最后的满足条件的ans = 无向图中度数为偶数的点的个数。
看到前排大牛的新姿势set删点：
先额外添加一个点标号n+1，使得度数为奇数的点都跟他连一条无向边。
然后就是求一个欧拉回路，可以用set表示邻接表，每添加一条边就对应删两个点。
最后输出不包含n+1的所有边就是答案
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
const int maxn = 210;

int t, n, m;
set<int> g[maxn];
vector<pair<int,int> > ans;

void dfs(int u){
    while( !g[u].empty() ){
        int x = *g[u].begin();
        g[u].erase(x);
        g[x].erase(u);
        ans.push_back(make_pair(u,x));
        dfs(x);
    }
}

int main(){
    scanf("%d", &t);
    while(t--){
        scanf("%d%d", &n, &m);
        int u, v;
        for(int i=0;i<m;i++){
            scanf("%d%d", &u, &v);
            g[u].insert(v);
            g[v].insert(u);
        }

        for(int i=1;i<=n;i++){
            if(g[i].size() & 1){
                g[n+1].insert(i);
                g[i].insert(n+1);
            }
        }
        cout << n - g[n+1].size() << endl;
        ans.clear();
        for(int i=1;i<=n;i++) dfs(i);
        for(int i=0;i<ans.size();i++){
            int u = ans[i].first, v = ans[i].second;
            if(u <= n && v <= n) printf("%d %d\n", u, v);
        }
    }
    return 0;
}

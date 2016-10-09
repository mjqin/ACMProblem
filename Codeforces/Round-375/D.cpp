/*
给一个n*m的矩阵，'.'代表水，'*'代表陆地，矩阵外全是水，相邻的水组成湖泊，求用土填掉最少的水的个数使得湖泊的个数等于K，保证初始湖泊个数不小于k。

bfs先求出每个湖泊的大小，然后从小到大依次填。
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
const int maxn = 55;

int n, m, k;
char s[maxn][maxn];
vector<pair<int,int> > V;
map<int, pair<int, int> > mp;
int id;

char g[] = {'.', '*'};
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool vis[maxn][maxn];

int bfs(int x, int y, int t){
    queue<pair<int, int> > q;
    q.push(make_pair(x, y));
    vis[x][y] = true;
    pair<int, int> node;
    int ret = 0;
    s[x][y] = g[t];
    bool flag = false;
    while(!q.empty()){
        node = q.front(); q.pop();
        ret++;
        for(int i=0;i<4;i++){
            int xx = node.first + dx[i];
            int yy = node.second + dy[i];
            if(xx < 0 || xx > n-1 || yy < 0 || yy > m-1) {flag = true; continue;}
            if(s[xx][yy] == '*') continue;
            if(xx == 0 || xx == n-1 || yy == 0 || yy == m-1) flag = true;
            if(vis[xx][yy]) continue;
            vis[xx][yy] = true;
            s[xx][yy] = g[t];
            q.push(make_pair(xx, yy));
        }
    }
    if(flag) return 0;
    return ret;
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for(int i=0;i<n;i++) scanf("%s", s[i]);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(s[i][j] == '.' && !vis[i][j]){
                int t = bfs(i, j, 0);
               // cout <<i << " " << j<< " " << t << endl;
                if(t > 0) {
                    V.push_back(make_pair(t, id));
                    mp[id++] = make_pair(i, j);
                }
            }
        }
    }
    sort(V.begin(), V.end());
    int ans = 0;
    memset(vis, false, sizeof(vis));
    for(int i=0;i<V.size()-k;i++){
        ans += V[i].first;
        bfs(mp[V[i].second].first, mp[V[i].second].second, 1);
    }
    cout << ans << endl;
    for(int i=0;i<n;i++) puts(s[i]);
    return 0;
}

// 相比之下，虽然基本思想一样，但写法确实简单很多
#include<bits/stdc++.h>
using namespace std;

const int N = 200010;

int n, m, s, t, ds, dt, has, sz[N], f[N];

vector<pair<int, int> > res;

int find(int v)
{
    if (v == f[v])
    {
        return v;
    }
    return f[v] = find(f[v]);
}

bool unt(int u, int v)
{
    int a = find(u);
    int b = find(v);
    if (sz[a] < sz[b])
    {
        swap(a, b);
    }
    if (a != b)
    {
        res.push_back({ u, v });
        sz[a] += sz[b];
        f[b] = a;
        return 1;
    }
    return 0;
}

vector<int> gs, gt;  

void read(int i)
{
    if (i == m)
    {
        scanf("%d%d%d%d", &s, &t, &ds, &dt);
        return;
    }
    int u, v;
    scanf("%d%d", &u, &v);
    read(i + 1);
    if (u != s && u != t && v != s && v != t)
    {
        unt(u, v);
    }
    else if (u == s && v == t || u == t && v == s)
    {
        has = 1;
    }
    else   // 保存所有与s，t相连的点
    {
        if (u == s)
        {
            gs.push_back(v);
        }
        else if (v == s)
        {
            gs.push_back(u);
        }
        if (u == t)
        {
            gt.push_back(v);
        }
        else if (v == t)
        {
            gt.push_back(u);
        }
    }
}

int main()
{

    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++)
    {
        sz[i] = 1;
        f[i] = i;
    }

    read(0);

// 先从s连向其他所有点，同时保证度数
    for (int i = 0; i < gs.size() && ds; i++)
    {
        ds -= unt(s, gs[i]);
    }

// 然后从t连向其他所有点，同时保证度数
    for (int i = 0; i < gt.size() && dt; i++)
    {
        dt -= unt(t, gt[i]);
    }

// 判断是否需要连接，s，t
    if (has && sz[find(1)] != n && ds && dt)
    {
        unt(s, t);
    }

// 判断所有点是否连通
    if (sz[find(1)] != n)
    {
        puts("No");
    }
    else
    {
        puts("Yes");
        for (auto i : res)
        {
            printf("%d %d\n", i.first, i.second);
        }
    }

    return 0;
}

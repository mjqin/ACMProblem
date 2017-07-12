/*
题目链接： http://hihocoder.com/problemset/problem/1401
一些学生要从门口到每一个办公室去注册，到每个办公室花费时间k，办公室与办公室之间同样花费时间k，现在给出每个学生到每个办公室的顺序，每个学生注册也花费
一定的但可能不同的时间，如果两个人同时到一个办公室，学号小的优先，求每个学生离开的最短时间。

分析：
简单的优先队列模拟。
*/
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
const int maxn = 1e4+10;

int n, m, k;

struct Student{
    int id, ti, tot, p[110], w[110];
}st[maxn];

struct Node{
    int id, time, index, th;  // id学号，time时间，index在Student数组中的下标，th当前注册到第几个办公室了
    Node(int a = 0, int b = 0, int c = 0, int d = 0){
        id = a;
        time = b;
        index = c;
        th = d;
    }
    friend bool operator < (Node a, Node b){
        if(a.time == b.time) return a.id > b.id;
        return a.time > b.time;
    }
};

int ans[maxn];
int pre[110];  // 该房间最后一名同学离开的时间

int main(){
    while(~scanf("%d%d%d", &n, &m, &k)){
        priority_queue<Node> que;
        memset(pre, 0, sizeof(pre));

        for(int i=0;i<n;i++){
            scanf("%d%d%d", &st[i].id, &st[i].ti, &st[i].tot);
            que.push(Node(st[i].id, st[i].ti, i, 0));
            for(int j=0;j<st[i].tot;j++) scanf("%d %d", &st[i].p[j], &st[i].w[j]);
        }

        Node node;
        int now;
        while( !que.empty() ){
            node = que.top();
            que.pop();
            int id = node.index, th = node.th;
            int offi = st[id].p[th];

            if(node.time + k < pre[offi]) node.time = pre[offi] - k;
            // printf("####%d %d\n", pre[offi], node.time);
            node.time += st[id].w[th] + k;
            pre[offi] = node.time;
            node.th++;

            // printf("## %d %d %d %d\n", id, th, node.time, offi);

            if( th == st[id].tot - 1){
                ans[id] = node.time;
                continue;
            }

            que.push(node);
        }

        for(int i=0;i<n;i++){
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}

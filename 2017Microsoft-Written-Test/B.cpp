/*
题目链接：http://hihocoder.com/problemset/problem/1400
给一个长度为n的字符串，和m个字母对，现在要删除一些字母，使得这m个字母对正着和倒着都不能在结果串中出现，求删除的最少字母个数。

分析：
转化一下，先求满足条件的最长的结果串，那么这个串的长度和原始串的长度差就是答案。
满足条件的最长串就是一个简单的动态规划。
dp[i]，表示以i+'a'结尾最长的满足条件的字符串，扫描一遍原始串然后对每个'a'-'z'更新一下dp即可。
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
const int maxn = 2e6+10;

int n, m;
char s[maxn], ss[2];
bool mp[30][30];
int dp[30];

int main(){
    scanf("%d", &n);
    scanf("%s", s);
    scanf("%d", &m);
    memset(mp, false, sizeof(mp));
    while(m--){
        scanf("%s", ss);
        mp[ss[0] - 'a'][ss[1] - 'a'] = true;
        mp[ss[1] - 'a'][ss[0] - 'a'] = true;
    }

    int ans = 0;
    for(int i=0;i<n;i++){
        int c = s[i] - 'a', tmp = 0;
        for(int j=0;j<26;j++){
            if(mp[c][j]) continue;
            if(dp[j] > tmp) tmp = dp[j];
        }
        dp[c] = tmp + 1;
        ans = max(ans, dp[c]);
    }
    cout << n - ans << endl;
    return 0;
}

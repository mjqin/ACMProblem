// http://codeforces.com/contest/725/problem/C
// 构造一个矩阵，使得一个给定字符串中左右字母都相邻，字母认为是相邻的如果他们在矩阵中相邻或者对角。
// 构造：先找出两个重复字母的位置，将整个串分为三段，中间一段比较特殊，所以先放入矩阵，然后再放两端的。

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

char s[30];
int p[30];
char ans[2][30];

int main(){
    scanf("%s", s+1);
    int x, y;
    for(int i=1;i<=27;i++){
        if(p[s[i] - 'A'])  {
            y = i;
            x = p[s[i] - 'A'];
            break;
        }else p[s[i] - 'A'] = i;
    }

    if( y - x == 1) puts("Impossible");
    else{
            // GABCDEFHIJKLMNOPQRSTUVWXYZG
            int f = 1, se = 1;

            int mid = (x + 1 + y - 1) / 2;
            for(int i=mid;i>=x+1;i--) {
                ans[0][f++] = s[i];
            }
            for(int i=mid+1;i<y;i++){
                ans[1][se++] = s[i];
            }

            int len = y - 1 - (x + 1) + 1;
            if( len & 1) ans[1][se++] = s[x];
            else ans[0][f++] = s[x];

            int tmp = 13;
            for(int i=x-1;i>=1;i--){
                if(f <= 13) ans[0][f++] = s[i];
                else ans[1][tmp--] = s[i];
            }

            tmp = 13;
            for(int i=y+1;i<=27;i++){
                if(se <= 13) ans[1][se++] = s[i];
                else ans[0][tmp--] = s[i];
            }

            printf("%s\n%s\n", ans[0]+1, ans[1] + 1);
    }
    return 0;
}

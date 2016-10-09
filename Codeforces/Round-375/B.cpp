/*
给一个值包含字母下划线和合法无内含括号的字符串，求括号外单词最长的长度和括号里单词的个数.

简单模拟。
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
const int maxn = 10010;

char s[maxn];
int len, ans1, ans2;

int main(){
    scanf("%d %s", &len, s);
    ans1 = ans2 = 0;
    bool flag = false;
    int tmp = 0;
    for(int i=0;i<len;i++){
        if(s[i] == '_'){
            if(tmp == 0) continue;
            if(flag) ans2++;
            else ans1 = max(ans1, tmp);
            tmp = 0;
        }
        else if(s[i] == '(') {
            ans1 = max(ans1, tmp);
            flag = true;
            tmp = 0;
        }
        else if(s[i] == ')') {
            if(tmp > 0) ans2++;
            flag = false;
            tmp = 0;
        }
        else tmp++;
    }
    ans1 = max(ans1, tmp);
    printf("%d %d\n", ans1, ans2);
    return 0;
}


KMP是个经典的字符转匹配算法，可以用来判断模式串在文本中是否出现，出现的次数，首次出现的位置等等.

**另外一个重要的应用就是求字符串的最小重复字串。**

KMP算法本质上是对暴力枚举算法的一种优化， 通过寻找匹配过程中的一些规律来将原来O(n*m)降到O(n+m).

模式串s: s1, s2, s3, si , sn

     i=  1   2   3   i

文本t: t1, t2, t3, ..., tm

    j= 1   2   3

假设模式串在匹配到第i个位置时失败了， 但是前i-1个字符和当前文本是匹配的， 那么也就是说如果我们找到s1,..,si-1的前缀和后缀最长的公共部分就可以直接把

i调到那个位置。

``` c++
// kmp
char s[N], t[N];
int fail[N];
int slen, tlen;

void getNext(){
    fail[1] = 0;
    for(int i=1;i<=slen){
        int p = fail[i];
        while(p && s[p+1] != s[i+1]) p = fail[p];
        fail[i+1] = p + (s[p+1] == s[i+1]);
    }
}

// 计算s在t中出现的次数
int kmp(char *s, char *t){
    slen = strlen(s+1), tlen = strlen(t+1);
    getNext();
    int j = 1, ans = 0;
    for(int i=1;i<=tlen;i++){
        if(t[i] == s[j]) j++;
        else j = fail[j] + 1;
        if(j == slen+1) {
            ans++;
            j = fail[j] + 1;
        }
    }
    return ans;
}

```

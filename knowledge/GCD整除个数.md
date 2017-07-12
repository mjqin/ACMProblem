这个知识点来源于 http://codeforces.com/contest/819/problem/C 原题进行简化之后归结为两个基本问题：

s, n, m <= 1e18.

* 1<=k<=n, 使得k|s的个数。
* 1<=k<=m, gcd(k, n) | s的k的个数。

其中第一个问题直接枚举s在[1,n]中的因子即可。

第二个问题就是本知识点的主要内容： 求满足条件的k的个数， 使得gcd(k, n) | s。


首先将n和s分别进行质因数分解n = p1^n1 * p2^n2 * ..., s = p1^s1 * p2^s2 * ...

对于其中的某一项因子pi， 如果ni > si, 且ai = pi^(si + 1)是k的因子， 那么s肯定不能整除gcd(k, n). 去掉不能整除的情况，
剩下的是满足条件的。

先求出所有的ai, 现在问题就转化为1<=k<=m, 求k不能整除ai中的任何一个的个数。这就可以利用容斥原理来解决。

``` c++

map<ll, int> Mn;
map<ll, int> Ms;  // n, s的质因子分解结果

for(auto it: Mn){
    if(Mn[it.FI] > Ms[it.FI]) Vp.push_back(quick_pow(it.FI, Ms[it.FI] + 1));  // 关键步骤！
}

// for(auto it: Vp) cout << "vp:" << it << endl;

ll t2 = 0;
for(int i=0;i<(1<<Vp.size());i++){
    ll x = 1, c = 0;
    for(int j=0;j<Vp.size();j++){
        if(i & (1 << j)){
            c++;
            x *= Vp[j];
        }
    }

    if(c&1) t2 -= m / x;   // 奇数减去能整除的， 结果求出来就是不能整除的
    else t2 += m / x;
}

```

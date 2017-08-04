
### Problem 1

题目来源于 http://codeforces.com/contest/837/problem/E

#### 描述

给定一个函数：

* f(a, 0) = 0;
* f(a, b) = f(a, b - gcd(a, b)) + 1;

求f(x, y), 1<=x,y<=10^12

#### 分析

直接暴力求的话对于x=1, y = 10^12这种类型的输入肯定会超时。

假设当前g = gcd(x, y)，那么下一步计算z = gcd(x, y-g)，且z%g == 0， 也就是说如果gcd(x, y)发生变化，那么只能不断增大。

如果能直接求出每次gcd发生变化需要执行的次数， 那么则必然能在至多log(10^12)内求解。

并且所有的gcd必然是x的因子。

所以一个可行的思路就是枚举下一个发生变化时的gcd，范围是所有x的因子，求从当前y到下一个gcd需要的最小次数，也就是y % 因子。

不断重复，直到y=0。

#### Submission

http://codeforces.com/contest/837/submission/29186364


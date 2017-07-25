
### 链接

此问题来源于: http://codeforces.com/contest/818/problem/G

### 描述

给定一个数组a[N]， 求4个该数组非空不相交的子序列的长度和的最大值，其中每个子序列b[]满足 abs(b[i+1]-b[i]) == 1 or abs(b[i+1]-b[i])%7 == 0。

### 分析

这类问题可以转化为最小费用最大流问题，一个比较直接的建图方式就是：

* 一个超级源点src， 一个超级汇点sink，每个点i拆成两个节点(i, n+i)
* src到每个i连一条边流量为1，费用为0； 所有n+i到sink连一条边，流量为1，费用为0
* 所有i到n+i连一条边， 流量为1，费用为-1， 表示如果选择了这个点，那么费用就要加1，因为后面要求最短路径，所以费用用负数表示
* 最后是所有的j > i， 并且满足题目条件的，从n+i到j连一条边，流量为1，费用为0

还有一个条件限制的就是4个子序列， 这可以再加一个点sink+1， 从sink到sink+1连一条流量为4，费用为0的边。

建图就完成了，这样求得的最大流最小费用取相反数就是最后的答案。

但是这样并不能通过所有的测试数据， 分析一下发现，在建图的第四步时，边的复杂度为O(n^2)，这样用spfa搜索增广路径时复杂度就变成了O(m*n^2)，
这样肯定会超时。

这里在处理第四步时有一个很巧妙的方式： 额外增加一条链，将数组中值相同的节点串起来，然后在额外增加的链上将数组中的节点加上去。

结果就像这样：

* cur是当前额外增加节点的当前序号
* to是数组中后面第一个值等于当前值节点对应的序号

需要添加的边为：cur -> to, cur -> i, n+i -> to (i -> n+i已经添加过了)

其中cur -> to 边的流量为无穷大， 费用为0

这样就把原来所有j > i且满足条件的a[j]用一条链连接起来了， 复杂度也由O(n^2)将为了O(n)

``` c++

  repi(i, 1, n+1) h[i] = c[i] = mcmf.sink;
  for(int i=n;i>=1;i--){
      int to = h[a[i]%7];
      int cur = cnt++;
      h[a[i]%7] = cur;
      mcmf.addEdge(cur, to, inf, 0); 
      mcmf.addEdge(cur, i, 1, 0);
      mcmf.addEdge(i+n, to, 1, 0);

      to = c[a[i]];
      cur = cnt++;
      c[a[i]] = cur;
      mcmf.addEdge(cur, to, inf, 0);
      mcmf.addEdge(cur, i, 1, 0);
      mcmf.addEdge(i+n, c[a[i]-1], 1, 0);
      mcmf.addEdge(i+n, c[a[i]+1], 1, 0);

      //cout << cnt << endl;
  }
  
```

### Submission

http://codeforces.com/contest/818/submission/28875228

### 举一反三

a[j]与a[i]之间的关系可以转化为任意的关系， 例如只要求a[j] >= a[i]， 就变成了4条上升子序列的问题。

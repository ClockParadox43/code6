2023.1.31:   今天学到多重背包III时, 感觉对代码的优化其实就是式子和式子之间的等价变形, 动态规划的转移方程可以等价变形
          那么多重背包III问题的优化应该就是动态规划的方程和单调队列的方程的等价变形吧? 当然, 感觉并不只是简单的恒等式转换
          感觉有一些构造的东西在里面, 算法导论讲的应该也是这些公式的推导吧...

2023.2.1:   今天学的是背包问题求方案数, 他们的转移方程看似一样, 但是因为所求不一样, 
         所表达的含义也不一样, 所以初始化也是不一样的, 比如 "不超过体积j的方案"和
         "恰好是体积j的方案"就是两种方案
            其实好多问题经过逻辑转化后都是一样的

2023.2.2:  要学会用数组1记录该件物品的某个信息, 数组2记录该件物品的某个信息..
         因为下标是唯一的, 所以可以快速利用该物品的下标可以快速找到对应该物品对应的信息
               int a[], b[], c[] // 记录信息a, 信息b, 信息c
               int cnt[], idx // 数组

               for (int i = 0; i < n; ++ i)
                  a[cnt[idx]] = _a;
                  b[cnt[idx]] = _b;
                  c[cnt[idx] ++ ] = _c;     // 开始记录下一个
               
               // 同样, 也可以找到
               for (int i = 0; i < n; ++ i)
                  int _a = a[cnt[idx]];
                  // ...

2023.2.3: 今天写状态机发现了一个小技巧, 想一下当前状态可以变成哪些状态
          其实这也就意味着, 变成的那个状态来自当前状态
          先正真想, 然后再倒着想

2023.2.4: 想要固定住一个点进行dfs时, 外面记得套循环, 啊啊啊啊, 又忘了 
          艹, 我终于明白为什么方案数可以由转移得到了, 因为当前的方案数中必定包含同一种状态
          去掉相同的状态就能得到之前的状态

2023.2.5: 写循环要考虑层数顺序的讲究
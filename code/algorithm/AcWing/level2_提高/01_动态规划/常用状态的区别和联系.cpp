
一般情况下三种不同的状态表示的区别联系:

 1) 体积最多是 j (最常见的, 每 i 个物品在不同体积状态下, 选择路径最优秀的那个)
    - 初始化全部为 0, 保证了体积 >= 0
      因为求的是不能超过当前体积, 所以 f[i-1, j-v] + w 为当前状态腾出空间再加上 w        


 2) 体积恰好是 j 
    - f[0] = 0, f[i] = 正无穷, 保证 v >= 0

 3) 体积至少是 j 
    - f[0] = 0, f[i] = 正无穷
    v是有小于0的状态的
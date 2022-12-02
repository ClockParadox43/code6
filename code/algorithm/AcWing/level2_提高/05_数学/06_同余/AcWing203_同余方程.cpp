// 复习:
// 扩展欧几里得算法
// (a,b) = d
// 给定一个方程使得 ax + by = d, 求 x,y 这两个系数
// 
// 欧几里得算法: (a,b) = (b,a mod b)
// 
// 扩展欧几里得原理
//            (a,b) = d, 
//          ax + by = d
//            (a,b) = (b, a mod b) => 开始迭代的时候, 将 x,y 代入
//  xb + y(a mod b) = d 
//  xb + y(a - ⌊a/b⌋ * b) = d
//  xb + ya - by⌊a/b⌋ = d
// ay + b(x - y⌊a/b⌋) = d
// x' = y, y' = x - ⌊a/b⌋y
//
// 求线性同余方程: ax ≡ b (mod c) 
//          ax - cy = b
//           设: y' = -y
//          ax + cy = b  => 因此可以推出扩展欧几里得算法
// 
// ax ≡ b (mod c) 通常能转换成不定方程的形式:
//      - ax ≡ b (mod c) <=> ax + cy = b 
// 不定方程有解条件: 整系数二元不定方向 ax + by = c中的系数 a, b 的最大公约数能整除 c, (a,b)|c
// 假设已经求出解: x = x₀, y = y₀
// 
// q: 求关于 x 的同余方程 ax ≡ 1(mod b) 的最小正整数解
// 设: ax ≡ 1(mod b)
// ∵ ax ≡ 1(mod b)
// ∴ ∃ y∈Z, s.t. ax + by = 1
// 因此可以通过 扩展欧几里得算法求出 x₀, y₀ 
// => 所有解: x = x₀ + kb, y = y₀ - ka   
#include <iostream>

using namespace std;


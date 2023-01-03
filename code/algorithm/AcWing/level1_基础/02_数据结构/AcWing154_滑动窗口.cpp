// 单调栈和单调队列的做法都是一样的
// 1) 先暴力模拟原来的问题(想清除朴素算法如何做)
// 2) 在朴素算法中找出没有用的元素
// 3) 删除所有没用的元素, 判断是否有单调性

// i - k + 1:得到的是开头的位置
// y 总提供的模板, hh 和 tt 必须 hh < tt, 才是队列为空, hh == tt 还剩下一个数据
// 左闭右闭, 算下标好算
// 栈也是, 别人的栈 stack[sz ++ ] = e, top = stack[sz - 1] 这种, 属于左闭右开    
#include <iostream>

using namespace std;

const int N = 1000010;

int n, k;
int a[N], q[N];

// 整体思路就是排除掉不要的数
// 只有下标过期时候时, hh 才会移动, 否则队头维护的就是当前窗口最小值
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++ i ) scanf("%d", &a[i]);

    int hh = 0, tt = -1;
    for (int i = 0; i < n; ++ i ) 
    {   
        // 判断过期下标, hh 暴力下来的也就是滑窗中最小的, 因为 tt 一直在判断更好的数字
        // i-k+1:有效下标, q[hh]: 如果 hh 还在有效下标左侧就要加上
        if (hh <= tt && i - k + 1 > q[hh]) ++ hh ;              
        // 如果新插入的数更小, 队尾数就先出队列
        while (hh <= tt && a[q[tt]] >= a[i]) -- tt ; 
        // 要么代替之前的要么插入队尾
        q[ ++ tt] = i;                  // t 是从 -1 开始的
        // 如果已经生成窗口
        if (i >= k - 1) printf("%d ", a[q[hh]]);
    }
    puts("");
    // i - k + 1 算下标 (过期随着 i 的增大而增大)
    hh = 0, tt = -1;
    for (int i = 0; i < n; ++ i )
    {
        if (hh <= tt && i - k + 1 > q[hh]) ++ hh;
        // 如果新来的数更大, 队尾数就弹出队尾
        while (hh <= tt && a[q[tt]] <= a[i]) -- tt;
        q[ ++ tt] = i;
        if (i >= k - 1) printf("%d ", a[q[hh]]);
    } 
    

    return 0;
}
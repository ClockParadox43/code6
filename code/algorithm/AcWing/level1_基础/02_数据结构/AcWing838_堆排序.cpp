// 堆分大根堆和小根堆, 两者不同区间就是左右孩子比自己小或者比自己大

#include <iostream>

using namespace std;

const int N = 10010;
int n, m;
int h[N], sz;

//    o
//  /   \  t 求 min
//  o   o
// u : 当前要向下调整的数
void down(int u)
{
    int t = u;
    // 左孩子不越界 且 左孩子小于父亲, t 就来到左孩子的位置
    if ((u << 1) <= sz && h[u << 1] < h[t]) t = u << 1;
    // 右孩子不越界 且 右孩子小于父亲/左孩子, t 就来到右孩子的位置
    if ((u << 1 | 1) <= sz && h[u << 1 | 1] < h[t]) t = u << 1 | 1;
    
    // 此时已经挑选出左右孩子中最小的

    // 最小和左右节点交换
    // 向下调整
    // 调到最后一定会越界, 所以t == t
    if (u != t)
    {
        swap(h[u], h[t]);
        down(t);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i ) scanf("%d", &h[i]);
    sz = n;
    // 建堆
    for (int i = n >> 1; i; -- i ) down(i);

    while (m -- )
    {
        // 1) 输出堆顶元素
        // 2) 最后一个元素覆盖堆顶元素(删除)
        // 3) 堆顶元素向下调整
        //    这样留在堆顶的还是最小的
        printf("%d ", h[1]);
        h[1] = h[sz];
        sz -- ;
        down(1);
    }
}

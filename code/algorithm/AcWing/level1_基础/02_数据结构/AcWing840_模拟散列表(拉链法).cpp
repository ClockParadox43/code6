#include <iostream>
#include <cstring>

using namespace std;

const int N = 100010;

// 拉链法
// h[N]:为 hash 表开槽 -> 防止冲突, 以 % 得的数开头 -> 记录 hash 表第几个数
// e[N]:当前值 
// ne[N]:下一个节点 
int h[N], e[N], ne[N], idx;

void insert(int x)
{
    int k = (x % N + N) % N;        // 防止负数, 如果是负数 + N 再 % N, 代表该 x 属于余数 k 这类 
   
    // 同一个集合的 idx 都会指向 该槽 的 上一个 元素
    // 比如 是 模数为 6 槽, 那么 新的 idx 是 4, 模数为 6 的槽最后一个 idx 是 2
    // 那么 4 就会指向 2, 它们都属于模数为 6 的槽
    // 最后 模数为 6 的槽的最后一个元素就是 4, 然后 idx + 1 
    e[idx] = x, ne[idx] = h[k], h[k] = idx ++ ;
}

//  k 是槽开始的位置, 所以每次都是从槽的最开始找(邻接表给定的是某个父亲的位置)
bool find(int x)
{
    int k = (x % N + N) % N;
    for (int i = h[k]; i != -1; i = ne[i])  // 从最开始的槽一直往下找
        if (e[i] == x) return true;         
    return false;
}

int main()
{
    int q; scanf("%d", &q);
    
    memset(h, -1, sizeof h);
    while (q -- )
    {
        char op[2];
        int x;
        scanf("%s%d", op, &x);
        if (*op == 'I') insert(x);
        else 
        {
            if (find(x)) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
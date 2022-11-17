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
    e[idx] = x, ne[idx] = h[k], h[k] = idx ++ ;
}

bool find(int x)
{
    int k = (x % N + N) % N;
    for (int i = h[k]; i != -1; i = ne[i])
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
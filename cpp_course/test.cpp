#include <iostream>

using namespace std;

const int N = 100010;

int n;
int e[N], ne[N], h[N], idx;
bool st[N];

int add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int dfs(int u)
{
    st[u] = true;
    
    // res : 当前树的联通块最大
    // sum : 自己作为子树的大小
    int sum = 1, res = 0;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!st[j])
        {
            int s = dfs(j);
            res = max(s, res);
            sum += s;
        }
    }

    res = max(res, n - sum);
    ans = min(res, s);
    return sum;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++ i )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
    } 

    return 0;
}
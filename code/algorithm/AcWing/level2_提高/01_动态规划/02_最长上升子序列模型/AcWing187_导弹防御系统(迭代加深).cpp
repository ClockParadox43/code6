// 依次枚举每个数
//      - 先枚举将该数当到单调上升的序列中, 还是单调下降的序列中
//        1.如果该数放到单调上升的序列中, 则枚举将该数放到哪个单调上升的序列后面
//        2.如果该数放到单调下降的序列中, 则枚举将该数放到哪个单调下降的序列后面

#include <iostream>

#define MAXN 55
using namespace std;

int n;
int w[MAXN];
int up[MAXN], dw[MAXN];

// depth:当前枚举到的层数
// u:当前能枚举到数
// su:上升子序列的组数
// sd:下降子序列的组数
bool dfs(int depth, int u, int su, int sd)
{   
    if (su + sd > depth) return false;    // 如果上升序列个数 + 下降序列个数 > 总个数是上限, 则回溯
    if (u == n) return true;        // 如果找完了 n 个数, 直接返回一个合法解

    // 枚举所有选法
    // 枚举是否归到上升子序列中的情况, flag 表示有没有归到一个上升子序列中
    bool flag = false;
    for (int i = 1; i <= su; ++ i)
        if (up[i] < w[u])
        {
            int t = up[i];
            up[i] = w[u];
            if (dfs(depth, u + 1, su, sd)) return true;
            up[i] = t;
            flag = true; 
            break;  // 注意由上述证明的贪心原理, 只要找到第一个可以放的序列, 就可以结束循环了
        }
    
    // 如果不能放到任意一个序列后面，则单开一个新的序列
    if (!flag)  
    {
        up[su + 1] = w[u];
        if (dfs(depth, u + 1, su + 1, sd)) return true;
    }

    // 枚举下降子序列
    flag = false;
    for (int i = 1; i <= sd; ++ i)
        if (dw[i] > w[u])
        {
            int t = dw[i];
            dw[i] = w[u];
            if (dfs(depth, u + 1, su, sd)) return true;
            dw[i] = t;
            flag = true;
            break;
        }
    
    if (!flag) 
    {
        dw[sd + 1] = w[u];
        if (dfs(depth, u + 1, su, sd + 1)) return true;
    }
    // 所有选法枚举完后还是没有解, 直接返回 false
    return false;
}

int main()
{
    while (cin >> n, n)
    {
        for (int i = 0; i < n; ++ i) cin >> w[i];
    
        int depth = 0;      // 迭代加深的层数
        while (!dfs(depth, 0, 0, 0)) depth ++ ;    // 在当前的层数之上, 搜到即可
        cout << depth << endl;
    }
    return 0;
}
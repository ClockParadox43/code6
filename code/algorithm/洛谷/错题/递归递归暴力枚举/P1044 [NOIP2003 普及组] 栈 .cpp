/*
    1) i 表示还有几个待排列的数, j 表示栈中有 j 个数, f[i,j]表示情况数
    2) 只要 f[i, j] 有值就返回, 表示该种情况的情况的数
    3) 返回, 如果数全在栈里了, 所以 i = 0, 返回 1
    4) 两种情况: 第一种是栈为空,  那么只有队列中的数可以入栈 f[i - 1][j + 1]
                 第二种是栈不为空, 那么队列中的数可以给栈 f[i + 1][j - 1]
                 或者只出栈 f[i][j - 1]
*/

#include <iostream>

using namespace std;
const int MAXN = 20;

int n;
int f[MAXN][MAXN];
int ans;

void dfs(int i, j)
{
    if (!i)
    {
        ans = 1;
        return ;
    }
    
    if (j)      // 栈中还剩下数的情况, 栈中的数给队列
        ans += dfs(i + 1, j - 1);
    else ans += dfs(i - 1, j + 1);
}

int main()
{
    scanf("%d", &n);
    dfs(n, 0);      // 初始情况栈里没有数
    cout << ans << endl;
    return 0;
}


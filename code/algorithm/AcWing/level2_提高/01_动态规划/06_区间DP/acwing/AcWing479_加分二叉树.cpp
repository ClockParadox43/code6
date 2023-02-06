// 因为中序遍历是一段连续的区间(不漏), 且按照根节点划分, 左子树和右子树不会产生交集
// 所以可以用区间dp解决该问题, 记得特判边界, 如果左边为空的话左边为1
// 右边为空的话, 右边为1, 遍历所有子集, 所有子集的最大值就是 f[i,j] 的值
#include <iostream>
#include <cstring>

using namespace std;

const int N = 55;

int n;
unsigned f[N][N];
int w[N];
int root[N][N]; // root(l, r)用于记录(l, r)区间内的根结点

void dfs(int l, int r)
{
    if (l > r) return;
    int k = root[l][r];
    cout << k << ' ';
    dfs(l, k - 1);
    dfs(k + 1, r);
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> w[i];
 
    for (int len = 1; len <= n; ++ len)
        for (int l = 1; l + len - 1 <= n; ++ l)
        {
            int r = l + len - 1;
            for (int k = l ; k <= r; ++ k)      // k:代表根节点 因为k是从小到大遍历的, 所以肯定是小的先存进去
            {
                int left = k == l ? 1 : f[l][k - 1];
                int right = k == r ? 1 : f[k + 1][r];
                // 如果划分点是他自己的话, 那么左右就有边界
                int score = left * right + w[k];
                if (l == r) score = w[k]; // 记录下自己的值
                // 每次都取第一个来保证字典序最小, 如果当前分数更大, 更新答案
                if (f[l][r] < score)    
                {
                    f[l][r] = score;
                    root[l][r] = k;
                }
            }
        }

    cout << f[1][n] << endl;
    dfs(1, n);
    puts("");
    return 0;
}
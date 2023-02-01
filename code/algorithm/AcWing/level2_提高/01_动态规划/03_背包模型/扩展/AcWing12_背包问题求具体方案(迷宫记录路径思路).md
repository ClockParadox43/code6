`这种转移方法是来自迷宫求最短路的记录方案的灵感`
```c++
开一个PII g[i][j]数组来记录, 表示first表示(i, j)是由first这个点转移而来,
 second表示由first转移而来的时候第first物品是否被选.
```
```c++
g[i][j] = {i + 1, false}:表示(i, j)这个状态是从没选第i + 1个物品转移而来.
g[i][j] = {i + 1, true}:表示(i, j)这个状态是从选第i + 1个物品转移而来
```
`然后边DP边记录即可`
```c++
对于输出的过程: 
首先要判断一下g[i][j].second是否为true如果为true, 那么表示是由选择一个物品转移而来
那么当前体积需要跟着变化, 那就是减去当前的v, 反之如果为false, 那么就不必减去当前的v
还有注意这两种情况下i都需要进行转移
```
```
还要注意的就是求解的时候还是要倒序求, 因为需要保证字典序最小
```
```c++
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define fs first
#define se second
typedef pair<int, bool> pii;
const int N = 1010;

int n, m;
int f[N][N];
int v[N], w[N];
pii g[N][N];   
vector<int> ans;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i ++ ) cin >> v[i] >> w[i];
    for (int i = n; i >= 1; i -- )
        for (int j = 0; j <= m; ++ j)
        {
            f[i][j] = f[i + 1][j];
            g[i][j] = {i + 1, false};
            if (j >= v[i])
                if (f[i + 1][j - v[i]] + w[i] >= f[i][j])   // 如果前i-1件物品+w[i] > 当前选择
                {
                    g[i][j] = {i + 1, true}; //注意这里一定要大于等于，因为为了保证字典序，能选必选
                    f[i][j] = f[i + 1][j - v[i]] + w[i];    // 更新当前决策的答案
                }
        }

    int i = 1, j = m;
    while (i <= n && j)
        if (g[i][j].se == true)
        {
            int t = i;   // 这里一定要临时存一下i, 因为下边i接着变成了它的上一个状态, 而j要减去的是当前状态的v
            cout << i << " ";
            i = g[i][j].fs;
            j -= v[t];
        }
        else i = g[i][j].fs;
}
```
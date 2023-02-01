// 既然是求具体方案, 那就简单粗暴的把每个状态的方案保存下来吧！
#include <iostream>
#include <vector>
using namespace std;
const int N = 1001;

int n, m;
int v[N], w[N], f[N];
vector<int> ans[N];
int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i ++ ) scanf("%d %d",&v[i],&w[i]);
    for(int i = 1; i <= n; i ++ )
        for(int j = m; j >= v[i]; j -- )
        {
            // f[j-v[i]]+w[i]:取之前没更新过的值更新自己
            // f[j-v[i]]:也就是上一层的值
            // f[j] < f[j-v[i]] + w[i], 当前层 < 在上一层选择第i件物品的情况下大于自己
            // 也就是发生更新 
            if(f[j] < f[j - v[i]] + w[i])   
            {
                ans[j] = ans[j - v[i]]; //复制方案
                ans[j].push_back(i);    // 更新方案
                f[j] = f[j - v[i]] + w[i];
            }
            else if(f[j] == f[j - v[i]] + w[i]) // 当前层和上一层相等的情况,
            {
                vector<int> b = ans[j - v[i]];  // 上一层的字典序 
                b.push_back(i);      // 更新第i件物品
                if(b < ans[j])       // 如果 b 的字典序小于当前枚举数组的的字典序
                    ans[j] = b;      // 就把上一层字典序更新给当前层  ps:为什么这么做, 因为我们要字典序最小的方案
            }
        }
    for(int i = 0; i < ans[m].size(); i ++ )    //输出方案
        cout << ans[m][i] << ' ';
    return 0;
}

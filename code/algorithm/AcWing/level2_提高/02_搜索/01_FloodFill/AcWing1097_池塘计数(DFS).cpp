#include <iostream>

using namespace std;

const int N = 1009;

int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};//方向
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};//方向

int n, m, ans = 0;
char mp[N][N];

void dfs(int x, int y)
{
    mp[x][y] = '.'; // 更新当前节点的类型
    for(int i = 0;i < 8;++ i)//枚举八连通方向
        if(mp[x + dx[i]][y + dy[i]] == 'W')//如果是水
            dfs(x + dx[i],y + dy[i]);//dfs 下一个节点
}

int main()
{
    cin >> n >> m;// 输入
    for(int i = 1;i <= n;++ i)
        for(int j = 1;j <= m;++ j)
            cin >> mp[i][j];// 输入

    for(int i = 1;i <= n;++ i)
        for(int j = 1;j <= m;++ j)
            if(mp[i][j] == 'W')
                dfs(i, j), ans ++;// 每递归一个连通块，ans ++
    cout << ans << endl;
    return 0;
}

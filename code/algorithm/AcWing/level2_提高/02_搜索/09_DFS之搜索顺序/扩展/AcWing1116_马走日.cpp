#include <iostream>
using namespace std;

int T,n,m,a,b,ans;
int vis[20][20];
int dx[8]={2,1,-1,-2,-2,-1,1,2};//方向数组
int dy[8]={1,2,2,1,-1,-2,-2,-1};//方向数组
void dfs(int x,int y,int step)//step记录当前走了几个格子
{
    if(step == n * m)
    {
        ans ++ ;//答案加一
        return;
    }
    for(int i = 0; i < 8; i ++ ){
        int kx = x + dx[i], ky = y + dy[i];
        if(kx >= 0 && kx < n && ky >= 0 && ky < m && vis[kx][ky] == 0)
        {   //判断
            vis[kx][ky] = 1;//标记
            dfs(kx, ky, step + 1);
            vis[kx][ky] = 0;//回溯
        }
    }
}
int main()
{
    scanf("%d", &T);
    while(T -- )
    {
        ans=0;
        memset(vis, 0, sizeof vis);
        scanf("%d%d%d%d",&n, &m, &a, &b);
        vis[a][b] = 1;//标记起点
        dfs(a, b, 1);
        printf("%d\n", ans);
    }
    return 0;
}


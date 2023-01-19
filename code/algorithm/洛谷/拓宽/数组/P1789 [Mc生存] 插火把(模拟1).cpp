#include <iostream>

using namespace std;

int a[105][105],n,m,k,x,y,cnt;

// 只枚举需要的格子时间复杂度小很多
int main()
{
    cin >> n >> m >> k;//读入数据 
    for(int i = 1;i <= m; i ++)
    {
        cin >> x >> y;
        for(int i= x-1;i <= x+1; i ++ )
            for(int j = y - 1; j <= y+1;j ++ )
            {    
                a[i][j] = true;     // 中间3*3的方格被照亮 
                a[x-2][y] = true;
                a[x+2][y] = true;
                a[x][y+2] = true;
                a[x][y-2] = true;// 别忘了四个角 
            }   
    }

    // 枚举 8 个方位
    for(int i = 1; i <= k; i ++ )
    {
        cin >> x >> y;
        for(int i = x - 2;i <= x + 2;i ++ )
            for(int j = y - 2;j <= y + 2; j ++)
                a[i][j] = true;           // 5*5的方格被照亮 
    }

    for(int i = 1;i <= n; i ++ )
        for(int j = 1;j <= n;j ++ )
            if(a[i][j] == 0) cnt++;//统计没光的地方 
    cout << cnt;
    return 0;//完美结束 
}
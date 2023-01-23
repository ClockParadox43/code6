#include <iostream>

using namespace std;
const int MAXN = 504;

int n, t, cnt;
int x, y, r, z;
int m[MAXN][MAXN], tmp[MAXN][MAXN];

// 顺时针
void cw(int x, int y, int r)
{
    for (int i = x - r; i <= x + r; ++ i)      // 拿出要旋转的那一部分
        for (int j = y - r; j <= y + r; ++ j)
            tmp[i][j] = m[i][j];
    
    // 起始位置, 转到 m[i,j]
    // 从 m[i,j] 开始枚举, 这是转到后的位置(从最低开始枚举可以每一个补充不漏的枚举到)
    // y-r:代表左侧一列
    int dx = x + r, dy = y - r;  
    for (int i = x - r; i <= x + r; ++ i)
    {
        for (int j = y - r; j <= y + r; ++ j)
        {
            m[i][j] = tmp[dx][dy];
            dx -- ;         // 将左侧一列顺时针旋转 90°, 行减1, 列加1, 正好每个能对应到 90°
        }
        dx = x + r, dy ++ ; // 然后继续转下一列
    }
}

// 逆时针
void ccw(int x, int y, int r)
{
    for (int i = x - r; i <= x + r; ++ i)
        for (int j = y - r; j <= y + r; ++ j)   
            tmp[i][j] = m[i][j];
    
    // y+r:代表右侧一列
    int dx = x - r, dy = y + r;
    for (int i = x - r; i <= x + r; ++ i)
    {
        for (int j = y - r; j <= y + r; ++ j)  
        {
            m[i][j] = tmp[dx][dy];
            dx ++ ;         // 将右侧一列逆时针旋转 90°
        }
        dx = x - r; dy -- ; 
    }
}

int main()
{
    cin >> n >> t;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            m[i][j] = ++ cnt;

    while (t -- )
    {
        cin >> x >> y >> r >> z;
        if (!z) cw(x, y, r);
        else ccw(x, y, r);   
    } 

    for (int i = 1; i <= n; ++ i)
    {
        for (int j = 1; j <= n; ++ j)
            cout << m[i][j] << ' ';
        puts("");
    }

    return 0;
}

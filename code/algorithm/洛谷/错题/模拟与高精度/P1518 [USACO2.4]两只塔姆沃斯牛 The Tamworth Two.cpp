// 没想出来的原因, 没有把朝向(状态)和方向数组结合在一起想
#include <iostream>

using namespace std;
const int MAXN = 15;

struct st
{
    int x, y, t = 0;        // t: 0 北, 1 东, 2 南, 3 西  
}cow, fm;
// fm.x, fm.y, fm.t, cow.x, cow.y, cow.t
int mark[11][11][5][11][11][5] = { 0 };  
int g[MAXN][MAXN];
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, 1, 0, -1 };
bool flag = false;

void move()
{
    // 开始转方向
    int fx = fm.x + dx[fm.t], fy = fm.y + dy[fm.t];
    int cx = cow.x + dx[cow.t], cy = cow.y + dy[cow.t];

    if (fx < 0 || fy >= 10 || !g[fx][fy])
        fm.t = (fm.t + 1) % 4; // 有障碍或者撞墙就顺时针转方向
    else if (g[fx][fy])
        fm.x = fx, fm.y = fy;  // 如果没有障碍
        
    if (cx < 0 || cy >= 10 || !g[cx][cy])
        cow.t = (cow.t + 1) % 4;
    else if (g[cx][cy])
        cow.x = cx, cow.y = cy;
}

int main()
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
        {
            char c; cin >> c;             // 障碍物记作 0, 空地记作 1
            if (c == '*') continue;
            
            g[i][j] = 1; // else if (c == '.') 路的话都是通过的, 包括 'F' 的起始坐标 和 'C' 的起始坐标 
            
            if (c == 'F') fm.x = i, fm.y = j;
            else if (c == 'C') cow.x = i, cow.y = j;
        }

    // 当两个人同时出现的状态是以前也有过的, 说明此时已经形成闭环
    int tm = 0;
    while (fm.x != cow.x || fm.y != cow.y)
    {
        tm++;
        if (mark[fm.x][fm.y][fm.t][cow.x][cow.y][cow.t]) { cout << 0; return 0;  }
        mark[fm.x][fm.y][fm.t][cow.x][cow.y][cow.t] = 1;
        move();
    }

    cout << tm << endl;
    return 0;
}

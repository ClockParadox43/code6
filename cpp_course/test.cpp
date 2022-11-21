
// AcWing 154. 滑动窗口     复习
// AcWing 843. n-皇后问题 复习
// AcWing 844. 走迷宫 复习
// AcWing 845. 八数码
//  - dfs, 下标间的转换, 二维状态的存储

// AcWing 846. 树的重心
// AcWing 847. 图中点的层次

#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

typedef pair<int, int> PII;

int bfs(string start)
{
    string end = "12345678x";
    queue<PII> q;
    q.push({start, 0});     // 状态和对应距离

    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    while (q.size())
    {
        auto t = q.front();
        q.pop();
        int dist = t.second;
        
        if (end == t.first) return dist;
        
        int k = f.first.find('x');      // 找 'x' 的位置
        int x = k / 3, y = k % 3;
        
        for (int i = 0; i < 4; ++ i )
        {
            int a = x + dx[i], b = y + dy[i];     // 利用偏移量进行移动
            if (a >= 0 && a < 3 && b >= 0 && b < 3)
            {
                swap(t[k], t[a * 3 + b]);   // 和转换后的下标交换位置
                if (!)
            }

            
        }
    }   
}

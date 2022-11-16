// 思路: 起点走到终点求短路 
// 难点:
//   1) 状态表示复杂, 每次矩阵的状态表示不是很方便
//          - 如何将状态存入队列
//          
//   2) 如何记录每个状状态的距离
// 
// 状态表示: stirng -> "2 3 4 1 5 x 7 6 8"
// 状态转移: 分别枚举上下左右
// 广度优先搜索是一层一层逐层往下搜索的，第一个搜到的答案，当然是最短
// 思路 : 将所有状态看做是图当中的一个节点, 如果某一个状态可以变成另外一个状态
//        就连一条从 a 指向 b 的边, 边的权值是 1
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

// start : 初始状态
// end : 终点
int bfs(string start)
{
    string end = "12345678x";

    queue<string> q;                // 记录每种状态
    unordered_map<string, int> d;   // 每种状态对应的距离

    q.push(start);
    d[start] = 0;       // "12x":0 -> 表示起点的距离是 0 
    
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

    while (q.size())
    {
        auto t = q.front();
        q.pop();

        int distance = d[t];
        if (t == end) return distance;  // 当前状态 == 最终状态, 返回最终状态的距离

        // 状态转移
        int k = t.find('x');      // 找到 x 的下标
        int x = k / 3, y = k % 3; // 将一维数组下标转换成二维数组下标
        
        for (int i = 0; i < 4; ++ i )
        {
            // 变化之后的坐标
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < 3 && b >= 0 && b < 3)
            {
                // row * m + col : 二维数组转一维数组下标 
                swap(t[k], t[a * 3 + b]);       // 位置换算 -> 当前位置和下一个位置交换(在一维数组上)

                // 如果这个转态没有被记录过
                // 来到该状态, 该状态入队列
                if (!d.count(t))
                {
                    d.insert({t, distance + 1});
                    q.push(t);
                }
                swap(t[k], t[a * 3 + b]);
            }
        }
    }
    return -1;
}

int main()
{
    string state;
    for (int i = 0; i < 9; ++i)
    {
        char c;
        cin >> c;
        state += c;
    }

    cout << bfs(state) << endl;
    return 0;
}
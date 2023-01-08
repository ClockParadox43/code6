// 思路: 起点走到终点求短路 
// 难点:
//   1) 状态表示复杂, 每次矩阵的状态表示不是很方便
//          - 如何将状态存入队列
//          - 下标之间的变化       
//              1) 一维数组转二维数组
//                      k / m = row, k % m = col
//              1) 二维数组转一维数组
//                      row * m + col = k
//
//      记录完后还得尝试其他路, 所以还需要再 swap 回来
//      和上一道题相对比, 一个是左右扩展一个是 swap      
//      左右扩展只需要在取出的坐标的基础上加上偏移量即可, 但是往 swap 不一样, 你还需要找原点找下一个尝试点
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

    // 为什么使用 map ?, 因为每种状态只会出现一次, 所以就可以用 map 来统计该状态是否出现过
    // 如果出现过就将
    unordered_map<string, int> d;   // 每种状态对应的距离
    

    q.push(start);
    d[start] = 0;       // "12x":0 -> 表示起点的距离是 0 
    
    

    while (q.size())
    {
        auto t = q.front();
        q.pop();

        int distance = d[t];
        if (t == end) return distance;  // 当前状态 == 最终状态, 返回最终状态的距离

        // 状态转移
        // 一维数组下标 / col = 二维数组行下标
        // 一维数组下标 % col = 二维数组列下标
        int k = t.find('x');      // 找到 x (空格)的下标, 将周围的数移动到 x 上去
        int x = k / 3, y = k % 3; // 将一维数组下标转换成二维数组下标
        
        // 遍历空格周围的数
        for (int i = 0; i < 4; ++ i )
        {
            // 算出 和 数字交换后 的位置
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < 3 && b >= 0 && b < 3)
            {
                // row * m + col : 二维数组转一维数组下标 
                // 数字和空格进行交换
                swap(t[k], t[a * 3 + b]);       // 位置换算 -> 当前位置和下一个位置交换(在一维数组上)

                // 如果这个转态没有被记录过
                // 来到该状态, 该状态入队列, 会有重复状态有了就不要记录
                if (!d.count(t))
                {
                    d.insert({t, distance + 1});
                    q.push(t);
                }
                swap(t[k], t[a * 3 + b]); // 换回来继续尝试下一个可以走的位置
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
// A* 算法所解决的问题和双向光搜所解决的问题是一样的
// 如果状态空间过于庞大, 直接搜可能会遍历到非常多的状态, 这可能会超时
// 所以我们可以加上一个启发函数来高效的求出起点到终点的最短距离
//
// 启发函数作用:只使用非常少的状态就能求出从它开始到终点的最短路径
//             所以并不适合状态空间较少的题
// A* 函数应用场景: 当搜索空间庞大时
// A* 算法框架: 1)将 BFS 的队列变成优先队列
//             2)取出队头(小根堆)
//             3)堆中数据, 除了存储真实距离还需要存储预估数据 
//               真实距离单位:起点到当前点
//               预估距离单位:从当前点到终点的估计距离
//               用每个点的估计值来排序
//             4)挑一个最小的点来扩展
//             5)当终点第一次出队的时候 break
// ps: A* 算法和 Dijsktra 很像, A* 算法可以处理的变权不一定是为 1, 只要没负权即可
//     A* 一定要是有接解的情景才能使用, 因为就算没解, A* 也会将所有状态都搜索一遍
//    这种情况 A* 算法效率低于普通 DFS
// Dijsktra 本质上可以看做所有预估函数都取 0 的 A* 算法
// 
// state:
//     d(state) + g(state) -> 起点到当前 state 是 d, 从 state 到终点的真实距离是 g, 相加就是最终距离
//     d(state) + f(state) -> f 是 state 到终点的估计距离
// 只要证明出 g(state) ≤ f(state) A*就是正确的
// 反证法:
//     假设终点 d 出队时不是最小值, 既然不是最小值, 那么 d 一定严格大于最优
//     队列当中此时也存在最优解
//     因为 f(u) 小于真实值, 所以 d(u) + f(u) ≤ d(u) + g(u) = 最优
//     因为 d 不是最优解, 所以 d > 最优 ≥ d(u) + f(u)
//     因为优先级队列中只会出最小值, 所以该情况就矛盾了, 
// A*算法只能保证终点的最小的但是并不能保证中间的点也是最小的 
// 入队出队都不能保证最优, 只能保证最终距离是最优的
//
// 预估函数是 L 的点在小根堆中, 当按照错误路径走到某个点的距离大于 L 时, 就该从 L 开始走
// 这样最终得到的就是正确答案 
//
// BFS, Dijkstra, A* 区别:
// BFS 可以在入队时判重 (入队时就是当前最小)
// Dijkstra 在出队时判重 (出来时就是最小的了)
// A* 不需要判重 (因为除了终点每个点出来时不一定是正确的)
// 
// 剪枝: 对于八数码问题而言, 有解的充要条件是读出来的逆序对数量是偶数 
//       如果是偶数一定有解, 如果是奇数一定无解
// 
// 估计距离:
// 每次移动只会改变某一个数的一个位置
// 经过观察可以发现, 每次移动只能把一个数字与空格交换位置
// 这样至多把一个数字向它在目标状态中的位置移近一步. 即使每一步移动都是有意义的
// 从任何一个状态到目标状态的移动步数也不可能小于所有数字当前位置与目标位置的曼哈顿距离之和.
//          ----《算法竞赛进阶指南》
// 也就是取当前函数与它的目标位置的曼哈顿距离之和
#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, string> PIS;

int f(string m)    // 预估函数
{
    int dt = 0;
    for (int i = 0; i < 9; ++ i )   // 这里 1~8 对应的下标 0~7  
        if (m[i] != 'x')    
        {
            int t = m[i] - '1';     // 对应下标
            dt = dt + abs(i / 3 - t / 3) + abs(i % 3 - t % 3);// 曼哈顿距离 
        }
    return dt;  //返回总曼哈顿距离
}

string bfs(string start)
{
    string end = "12345678x";
    unordered_map<string, int> d;   // 距离
    priority_queue<PIS, vector<PIS>, greater<PIS>> heap;  // 小根堆, 将元素的估计终点距离从小到大排序
    unordered_map<string, pair<string, char>> prev;       // 存储一个元素由哪种状态, 经过哪种操作得来, 跟前面几题一样

    heap.push({f(start), start}); // 加入起点
    d[start] = 0;   // 起点到起点的距离为 0
    
    // 将操作数与坐标变化数组一一对应
    char oper[] = "urdl";
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

    // 排序是按照预估距离(当前点到终点)谁距离终点近谁在上面
    while (heap.size())
    {
        auto t = heap.top();    
        heap.pop();
        string state = t.second; // 记录, 真实距离(起点到当前点)

        if (state == end) break;

        int x, y;   // 查找 x 的横纵坐标
        for (int i = 0; i < 9; ++ i )
            if (state[i] == 'x')
            {
                x = i / 3, y = i % 3;
                break;
            }
        
        string source = state;  // 原状态 (方便还原现场)
        for (int i = 0; i < 4; ++ i )
        {
            int a = x + dx[i], b = y + dy[i];
            if (a < 0 || a >= 3 || b < 0 || b >= 3) continue;   // 越界就跳过
            // (x,y):当前坐标, (a,b):偏移后坐标
            swap(state[a * 3 + b], state[x * 3 + y]);   // 交换下标位置
            if (!d.count(state) || d[state] > d[source] + 1) // 如果没有被记录或者小于记录
            {
                d[state] = d[source] + 1;     // 更新距离
                heap.push({f(state) + d[state], state});  // 加入堆中
                prev[state] = {source, oper[i]};  // 标记是由哪种状态转移而来, 并记录执行操作  
            }
            state = source;   // 因为要扩展到四个方向,所以要还原
        }
    }

    string ans;
    while (end != start)    
    {
        ans += prev[end].second; // 累加上操作顺序 
        end = prev[end].first;   // end 转移到之前的值
    }
    // 因为是倒着取出的, 所以翻转一下
    reverse(ans.begin(), ans.end());
    return ans;
}

int main()
{
    string start, seq;
    char c;
    while (cin >> c)
    {
        start += c;
        if (c != 'x') seq += c;
    } 

    int cnt = 0;    // 统计逆序对数量
    for (int i = 0; i < 8; ++ i )
        for (int j = i + 1; j < 8; ++ j )
            if (seq[i] > seq[j]) ++ cnt;
    
    if (cnt % 2) printf("unsolvable\n");
    else cout << bfs(start) << endl;
    return 0;
}

// 思路: 初始状态进行序列化, 再宽搜所有状态, 搜到的第一个就是
//          1) 每次宽搜判断字符串收否为最终状态
//          2) 判断该状态是否出现过, 没出现过加入到队列中去
//      存储每个状态是由哪个状态转移过来的, 这样就一定能从终点倒推到起点
// 
// 最小字典序输出, 按照 A,B,C 的方式扩展即可
// 
// 队列:|_x_x_x_|_x+1_x+1_x+1_| 
// 在一段 x 中虽然距离一样但对应的操作序列一定不同, 因为如果操作序列相同得到的状态一定相同
// 如果操作序列相同那么得到的 x 也会相同, 遍历重复的点, 这在 BFS 中是不允许的

#include <iostream>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

char g[2][4];
unordered_map<string, pair<char, string>> pre;
unordered_map<string, int> dist;


// 将一维变二维
void set(string state)
{
    for (int i = 0; i < 4; ++ i ) g[0][i] = state[i];
    for (int i = 7, j = 0; j < 4; i --, j ++ ) g[1][j] = state[i]; 
}

// 将二维变成一维
string get()
{
    string res;
    for (int i = 0; i < 4; ++ i ) res += g[0][i];
    for (int i = 3; i >= 0; -- i ) res += g[1][i];
    return res;
}


string move0(string state)
{
    set(state);
    for (int i = 0; i < 4; ++ i ) swap(g[0][i], g[1][i]);
    return get();
}

string move1(string state)
{
    set(state);
    int v0 = g[0][3], v1 = g[1][3]; // 取出最后一列的值
    for (int i = 3; i > 0; -- i )   // 覆盖掉
    {
        g[0][i] = g[0][i - 1];
        g[1][i] = g[1][i - 1];
    }
    g[0][0] = v0, g[1][0] = v1; // 插回去
    return get();
}

string move2(string state)
{
     set(state);
     int v = g[0][1];
     g[0][1] = g[1][1];
     g[1][1] = g[1][2];
     g[1][2] = g[0][2];
     g[0][2] = v; 
     return get();
}

int bfs(string start, string end)
{
    if (start == end) return 0;

    queue<string> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();
        string m[3];
        m[0] = move0(t);
        m[1] = move1(t);
        m[2] = move2(t);

        for (int i = 0; i < 3; ++ i )
            if (!dist.count(m[i]))          // 遍历每一种状态, 将每一种状态加入队列
            {
                dist[m[i]] = dist[t] + 1;   // 新状态距离 = 上一个状态 + 1
                pre[m[i]] = {'A' + i, t};   // pre<cur_state, <操作字典序, pre_state>>     操作字典序就按照 BFS 的顺序
                q.push(m[i]);
                if (m[i] == end) return dist[end];  // 一得到不同状态就返回  
            }
    }
    return -1;
}

int main()
{
    int x;
    string start, end;
    // 倒着 BFS, 从末尾状态 BFS 向开始状态, 这样就可以起到统计路径的作用
    // 从最开始 "复原的状态" 变成输入时 "打乱的状态"
    // 迷宫问题是是从 "终点" 倒推到 "起点" 
    for (int i = 0; i < 8; ++ i )   
    {
        scanf("%d", &x);
        end += char(x + '0');
    }

    for (int i = 1; i <= 8; ++ i ) start += char('0'+ i);

    int step = bfs(start, end);
    cout << step << endl;

    // 获得操作序列
    // 当最终状态不等于起始状态时
    // res 获得 end 前面的状态的字典序
    // end 成为它之前的状态 
    string res; 
    while (end != start)
    {
        res += pre[end].first;      
        end = pre[end].second;
    }
    // 因为是倒着取出来的所以还需要再翻转一下
    reverse(res.begin(), res.end());
    if (step > 0) cout << res << endl;
    return 0;
}

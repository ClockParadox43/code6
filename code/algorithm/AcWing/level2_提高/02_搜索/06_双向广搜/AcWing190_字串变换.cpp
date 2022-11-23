// 该题也是求某个状态变换成另外一个状态最少多少步数, 所以也是一个 BFS 模型
// 因为可变换的状态比较多, 扩展出的可能性也比较多, 所以用双向 BFS
// (感觉搜索长度太宽就用双向 BFS)
// 搜索方法1: A 搜一步, B 搜一步
// 搜索放法2: 看看哪个队列比较短, 优先搜索比较短的队列
// ps:双向 BFS 搜索的时候要扩展一整层的点, 否则答案可能有错

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <unordered_map>    // 那些状态已经搜过了

using namespace std;

const int N = 6;  // 规则数

int n;        // 记录规则数
string A, B;  // 起点, 终点
string a[N], b[N];  // 规则

// 扩展当前同一层的元素, 将与队首同一层的元素全部扩展出来
int extend(queue<string>& q, unordered_map<string, int>& da, unordered_map<string, int>& db,
    string a[N], string b[N])
{
    int d = da[q.front()];      // 取出队首元素的距离
    
    // 如果和队首元素在同一层就一直扩展, 同一层的距离相等, 扩展出的 x + 1 会往队尾放
    while (q.size() && da[q.front()] == d)  
    {
        auto t = q.front();
        q.pop();

        // substr(pos, len):从 pos 位置开始截取 len 个字符
        // 第一层枚举所有规则
        // 第二层枚举所有子串, 判断子串是否能在规则下进行变化
        for (int i = 0; i < n; ++ i )
            for (int j = 0; j < t.size(); ++ j )
                if (t.substr(j, a[i].size()) == a[i])   // 判断当前子串和规则是否相等: sub t 这个状态, 判断经过截取每一位是否可以和规则 a[i] 相等 
                {
                    // 如果相等, 就把 a[i] 替换成 b[i]
                    // 变换之后的结果state:前面不变的部分+ 变化的部分 + 后面不变的部分
                    string r = t.substr(0, j) + b[i] + t.substr(j + a[i].size());
                    // 他两同时搜到一个中间状态说明答案会经过这个中间状态(参考"正着搜再倒着往回走"得到唯一路径)
                    // da[t] + 1 自己到这个状态的距离, db[r] 对面到这个状态的距离
                    if (db.count(r)) return da[t] + db[r] + 1; 
                    if (da.count(r)) continue;      // 如果存在这个状态 continue 掉
                    da[r] = da[t] + 1;
                    q.push(r);
                }
    }
    // 返回 11 表示当前这一层状态已经扩展完了, 返回一个大于 10 的数表示还有步数可以用
    return 11;
}
int bfs()
{
    if (A == B) return 0;
    queue<string> qa, qb;
    unordered_map<string, int> da, db;  // 表示每个 bfs 的距离数组
    
    qa.push(A), qb.push(B);
    da[A] = db[B] = 0;
    // 只要有一个队列为空求说明无解
    // 因为从 "起点/终点" 搜把所有情况都搜完了还没有到对面, 所以无解
    
    // qa 和 qb 都有值, 说明可以扩展过来, 否则说明是不相交的
    int step = 0;
    while (qa.size() && qb.size())
    {
        int t;  // 如果找到了这个状态就会直接返回这个距离
        if (qa.size() < qb.size()) t = extend(qa, da, db, a, b);      // 如果 qa 比较短, 那就先扩展 qa, 变化是把 a 变成 b 
        else t = extend(qb, db, da, b, a);     // ps:正着扩展的时候是将 a 变成 b, 但是倒着扩展的时候是把要把 "终点状态" 往 "起始状态" 推
        
        if (t <= 10) return t; // 如果在 10 步以内找到答案就返回这个解
        if ( ++ step == 10) return -1;  // 每次扩展步数加 1 
    } 
    return -1;
}

int main()
{
    cin >> A >> B;
    while (cin >> a[n] >> b[n]) ++ n;

    int t = bfs();
    if (t == -1) puts("NO ANSWER!");
    else cout << t << endl;
    
    return 0;
}
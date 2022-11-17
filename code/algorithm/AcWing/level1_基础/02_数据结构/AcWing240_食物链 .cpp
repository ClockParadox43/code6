// 并查集可以用来维护很多额外信息
// 如何转化成维护这种额外信息的模型
// 该题是用并查集维护关系的模板题 
//
// 只要直到两个动物之间的关系就可以把他放到一个集合里面去
// 如果告诉我们了 x, y 的关系, 就可以知道 y, z 的关系, 就可以知道 x 和 z 的关系

#include <iostream>

using namespace std;

const int N = 50010;

int n, q;

// p[]:父节点
// d[]:距离
// d[x]存储的永远是 x 到 p[x] 的距离, 其目的是为了求 x 到根节点的距离
int p[N], d[N];

// 足厚返回的是到跟节点之间的距离
// d[x] 是到根节点的距离, 路径压缩后也是到根节点的距离
int find(int x)
{
    if (x != p[x])    // 如果 x 不是树根
    {
        int t = find(p[x]);         
        d[x] += d[p[x]];        // 自己到父亲节点的距离 += 父节点到根节点的距离, 最后自己的祖宗节点变成 t 
        p[x] = t;               // ps:先存储, 否则自己的父亲节点会被覆盖成根节, 那他自己存储的就是父亲节点到根节点的距离
    }
    return p[x];
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++ i ) p[i] = i;
    
    int res = 0;
    while (q -- )
    {
        // t: 说法, x/y: 动物种类
        int t, x, y;            
        scanf("%d%d%d", &t, &x, &y);

        // 满足 x~y 在 1~n 之间
        // 余1: 可以吃根节点
        // 余2: 可以被跟节点吃
        // 余0: 与根节点同类


        // 1) 假话 当前的话中 x 或 y 比 n 大, 就是假话
        if (x > n || y > n) res ++ ;
        else 
        {
            // px: x的根节点, py: y的跟节点
            int px = find(x), py = find(y);
            
            // x 和 y 是同类
            if (t == 1) 
            {
                // x 和 y 到根节点的距离 %3 是不同的, 就判定为假话
                // 因为 %3 的余数是哪一类, x 和 y 就是那一类
                // 他两到根节点如果到 %3 是不同的说明就进了不同的类   
                if (px == py && (d[x] - d[y]) % 3) res ++ ;
                else if (px != py)   
                {
                    // 如果是真话将他们合并到一个集合里面去
                    
                    p[px] = py;          // px 被合并进 py
                    d[px] = d[y] - d[x]; // px ~ 根节点(py) 的距离
                }
            }
            else
            {
                // x 吃 y 的合并
                // 因为 d[x] 比 d[y] 多 1 -> x 吃 y
                // 所以(d[x] - d[y] - 1) % 3 == 0
                if (px == py && (d[x] - d[y] - 1) % 3) res ++;
                else if (px != py)
                {
                    // 说明 x 和 y 不在一个集合
                    // x 比 y 多 1
                    // 因为 d[x] 比 d[y] 多 1
                    // (d[x] + ? - d[y] - 1) % 3 = 0
                    p[px] = py;
                    d[px] = d[y] + 1 - d[x];
                }
            }
        }
    }
    
    printf("%d\n", res);

    return 0;
}
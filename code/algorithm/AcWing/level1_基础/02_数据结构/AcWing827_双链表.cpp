#include <iostream>

using namespace std;

// 左边指向的点, 右边指向的点
// 下标最左边的点是 0 号点, 下标最右边的点是最后的点

const int N = 100010;

// e[i] 表示该点的值是多少
// l[i] 表示该左边点的值是多少
// r[i] 表示该右边点的值是多少
int e[N], l[N], r[N], idx;

// 初始化
// 0 表示左端点, 1 表示右端点
// 左端点和右端点被占用 idx = 2
void init()
{
    
    r[0] = 1, l[1] = 0;
    idx = 2;
}
      
// o <-> k <-> o <-> o  
//        \   /
//          o
// 
// o 的l,r 先指向前后两个端点
// 在 k 后面插入 x
void add(int k, int x)
{
    e[idx] = x;
    r[idx] = r[k];      // 当前节点右边指向 k 右边的指针
    l[idx] = k;         // 当前节点左边指向 k 
    r[k] = idx;         // 将 k 右边的指针指向当前节点
    l[r[idx]] = idx;    // 当前节点右指针指向的节点的左指针指向自己
    idx ++ ;
}

// 删除第 k 个点
// o <-> k <-> 0
void remove(int k)
{
    r[l[k]] = r[k];  // k 做指针指向的节点的右指针指向 k 的右
    l[r[k]] = l[k];
}

int main()
{
    int m;
    cin >> m;
    
    init();
    while (m -- )
    {
        string op;
        int k, x;
        cin >> op;
        
        if (op == "L")
        {
            cin >> x;
            add(0, x);
        }
        else if (op == "R")
        {
            cin >> x;
            add(l[1], x);
        }
        else if (op == "D")
        {
            cin >> k;
            remove(k + 1);
        }
        else if (op == "IL")
        {
            cin >> k >> x;
            add(l[k + 1], x);
        }
        else
        {
            cin >> k >> x;
            add(k + 1, x);
        }
    }
    
    for (int i = r[0]; i != 1; i = r[i]) cout << e[i] << ' ';
    cout << endl;
    
    return 0;
}
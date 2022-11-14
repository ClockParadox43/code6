//struct Node
//{
//	int val;
//	Node* next;
//};
// 
// 因为每一次要向堆区申请节点, 数据量平均在 10w~100w, 这导致会超时
// 所以一般不会采用动态的表达方式
//
// 
// 1) 数组模拟单链表 -> 单链表在笔试或者算法中用的最多的是邻接表
// 2) 数组模拟双链表
// 
// head -> 3 -> 5 -> 7 -> 9 -> / 
//         0    1    2    3
//  
// e[0] = 3, e[1] = 5, e[2] = 7, e[3] = 9
// ne[0] = 5, ne[1] = 7, ne[2] = 9, ne[3] = -1   

#include <iostream>

using namespace std;

const int N = 100010;

// head 会表示头节点的下标
// e[i] 表示节点 i 的值
// ne[i] 表示节点 i 的 next 指针是多少
// idx 存储当前已经到了哪个点
int head, e[N], ne[N], idx;

void init_list()
{
    head = -1;
    idx = 0;
}

// 将 x 插到头结点:
// 1) 将值存入当前节点
// 2) idx 先指向 head 指向值
// 3) head 指向 idx (head指回去)
void add_to_head(int x)
{
    e[idx] = x, ne[idx] = head, head = idx ++ ;                 
}

// 将 x 插到下标是 k 的点后面
// 新节点的 next 指针先指向 k 节点的下一个
// k 指向新节点
int add(int k, int x)
{
    e[idx] = x, ne[idx] = ne[k], ne[k] = idx ++;         
}

// 将下标是k的点后面的点删掉
void remove(int k)
{
    ne[k] = ne[ne[k]];
}

int main()
{
    int q;
    cin >> q;

    init_list();

    // 因为查询是从 1 开始所以 k 要减 1 
    while (q -- )
    {
        int k, x;
        char op;

        cin >> op;
        if (op == 'H')
        {
            cin >> x;
            add_to_head(x);
        }
        else if (op == 'D')
        {
            cin >> k;
            if (!k) head = ne[head];
            else remove(k - 1);
        }
        else
        {
            cin >> k >> x;
            add(k - 1, x);
        }
    }

    for (int i = head; i != -1; i = ne[i]) cout << e[i] << ' ';
    cout << endl;

    return 0;
}


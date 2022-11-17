#include <iostream>

using namespace std;

// 向链表头插入一个数
// 删除第 k 个插入的数后面的数
// 在第 k 个插入的数后插入一个数

const int N = 100010;

int head, e[N], ne[N], idx; 

void init_list()
{
    head = -1, idx = 0;
}

void add_to_head(int k)
{
    e[idx] = k, ne[idx] = head, head = idx ++ ;
}

void add(int k, int x)
{
    e[idx] = x, ne[idx] = ne[k], ne[k] = idx ++ ; 
}



int main()
{
    return 0;
}
#include <iostream>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

// 1) 因为ph[x]里面存的是第x个插入的数在堆里的下标, 所以ph的下标与对应的具体的数是绝对对应的.
//    比如 x 是第三个插入的数, 
//    那么无论你怎么 down 或 up 或 swap, x 永远是第 3 个被插入的数, 即 ph[3] 绝对是x的下标. 
//    所以先把 ph[3] 改成 x 在堆里面的下标, 但是这时候入参其实是 x 在堆里的下标, 所以用 hp[3] 来表示在堆里面的下标
// 
// 2) 这个时候hp没变，ph已经换好了，所以再把hp自己换过来就行了。
//
// 3) 最后把堆上面的值一换，一切就ok了。
// 
// 
// 需要知道第 k 个点插入的是什么
// 第几个插入的是绝对的
// ph[m] = sz: 第 m 个插入的是 sz 号下标  
// hp[sz] = m: 第 sz 号下标是第 m 个插入的
// 交换后得直到是由哪个 ph[i] 转过来的
//
//
// 从第几个插入的点找到堆里的元素
// 又要从堆里的元素找回来


const int N = 100010;

int n, m;
int h[N], ph[N], hp[N], sz;

void heap_swap(int a, int b)
{
    swap(ph[hp[a]], ph[hp[b]]);     // hp 中取出的是第几个插入的, 通过第几个插入的找到正确下标 
    swap(hp[a], hp[b]);             // 第几个交换的次序也变一下
    swap(h[a], h[b]);               // 交换 a, b 位置两个值
}

void down(int u)
{
    int t = u;
    if ((u << 1) <= sz && h[u << 1] < h[t]) 
        t = u << 1;
    if ((u << 1 | 1) <= sz && h[u << 1 | 1] < h[t])  
        t = u << 1 | 1;
    if (u != t)
    {
        heap_swap(u, t);
        down(t);
    }
}


void up(int u)
{
    while (u >> 1 && h[u >> 1] > h[u])
    {
        heap_swap(u >> 1, u);
        u >>= 1;
    }
}

void test()
{
    int n, m = 0;   // m:第几个数插入的
    scanf("%d", &n);
    while (n--)
    {
        char op[10];
        int k, x;

        scanf("%s", op);
        if (!strcmp(op, "I"))       // 插入
        {
            scanf("%d", &x);
            sz++;
            m++;
            ph[m] = sz, hp[sz] = m;     
            h[sz] = x;
            up(sz);
        }
        else if (!strcmp(op, "PM")) printf("%d\n", h[1]);  // 最小
        else if (!strcmp(op, "DM"))  // 删除最小值
        {
            heap_swap(1, sz);
            sz--;
            down(1);
        }
        else if (!strcmp(op, "D")) // 删除
        {
            scanf("%d", &k);
            k = ph[k];
            heap_swap(k, sz);    // 将第 k 个插入的和末尾的数交换
            sz--;
            down(k), up(k);
        }
        else    // 修改第 k 个数改为 x
        {
            scanf("%d%d", &k, &x);
            k = ph[k];                 // 取出第 m 个插入的下标 sz
            h[k] = x;                  // 将该号下标的值改为 x
            down(k), up(k);
        }
    }
}

int main()
{
    test();
    return 0;
}

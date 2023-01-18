// 先建一个全部为0的数组, 如果开灯就改为1. 如果关灯就再改回1
#include <iostream>

using namespace std;
const int MAXN = 1e6 + 4;

int n;
double x, y;
int st[MAXN];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)       // 一共操作 n 次, 每次操作都是将 a..ta(编号) 的开关各按 1 次
    {
        
        cin >> x >> y;
        for (double j = 1; j <= y; ++j)
            if (!st[int(j * x)]) st[int(j * x)] = 1;    // [a...2*a...3*a...k*a]
            else st[int(j * x)] = 0;
    }

    for (int i = 1; ; ++i)
        if (st[i])
        {
            cout << i;
            break;
        }


    return 0;
}
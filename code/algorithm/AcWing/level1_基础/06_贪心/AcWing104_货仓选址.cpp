
// 求所有点到货仓的距离
// f(x) = |x1-x| + |x2-x| + ... |(xn-1)-x| + |xn-x|
// 将第 1 个数合第 n 个数分成一组, 第 2 个数和第 n-1 个数分成一组
// 当 x 取中间的时候, 他们的距离是 a~b 的值
// 1 5 10
// 1 3 10

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n;
int q[N];

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) scanf("%d", &q[i]);

    sort(q, q + n);

    int res = 0;
    for (int i = 0; i < n; ++i) res += abs(q[i] - q[n / 2]);

    cout << res << endl;

    return 0;
}




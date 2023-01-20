#include <iostream>

using namespace std;
const int MAXN = 1003;

int a[MAXN], b[MAXN], c[MAXN];

int main()
{
    string A, B; cin >> A >> B;
    int len = max(A.size(), B.size());

    // 将低位存在最上面
    for (int i = A.size() - 1, j = 1; i >= 0; -- i, ++ j)
        a[j] = A[i] - '0';
    for (int i = A.size() - 1, j = 1; i >= 0; -- i, ++ j)
        b[j] = B[i] - '0';
    
    for (int i = 1; i <= len; ++ i)
    {
        c[i] += a[i] + b[i];    // 将低位加上
        c[i + 1] = c[i] / 10;   // 模拟进位
        c[i] %= 10;
    }

    if (c[len + 1]) len ++ ;
    for (int i = len; i >= 1; -- i)
        cout << c[i];
    return 0;
}

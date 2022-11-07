#include <iostream>

using namespace std;
// using std::cout;

// 求 a 的逆元
int main()
{
    int a = 7, m = 3;
    for (int i = 1; i < m; ++ i )
    {
        if (a * i % m == 1) printf("%d\n", i);
    }
    return 0;
}
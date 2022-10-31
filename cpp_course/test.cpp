#include <iostream>

using namespace std;
// using std::cout;

int main()
{
    int res = 1;
    int a = 2, b = 5;
    for (; b; b >>= 1 )
    {
        if (b & 1) res *= a;
        a *= a; 
    }
    // printf("%d", res);
    cout << res << endl; 
    return 0;
}
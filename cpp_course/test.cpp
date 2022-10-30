#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

int main()
{
    int res = 1;
    int a = 2, b = 5;
    for (; b; b >>= 1 )
    {
        if (b & 1) res *= a;
        a *= a; 
    }
    cout << res << endl;
    return 0;
}
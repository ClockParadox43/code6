#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

// 直接看 a 是否为2 * b或2 * b + 1, 或者 b 是否为2 * a或者2 * a + 1
int a, b;

int main()
{
    cin >> a >> b;
    if (a * 2 != b && a * 2 + 1 != b)
        cout << "No" << endl;
    else cout << "Yes" << endl;
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;
const int MAXN = 1004;

int n;
int m[MAXN][MAXN];
bool flag = false;

void rotate()
{
    int tmp = m[0][0];
    m[0][0] = m[1][0];
    m[1][0] = m[1][1];
    m[1][1] = m[0][1];
    m[0][1] = tmp;
}

bool check()
{
    if (m[0][0] < m[0][1] && m[0][0] < m[1][0] && m[0][1] < m[1][1] && m[1][0] < m[1][1])
        return true;
    return false;
}

int main()
{
    scanf("%d", &n);
    while (n--)
    {
        cin >> m[0][0] >> m[0][1] >> m[1][0] >> m[1][1];
        for (int i = 0; i < 4; ++i)
        {
            rotate();
            if (check()) { flag = true; break; }
        }
        if (flag) puts("Yes");
        else puts("No");
        flag = false;
    }
    return 0;
}
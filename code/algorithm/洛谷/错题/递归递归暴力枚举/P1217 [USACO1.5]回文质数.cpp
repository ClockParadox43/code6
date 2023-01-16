#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;
typedef long long LL;
const LL MAXN = 1e8;

int a, b, cnt;
int primes[MAXN];
bool st[MAXN];

void is_prime(int n)
{
    for (int i = 2; i <= n; ++i)
        if (!st[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j <= n; j += i) // j 删除 i 的所有倍数 
                st[j] = true;
        }
}

// 既然回文数正反一样, 那么我们就把它倒过来
bool is_palindrome(int x)
{
    int tmp = x, ans = 0;
    while (tmp)
    {
        ans = ans * 10 + tmp % 10;
        tmp /= 10;
    }
    if (ans == x) return true;
    else return false;
}

int main()
{
    scanf("%d%d", &a, &b);

    // b <= 10000000 这个判断条件来自: 除了11以外, 一个数的位数是偶数的话, 不可能为回文数素数
    // 如果一个回文素数的 "位数是偶数", 则它的 "奇数位上的数字和" 与 "偶数位上的数字和" 必然相等, 
    // 根据数的整除性理论, 容易判断这样的数肯定能被11整除, 所以它就不可能是素数
    if (b >= 10000000)
        b = 9999999;

    is_prime(b);

    if (a > b) return 0;

    if (!(a % 2)) a++;
    for (int i = a; i <= b; i += 2)
        if (!st[i] && is_palindrome(i))
        {
            printf("%d%c", i, 0x0A);
        }
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS

// 应用场景: 字符串匹配难度在于它太长了, 每次需要把模式串跑一遍
//           效率很低, 将字符串转化成数字, 再进行匹配
// 
// Hash算法核心思想:
//      如果两个字符串相同, 那么他们转化成的数字一定是相同的, 反之则一定不同
// 我们考虑将转化的数字对同一个大数字取模, 从而使得它的长度可以接受, 那么如果
// 两个字符串相同, 他们转换成的数字取模后一定相同, 反过来有 "极大" 概率不同,

#include <iostream>
#include <string.h> 

using namespace std;
const int MAXN = 100005, mod = 1e9 + 7, u = 131;
struct HashTable        // 取出 s[l~r] 的 O(1) 的作法
{
    // const int mod = 1e9 + 7, u = 131;

    // h[]:表示 1...i 的哈希值是多少
    // b[]:表示 u^i 是多少
    int h[MAXN], b[MAXN];

    void build(char* s)
    {
        int len = strlen(s + 1);
        b[0] = 1;   // b^0
        for (int i = 1; i <= len; ++i)
            b[i] = 1ll * b[i - 1] * u % mod;
        for (int i = 1; i <= len; ++i) 
            h[i] = (1ll * h[i - 1] * u + s[i] - 'a' + 1) % mod;
    }

    // 如何将子串的 Hash 值提取出来
    int getHash(int l, int r)
    {
        return (h[r] - 1ll * h[l - 1] * b[r - l + 1] % mod + mod) % mod;
        // 前半段:h[r]
        // 后半段h[r-1] * b[r-l+1] 次方
    }
}Hash1, Hash2;


// 当前的结果乘 u 再加上这一位
int Hash(char* s)
{
    int ans = 0, len = strlen(s + 1);
    for (int i = 1; i <= len; ++i)
        ans = (1ll * ans * u + s[i] - 'a' + 1) % mod;
    return ans;
}

void test_HashTable()
{
    // char s1[10] = "eqeabc";
    // char s2[10] = "abcfe";

    int n, m;
    scanf("%d%d", &n, &m);
    char s1[MAXN], s2[MAXN];
    scanf("%s%s", s1 + 1, s2 + 1);
    Hash1.build(s1); Hash2.build(s2);
    // int n = strlen(s1), m = strlen(s2);

    for (int i = 1; i <= n - m + 1; ++i)
    {
        if (Hash1.getHash(i, i + m - 1) == Hash2.getHash(1, m))
            printf("%d\n", i);
    }
}

int main()
{
    // int n, m;
    // scanf("%d%d", &n, &m);
    // scanf("%s%s", s + 1, t + 1);
    // char s[MAXN] = "adsdsadr"; 
    // printf("%d", Hash(s));

    test_HashTable();

    return 0;
}
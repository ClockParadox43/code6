
// 将数字变成 字符串 比较 拼接后的大小
// 只要前面的位大, 就可以忽略后面的位, 可以使用贪心解决, 把对字典序贡献最大的放在前面
#include <iostream>
#include <algorithm>

using namespace std;

string s[30];

bool cmp(string& a, string& b)
{
    return a + b > b + a;
}

int main()
{
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) cin >> s[i];
    sort(s + 1, s + 1 + n, cmp);
    for (int i = 1; i <= n; ++ i ) cout << s[i];
    return 0;
}
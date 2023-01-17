#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cctype>       // 这是一个拥有许多字符串处理函数声明的头文件, 这些函数可以用来对单独字符串进行分类和转换:isalpha()
#include <cstdio>
#include <cstring>

using namespace std;

int n, x, y;
char ss[20], ans[100], k;

// isalpha():检查这个字符是否为字母, 真返回1, 假返回0
// sscanf(s, "%d", &a): 从 char s[] 中读取一个整数 a
// sprintf(s, "%d", &a): 将一个 int a, 输出到一个字符串种
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", ss);
        if (isalpha(ss[0])) // 如果是字符 op
        {
            k = ss[0];
            scanf("%d%d", &x, &y);
        }
        else
        {
            x = atoi(ss);   // 如果是数字将字符串转化成数字
            scanf("%d", &y);
        }
        if (k == 'a') sprintf(ans, "%d+%d=%d", x, y, x + y);
        else if (k == 'b') sprintf(ans, "%d-%d=%d", x, y, x - y);
        else sprintf(ans, "%d*%d=%d", x, y, x * y);
        printf("%s\n%d\n", ans, strlen(ans));
    }
    return 0;
}
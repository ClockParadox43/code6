// 我们习惯性从可以看到的开始考虑
// 其实可以多方面考虑
// 找到最高的, 这样就方便低的输出空格个

#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;
const int MAXN = 104;

char s[MAXN];
int cnt[MAXN];

int main()
{
    for (int i = 0; i < 4; ++i)
    {
        memset(s, '\0', sizeof s);
        gets(s);    //gets读入
        for (int i = 0; s[i]; ++i)
            cnt[s[i] - 'A'] ++;
    }

    int maxn = -1;
    // 做多出现次数(最高圆柱), 奠定底
    for (int i = 0; i < 26; ++i) maxn = max(maxn, cnt[i]);

    for (int i = maxn; i > 0; --i)
    {
        for (int j = 0; j < 26; ++j)
            if (cnt[j] >= i) printf("* ");
            else printf("  ");
        puts("");
    }
    for (int i = 0; i < 26; ++i) printf("%c ", i + 'A');
    return 0;
}
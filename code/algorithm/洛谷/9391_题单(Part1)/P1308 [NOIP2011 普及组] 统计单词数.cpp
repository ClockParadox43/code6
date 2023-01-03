#include <cstring>
#include <cstdio>
#include <cctype>

void strlow(char *str)
{
    for (int i = 0; str[i]; ++ i )
    {   
        if (str[i] == ' ') continue;
        if (str[i] <= 90) str[i] += 32;
    }
}

int main()
{
    // s[]:要找的文章, w[]:要找的单词
    // p 和 q 是指针, 分别代表当前搜索到什么地方和最后一次找到的单词指针
    char s[1000005], w[15], *p, *q;
    gets(w), gets(s);
    strlow(w), strlow(s);       // 小写
    
    bool flag = false;      //  判断是否找到
    int ans = 0, ansl = -1; // 个数和首次出现的位置, ans1 的初值是 -1 是因为在没找到的时候就直接输出就行了, 省事

    int len = strlen(w);        // 单词长度

    p = s;   // 将指针设置为全部文章

    // 循环, strstr是在一个字符串里面给定一个字符串, 寻找有没有这个字符串, 若有, 返回首次出现的指针否则返回 NULL (空指针)
    // strstr(p, w): 文章里是否有目标单词
    for (; q = strstr(p, w); )
    {
        if (q != NULL  // 找到了
        && (q == s || *(q - 1) == ' ')  // 第一个条件是防止开头的越界, 第二个是判断前一个是不是空格
        && (*(q + len) == '\0' || *(q + len) == ' ')) // 如果后面也是空格
        {
            ++ ans;
            if (!flag)
            {
                flag = true;
                ansl = q - s; // 第一个位置, q(新单词开头的位置) - 起点位置 = 起点 到 q 的距离
            }
        }
        p = q + len;        // 刷新指针(正好加至空格), 最后一次开始找的位置 + 单词的长度
    }   

    if (flag) printf("%d %d", ans, ansl);
    else printf("%d", ansl);
    return 0;
}
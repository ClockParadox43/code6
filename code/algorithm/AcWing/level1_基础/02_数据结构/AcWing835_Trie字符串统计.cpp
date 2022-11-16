#include <iostream>

using namespace std;

const int N = 100010;

// son[][26]: 每个节点最多只会向外连 26 条边
// cnt[]: 以当前单词结尾的单词有多少个
//   idx: 当前用到的哪个下标
// 下标是 0 的点, 即是根节点, 又是空节点
int son[N][26], cnt[N], idx;    
char str[N];

void insert(char* str)
{
    int p = 0;
    for (int i = 0; str[i]; ++ i )
    {
        int u = str[i] - 'a';                           // 算出要映射的位置 0~25
        if (!son[p][u]) son[p][u] = ++ idx ;            // 如果不存在该节点, 创建出一个新的
        p = son[p][u];
    }
    cnt[p] ++ ;
}

int query(char* str)
{
    int p = 0;
    for (int i = 0; str[i]; ++ i )
    {
        int u = str[i] - 'a';
        if (!son[p][u]) return 0;           // 如果不存在该单词直接 return 0
        p = son[p][u];
    }
    
    return cnt[p];      // 返回以 p 结尾的单词数量
}

int main()
{
    int n;
    scanf("%d", &n);
    while (n -- )
    {
        char op[2];
        scanf("%s%s", op, str);
        if (op[0] == 'I') insert(str);
        else printf("%d\n", query(str));
    }
    return 0;
}
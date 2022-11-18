#include <iostream>

using namespace std;

const int N = 100010;

// 小节: 如果有相同的字符, cnt[p] 对应的字母数量 ++  
//       如果不是相同字母, 一定会另开节点, idx一直在累加, 一定是之前没有的

// son[][26]: 每个节点最多只会向外连 26 条边
// cnt[]: 以当前单词结尾的单词有多少个
//   idx: 序号是独一无二的, 层数 + 字符都能有一个独一无二的 idx
// 下标是 0 的点, 即是根节点, 又是空节点,
int son[N][26], cnt[N], idx;    
char str[N];

// 下次有类似的前缀还可以根据这个 idx 找到
void insert(char* str)
{
    int p = 0;
    for (int i = 0; str[i]; ++ i )
    {
        int u = str[i] - 'a';                           // 算出要映射的位置 0~25
        if (!son[p][u]) son[p][u] = ++ idx ;            // 注意是当前第 p 层, 如果不存在该节点, 创建出一个新的, ++ idx 可以让 p 直接往下跳
        p = son[p][u];                                  // 因为 son 里面存的是 idx, 所以 p = son[p, u] 可以来到之前出现过的节点, 像一种映射
    }
    cnt[p] ++ ;                 // 如果这个 idx 没有被记录过就 ++ 
}

// 没有该字符会返回 0, 如果是子串且不存在, 那么就不会记录以这个单词 idx
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
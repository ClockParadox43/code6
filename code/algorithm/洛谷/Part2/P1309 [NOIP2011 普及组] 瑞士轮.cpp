#include<iostream> 
#include<algorithm>    

using namespace std;

int n, r, q;
int a[200100], win[200100], lose[200100];
int s[200100], w[200100];

bool cmp(int x, int y)
{
    if (s[x] == s[y])   
        return x < y;
    return s[x] > s[y];
}

// 大家可以发现, 归并排序每次的操作只针对相邻区间, 或者说合并时是对相邻几个区间的操作, 
// 所以这符合只需要修改相邻几个分数的排布状况的题意
void merge()
{
    int i, j;
    i = j = 1, a[0] = 0;
    
    while (i <= win[0] && j <= lose[0])
        if (cmp(win[i], lose[j]))           // cmp 传入的为编号, 对手之间对比分数(失败方和胜利方)
            a[++a[0]] = win[i++];           // 更高的分数, 该编号优先放入 a[] (重新 按照分数进行排序） 
        else
            a[++a[0]] = lose[j++];       

    while (i <= win[0])
        a[++a[0]] = win[i++];
    while (j <= lose[0])
        a[++a[0]] = lose[j++];
}

int main()
{
    cin >> n >> r >> q; n *= 2;
    
    for (int i = 1; i <= n; i++)a[i] = i;
    for (int i = 1; i <= n; i++)cin >> s[i];
    for (int i = 1; i <= n; i++)cin >> w[i];
    
    // 根据 s[] 数组排序 a[] -> 制定对战名次 
    // 再利用排序后的编号查找到 对应的 w[i] 和 s[i]
    sort(a + 1, a + n + 1, cmp);
    
    for (int i = 1; i <= r; i++)
    {
        win[0] = lose[0] = 0;
        for (int j = 1; j <= n; j += 2)
            if (w[a[j]] > w[a[j + 1]])      // 此时获得的 id 已经排序好了
            {
                s[a[j]]++;
                win[++win[0]] = a[j];
                lose[++lose[0]] = a[j + 1];
            }
            else
            {
                s[a[j + 1]]++;
                win[++win[0]] = a[j + 1];
                lose[++lose[0]] = a[j];

                // 胜利方分数加一
                // win[0] 位置加 1, wini 的位置被赋值为 - 胜利方编号
                // lose[0] 位置加 1, losei 的位置被赋值为 - 失败方编号 
                // 这轮循环下来, win[] 里存的 当前轮的胜利方编号
                // lose[] 存的就是当前轮失败方编号
            }

        // 顺序是按照分数来排的
        // 我们下一轮要比的是分数更高的, 我们根据 w 已经将胜利方和失败方划分好
        // 因为归并排序相对顺序不会变, 之所以会出现 在 下一组分数 一定比 当前组 更低 (胜利方和失败方内部一定是有序的)
        // 将失败方和胜利方划分好, 相当于已经有序了(之前就有序, 每次衡量 + 1, 还是有序)
        // 组数两两之间比, 大的先走
        merge();
    }
    
    cout << a[q];
    return 0;
}
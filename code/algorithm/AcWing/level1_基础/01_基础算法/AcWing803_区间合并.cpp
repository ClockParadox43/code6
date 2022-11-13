
// 区间合并应用场景, 
// 区间合并算法: 有很多区间, 快速将有交集的区间合并起来
//
// 1) 将区间以后按照左端点进行排序(使得相邻的线段靠在一起)
// 2) 遍历所有线段, 如果 ed 大于新线段的开头, 说明是重合的
//    更新更长的末尾即可
// 3) 如果没有重合, 加入新的线段
//
// ps: 每个线段是是先合并再 push_back()
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n;
vector<PII> segs;

void merge(vector<PII>& segs)
{   
    vector<PII> res;
    sort(segs.begin(), segs.end());     // 按照左端点进行排序, 自动按照 first 进行排序

    int st = -2e9, ed = -2e9;
    for (auto seg : segs)     
        if (ed < seg.first)     
        {
            if (st != -2e9) res.push_back({st, ed});    // 不能是初始区间
            st = seg.first, ed = seg.second;
        }
        else ed = max(ed, seg.second);
    
    // 如果有区间的话, 将最后的区间加入答案
    if (st != -2e9) res.push_back({st, ed});    
    segs = res;
}

int main()
{
    scanf("%d", &n);

    // 初始化区间
    for (int i = 0; i < n; ++ i )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        segs.push_back({l, r}); 
    }

    merge(segs);

    printf("%d", segs.size());
    
    return 0;
}
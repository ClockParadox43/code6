#include <iostream>
#include <algorithm>

using namespace std;
const int MAXN = 1e5 + 6;

int n;
PII segs[MAXN];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i)
    {
        int l, r; scanf("%d%d", &l , &r);
        segs[i] = {l, r};
    }

    sort(segs, segs + n);   // 按照左端点排序

    int cnt = 0;
    int st = -1e9 + 1, ed = -1e9 + 1;
    for (int i = 0; i < n; ++ i)
    {
        if (ed < st)    // 有新的线段出现
            cnt ++, st = segs[i].first, ed = segs[i].seocnd;
        else 
            ed = ed;        // 扩大范围
    }   
    cout << cnt << endl;
}
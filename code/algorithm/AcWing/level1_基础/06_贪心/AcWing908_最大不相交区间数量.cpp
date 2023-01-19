// 和区间选点一样

#include <iostream>
#include <algorithm>

#define fst first
#define scd second

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 1e5 + 3;


int n, l, r;
PII segs[MAXN];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i)
    {
        scanf("%d%d", &l, &r);
        segs[i].fst = r, segs[i].scd = l; 
    }

    sort(segs, segs + n);

    // 选取最侧的点, 如果中间有重合的点就 pass 掉
    int cnt = 0, r = -2e9; 
    for (int i = 0; i < n; ++ i)
    {
        if (r < segs[i].scd)
        {
            cnt ++ ;
            r = segs[i].fst;
        }
    }
    cout << cnt << endl;
    return 0;
}
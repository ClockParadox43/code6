#define _CRT_SECURE_NO_WARNINGS

// 这种思考方式像是差分, 所以可以尝试用差分的思想写

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

struct node
{
    ll x, c;
    bool operator<(const struct node& T)
    {
        // 如果两个线段相等, 就用正负标记进行盘段, 将右区间优先排在前面
        if (x == T.x) return c < T.c;
        else return x < T.x;
    }
};
vector<node> v;

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0);

    ll n; cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        ll l, r; cin >> l >> r;
        v.push_back({ l, 1 });          // 左端点不加, 右端点加1
        v.push_back({ r + 1, -1 });
    }

    sort(v.begin(), v.end());

    ll cnt = 0, res = 0;
    for (auto& i : v)
    {
        cnt += i.c;
        res = max(res, cnt);
    }

    cout << res << endl;
    return 0;
}
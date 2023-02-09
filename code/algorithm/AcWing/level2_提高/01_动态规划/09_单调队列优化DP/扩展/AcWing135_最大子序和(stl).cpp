#include <iostream>
#include <queue>

#define repe(i, a, n) for (int i = a; i <= n; ++ i)
using namespace std;
typedef long long ll;

const int N = 3000100;

deque<ll> q;
ll n, m, l, r;
ll s[N], ans = -1e9;

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    repe(i, 1, n)
    {
        cin >> s[i];
        s[i] += s[i - 1];
    }
    q.push_back(0);
    repe(i, 1, n)
    {
        while (q.size() && q.front() < i - m) // 如果队头无法满足区间长度<m, 就弹出
            q.pop_front();             
        ans = max(ans, s[i] - s[q.front()]);    // 取当前最优值
        // sum[j]要尽量的小, 为了使得区间和最大
        while (q.size() && s[q.back()] >= s[i]) // 如果队尾>当前值
            q.pop_back();
        q.push_back(i); 
    }
    cout << ans;
    return 0;
}


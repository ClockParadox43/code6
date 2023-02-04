#include <iostream>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10, M = 2e5 + 10;

int n, m, ans;
int p[N];

int find(int x)
{
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}
int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; ++ i ) p[i] = i;
    for (int i = 0; i < m; ++ i)
    {
        int a, b; cin >> a >> b;
        
        if (pa != pb)
            p[pa] = p[pb];
        else ans ++ ;
    }    
    cout << ans << endl;
}
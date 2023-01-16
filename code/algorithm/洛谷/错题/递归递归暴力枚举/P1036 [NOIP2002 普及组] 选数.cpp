#include <iostream>

using namespace std;
int const MAXN = 25;
typedef long long LL; 

int n, k;
int a[MAXN], t[MAXN];
int ans;

bool prime(int a)
{
    for (int i = 2; i * i <= a; ++ i)
        if (!(a % i)) return false;
    return true; 
}

// startx:利用不降序进行去重
// n 个 数字, 可以选择 x 个. 可以利用这个进行去重, 全部选择的话一定不够选
// 例 n = 3, 当你选择完 123 后, 之后只能从 2 开始选, 但是你必须选满 3 个
// 因为保证不降序, 你到 2 时只是选了 2 个, 返回到最上面, 从 2 开始选, 下一层你会从 3(i+1)开始选
// 数量不够
// 所以无论哪种数字方案数量都只有一种
// 
// 只能从之前栈帧的的后面开始选, 后面的数选完后才会往上返回
// 所以达到了去重的效果
void dfs(int u, int sum, int startx)
{
    if (u == k)
    {
        if (prime(sum)) ++ ans;
        return;
    }

    for (int i = startx; i < n; ++ i)
        dfs(u + 1, sum + a[i], i + 1);
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++ i) scanf("%d", &a[i]);
    dfs(0, 0, 0);
    printf("%d\n", ans);
    return 0;
}
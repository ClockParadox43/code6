/*
    因为发现二叉树上被固定的前缀越长, 二叉树上的右儿子就组成了限定值, 既然能组成限定值
    那么范围也就确定下来了
    所以我们就可以发现可以用求组合数求出所有的组合方案再利用前缀和f(r)-f(l-1)求出范围中的数

    我们从高位开始分类讨论
    当前位的后面还有n位, 并且当前位前面已经写了last个1, 而我们一共要写k个1
    情况1_
        a.如果当前位也写了1, 那么我们只能从后面的n位中选择k-last-1个1
        b.如果当前位写了0, 那么我们可以从后面n位中选择k-last个1
            两个组合数加在一起, 就是该分类下的
    情况2_
        该位写a, 我们继续需要分类讨论, 但是如果a是1的话, 我们需要更新一下1的个数
    
    由于这道题只需要0和1, 所以题目有了一定的简化
    如果该位最大是a, 并且a是>1的, 那么我们写0还是1都不会超过上限, 此时不用继续再分类讨论
    直接得出结果即可
    所以, 如果该位>1, 那么我们直接求出两个组合数加在一起, 终止讨论
            - a=1, 按照数位DP进行左右分支的讨论
            - a=0, 那么这位只能填0
    分类到最后, 我们还需要判断一下刚才描绘的那棵数的右分支组成的树
    即上限值, 是否满足条件, 如果满足条件还需要对结果+1
*/ 
#include <iostream>
#include <vector>

using namespace std;

const int N = 40;

int C[N][N];
int x, y, k, b;

void init()
{
    for (int i = 0; i <= N; ++ i)
        for (int j = 0; j <= i; ++ j)
            if (!j) C[i][j] = 1;
            else C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
}

int dp(int n)
{
    int res = 0, res = 0;
    vector<int> v;
    while (n) v.push_back(n % b), n /= b;
    for (int i = v.size() - 1; i >= 0; -- i)
    {
        int x = v[i];
        if (x)
        {
            if (a > 1)  // a>1的时候直接返回, 限定值>1, 后面的数随便选, 因为本来就是从高位开始枚举的
            {
                if (k - last - 1 >= 0) res += C[i][k - last - 1];
                if (k - last >= 0) res += C[i][k - last];
                break;
            }
            else    // a=1的时候
            {
                if (k - last >= 0) // 分类讨论中的左支：这一位写0，后面随别写
                    res += C[i][k - last];
                ++ last; // 分类讨论的右边：这一位写了1，所以1的数目++
            }
        }
        if (!i && last == k) ++ res; // 到底了, 那么也算一种方案数,算上
    }
    return res;
}

int main()
{
    init();
    cin >> x >> y >> k >> b;
    cout << dp(y) - dp(x - 1) << endl;
    return 0;
}
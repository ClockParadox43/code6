// u 是从 1 开始的 1~5
// 1 2 3 
// 1 2 4 
// 1 2 5 
// 1 3 4 
// 1 3 5 
// 1 4 5 
// 2 3 4 
// 2 3 5 
// 2 4 5 
// 3 4 5
// 以上述例子来说, 就是 u 枚举到 4 的时候, 剩下的数不够选了, v.size() + (n - u + 1) < m
//
// 因为是选出有限的 m 个数, 且不能重复, 所以本质也是指数型枚 
// 其实只需要把例1的代码稍加修改就可以了
// 再增加两个情况, 一种是动态数组所选择的数已经超过了m个, 或者剩余的数凑不够m个, 排除这两种情况就是我们所要的答案了
#include <iostream>
#include <vector>

using namespace std;

int n,m;
vector<int> num;

void dfs(int k)
{
    //如题解所述
    // n = 5, k = 4
    // size = 0, 总数 - 枚举到的数 (没明白为什么 + 1)
    if(num.size() > m || num.size() + (n - k + 1) < m) return;
    //到达枚举边界，输出结果并结束
    if(k == n + 1)
    {
        for(int i = 0; i < num.size(); ++ i ) cout << num[i] << " ";
        cout << endl;
        return;
    }

    //选择这个数
    num.push_back(k);
    dfs(k+1);
    //回溯
    num.pop_back();

    //不选择这个数
    dfs(k+1);
}

int main(void)
{
    cin >> n >> m;
    dfs(1);
    return 0;
}


#include <iostream>
#include <vector>

using namespace std;

// 在同等代的层面上继续处理相同的问题选择不同的结果

int n;
vector<int> v;

void dfs(int x)
{
    if (x == n + 1) 
    {
        for (int i = 0; i < v.size(); ++ i ) printf("%d ", v[i]);
        cout << endl;
        return ;
    }
    
    dfs(x + 1);
    v.push_back(x);
    dfs(x + 1);
    v.pop_back();
}

int main()
{
    scanf("%d", &n);
    dfs(1);
    return 0;
}
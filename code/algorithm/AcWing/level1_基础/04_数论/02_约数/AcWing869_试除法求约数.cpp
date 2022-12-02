#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> get_divisors(int n)
{
    vector<int> ans;
    for (int i = 1; i <= n / i; ++ i )
    {
        if (n % i == 0)                 // 约数就记录
        {
            ans.push_back(i);
            if (i != n / i) ans.push_back(n / i);       // 另一个约数
        }
    }
    return ans;
}

int main()
{
    int _ ; 
    scanf("%d", &_);
    
    while (_ -- )
    {
        int n;
        scanf("%d", &n);
        vector<int> ans = get_divisors(n);
        sort(ans.begin(), ans.end());
        
        for (int e : ans) cout << e << ' ';
        cout << endl;
    }
    return 0;
}
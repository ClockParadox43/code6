#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



void solveI()
{
    int t;
    while (t -- )
    {
        int arr[4];
        for (int i = 0; i < 4; ++ i)
            cin >> arr[i];

        int maxi = arr[0], mini = arr[0];
        int a = 0, b = 0;
        for (int i = 0; i < 4; ++ i)
        {
            if (arr[i] > maxi) { a = i; maxi = arr[i]; }        
            if (arr[i] < mini) { b = i; mini = arr[i]; }
        }
        // 因为相对位置不会变, 只有相对位置不变, 才会转到符合条件的位置
        // 最大和最小一定在相反的角落 1/3, 2/0
        // 
        // 因此, 我们需要做的就是检查最小元素和最大元素是否位于相反的角落. 有很多方法可以做到这一点;
        // 在我看来, 最优雅的是阅读大小为 4 的数组中的所有四个元素; 
        // 然后矩阵的相对角对应于此数组中的位置 0 和 3, 或对应于位置 1 和 2. 
        // 因此, 我们检查最小值和最大值的仓位总和正好是 3 
        if (a + b == 3) cout << "Yes" << endl;      
        else cout << "No" << endl;
    }
}

void solveII()
{
    int t; cin >> t;
    while(t -- ) 
    {
        vector<int> a(4);
        for(int i = 0; i < 4; i ++ ) cin >> a[i];
 
        int maxpos = max_element(a.begin(),a.end()) - a.begin();    // 算出 maxi 的下标
        int minpos = min_element(a.begin(),a.end()) - a.begin();    // 算出 mini 的下标
        
        if(maxpos + minpos == 3) puts("YES");
        else puts("NO");
    }
}

int main()
{
    solveI();
    // solveII();
    return 0;
}
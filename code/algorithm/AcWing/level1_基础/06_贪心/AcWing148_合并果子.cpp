// 经典哈夫曼树的模型, 每次合并重量最小的两堆果子即可(最终合并成一个点)
//
// (a+b + c+d + a+b+c+d + e+f)*2
//          *
//        /   \
//       *     * 
//      / \   / \
//      * *   * *
//     /\ /\
//     ** **
//     ab cd
// 
// 每次合并要加上代价
// 1 2 9
// 3
// 3 + 9 = 12
// 12 + 3
// 
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 10010;

int n;

int main()
{
    scanf("%d", &n);
    
    priority_queue<int, vector<int>, greater<int>> heap;
    
    for (int i = 0; i < n; ++ i ) 
    {
        int x;
        scanf("%d", &x);
        heap.push(x);
    }
   
    int res = 0;
    while (heap.size() > 1)
    {
        int a = heap.top();
        heap.pop();
        int b = heap.top(); 
        heap.pop();
        
        res += a + b;
        heap.push(a + b);
    }
    
    cout << res << endl;
    return 0;
}
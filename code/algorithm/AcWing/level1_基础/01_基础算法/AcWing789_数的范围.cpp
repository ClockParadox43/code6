#include <iostream>

using namespace std;

const int N = 100010;

int q[N];

int main()
{
    int n, _; scanf("%d%d", &n, &_);
    for (int i = 0; i < n; ++ i ) scanf("%d", &q[i]);
    
    while (_ -- )
    {
        int x;
        scanf("%d", &x);
            
        // 找左边最大, 右边二分过来
        int l = 0, r = n - 1;
        while (l < r)
        {
            int m = l + r >> 1;
            if (q[m] >= x) r = m;       // 如果中位数更大, 那么 x 就在中位数左边, 所以 r 二分过来 
            else l = m + 1;
        }
        
        if (q[l] != x) printf("-1 -1\n");
        else
        {
            printf("%d ", l);
            
            // 找右边最大, 左边二分过来
            l = 0, r = n - 1;
            while (l < r)
            {
                int m = l + r + 1>> 1;
                if (q[m] <= x) l = m;
                else r = m - 1;
            } 
            printf("%d\n", l);
        }
    }
    return 0;
}
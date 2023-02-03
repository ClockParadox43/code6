// f[i]状态表示: 前i家店铺抢到的最大收益
//         属性: max
//     状态计算: 
//          不抢第i家店铺: f[i - 1]
//            抢第i家店铺: f[i - 2] + w 
#include <iostream>

using namespace std;

const int N = 1e5 + 5;
int T, n;
int f[N];

int main()
{
    cin >> T;
    while (T -- )
    {
        cin >> n;
        for (int i = 2; i <= n + 1; ++ i) 
        {
            int w; cin >> w;
            f[i] = max(f[i - 1], f[i - 2] + w);
        }
        cout << f[n + 1] << endl;
    }
    return 0;
}
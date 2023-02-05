#include<iostream>
#include<algorithm>

using namespace std;

const int N=210, INF=0x3f3f3f3f;

int n;
int a[N];
int g[N][N];

int main()
{
    cin >> n;
    for(int i = 1;i <= n;i ++ )
    {
        cin >> a[i];
        a[i + n] = a[i];
    }

    for(int len = 1;len <= n;len ++ )
        for(int i=1;i + len-  1 <= n * 2;i ++ )
        {
            int l = i, r = i + len - 1;
            if(len == 1) g[l][r] = 0;
            for(int k = l; k < r; k ++ ) 
                g[l][r] = max(g[l][r], g[l][k] + g[k+1][r] + a[l] * a[k+1] * a[r+1]);
            // 这里的过程同石子合并，这里不难想到若将l到k的珠子合并之后会变成一个首是l而尾k+1的珠子；
            // 同理若将k+1到r的珠子合并之后会变成一个首是k+1而尾r+1的珠子；
        }
        
    int maxv = -INF;
    for(int i = 1;i <= n;i ++ )
        maxv = max(g[i][i+n-1], maxv);// 区间长度为n
    cout << maxv << endl;
    return 0;
}

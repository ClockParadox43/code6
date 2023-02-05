#include<bits/stdc++.h>
using namespace std;
const int N =  55;
inline __int128 read(){
    __int128 x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void print(__int128 x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
__int128 f[N][N];
__int128 w[N];
const __int128 inf = 1e27;
int main(){
    int n;
    cin >>n;
    for(int i =1 ; i <= n ; i++) w[i] = read();
    for(int len = 3; len <= n; len++){
        for(int l = 1; l +len - 1 <= n; l++){
            int r = l + len -1;
            f[l][r] = inf;
            for(int k = l+ 1; k < r; k++){
                f[l][r] = min(f[l][r], f[l][k] + f[k][r] + w[l]*w[k]*w[r]);
            }
        }
    }
    print(f[1][n]);
    return 0;
}

作者：Alien
链接：https://www.acwing.com/solution/content/28488/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
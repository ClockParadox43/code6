/*

包含操作：
快读            rd
快输            print
高精度读入      iird
高精度输出      iiprint
高精度比较      iicmp
高精度加法      pls
高精度减法      sub
高精乘低精      mul
高精乘高精      iimul
高精整除以低精  div
对低精取模      mod
高精度gcd       iigcd
高精度快速幂    iipow
高精度开n次方根 root
// 注：也可以专门写 ++ 和 -- 的函数
// 文末附有高精度整除以高精度 和 负数高精度的修改方法

*/

// 笔记：
// 补齐前导零
// 是否需要x存储进位?
// 如果有x，注意处理最高位剩余的x
// 去除前导零

#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
// I love OI!

typedef __int128 ii;
typedef long long ll;
#define V vector<ii>
#define il inline 
#define pu push_back
#define sz size() // 改代码使用时强转为int
const ii base = 1e18;
const int baselen = 18;
// 下标从0开始
// 若只需加减运算，压位可以适当压多一点，保证两数相加不溢出即可
// 若需乘法运算，压位一般只压一半大小，保证两数相乘不溢出
// 该代码默认没有负数

// 快读
template <typename TT>
void inline rd(TT &x){
    x = 0;
    char c = getchar();
    for ( ; c < '0' || c > '9' ; c = getchar());
    for ( ; c >= '0' && c <= '9' ; c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
}

// 快输
template <typename tt>
void il print(tt x){
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

// 高精度读入
void il iird(V &A){
    A.clear();
    string S;
    cin >> S;
    reverse(S.begin(), S.end());
    for (int i = 0 ; i < (int)S.sz ; i += baselen){
        ii x = 0;
        for (int j = min((int)S.sz, i + baselen) - 1 ; j >= i ; j --)
            x = (x << 3) + (x << 1) + (S[j] ^ 48);
        A.pu(x);
    }
}

// 高精度输出
void il iiprint(V A){
    print(A[A.sz - 1]);
    for (int i = A.sz - 2 ; i >= 0 ; i --) 
        printf("%018lld", (ll)A[i]); // 改变baselen时需要同步修改
}

// 笔记：
// 补齐前导零
// 是否需要x存储进位?
// 如果有x，注意处理最高位剩余的x
// 去除前导零

// 高精度比较：若A < B返回1， A > B返回-1， A = B返回0
int il iicmp(V A, V B){
    if (A.sz != B.sz) return A.sz < B.sz ? 1 : -1;
    for (int i = A.sz - 1 ; i >= 0 ; i --)
        if (A[i] != B[i]) return A[i] < B[i] ? 1 : -1;
    return 0;
}

// 高精度加法
V il pls(V A, V B){
    while(A.sz < B.sz) A.pu(0); // 补齐前导零
    while(A.sz > B.sz) B.pu(0);
    ii x = 0; 
    V C;
    for (int i = 0, len = A.sz ; i < len ; i ++){
        x += A[i] + B[i];
        C.pu(x % base);
        x /= base;
    }
    if (x) C.pu(x); // 处理最高位剩余的x
    return C;
}

// 高精度减法
// 请提前用iicmp判断正负，这里默认A > B
V il sub(V A, V B){
    V C;
    while(B.sz < A.sz) B.pu(0); // 补齐前导零
    for (int i = 0, len = A.sz ; i < len ; i ++){
        if (A[i] < B[i]) {
            A[i + 1] --;
            A[i] += base;
        }
        C.pu(A[i] - B[i]);
    }
    while(C.sz > 1 && !C.back()) C.pop_back(); // 去除前导零
    return C;
}

// 高精乘低精
il V mul(V A, ii B){
    ii x = 0;
    V C;
    for (int i = 0, len = A.sz ; i < len ; i ++){
        x += A[i] * B;
        C.pu(x % base);
        x /= base;
    }
    while(x) C.pu(x % base), x /= base; // 处理最高位剩余的x
    while(C.sz > 1 && !C.back()) C.pop_back(); // 去除前导零
    return C;
}

// 高精乘高精
// 优化：FFT
il V iimul(V A, V B){
    V C;
    while(C.sz < A.sz + B.sz) C.pu(0);
    for (int i = 0, lenA = A.sz ; i < lenA ; i ++){
        ii x = 0;
        for (int j = 0, lenB = B.sz ; j < lenB ; j ++){
            x += C[i + j] + A[i] * B[j]; // 由于下标从0开始，注意这里是i + j
                                         // 如果下标从1开始，则为 i + j - 1 
            C[i + j] = x % base;
            x /= base;
        }
        C[i + B.sz] = x; // 处理最高位剩余的x
    }
    while(C.sz > 1 && !C.back()) C.pop_back(); // 去除前导零
    return C;
}

// 高精整除以低精
V il div(V A, ii B){
    V C;
    ii x = 0;
    // 注意除法从最高位开始
    for (int i = A.sz - 1 ; i >= 0 ; i --){
        x = x * base + A[i];
        C.pu(x / B);
        x %= B;
    }
    reverse(C.begin(), C.end()); // 反转
    while(C.sz > 1 && !C.back()) C.pop_back(); // 去除前导零
    return C;
}

// 对低精取模
il ii mod(V A, ii B){
    ii x = 0;
    for (int i = A.sz - 1 ; i >= 0 ; i --)
        x = (x * base + A[i]) % B;
    return x;
}

// 高精度gcd
V il iigcd(V A, V B){
    ii x = 0;
    V C;
    C.pu(1);
    while(!iicmp(B, C)){
        if (iicmp(A, B) == 1) swap(A, B);
        if (iicmp(B, C) == 1) break;
        if (A[0] % 2 == 0 && B[0] % 2 == 0)
            A = div(A, 2), B = div(B, 2), x ++;
        else if (A[0] % 2 == 0) A = div(A, 2);
        else if (B[0] % 2 == 0) B = div(B, 2);
        else A = sub(A, B);
    }
    while(x --) A = mul(A, 2);
    return A;
}

// 高精度快速幂
V il iipow(V A, ii k){
    if (k == 1) return A;
    V C;
    C.pu(1);
    for ( ; k ; k >>= 1, A = iimul(A, A))
        if (k & 1) C = iimul(C, A);
    return C;
}

// 高精度开n次方根（二分法+快速幂）
// 其他做法：基于倍增的牛顿迭代法
// https://www.luogu.com.cn/problem/solution/P2293
V il root(V A, ii k){
    if (k == 1) return A;
    V L, R = A, mid, _1, ans;
    mid.pu(0);
    if (A.empty() || (A.sz == 1 && A[0] == 0)) return mid;
    L.pu(1);
    _1.pu(1);
    while(iicmp(L, R) != -1){
        mid = div(pls(L, R), 2);
        if (mid.sz * k - k + 1 > A.sz) R = sub(mid, _1);
        else 
        if (iicmp(A, iipow(mid, k)) != 1) {
            if (iicmp(mid, ans) != 1) ans = mid;
            L = pls(mid, _1);
        } else R = sub(mid, _1);
    }
    return ans;
}

// 高精整除以高精，模拟竖式除法并转化为减法
void numcpy(int p[],int q[],int det){//将p数组拷贝到q数组中，从q的det位置开始 
    for(int i=1;i<=p[0];i++)q[i+det-1]=p[i];
    q[0]=p[0]+det-1;//更新q的位数 
}
void chu(int a[],int b[],int c[]){//除法运算函数 
    int i,tmp[101];
    c[0]=a[0]-b[0]+1;//确定商的位数 
    for(i=c[0];i>0;i--){
        memset(tmp,0,sizeof(tmp));
        numcpy(b,tmp,i);
        while(compare(a,tmp)>=0){//减法模拟除法运算过程 
            c[i]++;
            jian(a,tmp);    
        }
    }
    while(c[0]>0&&c[c[0]]==0) c[0]--;
    return ;
} 

/*
    其它做法：
    如每次不是减1次，而是减10的幂次
    或转化用二分枚举商，再用乘法判断
    https://blog.csdn.net/lybc2019/article/details/103712905
*/


// 高精度有负数的修改方式
// iird中：略
// iiprint中：if(f) putchar('-'),f=0;
// pls中:
if(f1^f2){
    if(f1) f1^=1, mnu(b,a), f1^=1;
    if(f2) f2^=1, mnu(a,b), f2^=1; //加负数等效于减正数
    return;
}
if(f1&f2){
    f1=f2=0, f^=1, pls(a,b);
    f1=f2=1;
    return;
}
int main(){
    // 注意初始化，如A.pu(0)，乘法运算前应先A.pu(1)
    V x, y;
    iird(x); 
    iird(y);
    x = pls(x, y);
    iiprint(x);
}



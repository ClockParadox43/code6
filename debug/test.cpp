#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int LEN = 8;
int mounth_day[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int main()
{
    // int a, b; scanf("%d%d", &a, &b);
    int a = 20110101, b = 20111231; 

    vector<int> A, B;
    while (a) { A.push_back(a % 10); a /= 10;}
    while (b) { B.push_back(b % 10); b /= 10;}
    reverse(A.begin(), A.end()), reverse(B.begin(), B.end());

    // 年: 0~3, 月: 4~5, 日: 6~7
    // 获得年
    int D = 1000;
    int a_year = 0, b_year = 0;
    for (int i = 0; i <= 3; ++ i )
    {   
        a_year += A[i] * D;
        b_year += B[i] * D;
        D /= 10; 
    }
    
    // 获取月
    D = 10;
    int a_mounth = 0, b_mounth = 0;
    for (int i = 4; i <= 5; ++ i )
    {
        a_mounth += A[i] * D;
        b_mounth += B[i] * D;
        D /= 10;
    }

    // 获取天
    D = 10;
    int a_day = 0, b_day = 0;
    for (int i = 6; i <= 7; ++ i )
    {
        a_day += A[i] * D;
        b_day += B[i] * D;
        D /= 10;
    }

    // 枚举出 a~b 的所有 年月日
    vector<int> alls;
    
    for (int i = a; i == b; )
    {   
        
    }
    
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <cctype>       
#include <cstdio>
#include <cstring>

using namespace std;
const int MAXN = 30;

string s;
char pos = 0;
int cnt = 0;

int main()
{
    cin >> s;
    for (int i = 0; i < s.size(); ++ i)
    {
        if (isdigit(s[i])) cnt ++ ;     // 记录第一个数的长度
        else { pos = s[i]; break; }
    }   

    int x = cnt;        // 记录末尾后一个数的位置即符号
    cnt -- ;

    // 1.去掉第一个数的后导 0      
    // 2.输出第一个数字
    while (s[cnt] == '0' && cnt > 0) cnt -- ; 
    for (int i = cnt; i >= 0; -- i) cout << s[i]; 
    
    if (pos == 0) return 0; // 无符号直接返回
    else 
        if (pos == '%') { cout << pos; return 0; }
        else cout << pos;
    
    // 去除第 2 个数字的前导 0, 第 2 个数字的后导 0
    // 输出第 2 个数字
    // m 是闭区间末尾的位置, 因为 x+1, 所以 x 要停留在末尾 -1 位置
    // x 在倒数第二位还会再走一步
    //  0001
    //   x m
    int m = s.size() - 1;
    while (s[x + 1] == '0' && x < m - 1) x ++ ;
    while (s[m] == '0' && m > x + 1) m -- ;
    for (int i = m; i > x; -- i) cout << s[i];
    
    return 0;
}
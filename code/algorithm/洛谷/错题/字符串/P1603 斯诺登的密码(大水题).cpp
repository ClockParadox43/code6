#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <cctype>       
#include <cstdio>
#include <cstring>
#include <unorderd_map>

using namespace std;
const int MAXN = 66;

unordered_map<string, int> q;
string s;
int top, st[MAXN];

int main()
{ 
    q["one"]=1;q["two"]=2;q["three"]=3;q["four"]=4;q["five"]=5;q["six"]=6;q["seven"]=7;q["eight"]=8;q["nine"]=9;q["ten"]=10;
    q["eleven"]=11;q["twelve"]=12;q["thirteen"]=13;q["fourteen"]=14;q["fifteen"]=15;q["sixteen"]=16;q["seventeen"]=17;q["eighteen"]=18;q["nineteen"]=19;q["twenty"]=20;
    q["a"]=1;q["both"]=2;q["another"]=1;q["first"]=1;q["second"]=2;q["third"]=3;
    //打表
    for (int i = 1; i <= 6; ++ i)
    {
        cin >> s;
        if (q[s])   // 如果可以构成数字
        {
            int k = q[s] * q[s] % 100;
            if (k == 0) continue;       // 如果为 0 没有必要存储
            st[ ++ top] = k;
        }
    }

    sort(st + 1, st + top + 1);     // 从小到大排序
    cout << st[1];

    for (int i = 2; i <= top; ++ i)
    {
        if (st[i] < 10) cout << 0;  // 01, 02, 03...
        cout << st[i];
    }
    return 0;
}
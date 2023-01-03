#include <iostream>

using namespace std;

typedef long long LL;

// 相较于玩具解密, 这道题的差值(j)并没有求出, 所以先需要算出差值
LL n, i, j, x;
string a, b, c, d;
string an[13] = {"Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig", "Rat"};  // 初始化
map<string, LL> year;

int main()
{
    year["Bessie"] = 0; // B 为最早的牛年
    cin >> n;   // 输入句子数量
    for (int i = 1; i <= n; ++ i )  
    {
        // a,d:姓名, c:生肖, b:prev/next
        // d 是已知的, 给定条件, 求出 a 的出身年份
        cin >> a >> b >> b >> b >> c >> d >> d >> d;    // 过滤掉不需要的东西
        if (b == "previous") 
        {
            // (j%12+12)%12:计算反向周期的下标
            // 往前枚举, 反向求周期, 最多枚举 12 个
            // 先 mod 保证 +12 后一定是正数
            // 最后又 mod 了一次 12 所以永远不会超过 12
            // 且 j 会已知叠加
            
            for (j = year[d] - 1; ; -- j )
                if (an[(j % 12 + 12) % 12] == c) break;  
            year[a] = j;   // 将 {a,j} 插入, 算出 a 在 d 的 j 年前出生
        }
        else
        {
            for (j = year[d] + 1; ; ++ j )
                if (an[(j % 12 + 12) % 12] == c) break;
            year[a] = j;
        }
    }   
    cout << abs(year["Elsie"]);
    return 0;
}

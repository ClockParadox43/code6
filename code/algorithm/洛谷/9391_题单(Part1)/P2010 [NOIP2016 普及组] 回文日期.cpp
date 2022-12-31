#include <iostream>

using namespace std;

int s[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31};

int main()
{
    int st, ed; scanf("%d%d", &st, &ed);
    
    // 枚举月和日
    int c;
    for (int i = 1; i <= 12; ++ i )
        for (int j = 1; j <= s[i]; ++ j )
        {
            c = (j % 10) * 1000 + (j / 10) * 100 + (i % 10) * 10 + (i / 10); // 算出前四位。
            
        }
}

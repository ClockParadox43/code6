// 用 * 构造一个对角线长 5 个字符，倾斜放置的菱形
//
//   *    1
//  ***   3   j <= 2*i + 1
// *****  5
//  ***    
//   *

#include <iostream>

using namespace std;

void print()
{
    for (int i = 0; i < 3; ++ i )
    {
        for (int j = 2; j >= i; -- j )
            printf(" ");
        for (int j = 1; j <= 2 * i + 1; ++ j )
            printf("*");
    
        cout << endl;
    }
    
    for (int i = 0; i < 2; ++ i )
    {
        for (int j = )
    }
}

int main()
{
    print();
    return 0;
}
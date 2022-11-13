// 123 * 12
// 3*12, 2*12, 1*12
// mod 10: 算出的该位的值
// 除 10 : 进位

#include <iostream>
#include <vector>

using namespace std;

vector<int> mul(vector<int>& A, int b)
{
    vector<int> C;
    // 当 i 没有循环完的时候并且进位没有处理完的时候, for 循环要继续
    for (int i = 0, t = 0; i < A.size() || t; ++ i )
    {
         if (i < A.size()) t += A[i] * b;       // 处理完最后一位后, 如果 t 没有因为 / 10 处理完, 还需要进行下次循环
         C.push_back(t % 10);
         t /= 10;
    }
    
    while (C.size() > 1 && C.back() == 0 ) C.pop_back();
    return C;
}

int main()
{
    string a;
    int b;
    
    cin >> a >> b;
    
    vector<int> A;
    
    for (int i = a.size() - 1; i >= 0; -- i ) A.push_back(a[i] - '0');
    
    vector<int> C = mul(A, b);
    
    for (int i = C.size() - 1; i >= 0; -- i ) cout << C[i];
    
    return 0;
}
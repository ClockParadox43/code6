#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// C[i]: 商, r:余数
vector<int> div(vector<int>& A, int b, int& r)
{
    vector<int> C;
    
    // 余数 = t * 10 + A[i]
    // C[i] = 余数 / 除数
    // // 下个余数 = r % b
    // 和其余运算不一样的是, 除法是从高位开始计算的 
    // 初始: 从 0 开始看, 商 0, 余数加上下一个余数
    for (int i = A.size() - 1; i >= 0; -- i )
    {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r %= b;                 // a = bc + r, r 为余数, 余数 = 被除数 - 除数
    }                           // 因为除法得余数时也是靠减所以 r%=b
                                
    reverse(C.begin(), C.end());
    while (C.size() > 1 && C.back() == 0) C.pop_back();
	return C;
}

int main()
{
    string a;
    int b;
    
    cin >> a >> b;
    vector<int> A;
    for (int i = a.size() - 1; i >= 0; -- i ) A.push_back(a[i] - '0');
    
    int r;
    auto C = div(A, b, r);
    
    for (int i = C.size() - 1; i >= 0; -- i ) cout << C[i];
    cout << endl << r << endl;
    
    return 0;
}
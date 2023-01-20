#include <iostream>
#include <vector>

using namespace std;

vector<int> mul(vector<int> &A, vector<int> &B)
{
    vector<int> C(A.size() + B.size() + 7);     // 初始化为 0, C 的 size 尽可能大些
    
    for (int i = 0; i < A.size(); ++ i)
        for (int j = 0; j < B.size(); ++ j)
            C[i + j] += A[i] * B[i];

    // i = C.size() - 1 时, t 一定小于 10
    int t = 0;
    for (int i = 0; i < C.size(); ++ i) 
    {
        t += C[i];
        C[i] = t % 10;
        t /= 10;
    }

    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

int main()
{
    string a, b;
    cin >> a >> b;

    vector<int> A, B;
    for (int i = a.size() - 1; i >= 0; -- i)
        A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; -- i)
        B.push_back(b[i] - '0');
    
    auto C = mul(A, B);
    for (int i = C.size() - 1; i >= 0; -- i)
        cout << C[i];
    return 0;
}

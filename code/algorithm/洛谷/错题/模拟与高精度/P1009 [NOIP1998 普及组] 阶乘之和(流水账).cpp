#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
const int MAXN = 55;

int n;
int num[MAXN];

// 3 = 1 * 2 * 3
vector<int> mul(vector<int>& A, vector<int>& B)
{
    vector<int> C(A.size() + B.size() + 7, 0);
    for (int i = 0; i < A.size(); ++i)
        for (int j = 0; j < B.size(); ++j)
            C[i + j] += A[i] * B[j];

    for (int i = 0; i + 1 < C.size(); ++i)
    {
        C[i + 1] += C[i] / 10;
        C[i] %= 10;
    }

    while (C.size() > 1 && C.back() == 0) C.pop_back();
    reverse(C.begin(), C.end());
    return C;
}

vector<int> add(vector<int>& A, vector<int>& B)
{
    if (A.size() < B.size()) return add(B, A);

    vector<int> C(max(A.size(), B.size()) + 7, 0);
    for (int i = 0; i < A.size(); ++i) C[i] += A[i];
    for (int i = 0; i < B.size(); ++i) C[i] += B[i];

    for (int i = 0; i + 1 < C.size(); ++i)
    {
        C[i + 1] += C[i] / 10;
        C[i] %= 10;
    }

    while (C.size() > 1 && C.back() == 0) C.pop_back();
    reverse(C.begin(), C.end());
    return C;
}

int main()
{
    scanf("%d", &n);
    vector<vector<int>> tmp(MAXN);    // !1
    for (int i = 1; i <= n; ++i)
    {
        int x = i, j = 0;
        // tmp[i].resize(MAXN);
        while (x)
        {
            tmp[i].push_back(x % 10);
            x /= 10;
        }
        if (i >= 10) reverse(tmp[i].begin(), tmp[i].end());
    }
    
    // 先算出 num 中的所有阶乘
    // 1,2,3,4,5 
    for (int i = 2; i <= n; ++i)
    {
        vector<int> a = tmp[i - 1];
        vector<int> b = tmp[i];

        vector<int> A, B;
        for (int j = a.size() - 1; j >= 0; --j) A.push_back(a[j]);
        for (int j = b.size() - 1; j >= 0; --j) B.push_back(b[j]);
        vector<int> C = mul(A, B);

        tmp[i] = C;
    }

    // 累加 tmp 中的值
    int k = 2;
    for (int i = 2; i <= n; ++i)
    {
        vector<int> a = tmp[i - 1];
        vector<int> b = tmp[i];

        vector<int> A, B;
        for (int j = a.size() - 1; j >= 0; --j) 
            A.push_back(a[j]);
        for (int j = b.size() - 1; j >= 0; --j) 
            B.push_back(b[j]);
        vector<int> C = add(A, B);

        tmp[i] = C;
    }

    for (int i = 0; i < tmp[n].size(); ++i)
        cout << tmp[n][i];
    return 0;
}
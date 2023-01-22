#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> add(vector<int> A, vector<int> B) 
{
    // A: 4 3 2 1
    // B: 6 5
    vector<int> C(max(A.size(), B.size()) + 7, 0);  // 数组C开大一点没事，反正可以去前导零的
    for (int i = 0; i < A.size(); i++) C[i] += A[i]; // 先累加上各自的位
    for (int i = 0; i < B.size(); i++) C[i] += B[i];

    // 处理进位
    for (int i = 0; i + 1 < C.size(); i++) 
    {
        C[i + 1] += C[i] / 10;
        C[i] %= 10;
    }

    // 处理前导零
    while (C.size() > 1 && C.back() == 0) C.pop_back();

    reverse(C.begin(), C.end());
    return C;
}

vector<int> mul(vector<int> A, vector<int> B) 
{
    // A: 4 3 2 1
    // B: 6 5
    vector<int> C(A.size() + B.size() + 7, 0);  // 数组C开大一点没事，反正可以去前导零的
    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < B.size(); j++) 
            C[i + j] += A[i] * B[j];
        
    // 处理进位
    for (int i = 0; i + 1 < C.size(); i++) 
    {
        C[i + 1] += C[i] / 10;
        C[i] %= 10;
    }

    // 处理前导零 "0000" 去掉前导零
    while (C.size() > 1 && C.back() == 0) C.pop_back();

    reverse(C.begin(), C.end());
    return C;
}

int main() 
{
    string s1 = "9899", s2 = "100";

    vector<int> A, B;
    for (int i = s1.size() - 1; i >= 0; i -- ) A.push_back(s1[i] - '0');
    for (int i = s2.size() - 1; i >= 0; i -- ) B.push_back(s2[i] - '0');

    vector<int> C = add(A, B);
    cout << s1 << "+" << s2 << "=";
    for (int i = 0; i < C.size(); i ++ ) cout << C[i];
    cout << endl;

    C = mul(A, B);
    cout << s1 << "*" << s2 << "=";
    for (int i = 0; i < C.size(); i ++ ) cout << C[i];
    cout << endl;

    return 0;
}

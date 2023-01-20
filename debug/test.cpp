#include <iostream>
#include <vector>

using namespace std;
const int MAXN = 1003;

vector<int> mul(vector<int>& A, vector<int>& B)
{
    vector<int> C(A.size() + B.size() + 7, 0);

    for (int i = 0; i < A.size(); ++ i)
        for (int j = 0; j < B.size(); ++ j)
            C[i + j] += A[i] * B[j];
    
    for (int i = 0; i + 1 < C.size(); ++ i)
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
    string A, B; cin >> A >> B;
    
    vector<int> A, B;
    for (int i = s1.size() - 1; i >= 0; -- i) A.push_back(s1[i] - '0');
    for (int i = s2.size() - 1; i >= 0; -- i) A.push_back(s2[i] - '0');

    vector<int> C = mul(A, B);
    for (int i = 0; i < C.size(); ++ i) cout << C[i];
    cout << endl;
    return 0;
}

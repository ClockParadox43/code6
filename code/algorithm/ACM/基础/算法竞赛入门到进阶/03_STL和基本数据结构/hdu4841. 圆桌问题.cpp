#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> v;

int main()
{
    while (cin >> n >> m)
    {
        v.clear();
        for (int i = 0; i < 2 * n; ++i) v.push_back(i);
        int pos = 0;
        for (int i = 0; i < 2; ++i)
        {
            // 往右数 m-1(左闭右开, 2 号下标对应第 3 个人) 个人
            // 之后在在原来的 pos 上继续数下一个人
            pos = (pos + m - 1) % v.size();     
            // 赶走坏人, 圆桌(v) 人数减 1
            v.erase(v.begin() + pos);           
        }

        int j = 0;
        for (int i = 0; i < 2 * n; ++i)
        {
            // 50 个字母输出一行
            if (!(i % 50) && i) cout << endl;   
            // 用 i 枚举圆桌上留下的下标, 圆桌上留下的都是好人
            if (j < v.size() && i == v[j]) { j++; cout << 'G'; }    
            else cout << 'B';
        }
        cout << endl << endl;
    }

    return 0;
}
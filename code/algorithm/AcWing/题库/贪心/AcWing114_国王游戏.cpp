// 金币数量 = ⌊前面所有人左手的数的乘积 / 当前人右手的数⌋ 
// 
// "让得到金币数量最多的人的金币数量尽可能少" 
// 这句话其实限制了整体, 金币数量最多的人的金币都很少, 那么别人的金币数量就更少了  
#include <iostream>
#include <vector>
#include <algorithm>

#define fs first
#define sc second
using namespace std;

typedef pair<int, int> pii;
const int N = 1010;

int n;
pii ps[N];  // 按照两个数的乘积排序

// 乘法(大数乘小数)
vector<int> mul(vector<int> &a, int b)
{
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size(); ++ i)
    {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    while (t) {c.push_back(t % 10), t /= 10;}  // 进位可能还没有算完
    return c;
}

// 除法(大数除小数)
vector<int> div(vector<int> &a, int b)
{
    vector<int> c;
    bool flag = true;  // 因为除法会出现非 0 位, 所以用变量标记一下
    for (int i = a.size() - 1, t = 0; i >= 0; -- i)
    {
        t = t * 10 + a[i];
        int x = t / b;      // 商:余数除除数
        if (!flag || x)     // 如果 flag为F ∨ x>0, 前导0的话一定是0先出现
        {
            flag = false;
            c.push_back(x);
        }
        t %= b; //下一个余数
    }
    reverse(c.begin(), c.end());
    return c;
}

// 比较: 因为 max 会直接调用 vector 的比较函数, vector的比较函数对比的是字典序
//       所以我们需要自己大数之间的比较(大数被逆置了)
vector<int> max_vec(vector<int> a, vector<int> b)
{
    if (a.size() > b.size()) return a;
    if (a.size() < b.size()) return b;
    // 因为存储的时候是低位在前, 高位在后, 所以判断的时候需要逆置
    // 构造一个新的vec, 是 a/b 的逆序, 这样就可以直接按照, a,b的字典序列来对比了
    if (vector<int>(a.rbegin(), a.rend()) > vector<int>(b.rbegin(), b.rend())) return a;
    return b;
}   

void output(vector<int> &a)
{
    for (int i = a.size() - 1; i >= 0; -- i) cout << a[i];
    cout << endl;
}

int main()
{
    int n; cin >> n;
    
    // 从 0 开始, 国王必须在第一个位置
    for (int i = 0; i <= n; ++ i)
    {
        int a, b; cin >> a >> b;
        ps[i] = { a * b, a };
    }
    sort(ps + 1, ps + 1 + n);

    vector<int> product(1, 1); // 存储大数(乘积)
    vector<int> res(1, 0);     // 答案

    // sc:右手, fs/sc:左手
    for (int i = 0; i <= n; ++ i)
    {
        if (i) res = max_vec(res, div(product, ps[i].fs / ps[i].sc)); // 前面所有数的乘积 / 除以当前左手的数
        product = mul(product, ps[i].sc); // 更新当前数的乘积
    }

    output(res);
    return 0;
}
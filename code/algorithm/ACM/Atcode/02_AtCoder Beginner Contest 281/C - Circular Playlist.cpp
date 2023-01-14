#include <iostream>
#include <vector>

using namespace std;
typedef long long LL;

int n;
LL t;

int main()
{
    // 这个函数是一个 "是否兼容stdio" 的开关, C++为了兼容C, 保证程序在使用了std::printf 和 std::cout 的时候不发生混乱, 将输出流绑到了一起
    // cin, cout之所以效率低, 是因为先把要输出的东西存入缓冲区, 再输出, 导致效率降低, 而这段语句可以来打消 iostream 的输入输出缓存, 可以节省许多时间
    // 使效率与scanf与printf相差无几
    ios::sync_with_stdio(false);
    // tie是将两个stream绑定的函数, 空参数的话返回当前的输出流指针
    // 在默认的情况下 cin 绑定的是cout, 每次执行 << 操作符的时候都要调用flush
    // 这样会增加 IO 负担. 可以通过tie(0)(0表示NULL) 来解除cin与cout的绑定, 进一步加快执行效
    cin.tie(0); cout.tie(0);

    cin >> n >> t;
    vector<LL> v(n);
    
    int sum = 0;
    for (auto& e : v)
    {
        cin >> e;
        sum += e;
    }

    // q1:求播放到哪一首
    // q2:播放到该首歌的第几秒
    // 总时长 % 一个周期的时长 = 在总时长内到了该周期的那个阶段
    // 对时间取模即可去掉循环播放的影响, 缩减至一个周期内
    // 然后直接从头遍历播放到哪首歌即可 
    t %= sum;     

    // 得到一个周期内的数后, 再用 周期内的数 - 一首歌的数 
    // 直到该首歌时长 >= 周期(来到了第 i 首歌),  
    int ans = 0;
    while (ans < n)
    {
        if (v[ans] <= t)    // 如果第 ans 首歌 <= mod得的秒数, 代表来到第 ans 首歌
        {
            t -= ans;
            ++ ans;
        }
        else break;
    }

    cout << ans + 1 << ' ' << t << endl;
    return 0;
}
// 这道题由于要求每一个点都尽量达到, 所以我们要按 t[i] 顺次考虑, 否则会出现有的点不能被遍历
// 而这道题由于两点之间只能沿着平行于坐标轴的网格上走, 因为要求尽量遍历, 所以我们要走最短路线, 即两点之间的曼哈顿距离：
// M(A,B) = |(xA-xB) + (yA-yB)|
//
// 那么代码实现很简单. 用 curx 和 cury 记录当前的位置, 每次用 mint 求出当前到达这一位置的时间
//      如果 mint + M(A,B) = t[i] 则更新 curx, cury 以及 mint
//      如果 mint + M(A,B) < t[i] 那么由于我们可以在某个网格上来回走, 所以我们需要判断 t[i] - (mint + M(A,B)) 是不是偶数(剩余的时间是不是偶数), 
// 如果不是那么不能回到原位如果是, 如果是那么更新
//      如果 mint + M(A,B) > t[i] 那么显然不可以, 用一个 flag = false 标记不成功. 跳出循环

#include <iostream>

using namespace std;
const int MAXN = 100005;
inline int mah(int ax, int ay, int bx, int by)
{
    return abs(ax - bx) + abs(ay - by);
}

int n;
int t[MAXN], x[MAXN], y[MAXN];  

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i)
        scanf("%d%d%d", &t[i], &x[i], &y[i]); // n 组测试用例, t 时间内想到达 (x, y)
    
    // 将目标向右移动 1 个-> 向左移动 1 个, 返回目标坐标的动作, 能够调整时间
    // 此时间调整仅再 dt-d 为偶数时停留在目标坐标中
    bool flag = true;
    int curx = 0, cury = 0, curt = 0;
    for (int i = 1; i <= n; ++ i)
    {
        // 当前所花费的时间 = 当前坐标到 (x, y) 的曼哈顿距离(时间单位为 1)
        curt += mah(curx, cury, x[i], y[i]); 

        if (curt > t[i]) { flag = false; break; }
        
        // 还有剩下时间的情况
        // 所话费的时间 - t[i] = 剩下的时间
        // 如果剩下的时间是奇数次, 就是false
        if (curt < t[i]) 
            if ((curt - t[i]) % 2) { flag = false; break; }
        
        // 计算下一组
        curx = x[i], cury = y[i], curt = t[i];
    }


}
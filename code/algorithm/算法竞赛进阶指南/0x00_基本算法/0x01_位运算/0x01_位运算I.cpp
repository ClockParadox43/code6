#include <iostream>

using namespace std;

// 1) C++ 中 8 位二进制(bit) 对应 char 类型
//    范围为 -128~127, 其中 0xFF 表示 -1, 0x7F 表示最大值 127
// 
// 2) 在 m 位二进制中, 从右到左依次推类, 最低位为第 0 位, 最高位为第 m-1 位
// 
// 3) 32 位二补码表示   unsigned int    int 
//     00000...00000        0            0
//     01111...11111    2147483647      2147483647
//     10000...00000    2147483648     -2147483648
//     11111...11111    4294967295       -1
//
// 4) 两个数值做加减法运算, 等价于在 32 位补码下做最高位不进位的二进制加减法运算
//    当发生算数溢出时, 32 位无符号整数相当于自动对 2^32 取模
//
// 5) 反码和补码的的绝对值差 1, 表格中, (1,4) 行是一对反码, (2,3) 行是一对反码
//    重点解决了 0 的编码唯一性问题
void p4()
{
    unsigned int un = 4294967295;
    int n = 2147483647;
    cout << "4294967295 + 1 = " << un + 1 << endl;
    cout << "相当于在 32 位补码下做最高位不进位二进制加减法," << endl << "当发生溢出时, 自动取模 2^32 所以等于 0 ." << endl;
    cout << endl;
    cout << "2147483647 + 1 = " << n + 1 << endl; 
    cout << "带符号整形, 加至符号位, 所以变成负数" << endl;
}

// 6) 因为二进制表示繁琐, 10进制不容易体现补码每一位, 十六进制通常形容常数
//    0x 只是声明了进制, 后面对应具体值
//    32 位二补码表示    int(十进制)    int(十六进制) 
//     00000...00000        0               0x0
//     01111...11111    2147483647      0x7F FF FF FF
//     00111111(重复4次)1061109567      0x3F 3F 3F 3F
//     11111...11111       -1           0xFF FF FF FF
//
// 7) 0x3F 3F 3F 3F 是一个很有用的值, 它是满足一下两个条件的最大整数
//    1.整数的两倍不超过 0x3F 3F 3F 3F, 即 int 能表达的最大整数
//    2.整数的每 8 位, 都是相同的
//   
// 8) 经常需要使用 memset(a, val, sizeof a) 来初始化 int a[]
//    val 通常在 0x00 ~ 0xFF 填充 a[] 的每个字节, 而一个 int 占用 4 个字节
//    所以用 memset 能复制出每 8 位相同的 int 
//    0x7F 7F 7F 7F 是用 memset 能初始化出的最大数值, 为了避免假发算数上的溢出或者繁琐判断
//    经常使用 memset(a, 0x3F, sizeof a)


int main()
{
    // p4();
    return 0;
}
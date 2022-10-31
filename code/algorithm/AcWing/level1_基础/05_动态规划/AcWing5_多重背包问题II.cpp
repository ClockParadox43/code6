#include <iostream>

using namespace std;

// f[i,j] 是从 0 开始的
//
// f[i,j-v] 是从 1 开始的, 因为 f[i,j-v] 必须减掉一个 v
// 但是当 k=0 的时候, f[i,j-v*0] == f[i,j]
// 所以 f[i,j-v] 是从 1 开始的
//
// f[i,j] =     f[i-1,j], f[i-1,j-v]+w, f[i-1,j-2v]+2w...f[i-1,j-sv]+sw
// f[i,j-v] =             f[i-1,j-v],   f[i-1,j-2v]+w... f[i-1,j-sv]+(s-1)w, f[i,j-(s+1)v]+sw
//                                                                           f[i,j-sv-v]+sw
// s=200
// 1 2 4 8 16 32


int main()
{
    return 0;
}

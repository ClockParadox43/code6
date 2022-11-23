#include <iostream>
using namespace std;

// 二位差分是二维前缀和逆过来
// 只要原矩阵是查分数组的前缀和即可, 
// 使得 a[i,j] 存的是 i,j 左上角所有 b[i,j] 的和
// 
// b[x1,y1] += c (以该点为起点右下角所有点 + c)
// b[x2+1,y1] -= c (下方以该点为起点 -= c)
// b[x1,y2+1] -= c (右方以该点为起点 -= c) 重复减去
// b[x2+1,y2+1] += c (以右下角为起点 += c) 

const int N = 1010;

int n, m, q;

int a[N][N], b[N][N];

// x1,y1 : 矩阵左上角点
// x2,y2 : 矩阵右下角点
void insert(int x1, int y1, int x2, int y2, int c)
{
	b[x1][y1] += c;
    b[x1][y2 + 1] -= c;
	b[x2 + 1][y1] -= c;
	b[x2 + 1][y2 + 1] += c;
}

int main()
{
   scanf("%d%d%d", &n, &m, &q);
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			scanf("%d", &a[i][j]);

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			insert(i, j, i, j, a[i][j]);

	while (q--)
	{
		int x1, y1, x2, y2, c;
		cin >> x1 >> y1 >> x2 >> y2 >> c;
		insert(x1, y1, x2, y2, c);
	}
	
    // 和前缀和的表达式一样, 处理完后 b 就是 a 的前缀和, 所以不用加 b[i][j]
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j) printf("%d ", b[i][j]);
		puts("");
	}
	
	return 0;
}
#include <iostream>

using namespace std;

int a[15][15];

// 中间四个while 语句分别代表右、下、左、上连续走, 条件也很好想
// 就是没有越界和没有填数就可以填了
int main()
{
	int n, k = 1, x = 1, y = 0;;
	cin >> n;
	while (k <= n * n)
	{
		while (y < n && !a[x][y + 1])   // x,y 正着填写的时候
			a[x][ ++ y] = k ++ ;
		while (x < n && !a[x + 1][y])
			a[ ++ x][y] = k ++ ;
		while (y > 1 && !a[x][y - 1])   // x,y 倒着填写的时候
			a[x][ -- y] = k ++ ;
		while (x > 1 && !a[x - 1][y])
			a[ -- x][y] = k ++ ;
	}

	for (int i = 1; i <= n; i ++ )
	{
		for (int j = 1; j <= n; j ++ )
            printf("%3d", a[i][j]);
		printf("\n");
	}
	return 0;
}
#include <iostream>

using namespace std;

const int N = 10010;
int n;
int a[N], s[N];

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i ) scanf("%d", &a[i]);

	int ans = 0;
	// 双指针解法
	for (int i = 0, j = 0; i < n; ++ i )
	{
		q[a[i]] ++ ;
		if (q[a[i]] > 1)
		{
			q[a[j]] -- ;
			++ j;
		}
		ans > (i - j + 1) ? ans : (i - j + 1);
	}
	
	cout << ans << endl;
	return 0;
}
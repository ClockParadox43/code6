#include <iostream>
#include <queue>

using namespace std;

const int MAXN = 100004;

int n;
int a[MAXN];

int main()
{
    scanf("%d", &n);
    priority_queue<int, vector<int, greater<int>> heap;

    for (int i = 0; i < n; ++ i)
    {
        int x; scanf("%d", &x);
        a[i] = x;
        heap.push(x);
    }    
    
    while (heap.size() > 1)
    {
        int a = heap.front(); heap.pop();
        int b = heap.front(); heap.pop();
        int c = a + b;
        heap.push(c); 
    }
    

}
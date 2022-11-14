#include <iostream>

using namespace std;

const int N = 100010;

int m;
int stack[N], tt;

int main()
{
    scanf("%d", &m);
    while (m -- )
    {
        string op;
        int x;
        
        cin >> op;
        if (op == "push")
        {
            cin >> x;
            stack[ ++ tt] = x;
        }
        else if (op == "pop") tt -- ;
        else if (op == "empty") cout << (tt ? "NO" : "YES") << endl;
        else cout << stack[tt] << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

int n;
char ch;

int main()
{
    scanf("%d", &n); getchar();
    while (n -- )
    {
        stack<int> s;
        while (true)
        {
            ch = getchar();
            if (ch == ' ' || ch == '\n' || ch == EOF)
            {
                while (!s.empty()) { printf("%c", s.top()); s.pop(); }
                if ()
            }
        }
    }
}
#include <iostream>
#include <algorithm>

using namespace std;


int main()
{
    string a("-280"); 
    while (a.size() > 1 && a[a.size() - 1] == '0') a.pop_back();
    
    if (a[0] == '-')
    {
        int l = 1, r = a.size() - 1; 
        while (l < r)
        {
            swap(a[l], a[r]);
            l++, r--;
        }
        cout << a;
    }
    else
    {
        // 380, 83    
        reverse(a.begin(), a.end());
        cout << a;
    }
    
    return 0;
}
#include <iostream>

using namespace std;

int main()
{
    double x;
    cin >> x;
    
    double l = -10000, r = 10000;
    while (r - l > 1e-8)
    {
        double m = (r + l) / 2;
        if (m * m * m >= x) r = m;
        else l = m;
    }
    printf("%lf\n", l);
    return 0;
}


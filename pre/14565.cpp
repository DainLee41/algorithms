#include <iostream>
using namespace std;
using llu = long long int;

llu xgcd(llu a, llu b, llu &x, llu &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    llu x1, y1;
    llu gcd = xgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

llu find_multiple(llu a, llu n)
{
    llu x, y;
    llu gcd = xgcd(a, n, x, y);
    if (gcd != 1)
        return -1;
    else
        return (x % n + n) % n;
}

int main()
{

    llu n, a;
    cin >> n >> a;

    cout << n - a << " " << find_multiple(a, n) << endl;
    return 0;
}
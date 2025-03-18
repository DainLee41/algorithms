#include <iostream>
using namespace std;
using llu = long long int;

llu xgcd(llu a, llu b, llu &x, llu &y)
{
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }

    llu x1, y1, gcd;
    gcd = xgcd(b % a, a, x1, y1);

    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

llu find_mul(llu a, llu n)
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
    llu a, n;
    cin >> n >> a;
    cout << n - a << " " << find_mul(a, n) << endl;
    return 0;
}
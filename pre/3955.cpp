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

    llu x1, y1;
    llu gcd = xgcd(b % a, a, x1, y1);

    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

llu find_candy(llu k, llu c)
{
    if (c == 1)
        return (k + 1 > 1e9) ? -1 : k + 1;
    if (k == 1)
        return 1;

    llu x, y;
    llu gcd = xgcd(k, c, x, y);

    if (gcd != 1)
        return -1;

    // 여기가 문제였던 듯
    y = (y % k + k) % k;
    return y;
}

int main()
{
    int t;
    llu k, c;

    cin >> t;

    for (int i = 0; i < t; i++)
    {
        cin >> k >> c;
        llu temp = find_candy(k, c);
        if (temp == -1)
            cout << "IMPOSSIBLE" << endl;
        else
            cout << temp << endl;
    }

    return 0;
}
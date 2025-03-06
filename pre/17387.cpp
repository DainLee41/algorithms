#include <iostream>
#include <algorithm>
using namespace std;

struct Point
{
    long long x = 0;
    long long y = 0;
};

struct Line
{
    Point Start;
    Point End;
};

int ccw(Point A, Point B, Point C)
{
    long long cp = (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
    return (cp > 0) - (cp < 0);
}

bool isCrossing(Line L1, Line L2)
{
    int a = ccw(L1.Start, L1.End, L2.Start);
    int b = ccw(L1.Start, L1.End, L2.End);
    int c = ccw(L2.Start, L2.End, L1.Start);
    int d = ccw(L2.Start, L2.End, L1.End);

    if (a * b <= 0 && c * d <= 0)
    {
        if (a == 0 && b == 0 && c == 0 && d == 0)
        {
            return max(L1.Start.x, L1.End.x) >= min(L2.Start.x, L2.End.x) &&
                   max(L1.Start.y, L1.End.y) >= min(L2.Start.y, L2.End.y) &&
                   max(L2.Start.x, L2.End.x) >= min(L1.Start.x, L1.End.x) &&
                   max(L2.Start.y, L2.End.y) >= min(L1.Start.y, L1.End.y);
        }

        return true;
    }
    return false;
}

int main()
{
    Line Line1, Line2;
    cin >> Line1.Start.x >> Line1.Start.y >> Line1.End.x >> Line1.End.y;
    cin >> Line2.Start.x >> Line2.Start.y >> Line2.End.x >> Line2.End.y;

    cout << (isCrossing(Line1, Line2) ? 1 : 0) << endl;
    return 0;
}
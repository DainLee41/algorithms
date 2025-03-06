#include <iostream>
#include <vector>
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

int ccw(Point _first, Point _second, Point _third)
{
    Point vector1 = {_second.x - _first.x, _second.y - _first.y};
    Point vector2 = {_third.x - _second.x, _third.y - _second.y};

    long long cp = vector1.x * vector2.y - vector1.y * vector2.x;

    return (cp < 0) ? -1 : 1;
}

int main()
{
    Line Line1, Line2;
    cin >> Line1.Start.x >> Line1.Start.y >> Line1.End.x >> Line1.End.y;
    cin >> Line2.Start.x >> Line2.Start.y >> Line2.End.x >> Line2.End.y;

    int a, b, c, d;
    a = ccw(Line1.Start, Line1.End, Line2.Start);
    b = ccw(Line1.Start, Line1.End, Line2.End);
    c = ccw(Line2.Start, Line2.End, Line1.Start);
    d = ccw(Line2.Start, Line2.End, Line1.End);

    printf("%d", (a * b < 0 && c * d < 0) ? 1 : 0);

    return 0;
}
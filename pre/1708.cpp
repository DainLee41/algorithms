#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long int;

struct Point
{
    ll x, y;
};

bool compareBase(const Point &a, const Point &b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

int ccw(const Point &O, const Point &A, const Point &B)
{
    ll cp = (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    return (cp > 0) - (cp < 0); // 1 = 반시계, -1은 시계, 0은 일직선
}

vector<Point> convexHull(vector<Point> &points, int n)
{
    sort(points.begin(), points.end(), compareBase);

    vector<Point> hull;
    hull.reserve(2 * n);

    for (int i = 0; i < n; i++)
    {
        while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), points[i]) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }

    for (int i = n - 2, t = hull.size() + 1; i >= 0; i--)
    {
        while (hull.size() >= t && ccw(hull[hull.size() - 2], hull.back(), points[i]) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }

    hull.pop_back(); // 마지막 점과 시작점이 중복되므로 제거하기
    return hull;
}

int main()
{
    int n;
    cin >> n;
    vector<Point> points(n);

    for (int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
    }

    vector<Point> hull = convexHull(points, n);

    cout << hull.size() << endl;

    return 0;
}
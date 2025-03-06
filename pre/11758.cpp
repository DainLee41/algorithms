#include <iostream>
using namespace std;

// 외적을 이용하기
// 벡터가 이루는 면적을 구하는 방법임
// 공식 = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1)
int ccw(int x1, int y1, int x2, int y2, int x3, int y3)
{
    int cp = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    if (cp > 0)
        return 1;
    else
        return (cp == 0) ? 0 : -1;
}

int main()
{
    int x1, x2, x3, y1, y2, y3;
    scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
    printf("%d", ccw(x1, y1, x2, y2, x3, y3));
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int tree[500000 * 4] = {0};

void compress(vector<int> &A)
{
    vector<int> B(A); // 배열 A를 B에 복사하기
    sort(B.begin(), B.end());
    for (int &x : A)
        x = lower_bound(B.begin(), B.end(), x) - B.begin(); // lower_bound는 찾고자 하는 값의 위치 반환
}

void update(int node, int st, int en, int idx)
{
    tree[node] += 1;
    if (st != en)
    {
        int mid = (st + en) >> 1;
        if (idx <= mid)
            update(node << 1, st, mid, idx);
        else
            update(node << 1 | 1, mid + 1, en, idx); // node << 1|1 은 시프트 연산 이후 + 1을 한 거임
    }
}

int query(int node, int st, int en, int left, int right)
{
    if (right < st || en < left)
        return 0;
    if (left <= st && en <= right)
        return tree[node];
    int mid = (st + en) >> 1;
    return query(node << 1, st, mid, left, right) + query(node << 1 | 1, mid + 1, en, left, right);
}

int main()
{
    int n;
    cin >> n;

    vector<int> A(n);
    for (int i = 0; i < n; i++)
        cin >> A[i];

    compress(A);

    for (int i = 0; i < n; i++)
    {
        cout << i + 1 - query(1, 0, 499999, 0, A[i] - 1) << '\n';
        update(1, 0, 499999, A[i]);
    }

    return 0;
}
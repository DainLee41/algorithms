#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 1001;
const int MAXM = 10001;

vector<int> adj[MAXN];
bool visited[MAXN];

void dfs(int v)
{
    visited[v] = true;
    cout << v << ' ';

    for (int i = 0; i < adj[v].size(); i++)
    {
        int next = adj[v][i];
        if (!visited[next])
        {
            dfs(next);
        }
    }
}

void bfs(int v)
{
    queue<int> q;
    q.push(v);
    visited[v] = true;

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        cout << cur << ' ';

        for (int i = 0; i < adj[cur].size(); i++)
        {
            int next = adj[cur][i];
            if (!visited[next])
            {
                q.push(next);
                visited[next] = true;
            }
        }
    }
}

int main()
{
    int N, M, V;
    cin >> N >> M >> V;

    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= N; i++)
    {
        sort(adj[i].begin(), adj[i].end());
    }

    dfs(V);
    cout << '\n';

    fill(visited, visited + MAXN, false); // visited 배열 초기화
    bfs(V);

    return 0;
}
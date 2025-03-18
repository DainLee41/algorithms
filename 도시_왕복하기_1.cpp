#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define INF 1e9

using namespace std;

const int MAXN = 410;

vector<int> adj[MAXN];
int capacity[MAXN][MAXN];
int level[MAXN];
int ptr[MAXN];

// bfs를 이용해 레벨 그래프 생성
bool bfs(int source, int sink)
{
    queue<int> q;
    q.push(source);
    level[source] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : adj[u])
        {
            if (level[v] == -1 && capacity[u][v] > 0)
            {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }

    return level[sink] != -1; // sink에 도달 가능한지 여부 반환
}

int dfs(int u, int sink, int flow)
{
    if (u == sink)
        return flow;

    for (int &i = ptr[u]; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (level[u] + 1 == level[v] && capacity[u][v] > 0)
        {
            int ret = dfs(v, sink, min(flow, capacity[u][v]));
            if (ret > 0)
            {
                capacity[u][v] -= ret;
                capacity[v][u] += ret;
                return ret;
            }
        }
    }

    return 0;
}

int maxFlow(int s, int t)
{
    int ret = 0;
    while (true)
    {
        memset(level, -1, sizeof(level));
        if (!bfs(s, t))
            break;

        memset(ptr, 0, sizeof(ptr));
        while (true)
        {
            int flow = dfs(s, t, INF);
            if (flow == 0)
                break;
            ret += flow;
        }
    }

    return ret;
}

int main()
{
    int N, P;
    cin >> N >> P;

    for (int i = 0; i < P; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        capacity[a][b] = 1;
    }

    cout << maxFlow(1, 2) << '\n';

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

#define INF 1e9
using namespace std;

const int MAXN = 210;

vector<int> adj[MAXN * 2];        // in과 out으로 구분한 그래프
int cost[MAXN];                   // 점거 비용
int capacity[MAXN * 2][MAXN * 2]; // 용량
int flow[MAXN * 2][MAXN * 2];     // 현재 흐르는 유량
int height[MAXN * 2];             // 높이
int excess[MAXN * 2];             // excess flow
int n, m, s, t;

void graphInput()
{
    // 점거 비용 입력
    for (int i = 1; i <= n; i++)
    {
        cin >> cost[i];
    }

    // 그래프 구성
    for (int i = 1; i <= n; i++)
    {
        int in = i * 2;
        int out = i * 2 + 1;

        adj[in].push_back(out);
        adj[out].push_back(in);
        capacity[in][out] = cost[i]; // 점거 비용을 capacity로 설정
    }

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        int u_in = u * 2;
        int u_out = u * 2 + 1;
        int v_in = v * 2;
        int v_out = v * 2 + 1;

        // 간선 추가: u -> v
        adj[u_out].push_back(v_in);
        adj[v_in].push_back(u_out);
        capacity[u_out][v_in] = INF;

        // 간선 추가: v -> u
        adj[v_out].push_back(u_in);
        adj[u_in].push_back(v_out);
        capacity[v_out][u_in] = INF;
    }
}

// u -> v로 유량을 보낼 수 있는지 확인
void push(int u, int v)
{
    int pushFlow = min(excess[u], capacity[u][v] - flow[u][v]);
    if (pushFlow <= 0)
        return;

    flow[u][v] += pushFlow;
    flow[v][u] -= pushFlow;

    excess[u] -= pushFlow;
    excess[v] += pushFlow;
}

// 더이상 유량을 보낼 수 없으면 노드의 높이를 재조정함
void relabel(int u)
{
    int minHeight = INF;
    for (int v : adj[u])
    {
        if (capacity[u][v] - flow[u][v] > 0)
        {
            minHeight = min(minHeight, height[v]);
        }
    }

    if (minHeight == INF)
        height[u] = INF;
    else
        height[u] = minHeight + 1;
}

void discharge(int u)
{
    while (excess[u] > 0)
    {
        static int current[MAXN * 2];
        if (current[u] >= adj[u].size())
        {
            current[u] = 0;
            relabel(u);
            continue;
        }

        int v = adj[u][current[u]];
        if (capacity[u][v] - flow[u][v] > 0 && height[u] > height[v])
        {
            push(u, v);
        }
        else
        {
            current[u]++;
        }
    }
}

void pushRelabel()
{
    // 초기화: source는 s_out, sink는 t_in으로 설정
    memset(height, 0, sizeof(height));
    memset(excess, 0, sizeof(excess));
    memset(flow, 0, sizeof(flow));

    height[s] = 2 * n; // source의 높이는 n * 2
    excess[s] = INF;   // source는 무한대의 유량을 가짐

    for (int v : adj[s])
    {
        push(s, v);
    }

    // 더이상 보낼 유량이 없을 때까지 반복하게 함
    for (int v : adj[s])
    {
        push(s, v);
    }

    // Push-Relabel 알고리즘 실행
    vector<int> nodes;
    for (int i = 1; i <= 2 * n + 1; i++)
    {
        if (i != s && i != t)
        {
            nodes.push_back(i);
        }
    }

    int p = 0;
    while (p < nodes.size())
    {
        int u = nodes[p];
        int old_height = height[u];
        discharge(u);

        if (height[u] > old_height)
        {
            // 높이가 변경되었다면 우선순위를 높임
            nodes.erase(nodes.begin() + p);
            nodes.insert(nodes.begin(), u);
            p = 0;
        }
        else
        {
            p++;
        }
    }
}

void dfs(int u, vector<bool> &visited)
{
    visited[u] = true;
    for (int v : adj[u])
    {
        if (!visited[v] && capacity[u][v] - flow[u][v] > 0)
        {
            dfs(v, visited);
        }
    }
}

void printMinCut()
{
    vector<bool> visited(2 * n + 2, false);
    dfs(s, visited); // s에서 dfs 통해 도달 가능한 노드 찾기

    vector<int> minCut;
    for (int i = 1; i <= n; i++)
    {
        int in = i * 2;
        int out = i * 2 + 1;
        if (visited[in] && !visited[out])
        {
            minCut.push_back(i);
        }
    }

    sort(minCut.begin(), minCut.end());
    for (int city : minCut)
    {
        cout << city << " ";
    }
    cout << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> s >> t;
    s = s * 2 + 1; // source는 s_out으로 설정
    t = t * 2;     // sink는 t_in으로 설정

    graphInput();
    pushRelabel();
    printMinCut();

    return 0;
}

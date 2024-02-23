#include <iostream>
#include <queue>

using namespace std;

int n, m, v;
int graph[1001][1001];
bool visited[1001];

void dfs(int start) {
    visited[start] = true;
    cout << start << ' ';

    for (int i = 1; i <= n; ++i) {
        if (graph[start][i] && !visited[i]) {
            dfs(i);
        }
    }
}

void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front(); q.pop();
        cout << current << ' ';
        for (int i = 1; i <= n; ++i) {
            if (graph[current][i] && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    cin >> n >> m >> v;

    int start, end;
    for (int i = 0; i < m; ++i) {
        cin >> start >> end;
        graph[start][end] = 1;
        graph[end][start] = 1;
    }

    dfs(v);
    cout << '\n';

    for (int i = 1; i <= n; ++i) visited[i] = 0;

    bfs(v);
    cout << '\n';

    return 0;
}
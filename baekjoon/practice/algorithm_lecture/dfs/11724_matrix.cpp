#include <iostream>

using namespace std;

int n, m; // n: 정점 수, m: 간선 수

int matrix[1001][1001];
int visited[1001];

void dfs(int now) {
    for (int j = 1; j <= n; ++j) {
        if (matrix[now][j] == 1 && visited[j] == 0) {
            visited[j] = 1;
            dfs(j);
        }
    }
}

int main() {
    cin >> n >> m;

    int u, v; // u: 시작점, v: 끝점
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        matrix[u][v] = 1;
        matrix[v][u] = 1;
    }

    for (int i = 1; i <= n; ++i) {
        if (visited[i] == 0) {
            visited[i] = 1;
            cnt++;
            for (int j = 1; j <= n; ++j) {
                if (visited[j] == 0 && matrix[i][j] == 1) {
                    visited[j] = 1;
                    dfs(j);
                }
            }
        }
    }
    
    cout << cnt << '\n';
}
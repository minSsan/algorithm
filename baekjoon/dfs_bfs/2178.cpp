#include <iostream>
#include <queue>

using namespace std;

int n, m;
char graph[101][101];
bool visited[101][101];
int dc[4] = {0, 0, -1, 1};
int dr[4] = {-1, 1, 0, 0};

struct node {
    int row;
    int col;
    int dist;
};

int bfs(int start_row, int start_col) {
    queue<node> q;
    q.push({start_row, start_col, 1});
    visited[start_row][start_col] = true;

    int next_row, next_col, dist;
    while (!q.empty()) {
        dist = q.front().dist;

        if (q.front().row == n-1 && q.front().col == m-1) {
            return dist;
        }

        for (int i = 0; i < 4; ++i) {
            next_row = q.front().row + dr[i]; next_col = q.front().col + dc[i];
            if (graph[next_row][next_col] == '1' && !visited[next_row][next_col]) {
                q.push({next_row, next_col, dist+1});
                visited[next_row][next_col] = true;
            }
        }
        q.pop();
    }
    return -1;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> graph[i][j];
        }
    }

    cout << bfs(0, 0) << '\n';

    return 0;
}
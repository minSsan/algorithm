#include <iostream>

using namespace std;

bool visited[1000][1000];
int planet[1000][1000];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

int n, m;

void dfs(int now_row, int now_col) {
    // cout << "now row: " << now_row << ", now col: " << now_col << '\n';
    visited[now_row][now_col] = true;

    for (int i = 0; i < 4; ++i) {
        int next_row = now_row + dy[i];
        int next_col = now_col + dx[i];

        if (next_row >= n) {
            next_row = 0;
        } else if (next_row < 0) {
            next_row = n - 1;
        } else if (next_col >= m) {
            next_col = 0;
        } else if (next_col < 0) {
            next_col = m - 1;
        }

        if (!visited[next_row][next_col] && planet[next_row][next_col] == 0) {
            dfs(next_row, next_col);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> planet[i][j];
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!visited[i][j] && planet[i][j] == 0) {
                dfs(i, j);
                cnt++;
            }
        }
    }

    cout << cnt << '\n';

    return 0;
}
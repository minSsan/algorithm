#include <iostream>
#include <string>

using namespace std;

int n, m, min_cnt, cnt;
char road[110][110];
int visited[110][110];

// 상 -> 하 -> 좌 -> 우 순서
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

// 다음에 방문할 row 값과 col 값
int next_row, next_col;

void dfs(int row, int col, int cnt) {
    if (row == n - 1 && col == m - 1) {
        if (cnt < min_cnt) {
            min_cnt = cnt;
        }
        return ;
    }

    for (int i = 0; i < 4; ++i) {
        next_row = row + dx[i];
        next_col = col + dy[i];

        if (visited[next_row][next_col] == 0 && road[next_row][next_col] == '1' && (next_row >= 0 && next_row < n && next_col >= 0 && next_col < m)) {
            visited[row][col] = 1;
            dfs(next_row, next_col, cnt+1);
            visited[row][col] = 0;
        }
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    min_cnt = n * m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> road[i][j];
        }
    }

    dfs(0, 0, 1);

    cout << min_cnt << '\n';

    return 0;
}
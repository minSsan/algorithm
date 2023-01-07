#include <iostream>
#include <queue>

using namespace std;

int m, n; // m: 가로 칸 수, n: 세로 칸 수
queue<pair<int, int>> q;
int box[1000][1000];
int cnt[1000][1000];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

int raw, raw_to_ripe;
int row, col;

void bfs() {
    while (!q.empty()) {
        row = q.front().first;
        col = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int next_row = row + dy[i];
            int next_col = col + dx[i];
            if ((next_row >= 0 && next_row < n && next_col >= 0 && next_col < m) && cnt[next_row][next_col] == 0 && box[next_row][next_col] == 0) {
                raw_to_ripe++;
                box[next_row][next_col] = 1;
                cnt[next_row][next_col] = cnt[row][col] + 1;
                q.push({next_row, next_col});
            }
        }
    }
}

int main() {
    cin >> m >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> box[i][j];
            if (box[i][j] == 1) {
                q.push({i, j});
            } else if (box[i][j] == 0) {
                raw++;
            }
        }
    }

    bfs();

    if (raw == raw_to_ripe) {
        cout << cnt[row][col] << '\n';
    } else {
        cout << -1 << '\n';
    }

    return 0;
}
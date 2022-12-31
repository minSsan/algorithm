#include <iostream>
#include <queue>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // ? 상 -> 하 -> 좌 -> 우
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {1, -1, 0, 0};

    int visited[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            visited[i][j] = 0;
        }
    }

    char road[n][m];

    for (int i = 0; i < n; ++i) {
        cin >> road[i];
    }

    queue<int> row_q;
    queue<int> col_q;
    queue<int> count_q;

    int row = 0, col = 0;
    int cnt;
    row_q.push(row); col_q.push(col);
    count_q.push(1);
    
    while (!(row == n - 1 && col == m - 1)) {
        row = row_q.front(); col = col_q.front();
        row_q.pop(); col_q.pop();

        // cout << "row: " << row << " ,col: " << col << '\n';
        
        cnt = count_q.front();
        count_q.pop();

        // cout << "cnt: " << cnt << '\n';

        if (visited[row][col] == 0) {
            visited[row][col] = 1;

            for (int i = 0; i < 4; ++i) {
                int now_row = row + dy[i];
                int now_col = col + dx[i];
                if ((now_row >= 0 && now_row < n && now_col >= 0 && now_col < m) && visited[now_row][now_col] == 0 && road[now_row][now_col] == '1') {
                    row_q.push(now_row);
                    col_q.push(now_col);
                    count_q.push(cnt + 1);
                }
            }
        }

    }

    cout << cnt << '\n';

    return 0;
}
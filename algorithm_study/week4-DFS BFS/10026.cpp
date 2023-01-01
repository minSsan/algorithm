#include <iostream>
#include <queue>

using namespace std;

int main() {
    // ? 상 -> 하 -> 좌 -> 우 순으로 탐색
    int dx[4] = {0, 0, -1, 1}; // col
    int dy[4] = {-1, 1, 0, 0}; // row

    int n;
    cin >> n;

    bool visited[n][n];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            visited[i][j] = false;
        }
    }

    char normal_grid[n][n]; // 정상인
    char abnormal_grid[n][n]; // 적록색약

    for (int i = 0; i < n; ++i) {
        cin >> normal_grid[i];
    }

    queue<pair<int, int>> q;
    char color;
    q.push({0, 0});
    int row, col;
    int next_row, next_col;
    int visit_cnt = 0, result = 0;
    
    // ? 정상인
    while (visit_cnt < n * n) {
        row = q.front().first; col = q.front().second;
        color = normal_grid[row][col];
        
        while (!q.empty()) {
            q.pop();

            cout << "row: " << row << " col: " << col << " color: " << color << '\n';

            if (!visited[row][col]) {
                visit_cnt++;
                cout << visit_cnt << '\n';
                visited[row][col] = true;
                for (int i = 0; i < 4; ++i) {
                    next_row = row + dy[i];
                    next_col = col + dx[i];
                    if (((next_row >= 0 && next_row < n) && (next_col >= 0 && next_col < n)) && normal_grid[next_row][next_col] == color && !visited[next_row][next_col]) {
                        visited[next_row][next_col] = true;
                        q.push({next_row, next_col});
                    }
                }
            }
        }
        result++;

        bool flag = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!visited[i][j]) {
                    q.push({i, j});
                    flag = true; break;
                }
            }
            if (flag) break;
        }
    }

    cout << result << '\n';

    return 0;
}
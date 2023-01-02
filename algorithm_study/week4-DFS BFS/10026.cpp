#include <iostream>
#include <queue>

using namespace std;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

int n;

int bfs(char (*grid)[100], int n) {
    bool visited[100][100] = {false};
    int visited_cnt = 0;
    int cnt = 0;

    int row = 0, col = 0;
    int next_row, next_col;

    queue<pair<int, int>> q;
    q.push({row, col});

    char color;

    while (visited_cnt < n * n) {
        while (!q.empty()) {
            row = q.front().first; col = q.front().second;
            q.pop();
            
            color = grid[row][col];

            if (!visited[row][col]) {
                visited[row][col] = true;
                visited_cnt++;

                for (int i = 0; i < 4; ++i) {
                    next_row = row + dy[i];
                    next_col = col + dx[i];

                    if ((next_row >= 0 && next_row < n && next_col >= 0 && next_col < n) && !visited[next_row][next_col] && grid[next_row][next_col] == color) {
                        q.push({next_row, next_col});
                    }
                }
            }
        }

        cnt++;

        bool flag = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!visited[i][j]) {
                    q.push({i, j});
                    flag = true;
                    break;
                }
            }
            if (flag) break;
        }
    }


    return cnt;
}

int main() {
    cin >> n;

    char grid[100][100];
    char abnormal_grid[100][100];

    // ? 정상인 인지 색상표
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    // ? 적록색맹 인지 색상표
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'G') {
                abnormal_grid[i][j] = 'R';
            } else {
                abnormal_grid[i][j] = grid[i][j];
            }
        }
    }

    
    cout << bfs(grid, n) << ' ';

    cout << bfs(abnormal_grid, n) << '\n';

    return 0;
}
#include <iostream>
#include <queue>

using namespace std;

int n;
char grid[101][101];
bool visited[100][100];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

void bfs(int start_row, int start_col) {
    queue<pair<int,int>> q;
    q.push({start_row, start_col});

    char color = grid[start_row][start_col];

    while (!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        if (!visited[row][col]) {
            visited[row][col] = true;
            for (int i = 0; i < 4; ++i) {
                int next_row = row + dy[i];
                int next_col = col + dx[i];
                if ((next_row >= 0 && next_row < n && next_col >= 0 && next_col < n) && !visited[next_row][next_col] && grid[next_row][next_col] == color) {
                    q.push({next_row, next_col});
                }
            }
        }
    }
}

int main() {
    cin >> n;

    int cnt = 0;

    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!visited[i][j]) {
                bfs(i, j);
                cnt++;
            }

            if (grid[i][j] == 'G') {
                grid[i][j] = 'R';
            }
        }
    }

    cout << cnt << ' ';

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            visited[i][j] = false;
        }
    }

    cnt = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!visited[i][j]) {
                bfs(i, j);
                cnt++;
            }
        }
    }

    cout << cnt << '\n';

    return 0;
}
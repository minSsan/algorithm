#include <iostream>

using namespace std;

int n;

bool visited[100][100];
bool visited_abnormal[100][100];
char grid[100][100];
char color;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

void dfs(int row, int col) {
    for (int i = 0; i < 4; ++i) {
        int next_row = row + dy[i];
        int next_col = col + dx[i];
        if ((next_row >= 0 && next_row < n && next_col >= 0 && next_col < n) && !visited[next_row][next_col] && grid[next_row][next_col] == color) {
            visited[next_row][next_col] = true;
            dfs(next_row, next_col);
        }
    }
}

void dfs_abnormal(int row, int col) {
    for (int i = 0; i < 4; ++i) {
        int next_row = row + dy[i];
        int next_col = col + dx[i];
        if ((next_row >= 0 && next_row < n && next_col >= 0 && next_col < n) && !visited_abnormal[next_row][next_col] && (grid[next_row][next_col] == color || color == 'R' && grid[next_row][next_col] == 'G' || color == 'G' && grid[next_row][next_col] == 'R')) {
            visited_abnormal[next_row][next_col] = true;
            dfs_abnormal(next_row, next_col);
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
                visited[i][j] = true;
                color = grid[i][j];
                dfs(i, j);
                cnt++;
            }
        }
    }

    cout << cnt << ' ';
    
    cnt = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!visited_abnormal[i][j]) {
                visited_abnormal[i][j] = true;
                color = grid[i][j];
                dfs_abnormal(i, j);
                cnt++;
            }
        }
    }

    cout << cnt << '\n';

    return 0;
}
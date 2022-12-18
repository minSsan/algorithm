#include <iostream>
#include <queue>

using namespace std;

int n;

char map[25][25];
int visited[25][25];
int cnt;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

priority_queue<int, vector<int>, greater<int>> result;

void dfs(int row, int col) {
    cnt++;
    visited[row][col] = 1;

    for (int i = 0; i < 4; ++i) {
        int next_row = row + dy[i];
        int next_col = col + dx[i];
        if (visited[next_row][next_col] == 0 && map[next_row][next_col] == '1' && (next_row >= 0 && next_row < n && next_col >= 0 && next_col < n)) {
            dfs(next_row, next_col);
        }
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> map[i];
    }

    int complex = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (visited[i][j] == 0 && map[i][j] == '1') {
                complex++;
                
                dfs(i, j);
                result.push(cnt);
                cnt = 0;
            }
        }
    }

    cout << complex << '\n';
    while (!result.empty()) {
        cout << result.top() << '\n';
        result.pop();
    }

    return 0;
}
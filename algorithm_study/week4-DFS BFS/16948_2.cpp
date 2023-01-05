#include <iostream>
#include <queue>

using namespace std;

int n;
int cnt[200][200];

int dy[6] = {-2, -2, 0, 0, 2, 2};
int dx[6] = {-1, 1, -2, 2, -1, 1};

int start_row, start_col, end_row, end_col;

void bfs(int start_row, int start_col) {
    queue<pair<int, int>> q;
    q.push({start_row, start_col});

    while (!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        if (row == end_row && col == end_col) {
            return;
        }
    
        for (int i = 0; i < 6; ++i) {
            int next_row = row + dy[i];
            int next_col = col + dx[i];

            if ((next_row >= 0 && next_row < n && next_col >= 0 && next_col < n) && cnt[next_row][next_col] == 0) {
                q.push({next_row, next_col});
                cnt[next_row][next_col] = cnt[row][col] + 1;
            }
        }
    }
    
}

int main() {
    cin >> n;
    cin >> start_row >> start_col >> end_row >> end_col;

    bfs(start_row, start_col);

    if (cnt[end_row][end_col]) {
        cout << cnt[end_row][end_col] << '\n';
    } else {
        cout << -1 << '\n';
    }

    return 0;
}
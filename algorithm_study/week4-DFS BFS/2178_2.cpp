#include <iostream>
#include <queue>

using namespace std;

int cnt[99][99];
char road[99][99];
int n, m;

// ? 상 -> 하 -> 좌 -> 우
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

void bfs(int start_row, int start_col) {
    queue<pair<int, int>> q;
    q.push({start_row, start_col});

    while(!q.empty() && cnt[n-1][m-1] == 0) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int next_row = row + dy[i];
            int next_col = col + dx[i];
            if ((next_row >= 0 && next_row < n && next_col >= 0 && next_col < m) && cnt[next_row][next_col] == 0 && road[next_row][next_col] == '1') {
                q.push({next_row, next_col});
                cnt[next_row][next_col] = cnt[row][col] + 1;
            }
        }
    }
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        cin >> road[i];
    }

    cnt[0][0] = 1;
    bfs(0, 0);

    cout << cnt[n-1][m-1] << '\n';

    return 0;
}
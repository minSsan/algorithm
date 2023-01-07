#include <iostream>
#include <queue>

using namespace std;

// ? bfs -> 모든 방향(상, 하, 좌, 우)의 탐색을 끝낼 때마다 1일씩 증가

int main() {
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    int m, n; // m: 가로 칸 수, n: 세로 칸 수
    cin >> m >> n;

    int box[n][m];
    queue<pair<int, int>> q;
    queue<pair<int, int>> temp_q;

    int raw_cnt = 0; // 익지 않은 토마토 수
    int cnt = 0; // 원래는 익지 않았다가 날이 지나면서 익은 토마토 수

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> box[i][j];
            if (box[i][j] == 1) {
                temp_q.push({i, j});
            } else if (box[i][j] == 0) {
                raw_cnt++;
            }
        }
    }

    int day = 0;
    int row, col;
    int next_row, next_col;

    while (!temp_q.empty() && cnt != raw_cnt) { // 다음날 살펴볼 토마토가 있거나, 익지 않았던 토마토가 모두 익을 때까지 반복
        while (!temp_q.empty()) {
            q.push({temp_q.front().first, temp_q.front().second}); // 오늘 살펴볼 토마토 목록에 옮기기
            temp_q.pop();
        }

        while (!q.empty()) { // 익은 토마토를 모두 살펴볼 때까지
            row = q.front().first;
            col = q.front().second;
            q.pop();

            for (int i = 0; i < 4; ++i) {
                next_row = row + dy[i];
                next_col = col + dx[i];
                // 익은 토마토와 인접한 토마토가 아직 익지 않았다면
                if ((next_row >= 0 && next_row < n && next_col >= 0 && next_col < m) && box[next_row][next_col] == 0) {
                    temp_q.push({next_row, next_col}); // 다음날 살펴볼 토마토 목록에 추가
                    box[next_row][next_col] = 1; // 토마토가 익음
                    cnt++;
                }
            }
        }

        day++; // 날이 1 증가

    }

    if (cnt == raw_cnt) {
        cout << day << '\n';
    } else {
        cout << -1 << '\n';
    }

    return 0;
}
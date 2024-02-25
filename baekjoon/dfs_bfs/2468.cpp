#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int n;
int graph[100][100];
bool visited[100][100];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool comp(int a, int b) {
    return a > b;
}

void bfs(int row, int col, int bound) {
    int current_row, current_col, next_row, next_col;
    queue<pair<int, int>> q;
    q.push({row, col});
    visited[row][col] = true;

    while (!q.empty()) {
        current_row = q.front().first; current_col = q.front().second;
        q.pop();
        for (int i = 0; i < 4; ++i) {
            next_row = current_row + dr[i]; next_col = current_col + dc[i];
            if ((0 <= next_row && next_row < n) && (0 <= next_col && next_col < n) 
                && !visited[next_row][next_col] 
                && graph[next_row][next_col] > bound) {
                    visited[next_row][next_col] = true;
                    q.push({next_row, next_col});
            }
        }
    }
    
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int max_h = 0;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
            if (graph[i][j] > max_h) max_h = graph[i][j];
        }
    }

    vector<int> result;
    int cnt;
    for (int i = 0; i < max_h; ++i) { // 높이가 i 보다 큰 영역 개수 찾기
        cnt = 0;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (!visited[r][c] && graph[r][c] > i) {
                    ++cnt;
                    bfs(r, c, i);
                }
            }
        }
        result.push_back(cnt);

        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                visited[r][c] = false;
            }
        }
    }

    sort(result.begin(), result.end(), comp);
    cout << result[0] << '\n';

    return 0;
}
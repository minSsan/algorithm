#include <iostream>
#include <vector>
#include <queue>

using namespace std;

char graph[5][5];
int num[5][5];
bool visited[26];
int result;
vector<pair<int, int>> positions;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
bool near_visited[5][5];

void print_result() {
    char results[5][5];
    fill(results[0], results[0] + 25, '.');
    for (pair<int, int> pos : positions) {
        results[pos.first][pos.second] = graph[pos.first][pos.second];
    }

    cout << '\n';
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cout << results[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void update_result() {
    int cnt = 0;
    for (pair<int, int> pos : positions) {
        int r = pos.first, c = pos.second;
        if (graph[r][c] == 'S') cnt++;
    }
    if (cnt >= 4) {
        // print_result();
        result++;
    }
}

bool is_valid_pos(int r, int c) {
    return r >= 0 && r < 5 && c >= 0 && c < 5;
}

int near_cnt() {
    int cnt = 1;
    queue<pair<int, int>> q;
    near_visited[positions.front().first][positions.front().second] = true;
    q.push(positions.front());

    while (!q.empty()) {
        int r = q.front().first, c = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int next_r = r + dr[i];
            int next_c = c + dc[i];
            if (is_valid_pos(next_r, next_c) && visited[next_r * 5 + next_c + 1] && !near_visited[next_r][next_c]) {
                near_visited[next_r][next_c] = true;
                q.push({next_r, next_c});
                cnt++;
            }
        }
    }

    return cnt;
}

void dfs() {
    if (positions.size() == 7) {
        fill(near_visited[0], near_visited[0] + 25, false);
        if (near_cnt() == 7) {
            update_result();
        }
        return;
    }

    int last = 0;
    if (!positions.empty()) {
        last = positions.back().first * 5 + positions.back().second + 1;
    }

    for (int i = last+1; i <= 25; ++i) {
        if (!visited[i]) {
            int r = (i-1) / 5, c = (i-1) % 5;
            positions.push_back({r, c});
            visited[i] = true;
            dfs();
            positions.pop_back();
            visited[i] = false;
        }
    }
}

int main() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> graph[i][j];
            num[i][j] = 5 * i + j + 1;
        }
    }

    dfs();

    cout << result << '\n';

    return 0;
}
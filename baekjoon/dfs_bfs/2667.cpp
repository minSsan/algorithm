#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
char graph[25][25];
bool visited[25][25];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int next_row, next_col;
int dist;

void dfs(int row, int col) {
    ++dist;
    visited[row][col] = true;
    for (int i = 0; i < 4; ++i) {
        next_row = row + dr[i]; next_col = col + dc[i];
        if (!(0 <= next_row && next_row < n && 0 <= next_col && next_col < n)) continue;

        if (graph[next_row][next_col] == '1' && !visited[next_row][next_col]) {
            dfs(next_row, next_col);
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    vector<int> result;
    int complex = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!visited[i][j] && graph[i][j] == '1') {
                ++complex;
                dfs(i, j);
                result.push_back(dist); dist = 0;
            }
        }
    }

    cout << complex << '\n';
    sort(result.begin(), result.end());
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << '\n';
    }

    return 0;
}
#include <iostream>
#include <vector>

using namespace std;

int n;
bool visited[15][15];
vector<pair<int, int>> v;
int dr[8] = {-1, 1, 0, 0, -1, 1, 1, -1};
int dc[8] = {0, 0, -1, 1, 1, 1, -1, -1};

int result;

bool is_safe_zone(int row, int col) {
    for (pair<int, int> pos : v) {
        int other_row = pos.first;
        int other_col = pos.second;
        if (col == other_col) return false;
        if (abs(other_row - row) == abs(other_col - col)) return false;
    }
    return true;
}

void dfs() {
    int cnt = v.size();
    if (cnt == n) {
        // cout << n << " 개 놓기 완료\n";
        result++;
        return;
    }

    for (int j = 0; j < n; ++j) {
        if (!visited[cnt][j] && is_safe_zone(cnt, j)) {
            // cout << i << ", " << j << " 에 놓는다\n";
            v.push_back({cnt, j});
            visited[cnt][j] = true;
            dfs();
            v.pop_back();
            visited[cnt][j] = false;
        }
    }
}

int main() {
    cin >> n;

    dfs();

    cout << result << '\n';

    return 0;
}
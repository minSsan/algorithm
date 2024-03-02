#include <iostream>

using namespace std;

int n, m, result; 
char load[99][99];
// ? 이미 방문한 타일인지 검사 (이게 없으면 무한루프에 빠짐)
int visited[99][99];

void dfs(int row, int col, int cnt) {
    // visited[row][col] = 1; // ? 여기서 visited를 1로 바꾸고 0으로 다시 초기화하지 않으면, 다른 가지에서 해당 타일을 밟을 수 없게 된다.

    if (row == n - 1 && col == m - 1) {
        if (cnt < result) {
            result = cnt;
        }
        return ;
    }

    if (row - 1 >= 0 && visited[row-1][col] != 1 && load[row-1][col] == '1') {
        visited[row-1][col] = 1; // ? 하나의 가지를 뻗을 때, 이미 밟았던 타일(이미 걸어온 길)을 밟지 않도록 visited를 1로 설정
        dfs(row - 1, col, cnt + 1);
        visited[row-1][col] = 0; 
    }
    if (row + 1 < n && visited[row+1][col] != 1 && load[row+1][col] == '1') {
        visited[row+1][col] = 1;
        dfs(row + 1, col, cnt + 1);
        visited[row+1][col] = 0;
    }
    if (col - 1 >= 0 && visited[row][col-1] != 1 && load[row][col-1] == '1') {
        visited[row][col-1] = 1;
        dfs(row, col - 1, cnt + 1);
        visited[row][col-1] = 0;
    }
    if (col + 1 < m && visited[row][col+1] != 1 && load[row][col+1] == '1') {
        visited[row][col+1] = 1;
        dfs(row, col + 1, cnt + 1);
        visited[row][col+1] = 0;
    }
}

int main() {
    cin >> n >> m;

    result = n * m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> load[i][j];
        }
    }

    dfs(0, 0, 1);

    cout << result << '\n';

    return 0;
}
#include <iostream>
#include <queue>

using namespace std;

int main() {
    int dx[6] = {-2, -2, 0, 0, 2, 2};
    int dy[6] = {-1, 1, -2, 2, -1, 1};

    int n;
    cin >> n;

    int row, col;
    cin >> row >> col;

    int end_row, end_col;
    cin >> end_row >> end_col;
    
    bool visited[200][200] = {false};
    queue<pair<int, int>> q;
    queue<int> cnt_q;

    q.push({row, col});
    cnt_q.push(1);

    int count, next_row, next_col;
    
    while (!q.empty()) {
        row = q.front().first; col = q.front().second;
        q.pop();
        count = cnt_q.front();
        cnt_q.pop();

        if (row == end_row && col == end_col) break;

        if (!visited[row][col]) {
            visited[row][col] = true;

            for (int i = 0; i < 6; ++i) {
                next_row = row + dy[i];
                next_col = col + dx[i];
                if ((next_row >= 0 && next_row < n && next_col >= 0 && next_col < n) && !visited[next_row][next_col]) {
                    q.push({next_row, next_col});
                    cnt_q.push(count + 1);
                }
            }
        }
    }

    cout << count << '\n';

    return 0;
}
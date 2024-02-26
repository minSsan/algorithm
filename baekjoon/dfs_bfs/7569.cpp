#include <iostream>
#include <queue>

using namespace std;

//? 1: 익은 토마토, 0: 익지 않은 토마토, -1: 빈 공간

struct node {
    int row;
    int col;
    int date;
};

int m, n, h;
int total, cnt;
int box[10000][100]; // row == n * h
queue<node> q;
// 앞 - 뒤 - 왼쪽 - 오른쪽
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int current_date;

void bfs() {
    int current_row, current_col, next_row, next_col;
    while (!q.empty()) {
        current_row = q.front().row; current_col = q.front().col;
        current_date = q.front().date;
        q.pop();

        // 같은 칸 내에서 이동 - 앞, 뒤, 오, 왼
        for (int i = 0; i < 4; ++i) {
            next_row = current_row + dr[i]; next_col = current_col + dc[i];
            if ((current_row / n == next_row / n)
                    && ((current_row / n) * n <= next_row && next_row < (current_row / n) * n + n) 
                    && (0 <= next_col && next_col < m) 
                    && box[next_row][next_col] == 0) {
                q.push({next_row, next_col, current_date+1});
                box[next_row][next_col] = 1;
                ++cnt;
            }
        }
        // 다른 칸으로 이동 - 위, 아래
        next_row = current_row + n;
        if (next_row < n * h && box[next_row][current_col] == 0) {
            q.push({next_row, current_col, current_date+1});
            box[next_row][current_col] = 1;
            ++cnt;
        }
        next_row = current_row - n;
        if (next_row >= 0 && box[next_row][current_col] == 0) {
            q.push({next_row, current_col, current_date+1});
            box[next_row][current_col] = 1;
            ++cnt;
        }
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);


    cin >> m >> n >> h;
    int input_num;
    for (int k = 0; k < h; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> input_num;
                box[k*n + i][j] = input_num;
                if (input_num == 1) q.push({k*n + i, j, 0});
                if (input_num == 0) ++total;
            }
        }
    }

    bfs();

    if (cnt == total) {
        cout << current_date << '\n';
    } else {
        cout << -1 << '\n';
    }

    return 0;
}
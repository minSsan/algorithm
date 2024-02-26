#include <iostream>
#include <queue>
#include <tuple>

#define MAX 100
#define RIPE 1
#define UNRIPE 0
#define EMPTY -1
#define DIRECTION 6

using namespace std;

struct node {
    int h;
    int r;
    int c;
    int date;
};

int box[MAX][MAX][MAX];
int row, col, height;
int total, cnt;
queue<node> q;

// 상 - 하 - 좌 - 우 - 위 - 아래
const int dr[6] = {-1, 1, 0, 0, 0, 0};
const int dc[6] = {0, 0, -1, 1, 0, 0};
const int dh[6] = {0, 0, 0, 0, -1, 1};

bool is_in_area(int r, int c, int h);
int current_date;

void bfs() {
    int current_row, current_col, current_height, next_row, next_col, next_height;
    while (!q.empty()) {
        current_row = q.front().r; current_col = q.front().c; current_date = q.front().date; current_height = q.front().h;
        q.pop();
        for (int i = 0; i < DIRECTION; ++i) {
            next_row = current_row + dr[i]; next_col = current_col + dc[i]; next_height = current_height + dh[i];
            if (is_in_area(next_row, next_col, next_height) && box[next_height][next_row][next_col] == UNRIPE) {
                box[next_height][next_row][next_col] = RIPE;
                ++cnt;
                int next_date = current_date + 1;
                q.push({next_height, next_row, next_col, next_date});
            }
        }
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> col >> row >> height;
    for (int h = 0; h < height; ++h) {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                cin >> box[h][i][j];
                if (box[h][i][j] == RIPE) {
                    q.push({h, i, j, 0});
                }
                if (box[h][i][j] == UNRIPE) {
                    ++total;
                }
            }
        }
    }

    bfs();

    if (total == cnt) cout << current_date << '\n';
    else cout << -1 << '\n';

    return 0;
}

bool is_in_area(int r, int c, int h) {
    return ((0 <= r && r < row) && (0 <= c && c < col) && (0 <= h && h < height));
}
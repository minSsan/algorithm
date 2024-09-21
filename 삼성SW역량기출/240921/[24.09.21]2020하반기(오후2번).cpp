#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m, k;

int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

struct fireball {
    int row;
    int col;
    int m; // 질량
    int s; // 속력
    int d; // 방향
};

vector<fireball> grid[50][50];

pair<int, int> get_next_pos(fireball ball) {
    int row = ball.row; int col = ball.col;
    int next_row = row + dr[ball.d]*ball.s, next_col = col + dc[ball.d]*ball.s;
    int interval = n;

    while (next_row < 0) {
        next_row += interval;
    }
    while (next_col < 0) {
        next_col += interval;
    }
    while (next_row > n-1) {
        next_row -= interval;
    }
    while (next_col > n-1) {
        next_col -= interval;
    }

    return {next_row, next_col};
}

void move_balls() {
    vector<fireball> temp[50][50];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (fireball ball : grid[i][j]) {
                pair<int, int> pos = get_next_pos(ball);
                ball.row = pos.first, ball.col = pos.second;
                temp[pos.first][pos.second].push_back(ball);
            }
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = temp[i][j];
        }
    }
}

void merge_balls() {
    vector<fireball> temp[50][50];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j].size() > 1) {
                int new_m = 0, new_s = 0;
                bool is_odd = grid[i][j][0].d % 2 == 1;
                bool all_same = true;
                for (fireball ball : grid[i][j]) {
                    new_m += ball.m;
                    new_s += ball.s;
                    if (is_odd) {
                        if (ball.d % 2 == 0) all_same = false;
                    } else {
                        if (ball.d % 2 == 1) all_same = false;
                    }
                }
                new_m = new_m / 5; new_s = new_s / grid[i][j].size();

                if (new_m == 0) {
                    continue;
                }

                if (all_same) {
                    for (int d = 0; d <= 6; d += 2) {
                        temp[i][j].push_back({i, j, new_m, new_s, d});
                    }
                } else {
                    for (int d = 1; d <= 7; d += 2) {
                        temp[i][j].push_back({i, j, new_m, new_s, d});
                    }
                }
            } else {
                temp[i][j] = grid[i][j];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = temp[i][j];
        }
    }
}

int get_m_sum() {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (fireball ball : grid[i][j]) {
                sum += ball.m;
            }
        }
    }
    return sum;
}

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int r, c, m, s, d;
        cin >> r >> c >> m >> s >> d;
        grid[r-1][c-1].push_back({r-1, c-1, m, s, d});
    }

    while (k--) {
        move_balls();
        merge_balls();
    }

    cout << get_m_sum() << '\n';

    return 0;
}
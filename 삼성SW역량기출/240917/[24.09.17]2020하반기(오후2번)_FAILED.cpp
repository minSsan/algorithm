#include <iostream>
#include <vector>

using namespace std;

int n, m, k;

struct fireball {
    int m; // 질량
    int s; // 속력
    int d; // 방향
};

// 북 -> 북동 -> 동 -> 남동 -> 남 -> 남서 -> 서 -> 북서
int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

vector<fireball> grid[50][50];

// (row, col)에 있는 파이어볼을 모두 이동시키는 함수
void move_ball(int row, int col) {
    int move_cnt; // 이동하는 칸의 수
    int interval; // 이동 간격 단위

    //? grid[row][col]에 있는 모든 파이어 볼을 꺼내서 temp에 옮기기
    vector<fireball> temp;
    while (!grid[row][col].empty()) {
        fireball ball = grid[row][col].back();
        temp.push_back(ball);
        grid[row][col].pop_back();
    }

    for (fireball ball : temp) { // N^2
        //* 1. 이동하는 칸의 수 계산
        switch (ball.d) {
            //* 1-1. 대각선 방향인 경우
            case 1:
            case 3:
            case 5:
            case 7:
                interval = n - abs(row-col);
                break;
            //* 1-2. 수평 방향인 경우
            case 0:
            case 2:
            case 4:
            case 6:
                interval = n;
                break;
            default:
                break;
        }
        move_cnt = ball.s % interval;

        //* 2. 이동 방향으로 move_cnt 만큼 이동
        int next_row = (row + (dr[ball.d] * move_cnt + interval)) % interval;
        int next_col = (col + (dc[ball.d] * move_cnt + interval)) % interval;

        cout << "next_row: " << next_row << ", next_col: " << next_col << '\n';

        grid[next_row][next_col].push_back(ball);
    }
}

// 
pair<int, pair<int, int>> get_merge_info(vector<fireball> v) { // {질량, 속력, 방향 홀짝 여부} 0: 방향 짝수, 1: 방향 홀수
    int new_m = 0, new_s = 0;
    int cnt = v.size();
    bool is_holsu = v[0].d % 2 == 1;
    bool all_same_d = true;
    while (!v.empty()) {
        fireball ball = v.back();
        new_m += ball.m;
        new_s += ball.s;
        if (!(is_holsu && ball.d % 2 == 1 || !is_holsu && ball.d % 2 == 0)) all_same_d = false;
        v.pop_back();
    }
    cout << "new_m: " << new_m / 5 << "new_s: " << new_s / cnt << '\n';
    return {new_m / 5, { new_s / cnt, all_same_d ? 0 : 1 }};
}

void merge_ball() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j].size() > 1) {
                pair<int, pair<int ,int>> merge = get_merge_info(grid[i][j]);
                bool is_holsu = merge.second.second;
                int new_m = merge.first;
                int new_s = merge.second.first;

                grid[i][j].clear();

                if (new_m == 0) continue;

                if (is_holsu) {
                    for (int d = 1; d <= 7; d+=2) {
                        grid[i][j].push_back({new_m, new_s, d});
                    }
                } else {
                    for (int d = 0; d <= 6; d += 2) {
                        grid[i][j].push_back({new_m, new_s, d});
                    }
                }
            }
        }
    }
}

int get_sum() {
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
        int r, c, mi, si, di;
        cin >> r >> c >> mi >> si >> di;
        grid[r-1][c-1].push_back({mi, si, di});
    }

    while (k--) {
        //* 1. 격자에 있는 모든 파이어 볼을 옮기기
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                move_ball(i, j);
            }
        }

        //* 2. 파이어볼 합치기
        merge_ball();
    }

    cout << get_sum() << '\n';

    return 0;
}
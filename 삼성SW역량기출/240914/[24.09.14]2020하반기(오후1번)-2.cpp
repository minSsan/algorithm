#include <iostream>

#define LEFT 0
#define DOWN 1
#define RIGHT 2
#define UP 3

using namespace std;

int n;

int grid[500][500];

int rate[9] = {1, 1, 2, 2, 5, 7, 7, 10, 10};
// 1%, 1%, 2%, 2%, 5%, 7%, 7%, 10%, 10%, a
int dr[4][10] = {
    {-1, 1, -2, 2, 0, -1, 1, -1, 1, 0},
    {-1, -1, 0, 0, 2, 0, 0, 1, 1, 1},
    {-1, 1, -2, 2, 0, -1, 1, -1, 1, 0},
    {1, 1, 0, 0, -2, 0, 0, -1, -1, -1}
};
int dc[4][10] = {
    {1, 1, 0, 0, -2, 0, 0, -1, -1, -1},
    {-1, 1, -2, 2, 0, -1, 1, -1, 1, 0},
    {-1, -1, 0, 0, 2, 0, 0, 1, 1, 1},
    {-1, 1, -2, 2, 0, -1, 1, -1, 1, 0}
};

int result = 0;

bool is_in_grid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

void move_sand(int direction, int dest_r, int dest_c) {
    int a = grid[dest_r][dest_c];

    int* current_dr = dr[direction];
    int* current_dc = dc[direction];

    //* 1. 비율 칸으로 모래 이동
    for (int i = 0; i < 9; ++i) {
        int next_r = dest_r + current_dr[i];
        int next_c = dest_c + current_dc[i];
        if (is_in_grid(next_r, next_c)) { // 해당 칸으로 모래 이동
            grid[next_r][next_c] += grid[dest_r][dest_c] * rate[i] / 100;
        } else { // 격자 밖으로 모래 이동
            result += grid[dest_r][dest_c] * rate[i] / 100;
        }
        a -= grid[dest_r][dest_c] * rate[i] / 100;
    }

    //* 2. alpha 칸으로 모래 이동
    int alpha_r = dest_r + current_dr[9];
    int alpha_c = dest_c + current_dc[9];
    if (is_in_grid(alpha_r, alpha_c)) {
        grid[alpha_r][alpha_c] += a;
    } else {
        result += a;
    }
}

pair<int, int> get_dest(int direction, int row, int col) {
    switch (direction) {
        case LEFT:
            return { row, col-1 };
        
        case RIGHT:
            return { row, col+1 };
        
        case UP:
            return { row-1, col };
        
        case DOWN:
            return { row+1, col };
        
        default:
            return { row, col };
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }
    
    int row = n / 2; int col = n / 2;
    int direction = 0;
    int limit = 2;

    for (int i = 1; i < n; ++i) {
        if (i == n-1) limit = 3;
        for (int j = 0; j < limit; ++j) {
            for (int m = 0; m < i; ++m) {
                //* 1. y 위치에서 모래 옮기기
                pair<int, int> pos = get_dest(direction, row, col);
                move_sand(direction, pos.first, pos.second);
                //* 2. y 위치에 모래 없애기
                grid[row][col] = 0;
                //* 3. 현재 토네이도 위치 갱신
                row = pos.first; col = pos.second;
            }
            direction = (direction + 1) % 4;
        }
    }

    cout << result << '\n';

    return 0;
}
// 문제 링크 - https://www.acmicpc.net/problem/20058
// 시간 - 1시간 30분 소요

#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;

int grid[65][65];
int step[1000];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int n, q, grid_size;

//? (start_row, start_col) ~ (end_row, end_col) 영역을 시계방향으로 90도 회전시키는 함수
void rotate_grid(int start_row, int start_col, int end_row, int end_col) {
    int m = end_row - start_row + 1;
    int origin[m][m];
    //* 1. copy
    // cout << "start: (" << start_row << ", " << start_col << "), end: (" << end_row << ", " << end_col << ")\n";
    // cout << "===== origin =====\n";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            origin[i][j] = grid[start_row+i][start_col+j];
            // cout << origin[i][j] << ' ';
        }
        // cout << '\n';
    }

    //* 2. rotate
    // cout << "==== grid ====\n";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            grid[start_row+i][start_col+j] = origin[(m-1)-j][i];
            // cout << grid[start_row+i][start_col+j] << ' ';
        }
        // cout << '\n';
    }
    // cout << "\n\n";
}

bool is_valid(int row, int col) {
    return row >= 0 && row < grid_size && col >= 0 && col < grid_size;
}

void update_ice() {
    int origin[grid_size][grid_size];
    //? copy
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            origin[i][j] = grid[i][j];
        }
    }

    int next_row, next_col;
    for (int row = 0; row < grid_size; ++row) {
        for (int col = 0; col < grid_size; ++col) {
            int cnt = 0;
            for (int i = 0; i < 4; ++i) {
                next_row = row + dr[i]; next_col = col + dc[i];
                if (is_valid(next_row, next_col) && origin[next_row][next_col] > 0) cnt++;
            }
            if (cnt < 3 && grid[row][col] > 0) --grid[row][col];
        }
    }
}

bool visited[65][65];

int get_size(int row, int col) {
    int cnt = 0;

    queue<pair<int, int>> q;

    q.push({row, col});
    visited[row][col] = true;

    while (!q.empty()) {
        cnt++;
        int current_row = q.front().first;
        int current_col = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int next_row = current_row + dr[i];
            int next_col = current_col + dc[i];
            if (is_valid(next_row, next_col) && !visited[next_row][next_col] && grid[next_row][next_col] > 0) {
                visited[next_row][next_col] = true;
                q.push({next_row, next_col});
            }
        }
    }
    return cnt;
}

pair<int, int> get_results() {
    int sum = 0; // 얼음 총 합
    int max_cnt = 0; // 가장 큰 덩어리가 차지하는 칸의 수
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            //? 1. 얼음 총량 더하기
            sum += grid[i][j];
            if (!visited[i][j] && grid[i][j] > 0) {
                //? 2. 큰 덩어리 차지하는 칸 수 갱신
                int tmp = get_size(i, j);
                if (tmp > max_cnt) max_cnt = tmp;
            }
        }
    }
    return {sum, max_cnt};
}

void print_grid() {
    cout << "=== grid ===\n";
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    cin >> n >> q;
    grid_size = pow(2, n);
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i < q; ++i) {
        cin >> step[i];
    }

    //* 1. step을 순회하면서 능력 사용
    for (int i = 0; i < q; ++i) {
        // cout << "======= L = " << step[i] << " 능력 사용 =======\n";
        
        int part_size = pow(2, step[i]);

        //* 1-1. 격자를 pow(2, step[i]) X pow(2, step[i]) 로 쪼개어 모두 시계방향 90도 회전
        for (int start_row = 0; start_row < grid_size; start_row += part_size) {
            for (int start_col = 0; start_col < grid_size; start_col += part_size) {
                rotate_grid(start_row, start_col, start_row + part_size - 1, start_col + part_size - 1);
            }
        }
        //* 2. 각 능력 사용 이후 얼음양 갱신 (상-하-좌-우 얼음이 0인 곳이 2칸 이상인 경우, -1)
        update_ice();
        // print_grid();
    }

    pair<int, int> results = get_results();
    cout << results.first << '\n' << results.second << '\n';

    return 0;
}
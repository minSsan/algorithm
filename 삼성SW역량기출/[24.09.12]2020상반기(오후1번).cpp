// 문제 링크 - https://www.acmicpc.net/problem/19237
// 시간 - 2시간 50분 소요

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#define EMPTY 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

using namespace std;

int n, m, k; // n: 격자 크기, m: 상어 수, k: 냄새가 사라지는 기준
int grid[21][21]; // 격자 상태 (n - n번 상어가 있음)
pair<int, int> smell[21][21]; // (상어 번호, 냄새 남은 시간)
int direction[401]; // n번 상어의 방향
pair<int, int> position[401]; // n번 상어의 위치 (row, col)
int priority[401][5][4]; // n번 상어의 이동 방향 우선순위 - priority[n][1] => UP 방향일 때의 이동 방향 우선순위

bool is_out[401]; // n번 상어가 격자 밖으로 쫓겨났는지

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int seconds;

/**
 * 상어의 이동이 끝난 후, 냄새를 감소시키는 함수
 * - 현재 상어가 있는 위치의 냄새는 감소시키지 않는다.
*/
void decrease_smell() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] != 0 || smell[i][j].first == 0) continue;
            smell[i][j].second--;
            if (smell[i][j].second == 0) smell[i][j].first = 0;
        }
    }
}

bool check_end() {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] != 0) cnt++;
        }
    }
    if (cnt == 1) return true;
    return false;
}

bool can_move(int row, int col) {
    return row >= 0 && row < n && col >= 0 && col < n;
}

void bfs() {
    int current_grid[21][21];
    pair<int, int> current_smell[21][21];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            current_grid[i][j] = grid[i][j];
            current_smell[i][j] = { smell[i][j].first, smell[i][j].second };
        }
    }

    // 1번 상어부터 m번 상어까지 이동
    for (int i = 1; i <= m; ++i) {
        if (is_out[i]) continue;

        // cout << i << "번 상어 이동\n";
        int current_direction = direction[i];
        int* current_priority = priority[i][current_direction];
        int current_row = position[i].first;
        int current_col = position[i].second;

        // 우선순위 기준으로 인접한 위치를 확인하여 이동
        bool flag = false;
        for (int j = 0; j < 4; ++j) {
            int next_direction = current_priority[j];
            int dc = 0, dr = 0;
            
            switch (next_direction) {
                case UP:
                    dr = -1;
                    break;
                case DOWN:
                    dr = 1;
                    break;
                case LEFT:
                    dc = -1;
                    break;
                case RIGHT:
                    dc = 1;
                    break;
                default:
                    break;
            }

            int next_row = current_row + dr;
            int next_col = current_col + dc;

            if (!can_move(next_row, next_col)) continue;
            
            // 1. 냄새가 없는 칸
            if (smell[next_row][next_col].first == 0) {
                // 상어의 방향을 이동한 방향으로 변경
                direction[i] = next_direction;
                flag = true;
                // 숫자가 더 낮은 상어가 먼저 찜한 경우 잡아 먹힌다.
                if (current_smell[next_row][next_col].first != 0 && current_smell[next_row][next_col].first < i) {
                    current_grid[current_row][current_col] = 0;
                    is_out[i] = true;
                    break;
                }
                current_grid[current_row][current_col] = 0;
                current_grid[next_row][next_col] = i;
                current_smell[next_row][next_col] = {i, k};
                position[i] = {next_row, next_col};
                break;
            }
        }

        // 2. 자신의 냄새가 있는 칸
        if (!flag) {
            for (int j = 0; j < 4; ++j) {
                int next_direction = current_priority[j];
                int dc = 0, dr = 0;
                
                switch (next_direction) {
                    case UP:
                        dr = -1;
                        break;
                    case DOWN:
                        dr = 1;
                        break;
                    case LEFT:
                        dc = -1;
                        break;
                    case RIGHT:
                        dc = 1;
                        break;
                    default:
                        break;
                }

                int next_row = current_row + dr;
                int next_col = current_col + dc;

                if (smell[next_row][next_col].first == i) {
                    // 상어의 방향을 이동한 방향으로 변경
                    direction[i] = next_direction;
                    
                    current_grid[current_row][current_col] = 0;
                    current_grid[next_row][next_col] = i;
                    current_smell[next_row][next_col].second = k;
                    position[i] = {next_row, next_col};

                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = current_grid[i][j];
            smell[i][j] = current_smell[i][j];
        }
    }
}

int main() {
    cin >> n >> m >> k;
    //* 1. 격자 입력
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] != 0) {
                smell[i][j] = {grid[i][j], k};
                position[grid[i][j]] = {i, j};
            }
        }
    }
    //* 2. 각 상어의 방향 입력
    for (int i = 1; i <= m; ++i) {
        cin >> direction[i];
    }
    //* 3. 각 상어의 방향 우선순위 입력
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= 4; ++j) {
            for (int d = 0; d < 4; ++d) {
                cin >> priority[i][j][d];
            }
        }
    }

    // 1000초가 넘을 때까지 반복
    while (seconds <= 1000) {
        bfs();
        // 시간 증가 및 냄새 감소
        seconds++;
        decrease_smell();

        if (check_end()) break;
    }

    if (seconds > 1000) {
        cout << -1 << '\n';
        return 0;
    }

    cout << seconds << '\n';

    return 0;
}
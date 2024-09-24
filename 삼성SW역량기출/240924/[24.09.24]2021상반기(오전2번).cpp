// 문제 링크 - https://www.acmicpc.net/problem/21609
// 시간 - 2시간 10분 소요

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define BLACK -1
#define RAINBOW 0
#define EMPTY -100

using namespace std;

struct group_info {
    int size; // 블록 그룹 크기
    int rainbow_cnt; // 무지개 블록 수
    int row; // 기준 블록 행
    int col; // 기준 블록 열
};

vector<group_info> coord;

int score;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int n, m;
int grid[20][20];
bool visited[20][20];

void print_coord() {
    cout << "==== coord ==== \n";
    for (group_info info : coord) {
        cout << "row: " << info.row << ", col: " << info.col << ", size: " << info.size << '\n';
    }
}

void print_grid() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == EMPTY) cout << "   ";
             else cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
}

bool compare(group_info a, group_info b) {
    if (a.size != b.size) return a.size > b.size;
    if (a.rainbow_cnt != b.rainbow_cnt) return a.rainbow_cnt > b.rainbow_cnt;
    if (a.row != b.row) return a.row > b.row;
    return a.col > b.col;
}

bool compare_pos(pair<int, int> a, pair<int, int> b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second < b.second;
}

void rotate() {
    int tmp[20][20];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            tmp[(n-1)-j][i] = grid[i][j];
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = tmp[i][j];
        }
    }
}

bool is_valid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

//? row, col 위치부터 탐색해서 해당 row, col이 속한 그룹의 정보를 가져오는 함수
group_info extract_info(int row, int col) {
    group_info result = {0, 0, 0, 0};

    vector<pair<int, int>> coord_pos;
    vector<pair<int, int>> rainbow_pos;
    queue<pair<int, int>> q;

    coord_pos.push_back({row, col});
    q.push({row, col});
    visited[row][col] = true;
    int color = grid[row][col];

    //* 1. size, rainbow_cnt 값 결정
    while (!q.empty()) {
        pair<int, int> pos = q.front();
        int row = pos.first, col = pos.second;
        q.pop();

        result.size++;
        if (grid[row][col] == RAINBOW) {
            result.rainbow_cnt++;
        }

        for (int i = 0; i < 4; ++i) {
            int next_row = row + dr[i];
            int next_col = col + dc[i];
            if (is_valid(next_row, next_col) && !visited[next_row][next_col] && (grid[next_row][next_col] == RAINBOW || grid[next_row][next_col] == color)) {
                visited[next_row][next_col] = true;
                if (grid[next_row][next_col] == RAINBOW) {
                    rainbow_pos.push_back({next_row, next_col});
                } else {
                    coord_pos.push_back({next_row, next_col});
                }
                q.push({next_row, next_col});
            }
        }
    }
    
    //* 2. row, col 값 결정
    sort(coord_pos.begin(), coord_pos.end(), compare_pos);
    pair<int, int> pos = coord_pos[0];
    result.row = pos.first; result.col = pos.second;

    for (pair<int, int> rainbow : rainbow_pos) {
        visited[rainbow.first][rainbow.second] = false;
    }

    return result;
}

group_info find_priority_group() {
    sort(coord.begin(), coord.end(), compare);
    return coord[0];
}

void remove_group(group_info info) {
    queue<pair<int, int>> q;
    q.push({info.row, info.col});
    int color = grid[info.row][info.col];
   
    while (!q.empty()) {
        int row = q.front().first, col = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int next_row = row + dr[i], next_col = col + dc[i];
            if (is_valid(next_row, next_col) && (grid[next_row][next_col] == RAINBOW || grid[next_row][next_col] == color)) {
                grid[next_row][next_col] = EMPTY;
                q.push({next_row, next_col});
            }
        }
    }
    score += info.size * info.size;
}

//? 블록 그룹이 존재하는지
void update_coord() {
    coord.clear();
    //* init (visited 배열 초기화)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            visited[i][j] = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!visited[i][j] && grid[i][j] > 0) {
                group_info info = extract_info(i, j);
                if (info.size >= 2) coord.push_back(info);
            }
        }
    }
}

void gravity() {
    for (int col = 0; col < n; ++col) {
        int accum = 0;
        for (int row = n-1; row >= 0; --row) {
            switch (grid[row][col]) {
                case BLACK:
                    accum = 0;
                    break;
                case EMPTY:
                    accum++;
                    break;
                default:
                    if (accum > 0) {
                        grid[row+accum][col] = grid[row][col];
                        grid[row][col] = EMPTY;
                    }
                    break;
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    update_coord();
    while (coord.size() > 0) {
        //* 1. 블록그룹 찾기
        group_info info = find_priority_group();

        //* 2. 1의 그룹의 블록 제거
        remove_group(info);
        // cout << "=== 삭제 후 그리드 상태\n";
        // print_grid();

        //* 3. 중력
        gravity();
        // cout << "=== 중력 후 그리드 상태\n";
        // print_grid();

        //* 4. 회전
        rotate();
        // cout << "=== 회전 후 그리드 상태\n";
        // print_grid();

        //* 5. 중력
        gravity();
        // cout << "=== 중력 후 그리드 상태\n";
        // print_grid();

        update_coord();
    }

    cout << score << '\n';

    return 0;
}
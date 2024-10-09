#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

#define SIZE 5
#define DEGREE_90 0
#define DEGREE_180 1
#define DEGREE_270 2

using namespace std;

int k, m;
int grid[SIZE][SIZE];
int tmp[SIZE][SIZE];
queue<int> wall;
bool visited[SIZE][SIZE];
int copy_board[3][3];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

struct same_pos_node {
    int cnt; // 얻을 수 있는 조각 수
    int degree; // 회전 각도
};

struct node {
    int cnt;
    int degree;
    int row;
    int col;
};

void print_grid() {
    cout << "=== grid ===\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "=======\n";
}

void print_tmp() {
    cout << "=== tmp ===\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << tmp[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "=======\n";
}

bool compare_same_pos(same_pos_node a, same_pos_node b) {
    if (a.cnt != b.cnt) return a.cnt > b.cnt;
    return a.degree < b.degree;
}

bool compare_node(node a, node b) {
    if (a.cnt != b.cnt) return a.cnt > b.cnt;
    if (a.degree != b.degree) return a.degree < b.degree;
    if (a.col != b.col) return a.col < b.col;
    return a.row < b.row;
}

void init_visited() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            visited[i][j] = false;
        }
    }
}

bool is_valid_pos(int row, int col) {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

void copy_grid_to_tmp() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            tmp[i][j] = grid[i][j];
        }
    }
}

void set_copy_board(int start_row, int end_row, int start_col, int end_col, int degree) {
    int copy_tmp[3][3];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            copy_tmp[i][j] = grid[start_row+i][start_col+j];
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (degree == DEGREE_90) {
                copy_board[j][2-i] = copy_tmp[i][j];
            }
            else if (degree == DEGREE_180) {
                copy_board[2-i][2-j] = copy_tmp[i][j];
            }
            else if (degree == DEGREE_270) {
                copy_board[2-j][i] = copy_tmp[i][j];
            }
        }
    }
}

// tmp 배열에서 row, col을 기준으로 3X3을 degree 각도만큼 회전
void rotate_tmp(int row, int col, int degree) {
    copy_grid_to_tmp();
    int start_row = row - 1, end_row = row + 1;
    int start_col = col - 1, end_col = col + 1;
    set_copy_board(start_row, end_row, start_col, end_col, degree);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            tmp[start_row+i][start_col+j] = copy_board[i][j];
        }
    }
}

int get_tmp_linked_pieces(int row, int col) {
    int cnt = 1;
    queue<pair<int, int>> q;
    int target = tmp[row][col];

    q.push({row, col});
    visited[row][col] = true;

    while (!q.empty()) {
        int r = q.front().first, c = q.front().second;
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int next_r = r + dr[i], next_c = c + dc[i];
            if (is_valid_pos(next_r, next_c) && !visited[next_r][next_c] && tmp[next_r][next_c] == target) {
                cnt++;
                visited[next_r][next_c] = true;
                q.push({next_r, next_c});
            }
        }
    }
    return cnt;
}

int get_tmp_pieces() {
    init_visited();
    int result = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (!visited[i][j]) {
                int linked_cnt = get_tmp_linked_pieces(i, j);
                if (linked_cnt >= 3) {
                    result += linked_cnt;
                }
            }
        }
    }
    return result;
}

// 회전 정보로 grid 배열을 회전시키는 함수
void rotate_grid(node info) {
    int start_row = info.row - 1, end_row = info.row + 1;
    int start_col = info.col - 1, end_col = info.col + 1;
    int degree = info.degree;
    
    set_copy_board(start_row, end_row, start_col, end_col, degree);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            grid[start_row+i][start_col+j] = copy_board[i][j];
        }
    }
}

void investing() {
    int start_row = 1, end_row = SIZE-2;
    int start_col = 1, end_col = SIZE-2;

    vector<node> coord;
    for (int i = start_row; i <= end_row; ++i) {
        for (int j = start_col; j <= end_col; ++j) {
            vector<same_pos_node> tmp_coord;
            rotate_tmp(i, j, DEGREE_90);
            int cnt = get_tmp_pieces();
            // cout << "{ " << i+1 << ", " << j+1 << " } 기준으로 90도 회전할 때 cnt: " << cnt << '\n';
            tmp_coord.push_back({cnt, DEGREE_90});

            rotate_tmp(i, j, DEGREE_180);
            cnt = get_tmp_pieces();
            // cout << "{ " << i+1 << ", " << j+1 << " } 기준으로 180도 회전할 때 cnt: " << cnt << '\n';
            tmp_coord.push_back({cnt, DEGREE_180});

            rotate_tmp(i, j, DEGREE_270);
            cnt = get_tmp_pieces();
            // cout << "{ " << i+1 << ", " << j+1 << " } 기준으로 270도 회전할 때 cnt: " << cnt << '\n';
            tmp_coord.push_back({cnt, DEGREE_270});

            sort(tmp_coord.begin(), tmp_coord.end(), compare_same_pos);

            // i, j 위치에서 가장 우선순위 높은 것 넣기
            auto node = tmp_coord[0];
            coord.push_back({node.cnt, node.degree, i, j});
        }
    }
    sort(coord.begin(), coord.end(), compare_node);
    auto rotate_info = coord[0];

    rotate_grid(rotate_info);
}

// vector<pair<int, int>> get_linked_pos() {
//     vector<pair<int, int>> result;
//     init_visited();
//     for (int i = 0; i < SIZE; ++i) {
//         for (int j = 0; j < SIZE; ++j) {
//             if (!visited[i][j]) {
//                 vector<pair<int, int>> pos;

//                 queue<pair<int, int>> q;
//                 q.push({i, j});
//                 visited[i][j] = true;
//                 pos.push_back({i, j});

//                 while (!q.empty()) {
//                     int row = q.front().first, col = q.front().second;
//                     q.pop();

//                     for (int d = 0; d < 4; ++d) {
//                         int next_row = row + dr[d], next_col = col + dc[d];
//                         if (is_valid_pos(next_row, next_col) 
//                         && !visited[next_row][next_col] 
//                         && grid[next_row][next_col] == grid[row][col]) {
//                             visited[next_row][next_col] = true;
//                             q.push({next_row, next_col});
//                             pos.push_back({next_row, next_col});
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

// 연결된 유물 존재 여부
bool is_exist_linked() {
    init_visited();
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (!visited[i][j]) {
                int cnt = 1;

                queue<pair<int, int>> q;
                q.push({i, j});
                visited[i][j] = true;

                while (!q.empty()) {
                    int row = q.front().first, col = q.front().second;
                    q.pop();

                    for (int d = 0; d < 4; ++d) {
                        int next_row = row + dr[d], next_col = col + dc[d];
                        if (is_valid_pos(next_row, next_col) 
                        && !visited[next_row][next_col] 
                        && grid[next_row][next_col] == grid[row][col]) {
                            visited[next_row][next_col] = true;
                            q.push({next_row, next_col});
                            cnt++;
                        }
                    }
                }

                if (cnt >= 3) {
                    return true;
                }
            }
        }
    }

    return false;
}

int get_pieces() {
    int sum = 0;

    init_visited();
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (!visited[i][j]) {
                vector<pair<int, int>> pos;

                queue<pair<int, int>> q;
                q.push({i, j});
                visited[i][j] = true;
                pos.push_back({i, j});

                while (!q.empty()) {
                    int row = q.front().first, col = q.front().second;
                    q.pop();

                    for (int d = 0; d < 4; ++d) {
                        int next_row = row + dr[d], next_col = col + dc[d];
                        if (is_valid_pos(next_row, next_col) 
                        && !visited[next_row][next_col] 
                        && grid[next_row][next_col] == grid[row][col]) {
                            visited[next_row][next_col] = true;
                            q.push({next_row, next_col});
                            pos.push_back({next_row, next_col});
                        }
                    }
                }

                if (pos.size() >= 3) {
                    for (pair<int, int> p : pos) {
                        grid[p.first][p.second] = 0;
                    }
                    sum += pos.size();
                }
            }
        }
    }
    return sum;
}

void fill_empty_grid() {
    for (int c = 0; c < SIZE; ++c) {
        for (int r = SIZE-1; r >= 0; --r) {
            if (grid[r][c] == 0) {
                grid[r][c] = wall.front();
                wall.pop();
            }
        }
    }
}

int main() {
    cin >> k >> m;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cin >> grid[i][j];
        }
    }

    for (int i = 0; i < m; ++i) {
        int n;
        cin >> n;
        wall.push(n);
    }

    while (k--) {
        int ans = 0; // 유물 조각 수

        //* 1. 우선순위 기준으로 격자 일부 회전
        investing();
        // cout << "=== 격자 회전 완료 후 ===\n";
        // print_grid();
        // cout << "================\n";

        //* 2. 획득할 유물 없을 때까지 유물 획득
        while (is_exist_linked()) {
            //* 2-1. 유물 수집 및 삭제
            ans += get_pieces();

            // cout << "=== 3개 이상 연속한 유물을 모두 삭제한 후 ===\n";
            // print_grid();
            // cout << "=======================\n";

            //* 2-2. 빈 공간 채우기
            fill_empty_grid();

            // cout << "=== 빈 공간을 채운 후 ===\n";
            // print_grid();
            // cout << "======================\n";
        }

        if (ans == 0) break;
        cout << ans << ' ';
    }
    cout << '\n';

    return 0;
}
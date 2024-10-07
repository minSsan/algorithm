#include <iostream>
#include <deque>
#include <vector>
#include <queue>
#include <algorithm>

#define EMPTY -1

using namespace std;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int n, k;

int r, c; //? 쌓인 어항의 row, col 값
int cnt; //? 어항 정리 횟수
long long max_cnt, min_cnt;

deque<int> line;
vector<vector<int>> stacked;

void print_grid() {
    cout << "==== 쌓여있는 어항 ====\n";
    for (int i = 0; i < stacked.size(); ++i) {
        for (int j = 0; j < stacked[0].size(); ++j) {
            cout << stacked[i][j] << ' ';
        }
        cout << '\n';
    }
}

void print_line() {
    cout << "==== 바닥에 있는 어항 ====\n";
    for (int i = 0; i < line.size(); ++i) {
        cout << line[i] << ' ';
    }
    cout << '\n';
}

//? 어항에서 물고기 수가 가장 적은 어항의 인덱스 배열 반환
vector<int> get_min_index() {
    vector<int> coord;
    int _min = line.front();
    coord.push_back(0);
    for (int i = 1; i < line.size(); ++i) {
        if (line[i] == _min) {
            coord.push_back(i);
            continue;
        }
        if (line[i] < _min) {
            _min = line[i];
            coord.clear();
            coord.push_back(i);
        }
    }
    return coord;
}

vector<vector<int>> rotate_bowl(vector<vector<int>> grid) {
    r = grid[0].size(); c = grid.size();
    vector<vector<int>> result(r);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            result[i].push_back(0);
        }
    }

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            result[j][(grid.size()-1)-i] = grid[i][j];
        }
    }
    
    return result;
}

//? 어항 쌓기
void stack_bowl() {
    r = 2; c = 1;

    vector<vector<int>> grid(r);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            grid[i].push_back(0);
        }
    }

    grid[0][0] = line.front(); // 가장 왼쪽에 있는 어항을 먼저 쌓는다.
    line.pop_front();
    grid[1][0] = line.front();
    line.pop_front();

    while (r <= line.size()) {
        grid = rotate_bowl(grid);
        vector<int> new_bowl; // r+1번째 행에 새로운 어항 추가
        for (int i = 0; i < c; ++i) {
            new_bowl.push_back(line.front());
            line.pop_front();
        }
        grid.push_back(new_bowl);
        r++;
    }

    stacked = grid;
}

//? 어항 배열의 왼쪽 절반을 180도 회전
vector<vector<int>> rotate_bowl_180(vector<vector<int>> grid) {
    int new_r = grid.size(), new_c = grid[0].size() / 2;
    vector<vector<int>> result(new_r);
    for (int i = 0; i < new_r; ++i) {
        for (int j = 0; j < new_c; ++j) {
            result[i].push_back(0);
        }
    }

    // cout << "===180도 회전 후===\n";
    for (int i = 0; i < new_r; ++i) {
        for (int j = 0; j < new_c; ++j) {
            result[i][j] = grid[new_r - 1 - i][new_c - 1 - j];
            // cout << result[i][j] << ' ';
        }
        // cout << '\n';
    }

    return result;
}

void stack_bowl_180() {
    vector<vector<int>> grid(1);
    for (int i = 0; i < line.size(); ++i) {
        grid[0].push_back(line[i]);
    }
    line.clear();

    for (int i = 0; i < 2; ++i) {
        vector<vector<int>> half_grid = rotate_bowl_180(grid);
        // cout << "===아래에 붙일 어항===\n";
        for (int row = 0; row < grid.size(); ++row) {
            vector<int> new_bowl;
            for (int col = grid[0].size() / 2; col < grid[0].size(); ++col) {
                new_bowl.push_back(grid[row][col]);
                // cout << grid[row][col] << ' ';
            }
            // cout << '\n';
            half_grid.push_back(new_bowl);
        }
        grid = half_grid;
    }

    stacked = grid;
}

//? 쌓인 어항과 바닥에 나열된 어항을 합치기
vector<vector<int>> merge_bowl_line() {
    int m = stacked[0].size();
    int merge_row = stacked.size();
    int merge_col = m + line.size();
    // init
    vector<vector<int>> result(merge_row);
    for (int i = 0; i < merge_row; ++i) {
        for (int j = 0; j < merge_col; ++j) {
            result[i].push_back(EMPTY);
        }
    }

    // 채우기
    for (int i = 0; i < merge_row; ++i) {
        for (int j = 0; j < stacked[0].size(); ++j) {
            result[i][j] = stacked[i][j];
        }
    }

    for (int i = 0; i < line.size(); ++i) {
        result[merge_row-1][m + i] = line[i];
    }
    line.clear();
    return result;
}

//? 물고기 수 조절 (bfs)
vector<vector<int>> manage_fish_cnt() {
    vector<vector<int>> arr = merge_bowl_line();

    int arr_r = arr.size(), arr_c = arr[0].size();
    int diff[arr_r][arr_c];
    bool visited[arr_r][arr_c];
    for (int i = 0; i < arr_r; ++i) {
        for (int j = 0; j < arr_c; ++j) {
            visited[i][j] = 0;
            diff[i][j] = 0;
        }
    }

    queue<pair<int, int>> q;
    q.push({0, 0});
    // visited[0][0] = true;

    while (!q.empty()) {
        int row = q.front().first, col = q.front().second;
        int cur_fish = arr[row][col];
        q.pop();
        if (visited[row][col]) continue;
        visited[row][col] = true;

        for (int i = 0; i < 4; ++i) {
            int next_row = row + dr[i];
            int next_col = col + dc[i];

            if (!(next_row >= 0 && next_row < arr_r && next_col >= 0 && next_col < arr_c) 
                    || visited[next_row][next_col] 
                    || arr[next_row][next_col] == EMPTY) continue;

            int next_fish = arr[next_row][next_col];
            int diff_fish = abs(cur_fish - next_fish) / 5;
            if (diff_fish > 0) {
                // cout << "\n{ " << next_row << ", " << next_col << " } <-> { " << row << ", " << col << " } : " << diff_fish << '\n';
                if (next_fish > cur_fish) {
                    diff[next_row][next_col] -= diff_fish;
                    diff[row][col] += diff_fish;
                } else {
                    diff[next_row][next_col] += diff_fish;
                    diff[row][col] -= diff_fish;
                }
            }

            // visited[next_row][next_col] = true;
            q.push({next_row, next_col});
        }
    }

    // cout << "===물고기 수 조절 후===\n";
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = 0; j < arr[0].size(); ++j) {
            arr[i][j] += diff[i][j];
            // cout << arr[i][j] << ' ';
        }
        // cout << '\n';
    }
    
    return arr;
}

void set_line(vector<vector<int>> v) {
    int arr_r = v.size(), arr_c = v[0].size();
    for (int c = 0; c < arr_c; ++c) {
        for (int r = arr_r-1; r >= 0; --r) {
            if (v[r][c] != EMPTY) line.push_back(v[r][c]);
        }
    }
    stacked.clear();
}

//? {max, min} 값을 갱신하는 함수
void set_max_min() {
    max_cnt = 0; min_cnt = 123456789;
    for (int i = 0; i < line.size(); ++i) {
        if (line[i] > max_cnt) max_cnt = line[i];
        if (line[i] < min_cnt) min_cnt = line[i];
    }
}

int main() {
    cin >> n >> k;
    max_cnt = 0; min_cnt = 1000000;
    for (int i = 0; i < n; ++i) {
        int input_num;
        cin >> input_num;
        line.push_back(input_num);
        if (input_num > max_cnt) max_cnt = input_num;
        if (input_num < min_cnt) min_cnt = input_num;
    }

    // cout << "max: " << max_cnt << ", min: " << min_cnt << '\n';
    
    while (max_cnt - min_cnt > k) {
        //* 1. 물고기 수가 가장 적은 어항에 물고기 +1씩
        vector<int> coord_idx = get_min_index();
        for (int i : coord_idx) {
            // cout << "최소 인덱스: " << i << '\n';
            line[i]++;
        }

        // cout << "[시작 상태]\n";
        // print_grid();
        // print_line();

        //* 2. 어항 쌓기 (90도 회전)
        stack_bowl();
        // cout << "[1. 어항 쌓기(90도) 완료 후]\n";
        // print_grid();
        // print_line();

        //* 3. 물고기 수 조절 (!동시 발생)
        vector<vector<int>> two_dimension = manage_fish_cnt();

        //* 4. 어항 일렬 정리
        set_line(two_dimension);
        // cout << "[3. 어항 일렬 정리 완료 후]\n";
        // print_grid();
        // print_line();

        //* 5. 어항 쌓기 (180도 회전) 2회
        stack_bowl_180();
        // cout << "[4. 어항 쌓기(180도) 완료 후]\n";
        // print_grid();
        // print_line();

        //* 6. 물고기 수 조절 (!동시 발생)
        two_dimension = manage_fish_cnt();

        //* 7. 어항 일렬 정리
        set_line(two_dimension);
        // cout << "[5. 어항 일렬정리 완료 후]\n";
        // print_grid();
        // print_line();
        
        cnt++;
        set_max_min();
    }

    cout << cnt << '\n';

    return 0;
}
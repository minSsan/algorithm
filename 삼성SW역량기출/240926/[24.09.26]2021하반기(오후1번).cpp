// 문제 링크 - https://www.acmicpc.net/problem/23290
// 시간 - 2시간 50분 소요 (!힌트 보고 문제 해결)

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int m, s; // m: 물고기 수, s: 연습 횟수
queue<int> grid[4][4]; // {i, j}에 있는 물고기의 방향들을 저장
queue<int> temp[4][4]; // 복제를 위한 임시 배열
queue<int> move_result[4][4]; // 물고기 옮기기 위한 임시 배열
pair<int, int> shark_pos;

int dr_fish[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int dc_fish[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};

// 상: 1, 좌: 2, 하: 3, 우: 4
int dr_shark[5] = {0, -1, 0, 1, 0};
int dc_shark[5] = {0, 0, -1, 0, 1};

int smell[4][4]; // {i, j}에 남은 냄새 강도

struct navigate_info { // 백트래킹에서 사용할 구조체
    int fish_cnt;
    vector<int> directions; // 이동 방향 순서 (d값 배열)
};

void print_shark_pos() {
    cout << "== 상어 위치 { " << shark_pos.first << ", " << shark_pos.second << " } ==\n";
}

void print_grid() {
    cout << "== grid 물고기 수 ==\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << grid[i][j].size() << ' ';
        }
        cout << '\n';
    }
}

void print_smell() {
    cout << "== 냄새 강도 ==\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << smell[i][j] << ' ';
        }
        cout << '\n';
    }
}

// 상어의 이동방향 결정
bool compare(navigate_info a, navigate_info b) {
    if (a.fish_cnt != b.fish_cnt) return a.fish_cnt > b.fish_cnt;
    
    int a_num = 0, b_num = 0;
    int index = 0;
    for (int i = 100; i >= 1; i /= 10) {
        a_num += a.directions[index] * i;
        b_num += b.directions[index] * i;
        index++;
    }
    return a_num < b_num;
}

void copy_to_temp() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            temp[i][j] = grid[i][j];
        }
    }
}

int max(int a, int b) {
    if (a < b) return b;
    return a;
}

bool is_valid(int r, int c) {
    return r >= 0 && r < 4 && c >= 0 && c < 4;
}

bool is_shark_pos(int r, int c) {
    return r == shark_pos.first && c == shark_pos.second;
}

bool is_smelled_pos(int r, int c) {
    return smell[r][c] > 0;
}

// {r, c}에 있는 물고기를 이동시키기
void move_fish(int r, int c) {
    int cnt = grid[r][c].size();
    while (cnt--) {
        bool flag = false;
        int d = grid[r][c].front();
        grid[r][c].pop();
        
        //? 이동 위치 탐색
        for (int i = 0; i < 8; ++i) {
            int next_r = r + dr_fish[d], next_c = c + dc_fish[d];
            if (is_valid(next_r, next_c) && !is_shark_pos(next_r, next_c) && !is_smelled_pos(next_r, next_c)) {
                move_result[next_r][next_c].push(d);
                flag = true;
                break;
            }
            d = (d-1) == 0 ? 8 : d-1;
        }

        //? 이동할 위치 못 찾았을 경우 -> 그대로 다시 push
        if (!flag) {
            grid[r][c].push(d);
            move_result[r][c].push(d);
        }
    }
    
}

void move_all_fish() {
    //? move_result 배열 초기화
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            while (!move_result[i][j].empty()) {
                move_result[i][j].pop();
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            move_fish(i, j);
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            grid[i][j] = move_result[i][j];
        }
    }
}

int mark[4][4];
vector<navigate_info> coord;

void backtracking(int row, int col, navigate_info info) {
    if (info.directions.size() == 3) {
        coord.push_back(info);
        return;
    }

    for (int i = 1; i < 5; ++i) {
        int next_row = row + dr_shark[i], next_col = col + dc_shark[i];
        if (is_valid(next_row, next_col)) {
            info.directions.push_back(i);
            if (mark[next_row][next_col] == 0) {
                info.fish_cnt += grid[next_row][next_col].size();
            }
            mark[next_row][next_col]++;
            backtracking(next_row, next_col, info);
            info.directions.pop_back();
            mark[next_row][next_col]--;
            if (mark[next_row][next_col] == 0) {
                info.fish_cnt -= grid[next_row][next_col].size();
            }
        }
    }
}

//? 상어가 이동할 방향 순서를 배열로 리턴하는 함수
vector<int> find_shark_direction() {
    coord.clear();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            mark[i][j] = 0;
        }
    }

    backtracking(shark_pos.first, shark_pos.second, {0, {}});

    sort(coord.begin(), coord.end(), compare);
    return coord[0].directions;
}

void decrease_smell() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            smell[i][j] = max(smell[i][j]-1, 0);
        }
    }
}

void move_shark(vector<int> dirs) {
    int r = shark_pos.first, c = shark_pos.second;
    for (int d : dirs) {
        r = r + dr_shark[d], c = c + dc_shark[d];
        if (grid[r][c].size() > 0) {
            while (!grid[r][c].empty()) {
                grid[r][c].pop();
            }
            smell[r][c] = 2;
        }
    }
    shark_pos.first = r; shark_pos.second = c;
}

void copy_to_grid() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            while (!temp[i][j].empty()) {
                grid[i][j].push(temp[i][j].front());
                temp[i][j].pop();
            }
        }
    }
}

int get_fish_cnt() {
    int result = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result += grid[i][j].size();
        }
    }
    return result;
}

int main() {
    cin >> m >> s;
    for (int i = 0; i < m; ++i) {
        int r, c, d;
        cin >> r >> c >> d;
        grid[r-1][c-1].push(d);
    }
    cin >> shark_pos.first >> shark_pos.second;
    shark_pos.first--; shark_pos.second--;

    int count = 1;

    while (s--) {
        // cout << "\n[ " << count++ << " 번째 ]\n";

        //* 1. 복제 마법 시전 (temp 배열에 현재 물고기 정보 복사)
        copy_to_temp();
        // cout << "< 처음 상태 >\n";
        // print_grid();
        // cout << "====================\n";

        //* 2. 모든 물고기 한 칸씩 이동 (이동할 수 없으면 그대로)
        move_all_fish();
        // cout << "< 물고기 한 칸씩 이동 후 >\n";
        // print_grid();
        // cout << "====================\n";

        //* 3. 상어 이동방향 결정
        vector<int> move_dir = find_shark_direction();

        //* 4. 기존 냄새를 모두 -1씩
        decrease_smell();
        // cout << "< 냄새 감소 후 >\n";
        // print_smell();
        // cout << "====================\n";

        //* 5. 상어를 3의 이동방향으로 이동시키면서, 거친 경로의 냄새를 2로 설정
        move_shark(move_dir);
        // cout << "< 상어 이동 후 >\n";
        // print_grid();
        // print_smell();
        // print_shark_pos();
        // cout << "====================\n";

        //* 6. 복제 마법 완료 (temp 배열 값을 원본 배열에 복사)
        copy_to_grid();
        // cout << "< 복제 마법 적용 후 >\n";
        // print_grid();
        // print_smell();
        // cout << "====================\n";
    }

    cout << get_fish_cnt() << '\n';

    return 0;
}
#include <iostream>
#include <list>

using namespace std;

int n, m;
int shark_r, shark_c;

int grid[50][50];
list<int> beads; // 구슬 번호 저장
int bombs[4]; // bombs[i]: i번 구슬이 폭발한 횟수

int dr[5] = {0, -1, 1, 0, 0};
int dc[5] = {0, 0, 0, -1, 1};

int dr_grid[4] = {0, 1, 0, -1};
int dc_grid[4] = {-1, 0, 1, 0};

void print_grid() {
    cout << "[ grid ]\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
}

void print_beads() {
    cout << "[ beads ]\n";
    list<int>::iterator iter = beads.begin();
    while (iter != beads.end()) {
        cout << *iter << ' ';
        ++iter;
    }
    cout << '\n';
}

void resize_beads() {
    int empty_cnt = n * n - beads.size();

    if (empty_cnt > 0) {
        while (empty_cnt--) {
            beads.push_back(0);
        }
    } else {
        int cnt = abs(empty_cnt);
        while (cnt--) {
            beads.pop_back();
        }
    }
}

//* grid 배열로 beads 리스트 업데이트
void update_beads() {
    int limit = 2;
    int d = 0; // 좌측 방향부터 시작
    int current_r = shark_r, current_c = shark_c;

    beads.clear();

    for (int i = 1; i < n; ++i) {
        if (i == n-1) limit = 3;
        for (int j = 0; j < limit; ++j) {
            for (int k = 0; k < i; ++k) {
                current_r += dr_grid[d]; current_c += dc_grid[d];
                if (grid[current_r][current_c] != 0) {
                    beads.push_back(grid[current_r][current_c]);
                }
            }
            d = (d+1) % 4;
        }
    }

    resize_beads();
}

bool is_valid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

//* beads 리스트로 grid 배열 업데이트
void update_grid() {
    int limit = 2;
    int d = 0; // 좌측 방향부터 시작
    int current_r = shark_r, current_c = shark_c;
    int index = 0;
    list<int>::iterator iter = beads.begin();

    resize_beads();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = 0;
        }
    }

    for (int i = 1; i < n; ++i) {
        if (i == n-1) limit = 3;
        for (int j = 0; j < limit; ++j) {
            for (int k = 0; k < i; ++k) {
                current_r += dr_grid[d]; current_c += dc_grid[d];
                grid[current_r][current_c] = *iter;
                ++iter;
            }
            d = (d+1) % 4;
        }
    }
}

//? 블리자드 시전하여 구슬 삭제하기
void blizard(int d, int s) {
    for (int i = 1; i <= s; ++i) {
        int next_r = shark_r + dr[d] * i, next_c = shark_c + dc[d] * i;
        if (is_valid(next_r, next_c)) {
            grid[next_r][next_c] = 0;
        }
    }
    update_beads();
    update_grid();
}

void bomb_bead(list<int>::iterator start, int num) {
    int cnt = 0;
    while (*start == num) {
        ++cnt;
        bombs[num]++;
        start = beads.erase(start);
    }
    
    resize_beads();
}

bool is_exist() {
    list<int>::iterator iter;
    int same_num = beads.front();
    int same_cnt = 1;
    for (iter = next(beads.begin()); iter != beads.end(); ++iter) {
        if (*iter == 0) break;

        if (*iter == same_num) {
            same_cnt++;
            if (same_cnt == 4) {
                return true;
            }
        } else {
            same_cnt = 1;
            same_num = *iter;
        }
    }
    return false;
}

//? 4개 이상 연속하는 구슬 삭제하기 (폭발 구슬 수 갱신 필요)
void bomb_beads() {
    while (is_exist()) {
        list<int>::iterator iter = next(beads.begin()), start = beads.begin();
        int num = beads.front();
        int same_cnt = 1;
        while (iter != beads.end()) {
            if (*iter == num) {
                same_cnt++;
                if (same_cnt == 4) {
                    while (*start == num) {
                        bombs[num]++;
                        start = beads.erase(start);
                    }
                    iter = start;
                } else {
                    ++iter;
                    continue;
                }
            }
            same_cnt = 1;
            num = *iter;
            start = iter;
            ++iter;
        }
    }

    update_grid();
    update_beads();
}

//? start부터 구슬 번호가 num인 모든 구슬을 합치기
list<int>::iterator change_bead(list<int>::iterator start, int num) {
    int a = 0;
    while (*start == num) {
        ++a;
        start = beads.erase(start);
    }
    beads.insert(start, a);
    beads.insert(start, num);
    return start;
}

//? 구슬 변화하기
void change_beads() {
    list<int>::iterator start = beads.begin();
    list<int>::iterator cur = next(start);
    int num = beads.front();
    while (cur != beads.end()) {
        if (*cur != num) {
            cur = change_bead(start, num);
            num = *cur;
            start = cur;
        }
        ++cur;
    }

    update_grid();
    update_beads();
}

int get_result() {
    int result = 0;
    for (int i = 1; i <= 3; ++i) {
        result += i * bombs[i];
    }
    return result;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    shark_r = n / 2; shark_c = n / 2;

    update_beads();

    for (int i = 0; i < m; ++i) {
        int d, s;
        cin >> d >> s;

        // cout << "==== " << i+1 << " 번째 블리자드 ====" << '\n';
        //* 1. 블리자드
        blizard(d, s);
        // print_grid();
        // print_beads();
        //* 2. 구슬 폭발 및 구슬 채우기
        // cout << "[ 구슬 폭발 후 ]\n";
        bomb_beads();
        // print_grid();
        // print_beads();
        //* 3. 구슬 변화
        change_beads();

        // cout << "==== " << i+1 << " 번째 블리자드 후 ====" << '\n';
        // print_grid();
        // print_beads();
    }

    cout << get_result() << '\n';
    
    return 0;
}
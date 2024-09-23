#include <iostream>
#include <map>

using namespace std;

pair<int, int> grid_pos[2501]; // beads_map의 i번째 원소가 grid 상에 어느 {row, col} 위치에 있는지
int map_pos[50][50]; // grid[i][j]가 beads_map의 몇 번째 원소로 있는지

int n, m;
int shark_r, shark_c;
int grid[50][50];
map<int, int> beads_map;

int dr[5] = {0, -1, 1, 0, 0};
int dc[5] = {0, 0, 0, -1, 1};

int bombs[4];

void print_map() {
    cout << "[ beads map ]\n";
    for (map<int, int>::iterator iter = beads_map.begin(); iter != beads_map.end(); ++iter) {
        cout << "index: " << iter->first << ", value: " << iter->second << '\n';
    }
    // cout << '\n';
}

void print_grid() {
    cout << "[ beads grid ]\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
}

void init() {
    int grid_dr[4] = {0, 1, 0, -1};
    int grid_dc[4] = {-1, 0, 1, 0};
    int d = 0, limit = 2;
    int map_index = 0;

    int current_r = shark_r; int current_c = shark_c;
    for (int i = 1; i < n; ++i) {
        if (i == n-1) limit = 3;
        for (int j = 0; j < limit; ++j) {
            for (int k = 0; k < i; ++k) {
                current_r += grid_dr[d]; current_c += grid_dc[d];

                grid_pos[map_index] = {current_r, current_c};
                map_pos[current_r][current_c] = map_index;

                beads_map[map_index] = grid[current_r][current_c];
                map_index++;
            }
            d = (d + 1) % 4;
        }
    }

    // cout << "=== init 후 ===\n";
    // print_map();
}

bool is_valid(int row, int col) {
    return row >= 0 && row < n && col >= 0 && col < n;
}

void blizard(int d, int s) {
    for (int i = 1; i <= s; ++i) {
        int row = shark_r + dr[d] * i, col = shark_c + dc[d] * i;
        if (is_valid(row, col)) {
            grid[row][col] = 0;
            int index = map_pos[row][col];
            beads_map[index] = 0;
        }
    }
}

bool can_bomb() {
    map<int, int>::iterator start = beads_map.begin();
    map<int, int>::iterator end = beads_map.begin();
    int current_num = start->second;
    int count = 1;

    while (start != beads_map.end() && end != beads_map.end()) {
        end++;
        if (current_num != 0 && current_num == end->second) {
            count++;
            continue;
        }
        if (count >= 4) {
            break;
        }
        start = end;
        current_num = end->second;
        count = 1;
    }
    return count >= 4;
}

void pull_beads() {
    int bomb_cnt = 0;
    for (int i = 0; i < beads_map.size(); ++i) {
        if (beads_map[i] == 0) {
            bomb_cnt++;
            continue;
        }
        pair<int, int> current_pos = grid_pos[i];
        pair<int, int> new_pos = grid_pos[i-bomb_cnt];

        grid[new_pos.first][new_pos.second] = grid[current_pos.first][current_pos.second];
        beads_map[i-bomb_cnt] = beads_map[i];
        // cout << i << "번째 구슬이 " << i-bomb_cnt << "번째로 옮겨짐\n";
    }

    for (int i = 1; i <= bomb_cnt; ++i) {
        pair<int, int> pos = grid_pos[beads_map.size()-i];
        beads_map[beads_map.size()-i] = 0;
        grid[pos.first][pos.second] = 0;
    }
}

void bomb_beads() {
    map<int, int>::iterator start = beads_map.begin();
    map<int, int>::iterator end = beads_map.begin();
    int current_num = start->second;
    int count = 1;

    while (start != beads_map.end() && end != beads_map.end()) {
        end++;
        if (current_num == end->second) {
            count++;
            continue;
        }
        
        if (count >= 4) {
            for (map<int, int>::iterator iter = start; iter != end; ++iter) {
                bombs[iter->second]++;
                iter->second = 0;
                pair<int, int> pos = grid_pos[iter->first];
                int row = pos.first, col = pos.second;
                grid[row][col] = 0;
            }
        }
        start = end;
        current_num = end->second;
        count = 1;
    }

    if (count >= 4) {
        for (map<int, int>::iterator iter = start; iter != end; ++iter) {
            iter->second = 0;
            pair<int, int> pos = grid_pos[iter->first];
            int row = pos.first, col = pos.second;
            grid[row][col] = 0;
        }
    }
}

void merge_beads() {
    map<int, int> temp_map;
    for (int i = 0; i < beads_map.size(); ++i) {
        temp_map[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = 0;
        }
    }

    map<int, int>::iterator map_iter = beads_map.begin();
    int num = map_iter->second, cnt = 1;
    int temp_index = 0;

    ++map_iter;
    while (num != 0 && map_iter != beads_map.end() && temp_index < beads_map.size()) {
        while (map_iter != beads_map.end() && num == map_iter->second) {
            ++cnt;
            ++map_iter;
        }
        //* A
        pair<int, int> pos = grid_pos[temp_index];
        grid[pos.first][pos.second] = cnt;
        temp_map[temp_index++] = cnt;

        if (temp_index >= beads_map.size()) break;

        //* B
        pos = grid_pos[temp_index];
        grid[pos.first][pos.second] = num;
        temp_map[temp_index++] = num;

        num = map_iter->second;
        map_iter++;
        cnt = 1;
    }

    beads_map = temp_map;
}

int main() {
    cin >> n >> m;
    shark_r = n / 2; shark_c = n / 2;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }
    init();
    for (int i = 0; i < m; ++i) {
        int d, s;
        cin >> d >> s;
        //* 1. 블리자드
        blizard(d, s);
        pull_beads();
        // cout << "=== 블리자드 후 ===\n";
        // print_map();
        // print_grid();
        //* 2. 구슬 폭발
        while (can_bomb()) {
            bomb_beads();
            pull_beads();
        }
        // cout << "=== 폭발 후 ===\n";
        // print_map();
        // print_grid();
        //* 3. 구슬 변화
        merge_beads();
        // cout << "=== 재배치 후 ===\n";
        // print_map();
        // print_grid();
    }

    int result = 0;
    for (int i = 1; i <= 3; ++i) {
        result += i * bombs[i];
    }
    cout << result << '\n';

    return 0;
}
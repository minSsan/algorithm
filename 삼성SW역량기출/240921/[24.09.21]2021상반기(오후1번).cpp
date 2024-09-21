// https://www.acmicpc.net/problem/21610

#include <iostream>
#include <vector>

using namespace std;

int n, m;

int dr[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int dc[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int water[50][50];

vector<pair<int, int>> clouds;

bool is_valid(int row, int col) {
    return row >= 0 && row < n && col >= 0 && col < n;
}

void move_clouds(int d, int s) {
    vector<pair<int, int>> temp;
    for (pair<int, int> pos : clouds) {
        int next_row = pos.first + dr[d] * s; int next_col = pos.second + dc[d] * s;
        while (next_row < 0) {
            next_row += n;
        }
        while (next_col < 0) {
            next_col += n;
        }
        while (next_row > n-1) {
            next_row -= n;
        }
        while (next_col > n-1) {
            next_col -= n;
        }
        temp.push_back({next_row, next_col});
    }
    clouds = temp;
}

void add_water() {
    for (pair<int ,int> pos : clouds) {
        int row = pos.first; int col = pos.second;
        water[row][col]++;
    }
}

void water_copy_bug() {
    for (pair<int, int> pos : clouds) {
        int row = pos.first; int col = pos.second;
        for (int i = 2; i <= 8; i+=2) {
            int next_row = row + dr[i]; int next_col = col + dc[i];
            if (is_valid(next_row, next_col) && water[next_row][next_col] > 0) {
                water[row][col]++;
            }
        }
    }
}

bool not_in_clouds(int r, int c) {
    for (pair<int, int> pos : clouds) {
        if (pos.first == r && pos.second == c) return false;
    }
    return true;
}

void generate_clouds() {
    vector<pair<int, int>> temp;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (water[i][j] >= 2 && not_in_clouds(i, j)) {
                water[i][j] -= 2;
                temp.push_back({i, j});
            }
        }
    }
    clouds = temp;
}

int get_total_water() {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            sum += water[i][j];
        }
    }
    return sum;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> water[i][j];
        }
    }

    clouds.push_back({n-1, 0});
    clouds.push_back({n-1, 1});
    clouds.push_back({n-2, 0});
    clouds.push_back({n-2, 1});

    int d, s;
    while (m--) {
        cin >> d >> s;
        move_clouds(d, s);
        add_water();
        water_copy_bug();
        generate_clouds();
    }

    cout << get_total_water() << '\n';

    return 0;
}
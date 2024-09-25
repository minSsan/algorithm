// 문제 링크 - https://www.acmicpc.net/problem/19238
// 시간 - 2시간 10분 소요

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define EMPTY 0
#define WALL 1

using namespace std;

int n, m;
long long oil;
pair<int, int> taxi_pos;

int road[20][20];
pair<int, int> client_dest[410]; // i번째 승객의 목적지 정보
int dist[20][20]; // 현재 택시 위치를 기준으로, i행 j열까지 이동하는데 필요한 연료(거리)
bool visited[20][20];
int success_cnt;

int dr[5] = {0, -1, 1, 0, 0};
int dc[5] = {0, 0, 0, -1, 1};

struct client_info {
    int num;
    int row;
    int col;
};

bool is_valid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

bool compare(client_info a, client_info b) {
    if (a.row != b.row) return a.row < b.row;
    return a.col < b.col;
}

//* 우선순위가 가장 높은 승객의 번호를 리턴하는 함수
client_info get_client() {
    //* 1. dist배열 & visited 배열 초기화
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            visited[i][j] = false;
            dist[i][j] = 0;
        }
    }

    vector<client_info> coord;
    queue<pair<int, int>> q;

    q.push({taxi_pos.first, taxi_pos.second});

    //* 2. 탐색
    while (!q.empty()) {
        int row = q.front().first, col = q.front().second;

        // cout << "{ " << row << ", " << col << " } 위치 값은 " << road[row][col] << '\n';

        if (road[row][col] >= 2) {
            while (!q.empty() && dist[q.front().first][q.front().second] == dist[row][col]) {
                // cout << "{ " << q.front().first << ", " << q.front().second << " } 거리 = " << dist[q.front().first][q.front().second] << '\n';
                if (road[q.front().first][q.front().second] >= 2) {
                    coord.push_back({road[q.front().first][q.front().second], q.front().first, q.front().second});
                }
                q.pop();
            }
            sort(coord.begin(), coord.end(), compare);
            return coord[0];
        }
        q.pop();

        for (int i = 0; i < 5; ++i) {
            int next_row = row + dr[i], next_col = col + dc[i];
            if (is_valid(next_row, next_col) && !visited[next_row][next_col] && road[next_row][next_col] != WALL) {
                if (i != 0) dist[next_row][next_col] = dist[row][col] + 1;
                visited[next_row][next_col] = true;
                q.push({next_row, next_col});
            }
        }
    }
    return {-1, -1, -1};
}

//* 택시를 승객이 있는 위치로 이동시키기
bool move_client(client_info client) {
    // cout << "승객을 태우는데 필요한 연료: " << dist[client.row][client.col] << '\n';
    if (oil - dist[client.row][client.col] >= 0) {
        oil -= dist[client.row][client.col];
        taxi_pos = {client.row, client.col};
        road[client.row][client.col] = EMPTY;
        return true;
    }
    return false;
}

bool move_dest(int dest_r, int dest_c) {
    // cout << "taxi: " << taxi_pos.first << ", " << taxi_pos.second << '\n';
    // cout << "dest: " << dest_r << ", " << dest_c << '\n';
    //* 1. dist배열 & visited 배열 초기화
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            visited[i][j] = false;
            dist[i][j] = 0;
        }
    }

    queue<pair<int, int>> q;

    q.push({taxi_pos.first, taxi_pos.second});
    visited[taxi_pos.first][taxi_pos.second] = true;

    while (!q.empty()) {
        int row = q.front().first, col = q.front().second;
        q.pop();

        // cout << "row: " << row << ", col: " << col << '\n';

        if (row == dest_r && col == dest_c) {
            if (oil - dist[dest_r][dest_c] >= 0) {
                taxi_pos = {dest_r, dest_c};
                oil += dist[dest_r][dest_c];
                success_cnt++;
                return true;
            }
            return false;
        }

        for (int i = 1; i < 5; ++i) {
            int next_row = row + dr[i], next_col = col + dc[i];
            if (is_valid(next_row, next_col) && !visited[next_row][next_col] && road[next_row][next_col] != WALL) {
                dist[next_row][next_col] = dist[row][col] + 1;
                q.push({next_row, next_col});
                visited[next_row][next_col] = true;
            }
        }
    }

    return false;
}

int main() {
    cin >> n >> m >> oil;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> road[i][j];
        }
    }
    cin >> taxi_pos.first >> taxi_pos.second;
    taxi_pos.first--; taxi_pos.second--;

    int client_num = 2;
    for (int i = 0; i < m; ++i) {
        int start_row, start_col, dest_row, dest_col;
        cin >> start_row >> start_col >> dest_row >> dest_col;
        start_row--; start_col--; dest_row--; dest_col--;
        
        road[start_row][start_col] = client_num;
        client_dest[client_num] = {dest_row, dest_col};
        client_num++;
    }

    while (success_cnt < m) {
        //* 1. 승객 고르기
        client_info client = get_client();
        if (client.num == -1) {
            cout << -1 << '\n';
            return 0;
        }

        // cout << success_cnt + 1 << "번째 승객: " << client.num - 1 << '\n';

        //* 2. 승객을 태우러 가기
        if (!move_client(client)) {
            cout << -1 << '\n';
            return 0;
        }

        // cout << "승객을 태우고 남은 연료: " << oil << '\n';

        //* 3. 선택한 승객을 목적지로 이동시키기
        pair<int, int> dest = client_dest[client.num];
        if (!move_dest(dest.first, dest.second)) {
            cout << -1 << '\n';
            return 0;
        }

        // cout << "승객 태우기 성공, 남은 연료: " << oil << '\n';
    }
    cout << oil << '\n';

    return 0;
}
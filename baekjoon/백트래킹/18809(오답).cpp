#include <iostream>
#include <queue>
#include <vector>

#define LAKE 0
#define X 1
#define O 2

#define FLOWER 3
#define GREEN 4
#define RED 5

using namespace std;

int graph[50][50];
bool visited[50][50]; //* 배양액 방문 여부
pair<int, int> status[50][50]; //* 각 주기의 정원 상태 {상태, 주기}

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int n, m, g, r;
int max_cnt;

void init_visited() {
    fill(visited[0], visited[0] + n * m, false);
}

void reset_status() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            status[i][j] = {-1, -1};
        }
    }
}

bool is_valid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m && graph[r][c] != LAKE;
}

int get_flower_cnt() {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (status[i][j].first == FLOWER) {
                cnt++;
            }
        }
    }
    return cnt;
}

void bfs() {
    init_visited();
    queue<pair<pair<int, int>, int>> q; // {{r, c}, cnt}
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (status[i][j].first == GREEN || status[i][j].first == RED) {
                q.push({{i, j}, 0});
                visited[i][j] = true;
            }
        }
    }

    while (!q.empty()) {
        int row = q.front().first.first, col = q.front().first.second;
        int cnt = q.front().second;
        q.pop();

        if (status[row][col].first == FLOWER) continue;

        for (int i = 0; i < 4; ++i) {
            int next_row = row + dr[i];
            int next_col = col + dc[i];
            int next_cnt = cnt+1;
            if (is_valid(next_row, next_col)) {
                //* 아직 배양액을 뿌리지 않은 위치인 경우
                if (!visited[next_row][next_col]) {
                    status[next_row][next_col] = status[row][col]; // 배양액 뿌리기
                    status[next_row][next_col].second = next_cnt;
                    visited[next_row][next_col] = true;
                    q.push({{next_row, next_col}, next_cnt});
                }
                //* 배양액을 이미 뿌린 경우
                else {
                    //? 서로 다른 배양액이 동일한 주기에 만나는 경우
                    if (status[next_row][next_col].second == next_cnt && status[next_row][next_col].first != status[row][col].first) {
                        status[next_row][next_col].first = FLOWER;
                    }
                }
            }
        }
    }
}

bool dfs_visited[2500];
vector<int> pos;
vector<int> nums;

void dfs() {
    if (nums.size() == g + r) {
        reset_status();
        //TODO: status 배열 채운 뒤 bfs 호출
        for (int i = 0; i < g; ++i) {
            int r = nums[i] / n;
            int c = nums[i] % n;
            status[r][c] = {GREEN, 0};
        }
        for (int i = 0; i < r; ++i) {
            int r = nums[g+i] / n;
            int c = nums[g+i] % n;
            status[r][c] = {RED, 0};
        }

        bfs();

        int cnt = get_flower_cnt();
        if (cnt > max_cnt) {
            max_cnt = cnt;
        }
        return;
    }

    for (int num : pos) {
        if (!dfs_visited[num]) {
            dfs_visited[num] = true;
            nums.push_back(num);
            dfs();
            nums.pop_back();
            dfs_visited[num] = false;
        }
    }
}

int main() {
    cin >> n >> m >> g >> r;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> graph[i][j];
            if (graph[i][j] == O) {
                pos.push_back(i * n + j);
            }
        }
    }
    
    dfs();

    cout << max_cnt << '\n';

    return 0;
}
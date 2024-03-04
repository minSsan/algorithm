#include <iostream>
#include <queue>
#include <math.h>

using namespace std;

//? - 1년마다 빙산의 각 부분에 대해 동-서-남-북 검사 후 빙산의 크기 갱신
//? - 빙산의 크기 갱신 후, 빙산이 몇 덩어리로 나뉘어 있는지 검사
//?     - 만약 빙산이 두 덩어리 이상 분리되면 시간 출력 후 종료
//?     - 만약 빙산이 0개의 덩어리로 된다면(= 다 녹으면) 0을 출력

struct node {
    short row;
    short col;
    int year;
};

short n, m;
int graph[300][300];
bool water[300][300];
queue<node> q;
short dr[4] = {-1, 1, 0, 0};
short dc[4] = {0, 0, -1, 1};

int year;
short current_r, current_c;

/**
 * 입력받은 위치가 물의 영역인지 검사하는 함수
*/
bool is_water(short row, short col) {
    return (0 <= row && row < n) && (0 <= col && col < m) && (water[row][col]);
}

/**
 * 물이 존재하는 영역을 표시하는 함수
*/
void mark_water() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            water[i][j] = graph[i][j] == 0;
        }
    }
}

bool visited[300][300];
short next_r, next_c;
/**
 * 현재 빙산과 연결된 다른 빙산을 모두 방문하는 함수
*/
void dfs(short row, short col) {
    visited[row][col] = true;

    for (int i = 0; i < 4; ++i) {
        next_r = row + dr[i]; next_c = col + dc[i];
        if (0 <= next_r && next_r < n && 0 <= next_c && next_c < m && graph[next_r][next_c] > 0 && !visited[next_r][next_c]) {
            dfs(next_r, next_c);
        }
    }
}

/**
 * 현재 빙산의 덩어리 수를 반환하는 함수
*/
int get_lump() {
    for (short i = 0; i < n; ++i) {
        for (short j = 0; j < m; ++j) {
            visited[i][j] = false;
        }
    }

    int cnt = 0;
    for (short i = 0; i < n; ++i) {
        for (short j = 0; j < m; ++j) {
            if (!visited[i][j] && graph[i][j] > 0) {
                ++cnt;
                dfs(i, j);
            }
        }
    }

    return cnt;
}

int bfs() {
    int lump;
    mark_water();

    while (!q.empty()) {
        if (year != q.front().year) {
            lump = get_lump();
            if (lump == 0) return 0;
            if (lump >= 2) return q.front().year;
            mark_water();
        }

        current_r = q.front().row; current_c = q.front().col; year = q.front().year;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            if (is_water(current_r + dr[i], current_c + dc[i])) {
                graph[current_r][current_c] = max(graph[current_r][current_c] - 1, 0);
            }
        }

        if (graph[current_r][current_c] > 0) q.push({current_r, current_c, year+1});
    }

    return 0;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> m;

    for (short i = 0; i < n; ++i) {
        for (short j = 0; j < m; ++j) {
            cin >> graph[i][j];
            if (graph[i][j] != 0) q.push({i, j, 0});
        }
    }

    cout << bfs() << '\n';

    return 0;
}
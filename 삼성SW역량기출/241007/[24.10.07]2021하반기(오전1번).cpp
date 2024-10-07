#include <iostream>
#include <deque>
#include <queue>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define HORIZON_LEFT 0
#define HORIZON_ABOVE 1
#define HORIZON_RIGHT 2
#define HORIZON_BOTTOM 3

#define VERTICAL_UP 0
#define VERTICAL_ABOVE 1
#define VERTICAL_DOWN 2
#define VERTICAL_BOTTOM 3

using namespace std;

deque<int> horizon(4);
deque<int> vertical(4);

int n, m, k;
int map[20][20];
int score;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

//? 주사위의 현재 위치
pair<int, int> pos;
//? 주사위의 이동 방향
int direction;

void print_direction() {
    switch (direction) {
        case LEFT:
            cout << "이동방향은 왼쪽\n";
            break;
        
        case RIGHT:
            cout << "이동방향은 오른쪽\n";
            break;
        
        case UP:
            cout << "이동방향은 위쪽\n";
            break;
        
        case DOWN:
            cout << "이동방향은 아래쪽\n";
            break;
        
        default:
            break;
    }
}

void print_pos() {
    cout << "위치는 { " << pos.first << ", " << pos.second << " }\n";
}

bool is_valid_pos(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m;
}

void move_dice() {
    if (!is_valid_pos(pos.first + dr[direction], pos.second + dc[direction])) {
        direction = (direction + 2) % 4; // 방향을 반대로
    }

    int next_row = pos.first + dr[direction]; int next_col = pos.second + dc[direction];

    pos = {next_row, next_col};

    //? 좌-우 이동
    if (direction == LEFT) {
        horizon.push_back(horizon.front());
        horizon.pop_front();
    }
    if (direction == RIGHT) {
        horizon.push_front(horizon.back());
        horizon.pop_back();
    }
    //? 상-하 이동
    if (direction == UP) {
        vertical.push_back(vertical.front());
        vertical.pop_front();
    }
    if (direction == DOWN) {
        vertical.push_front(vertical.back());
        vertical.pop_back();
    }

    if (direction == LEFT || direction == RIGHT) {
        vertical[VERTICAL_ABOVE] = horizon[HORIZON_ABOVE];
        vertical[VERTICAL_BOTTOM] = horizon[HORIZON_BOTTOM];
    } else {
        horizon[HORIZON_ABOVE] = vertical[VERTICAL_ABOVE];
        horizon[HORIZON_BOTTOM] = vertical[VERTICAL_BOTTOM];
    }
}

bool visited[20][20];

int get_score() {
    int B = map[pos.first][pos.second];
    int C = 1;

    for (int i = 0; i < n; ++i) {
        fill(visited[i], visited[i]+m, 0);
    }

    queue<pair<int, int>> q;
    q.push(pos);
    visited[pos.first][pos.second] = true;

    while (!q.empty()) {
        int row = q.front().first, col = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int next_row = row + dr[i], next_col = col + dc[i];
            if (is_valid_pos(next_row, next_col) && !visited[next_row][next_col] && map[next_row][next_col] == B) {
                C++;
                q.push({next_row, next_col});
                visited[next_row][next_col] = true;
            }
        }
    }

    return B * C;
}

void change_dir() {
    int A = horizon[HORIZON_BOTTOM];
    int B = map[pos.first][pos.second];
    
    if (A > B) {
        direction = (direction + 1) % 4;
    } else if (A < B) {
        direction = (direction + 3) % 4;
    }
}

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> map[i][j];
        }
    }

    pos = {0, 0};
    direction = RIGHT;

    //? 전개도 초기화
    horizon[HORIZON_LEFT] = 4;
    horizon[HORIZON_ABOVE] = 1;
    horizon[HORIZON_RIGHT] = 3;
    horizon[HORIZON_BOTTOM] = 6;

    vertical[VERTICAL_UP] = 2;
    vertical[VERTICAL_ABOVE] = 1;
    vertical[VERTICAL_DOWN] = 5;
    vertical[VERTICAL_BOTTOM] = 6;

    while (k--) {
        //* 1. 이동 방향으로 한 칸 이동 *이동방향에 칸이 없으면 이동방향을 반대로 설정하여 이동* (전개도 변경)
        move_dice();

        //* 2. 도착 칸의 점수 획득 (bottom 점수 B X 연속해서 이동 가능한 칸의 수 C)
        score += get_score();

        //* 3. 주사위 아랫면, 도착 칸의 정수 값(bottom 값)을 비교하여 이동 방향 변경
        change_dir();
    }

    cout << score << '\n';
    
    return 0;
}
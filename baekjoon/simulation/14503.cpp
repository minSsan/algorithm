#include <iostream>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

using namespace std;

short n, m;
short graph[50][50];
bool clean[50][50];
short current_row, current_col;
short direction;
short cnt;
short dirty;
short dr[4] = {-1, 1, 0, 0};
short dc[4] = {0, 0, -1, 1};
short next_row, next_col;

bool not_clean(short r, short c) {
    return (0 <= r && r < n && 0 <= c && c < m) && (graph[r][c] == 0) && (!clean[r][c]);
}

/**
 * 로봇청소기를 반시계 방향으로 90도 회전시키는 함수
*/
void rotate() {
    direction = ((direction - 1) + 4) % 4;
}

bool move_back() {
    switch (direction) {
        case NORTH:
            if (current_row+1 < n && graph[current_row+1][current_col] == 0) {
                ++current_row;
                return true;
            }
            return false;
        case EAST:
            if (current_col-1 >= 0 && graph[current_row][current_col-1] == 0) {
                --current_col;
                return true;
            }
            return false;
        case SOUTH:
            if (current_row-1 >= 0 && graph[current_row-1][current_col] == 0) {
                --current_row;
                return true;
            }
            return false;
        case WEST:
            if (current_col+1 < m && graph[current_row][current_col+1] == 0) {
                ++current_col;
                return true;
            }
            return false;
        default:
            return false;
    }
}

/**
 * 앞쪽 칸이 청소되지 않은 칸인 경우 전진시키는 함수
*/
void move_front() {
    switch (direction) {
        case NORTH:
            if (not_clean(current_row-1, current_col)) {
                --current_row;
            }
            break;
        case EAST:
            if (not_clean(current_row, current_col+1)) {
                ++current_col;
            }
            break;
        case SOUTH:
            if (not_clean(current_row+1, current_col)) {
                ++current_row;
            }
            break;
        case WEST:
            if (not_clean(current_row, current_col-1)) {
                --current_col;
            }
            break;
        default:
            break;
    }
}

void robot() {
    while (true) {
        if (!clean[current_row][current_col]) {
            clean[current_row][current_col] = true;
            cnt++;
        }
        
        // 청소되지 않은 빈칸 찾기
        for (int i = 0; i < 4; ++i) {
            next_row = current_row + dr[i]; next_col = current_col + dc[i];
            if (not_clean(next_row, next_col)) {
                dirty++;
            }
        }

        // 청소할 수 있는 칸이 없는 경우
        if (dirty == 0) {
            if (!move_back()) { // 후진 가능 검사
                break;
            }
        } 
        // 청소할 수 있는 칸이 있는 경우
        else {
            rotate();
            move_front();
        }
        
        dirty = 0;
    }
    
}

int main() {
    cin >> n >> m;
    cin >> current_row >> current_col >> direction;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> graph[i][j];
        }
    }

    robot();

    cout << cnt << '\n';

    return 0;
}
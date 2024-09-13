// 문제 링크 - https://www.acmicpc.net/problem/20061
// 재시도 성공

#include <iostream>
#include <set>

#define BLUE 0
#define GREEN 1

using namespace std;

//* t = 1 -> 1 X 1 블록을 (x행, y열)에 놓은 경우
//* t = 2 -> 1 X 2 블록을 (x행, y열), (x행, y+1열)에 놓은 경우
//* t = 3 -> 2 X 1 블록을 (x행, y열), (x+1행, y열)에 놓은 경우

bool blue_board[4][6];
bool green_board[6][4];

int score;

/**
 * 파란색 보드의 블록을 옮기는 함수
 */
void move_block_right(int t, int x, int y) {
    int col;
    int final_col;

    switch (t) {
        case 1: //? 1 X 1 블록을 (x행, y열)에 놓은 경우
            for (col = 0; col < 6; ++col) {
                if (blue_board[x][col]) break;
            }
            final_col = col - 1;
            blue_board[x][final_col] = true;
            break;
        
        case 2: //? 1 X 2 블록을 (x행, y열), (x행, y+1열)에 놓은 경우
            for (col = 0; col < 6; ++col) {
                if (blue_board[x][col]) break;
            }
            final_col = col - 1;
            blue_board[x][final_col] = true;
            blue_board[x][final_col-1] = true;
            break;
        
        case 3: //? 2 X 1 블록을 (x행, y열), (x+1행, y열)에 놓은 경우
            for (col = 0; col < 6; ++col) {
                if (blue_board[x][col] || blue_board[x+1][col]) break;
            }
            final_col = col - 1;
            blue_board[x][final_col] = true;
            blue_board[x+1][final_col] = true;
            break;

        default:
            break;
    }
}

/**
 * 초록색 보드의 블록을 옮기는 함수
 */
void move_block_down(int t, int x, int y) {
    int row;
    int final_row;

    switch (t) {
        case 1: //? 1 X 1 블록을 (x행, y열)에 놓은 경우
            for (row = 0; row < 6; ++row) {
                if (green_board[row][y]) break;
            }
            final_row = row - 1;
            green_board[final_row][y] = true;
            break;
        
        case 2: //? 1 X 2 블록을 (x행, y열), (x행, y+1열)에 놓은 경우
            for (row = 0; row < 6; ++row) {
                if (green_board[row][y] || green_board[row][y+1]) break;
            }
            final_row = row - 1;
            green_board[final_row][y] = true;
            green_board[final_row][y+1] = true;
            break;

        case 3: //? 2 X 1 블록을 (x행, y열), (x+1행, y열)에 놓은 경우
            for (row = 0; row < 6; ++row) {
                if (green_board[row][y]) break;
            }
            final_row = row - 1;
            green_board[final_row][y] = true;
            green_board[final_row-1][y] = true;
            break;
        default:
            break;
    }
}

/**
 * 모두 채워진 열이 존재하면 가장 값이 큰 열의 값을, 아니라면 -1 리턴
 */
int is_exist_filled_col() {
    for (int col = 5; col >= 0; --col) {
        int cnt = 0;
        for (int row = 0; row < 4; ++row) {
            if (blue_board[row][col]) ++cnt;
        }
        if (cnt == 4) return col;
    }
    return -1;
}

int is_exist_filled_row() {
    for (int row = 5; row >= 0; --row) {
        int cnt = 0;
        for (int col = 0; col < 4; ++col) {
            if (green_board[row][col]) ++cnt;
        }
        if (cnt == 4) return row;
    }
    return -1;
}

void check_board() {
    //* 1. 파란색 보드 검사
    //* 1-1. 모두 채워진 열 검사
    int filled_col = is_exist_filled_col();
    while (filled_col != -1 && (filled_col != 0 || filled_col != 1)) {
        ++score;
        //? filled_col 지우기
        for (int col = filled_col; col >= 1; --col) {
            for (int row = 0; row < 4; ++row) {
                blue_board[row][col] = blue_board[row][col-1];
            }
        }
        //? 0번 열 초기화
        for (int row = 0; row < 4; ++row) {
            blue_board[row][0] = false;
        }

        filled_col = is_exist_filled_col();
    }

    //* 1-2. 0번, 1번 열 검사
    set<int> special_cols;
    for (int row = 0; row < 4; ++row) {
        if (blue_board[row][0]) special_cols.insert(0);
        if (blue_board[row][1]) special_cols.insert(1);
    }

    for (int i = 0; i < special_cols.size(); ++i) {
        for (int col = 5; col > 0; --col) {
            for (int row = 0; row < 4; ++row) {
                blue_board[row][col] = blue_board[row][col-1];
            }
        }
        //? 0번 열 초기화
        for (int row = 0; row < 4; ++row) {
            blue_board[row][0] = false;
        }
    }

    //* 2. 초록색 보드 검사
    //* 2-1. 모두 채워진 행 검사
    int filled_row = is_exist_filled_row();
    while (filled_row != -1 && (filled_row != 0 || filled_row != 1)) {
        ++score;
        //? filled_row 지우기
        for (int row = filled_row; row >= 1; --row) {
            for (int col = 0; col < 4; ++col) {
                green_board[row][col] = green_board[row-1][col];
            }
        }
        //? 0번 행 초기화
        for (int col = 0; col < 4; ++col) {
            green_board[0][col] = false;
        }

        filled_row = is_exist_filled_row();
    }

    //* 2-2. 0번, 1번 행 검사
    set<int> special_rows;
    for (int col = 0; col < 4; ++col) {
        if (green_board[0][col]) special_rows.insert(0);
        if (green_board[1][col]) special_rows.insert(1);
    }

    for (int i = 0; i < special_rows.size(); ++i) {
        for (int row = 5; row > 0; --row) {
            for (int col = 0; col < 4; ++col) {
                green_board[row][col] = green_board[row-1][col];
            }
        }
        //? 0번 행 초기화
        for (int col = 0; col < 4; ++col) {
            green_board[0][col] = false;
        }
    }
}

int get_tile_cnt() {
    int result = 0;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (green_board[i][j]) ++result;
            if (blue_board[j][i]) ++result;
        }
    }
    return result;
}

int main() {
    int n, t, x, y;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> t >> x >> y;

        //* 1. 초록색 / 파란색 보드에 블록을 옮긴다.
        move_block_down(t, x, y);
        move_block_right(t, x, y);

        //* 2. 점수를 계산한다.
        check_board();
    }

    cout << score << '\n' << get_tile_cnt() << '\n';
    return 0;
}
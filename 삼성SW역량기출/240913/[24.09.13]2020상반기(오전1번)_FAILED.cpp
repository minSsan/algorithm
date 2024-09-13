// 문제 링크 - https://www.acmicpc.net/problem/20061
// 시간 - 2시간 58분 소요 (예제 모두 맞으나 제출 1%에서 틀림)

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

int n;
bool red_board[4][4];
bool blue_board[4][6];
bool green_board[6][4];
int score;

void move_right_vivid(int col_arr);
void move_down_vivid(int row_arr);
void move_right_all();
void move_down_all();

// 파란 보드의 블록 이동이 모두 끝난 후, 조건에 맞게 보드 칸을 이동시키는 함수
void move_right(vector<int> col_arr) { // col_arr - 가장 최근 들어온 블록들의 최종 위치 column 값들
    vector<int> filled_col;
    set<int> special_col;

    //* 1. 가득 찬 타일 + 0, 1 열 타일 존재 조건 모두 만족하는지 확인
    for (int col : col_arr) {
        if (col == 0 || col == 1) special_col.insert(col);

        int cnt = 0;
        for (int row = 0; row < 4; ++row) {
            if (blue_board[row][col]) ++cnt;
        }
        if (cnt == 4) filled_col.push_back(col);
    }

    //* 2. 두 조건 중 하나라도 성립하는 경우
    if (filled_col.size() > 0 || special_col.size() > 0) {
        //* 1. 가득 찬 열을 먼저 이동시킨다. (두 조건이 모두 성립할 경우 이를 먼저 실행해야 함)
        for (int col : filled_col) {
            move_right_vivid(col);
            ++score;
        }

        //* 2. 블록이 포함 된 연한 열의 개수만큼 이동시킨다.
        for (int i = 0; i < special_col.size(); ++i) {
            move_right_all();
        }
    }
}

// 초록 보드의 블록 이동이 모두 끝난 후, 조건에 맞게 보드 칸을 이동시키는 함수
void move_down(vector<int> row_arr) { // row_arr - 가장 최근 들어온 블록들의 최종 위치 rows 값들
    vector<int> filled_row;
    set<int> special_row;

    //* 1. 가득 찬 타일 + 0, 1 행 타일 존재 조건 모두 만족하는지 확인
    for (int row : row_arr) {
        if (row == 0 || row == 1) special_row.insert(row);

        int cnt = 0;
        for (int col = 0; col < 4; ++col) {
            if (green_board[row][col]) ++cnt;
        }
        if (cnt == 4) { filled_row.push_back(row);}
    }

    //* 2. 두 조건 중 하나라도 성립하는 경우
    if (filled_row.size() > 0 || special_row.size() > 0) {
        //* 1. 가득 찬 행을 먼저 이동시킨다. (두 조건이 모두 성립할 경우 이를 먼저 실행해야 함)
        for (int row : filled_row) {
            move_down_vivid(row);
            ++score;
        }

        //* 2. 블록이 포함 된 연한 행의 개수만큼 이동시킨다.
        for (int i = 0; i < special_row.size(); ++i) {
            move_down_all();
        }
    }
}

// 파란색 보드의 칸을 모두 오른쪽으로 이동시키는 함수
void move_right_all() {
    for (int col = 5; col >= 1; --col) {
        for (int row = 0; row < 4; ++row) {
            blue_board[row][col] = blue_board[row][col-1];
        }
    }
}

// 초록색 보드의 칸을 모두 아래로 이동시키는 함수
void move_down_all() {
    for (int row = 5; row >= 1; --row) {
        for (int col = 0; col < 4; ++col) {
            green_board[row][col] = green_board[row-1][col];
        }
    }
}

// 파란색 보드의 진한 칸만 오른쪽으로 이동시키는 함수 (두 조건을 동시에 만족할 때 실행)
void move_right_vivid(int start_col) {
    //* 1. start_col번 열 ~ 3번 열 덮어 쓰기
    for (int col = start_col; col >= 3; --col) {
        for (int row = 0; row < 4; ++row) {
            blue_board[row][col] = blue_board[row][col-1];
        }
    }
    //* 2. 2번 열 초기화하기
    for (int row = 0; row < 4; ++row) {
        blue_board[row][2] = false;
    }
}

// 초록색 보드의 진한 칸만 아래로 이동시키는 함수 (두 조건을 동시에 만족할 때 실행)
void move_down_vivid(int start_row) {
    //* 1. start_row번 행 ~ 3번 행 덮어 쓰기
    for (int row = start_row; row >= 3; --row) {
        for (int col = 0; col < 4; ++col) {
            green_board[row][col] = green_board[row-1][col];
        }
    }
    //* 2. 2번 행 초기화하기
    for (int col = 0; col < 4; ++col) {
        green_board[2][col] = false;
    }
}

vector<int> move_block_right(int t, int x, int y) {
    vector<int> col_arr;
    int final_col;
    int col;
    switch (t) {
        case 1: //? 1 X 1 블록을 (x행, y열)에 놓은 경우
            for (col = 0; col < 6; ++col) {
                if (blue_board[x][col]) {
                    break;
                }
            }
            final_col = col-1;
            blue_board[x][final_col] = true;
            col_arr.push_back(final_col);
            break;
        
        case 2: //? 1 X 2 블록을 (x행, y열), (x행, y+1열)에 놓은 경우
            //* 더 우측에 있는 블록을 기준으로 이동시킨다.
            for (col = 1; col < 6; ++col) {
                if (blue_board[x][col]) {
                    break;
                }
            }
            final_col = col-1;
            blue_board[x][final_col] = true;
            blue_board[x][final_col-1] = true;
            col_arr.push_back(final_col);
            col_arr.push_back(final_col-1);
            break;

        case 3: //? 2 X 1 블록을 (x행, y열), (x+1행, y열)에 놓은 경우
            for (col = 0; col < 6; ++col) {
                if (blue_board[x][col] || blue_board[x+1][col]) {
                    break;
                }
            }
            final_col = col-1;
            blue_board[x][final_col] = true;
            blue_board[x+1][final_col] = true;
            col_arr.push_back(final_col);
            break;
        
        default:
            break;
    }
    return col_arr;
}

vector<int> move_block_down(int t, int x, int y) {
    vector<int> row_arr;
    int final_row;
    int row;
    switch (t) {
        case 1: //? 1 X 1 블록을 (x행, y열)에 놓은 경우
            for (row = 0; row < 6; ++row) {
                if (green_board[row][y]) {
                    break;
                }
            }
            final_row = row-1;
            green_board[final_row][y] = true;
            row_arr.push_back(final_row);
            break;
        
        case 2: //? 1 X 2 블록을 (x행, y열), (x행, y+1열)에 놓은 경우
            for (row = 0; row < 6; ++row) {
                if (green_board[row][y] || green_board[row][y+1]) {
                    break;
                }
            }
            final_row = row-1;
            green_board[final_row][y] = true;
            green_board[final_row][y+1] = true;
            row_arr.push_back(final_row);
            break;

        case 3: //? 2 X 1 블록을 (x행, y열), (x+1행, y열)에 놓은 경우
            //* 더 아래에 있는 블록을 기준으로 이동시킨다.
            for (row = 1; row < 6; ++row) {
                if (green_board[row][y]) {
                    break;
                }
            }
            final_row = row-1;
            green_board[final_row][y] = true;
            green_board[final_row-1][y] = true;
            row_arr.push_back(final_row);
            row_arr.push_back(final_row-1);
            break;
        
        default:
            break;
    }
    return row_arr;
}

//* t = 1 -> 1 X 1 블록을 (x행, y열)에 놓은 경우
//* t = 2 -> 1 X 2 블록을 (x행, y열), (x행, y+1열)에 놓은 경우
//* t = 3 -> 2 X 1 블록을 (x행, y열), (x+1행, y열)에 놓은 경우
int main() {
    cin >> n;
    int t, x, y;
    
    for (int i = 0; i < n; ++i) {
        cin >> t >> x >> y;
        
        //* 1. 파란색 보드에서 이동
        vector<int> col_arr = move_block_right(t, x, y);

        //* 2. 초록색 보드에서 이동
        vector<int> row_arr = move_block_down(t, x, y);
        
        //* 3-1. 파란색 보드에서 가득 찬 열 검사 및 점수 계산 + 블록 이동 (2번 열부터 ... 0, 1 열 제외하고 이동)
        //* 3-2. 파란색 보드에서 연한 영역(0번, 1번 열)에 블록이 존재하는 줄만큼 오른쪽으로 이동
        move_right(col_arr);

        //* 4-1. 초록색 보드에서 가득 찬 열 검사 및 점수 계산 + 블록 이동 (2번 열부터 ... 0, 1 열 제외하고 이동)
        //* 4-1. 초록색 보드에서 연한 영역(0번, 1번 열)에 블록이 존재하는 줄만큼 오른쪽으로 이동
        move_down(row_arr);

    }

    int result = 0;
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (green_board[row][col]) ++result;
            if (blue_board[col][row]) ++result;
        }
    }

    cout << score << '\n' << result << '\n';

    return 0;
}
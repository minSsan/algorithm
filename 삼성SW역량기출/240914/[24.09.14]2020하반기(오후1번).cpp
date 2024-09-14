// 문제 링크 - https://www.acmicpc.net/problem/20057
// 시간 - 2시간 40분 소요 (첫 풀이 실수 -> 두 번째 풀이 정답)

#include <iostream>

// 좌 - 하 - 우 - 상 방향을 주기로 ...
#define LEFT 1
#define DOWN 2
#define RIGHT 3
#define UP 4

using namespace std;

int n; // 홀수
int sand[500][500];

int dr[500];
int dc[500];

pair<int, int> get_dest(int direction, int row, int col) {
    switch (direction) {
        case LEFT:
            return {row, col-1};

        case DOWN:
            return {row+1, col};
        
        case RIGHT:
            return {row, col+1};
        
        case UP:
            return {row-1, col};
        default:
            return {row, col};
    }
}

int get_exit_sand(int direction, int row, int col) {
    pair<int, int> dest = get_dest(direction, row, col);
    int dest_row = dest.first; int dest_col = dest.second;
    
    int result = 0;
    int remain = 0;
    //* 1. 상-하 / 좌-우 모레(7% + 2%) 검사
    switch (direction) {
        case LEFT:
        case RIGHT:
            //? 7% 검사
            if (dest_row - 1 < 0) result += sand[dest_row][dest_col] * 0.07;
            else sand[dest_row-1][dest_col] += sand[dest_row][dest_col] * 0.07;
            remain += sand[dest_row][dest_col] * 0.07;

            if (dest_row + 1 > n-1) result += sand[dest_row][dest_col] * 0.07;
            else sand[dest_row+1][dest_col] += sand[dest_row][dest_col] * 0.07;
            remain += sand[dest_row][dest_col] * 0.07;

            //? 2% 검사
            if (dest_row - 2 < 0) result += sand[dest_row][dest_col] * 0.02;
            else sand[dest_row-2][dest_col] += sand[dest_row][dest_col] * 0.02;
            remain += sand[dest_row][dest_col] * 0.02;

            if (dest_row + 2 > n-1) result += sand[dest_row][dest_col] * 0.02;
            else sand[dest_row+2][dest_col] += sand[dest_row][dest_col] * 0.02;
            
            remain += sand[dest_row][dest_col] * 0.02;
            break;
        
        case UP:
        case DOWN:
            //? 7% 검사
            if (dest_col - 1 < 0) result += sand[dest_row][dest_col] * 0.07;
            else sand[dest_row][dest_col-1] += sand[dest_row][dest_col] * 0.07;
            
            remain += sand[dest_row][dest_col] * 0.07;

            if (dest_col + 1 > n-1) result += sand[dest_row][dest_col] * 0.07;
            else sand[dest_row][dest_col+1] += sand[dest_row][dest_col] * 0.07;
            
            remain += sand[dest_row][dest_col] * 0.07;

            //? 2% 검사
            if (dest_col - 2 < 0) result += sand[dest_row][dest_col] * 0.02;
            else sand[dest_row][dest_col-2] += sand[dest_row][dest_col] * 0.02;
            
            remain += sand[dest_row][dest_col] * 0.02;

            if (dest_col + 2 > n-1) result += sand[dest_row][dest_col] * 0.02;
            else sand[dest_row][dest_col+2] += sand[dest_row][dest_col] * 0.02;
            
            remain += sand[dest_row][dest_col] * 0.02;
            break;
        default:
            break;
    }

    //* 2. 5% 모래 검사
    switch (direction) {
        case LEFT:
            if (dest_col - 2 < 0) result += sand[dest_row][dest_col] * 0.05;
            else sand[dest_row][dest_col-2] += sand[dest_row][dest_col] * 0.05;
            
            remain += sand[dest_row][dest_col] * 0.05;
            break;
        case RIGHT:
            if (dest_col + 2 > n-1) result += sand[dest_row][dest_col] * 0.05;
            else sand[dest_row][dest_col+2] += sand[dest_row][dest_col] * 0.05;
            
            remain += sand[dest_row][dest_col] * 0.05;
            break;
        case UP:
            if (dest_row - 2 < 0) result += sand[dest_row][dest_col] * 0.05;
            else sand[dest_row-2][dest_col] += sand[dest_row][dest_col] * 0.05;
            
            remain += sand[dest_row][dest_col] * 0.05;
            break;
        case DOWN:
            if (dest_row + 2 > n-1) result += sand[dest_row][dest_col] * 0.05;
            else sand[dest_row+2][dest_col] += sand[dest_row][dest_col] * 0.05;
            
            remain += sand[dest_row][dest_col] * 0.05;
            break;
        default:
            break;
    }

    //* 3. 대각선 (10%, 1%) 모레 검사
    switch (direction) {
        case LEFT:
            if (dest_col-1 < 0 || dest_row-1 < 0) result += sand[dest_row][dest_col] * 0.1;
            else sand[dest_row-1][dest_col-1] += sand[dest_row][dest_col] * 0.1;
            
            remain += sand[dest_row][dest_col] * 0.1;

            if (dest_col-1 < 0 || dest_row+1 > n-1) result += sand[dest_row][dest_col] * 0.1;
            else sand[dest_row+1][dest_col-1] += sand[dest_row][dest_col] * 0.1;
            
            remain += sand[dest_row][dest_col] * 0.1;
            
            if (dest_col+1 > n-1 || dest_row-1 < 0) result += sand[dest_row][dest_col] * 0.01;
            else sand[dest_row-1][dest_col+1] += sand[dest_row][dest_col] * 0.01;
            
            remain += sand[dest_row][dest_col] * 0.01;

            if (dest_col+1 > n-1 || dest_row+1 > n-1) result += sand[dest_row][dest_col] * 0.01;
            else sand[dest_row+1][dest_col+1] += sand[dest_row][dest_col] * 0.01;
            
            remain += sand[dest_row][dest_col] * 0.01;
            break;
        case RIGHT:
            if (dest_col-1 < 0 || dest_row-1 < 0) result += sand[dest_row][dest_col] * 0.01;
            else sand[dest_row-1][dest_col-1] += sand[dest_row][dest_col] * 0.01;
            
            remain += sand[dest_row][dest_col] * 0.01;

            if (dest_col-1 < 0 || dest_row+1 > n-1) result += sand[dest_row][dest_col] * 0.01;
            else sand[dest_row+1][dest_col-1] += sand[dest_row][dest_col] * 0.01;
            
            remain += sand[dest_row][dest_col] * 0.01;

            if (dest_col+1 > n-1 || dest_row-1 < 0) result += sand[dest_row][dest_col] * 0.1;
            else sand[dest_row-1][dest_col+1] += sand[dest_row][dest_col] * 0.1;
            
            remain += sand[dest_row][dest_col] * 0.1;

            if (dest_col+1 > n-1 || dest_row+1 > n-1) result += sand[dest_row][dest_col] * 0.1;
            else sand[dest_row+1][dest_col+1] += sand[dest_row][dest_col] * 0.1;
            
            remain += sand[dest_row][dest_col] * 0.1;
            break;
        case UP:
            if (dest_col-1 < 0 || dest_row-1 < 0) result += sand[dest_row][dest_col] * 0.1;
            else sand[dest_row-1][dest_col-1] += sand[dest_row][dest_col] * 0.1;
            
            remain += sand[dest_row][dest_col] * 0.1;

            if (dest_col-1 < 0 || dest_row+1 > n-1) result += sand[dest_row][dest_col] * 0.01;
            else sand[dest_row+1][dest_col-1] += sand[dest_row][dest_col] * 0.01;
            
            remain += sand[dest_row][dest_col] * 0.01;

            if (dest_col+1 > n-1 || dest_row-1 < 0) result += sand[dest_row][dest_col] * 0.1;
            else sand[dest_row-1][dest_col+1] += sand[dest_row][dest_col] * 0.1;
            
            remain += sand[dest_row][dest_col] * 0.1;

            if (dest_col+1 > n-1 || dest_row+1 > n-1) result += sand[dest_row][dest_col] * 0.01;
            else sand[dest_row+1][dest_col+1] += sand[dest_row][dest_col] * 0.01;
            
            remain += sand[dest_row][dest_col] * 0.01;
            break;
        case DOWN:
            if (dest_col-1 < 0 || dest_row-1 < 0) result += sand[dest_row][dest_col] * 0.01;
            else sand[dest_row-1][dest_col-1] += sand[dest_row][dest_col] * 0.01;
            
            remain += sand[dest_row][dest_col] * 0.01;

            if (dest_col-1 < 0 || dest_row+1 > n-1) result += sand[dest_row][dest_col] * 0.1;
            else sand[dest_row+1][dest_col-1] += sand[dest_row][dest_col] * 0.1;
            
            remain += sand[dest_row][dest_col] * 0.1;

            if (dest_col+1 > n-1 || dest_row-1 < 0) result += sand[dest_row][dest_col] * 0.01;
            else sand[dest_row-1][dest_col+1] += sand[dest_row][dest_col] * 0.01;
            
            remain += sand[dest_row][dest_col] * 0.01;

            if (dest_col+1 > n-1 || dest_row+1 > n-1) result += sand[dest_row][dest_col] * 0.1;
            else sand[dest_row+1][dest_col+1] += sand[dest_row][dest_col] * 0.1;
            
            remain += sand[dest_row][dest_col] * 0.1;
            break;
        default:
            break;
    }

    //* 4. 알파 모레 이동
    int alpha = sand[dest_row][dest_col] - remain;
    switch (direction) {
        case LEFT:
            if (dest_col - 1 < 0) result += alpha;
            else sand[dest_row][dest_col-1] += alpha;
            break;
        
        case RIGHT:
            if (dest_col + 1 > n-1) result += alpha;
            else sand[dest_row][dest_col+1] += alpha;
            break;
        
        case UP:
            if (dest_row - 1 < 0) result += alpha;
            else sand[dest_row-1][dest_col] += alpha;
            break;
        
        case DOWN:
            if (dest_row + 1 > n-1) result += alpha;
            else sand[dest_row+1][dest_col] += alpha;
            break;
        
        default:
            break;
    }

    return result;
}

int main() {
    int result = 0;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> sand[i][j];
        }
    }

    int row = n / 2, col = n / 2;
    int next_row, next_col;

    int directions[4] = {LEFT, DOWN, RIGHT, UP};
    int cursor = 0; int limit = 2;
    for (int i = 1; i < n; ++i) {
        if (i == n-1) limit = 3;
        for (int j = 0; j < limit; ++j) {
            for (int m = 0; m < i; ++m) {
                // cout << "row: " << row<< ", col: " << col << '\n';
                //* i번 만큼 directions[cursor] 방향으로 이동
                result += get_exit_sand(directions[cursor], row, col);
                
                //* y에 있는 모래 없애기
                pair<int, int> p = get_dest(directions[cursor], row, col);
                next_row = p.first; next_col = p.second;
                sand[next_row][next_col] = 0;

                //* row, col 값 갱신
                row = next_row;
                col = next_col;
            }
            cursor = (cursor+1) % 4;
        }
    }

    cout << result << '\n';

    return 0;
}
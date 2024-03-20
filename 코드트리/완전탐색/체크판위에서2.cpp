#include <iostream>
#include <queue>

using namespace std;

struct node {
    int r;
    int c;
    int cnt;
};

//? R * C 직사각형
//? 각 칸은 W(흰색), B(검은색)로 표시
//? 왼쪽 상단 -> 우측 하단으로 이동할 때, 룰을 만족하면서 이동에 성공할 수 있는 경우의 수
//?     이동: 점프로만 진행
//?     점프: 점프 진행시 항상 현재 위치 색과, 점프한 이후의 칸(다음 칸)의 색은 달라야 함
//?     단, 점프 진행은 오른쪽 아래 방향으로만 가능
//?     시작, 도착 지점 제외하고 점프하며 도달한 위치가 "두 곳만" 있어야 함
int main() {
    int r, c;
    cin >> r >> c;
    char graph[r][c];
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cin >> graph[i][j];
        }
    }

    int current_r = 0, current_c = 0, current_cnt;
    int next_r, next_c;
    char current_color;
    queue<node> q;
    q.push({0, 0, 0});
    int cnt = 0;
    while (!q.empty()) {
        current_r = q.front().r; current_c = q.front().c; current_cnt = q.front().cnt;
        q.pop();

        if (current_r == r-1 && current_c == c-1 && current_cnt == 3) {
            ++cnt;
            continue;
        }

        current_color = graph[current_r][current_c];
        // 현재 위치에서 세로로 i칸 만큼, 가로로 j칸 만큼 점프
        for (int i = 1; i < r - current_r; ++i) {
            for (int j = 1; j < c - current_c; ++j) {
                next_r = current_r + i; next_c = current_c + j;
                if (graph[next_r][next_c] != current_color) {
                    q.push({next_r, next_c, current_cnt+1});
                }
            }
        }
    }

    cout << cnt << '\n';

    return 0;
}
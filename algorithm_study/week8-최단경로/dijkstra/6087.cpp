#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#define INF 99999999

using namespace std;

//*  . : 빈칸
//*  * : 벽
//*  C : 레이저로 연결해야 하는 칸
//*  - 'C'는 항상 두 개이고, 레이저로 연결할 수 있는 입력만 주어진다.
//?  - 첫째 줄에 C를 연결하기 위해 설치해야 하는 거울 개수의 최솟값을 출력한다.

vector<vector<int>> v(100); // 0: 시작 | 끝점, 1: 빈칸, INF: 벽

void dijkstra(int start_row, int start_col) {
    // ? 최소힙
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;
    pq.push(make_tuple(0, start_row, start_col));

    while (!pq.empty()) {
        
    }
}

int main() {
    //* ============= 입력 =============
    int row, col; // row: 세로(H), col: 가로(W)
    cin >> col >> row;
    string s;
    int start_row = -1, start_col = -1;
    for (int i = 0; i < row; ++i) {
        cin >> s;
        for (int j = 0; j < s.size(); ++j) {
            char c = s[j];
            switch (c) {
                case '.':
                    v[i].push_back(1);
                    break;
                case '*':
                    v[i].push_back(INF);
                    break;
                case 'C':
                    v[i].push_back(0);
                    if (start_row == -1 && start_col == -1) {
                        start_row = i; start_col = j;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    //* ==============================

    return 0;
}
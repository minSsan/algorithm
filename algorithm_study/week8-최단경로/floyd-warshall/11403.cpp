#include <iostream>

using namespace std;

// * 가중치 없는 방향 그래프 G
// * 모든 정점 (i, j)에 대해서, i에서 j로 가는 경로가 있는지 없는지 구하는 프로그램을 작성하시오.
// ? -> 모든 정점에서 모든 정점으로 가는 경로를 구하는 문제이므로, 플로이드 워셜 알고리즘 사용

int main() {
    int n;
    cin >> n;

    bool graph[n][n]; // 0: 경로 없음, 1: 경로 존재
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    // ? node를 거쳐가는 경우, 경로가 존재하는지 확인한다.
    for (int node = 0; node < n; ++node) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // ? node를 중간에 거쳐가는 경로만 확인하기 때문에,
                // ? 시작점이 node인 경우, 도착점이 node인 경우는 제외한다.
                if (i == node || j == node) {
                    continue;
                }

                if (graph[i][node] && graph[node][j]) {
                    // ? i -> j 경로가 존재함
                    graph[i][j] = true;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << graph[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
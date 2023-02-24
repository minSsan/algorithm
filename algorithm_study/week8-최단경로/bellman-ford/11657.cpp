#include <iostream>
#define INF 30000000000

using namespace std;

struct node
{
    int start;
    int end;
    int cost;
};

int n, m; // n: 도시의 수, m: 노선의 수
long long min_d[501]; // 각 도시에 도달하는 최단경로
node route[6000]; // 노선을 저장하는 배열. 최대 6000개까지 입력

bool bellman_ford(int start) {
    min_d[start] = 0;

    for (int i = 0; i <= n-1; ++i) { // ? (노드 - 1)번 반복
        for (int j = 0; j < m; ++j) { // ? 모든 간선(노선)을 탐색
            int start = route[j].start;
            int end = route[j].end;
            int cost = route[j].cost;

            if (min_d[start] != INF && min_d[start] + cost < min_d[end]) {
                if (i == n-1) return false;
                min_d[end] = min_d[start] + cost;
            }
        }
    }

    return true;
}

int main() {
    cin >> n >> m;

    // ? 최단 경로 그래프 초기화
    for (int i = 1; i <= n; ++i) {
        min_d[i] = INF;
    }

    // ? 노선 정보 입력받기
    for (int i = 0; i < m; ++i) {
        int start, end, cost;
        cin >> start >> end >> cost;
        route[i] = {start, end, cost};
    }

    // ? 1번 도시로부터 각 도시에 도달하는 최단 경로 구하기
    if (bellman_ford(1)) {
        for (int i = 2; i <= n; ++i) {
            if (min_d[i] == INF) {
                cout << -1 << '\n';
            } else {
                cout << min_d[i] << '\n';
            }
        }
    } else {
        cout << -1 << '\n';
    }
    
    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// * - 단방향 그래프, 다익스트라(시작점으로 부터 각 지점까지의 최단경로 계산)
// * - 도시 번호는 1 ~ N
// * - x에서부터 최단 경로가 k인 지점의 갯수를 구하라

int n, m; // n: 도시(노드)의 갯수, m: 도로(간선)의 갯수
int k, x; // k: 찾고자 하는 최단 경로, x: 출발 도시 번호

bool visited[300001]; // ? 각 노드의 방문 기록을 저장하는 배열
int min_d[300001]; // ? 시작점으로부터 각 노드까지의 최단 거리를 저장하는 배열
vector<int> graph[300002];

int const MAX = 300000;

void dijkstra(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    min_d[start] = 0;
    visited[start] = true;
    pq.push({0, start});

    while (!pq.empty()) {
        int now = pq.top().second; // 현재 노드
        int distance = pq.top().first; // 시작 노드부터 현재 노드까지의 최단경로
        pq.pop();

        // 현재 노드와 연결된 모든 노드들을 탐색
        for (int i = 0; i < graph[now].size(); ++i) {
            int next = graph[now][i];
            int next_distance = distance + 1;
            if (!visited[next] && next_distance < min_d[next]) { // 아직 방문하지 않은 노드를 발견하였다면,
                min_d[next] = next_distance;
                visited[next] = true;
                pq.push({next_distance, next});
            }
        }
    }
}

int main() {
    cin >> n >> m >> k >> x;

    for (int i = 1; i <= n; ++i) {
        min_d[i] = MAX; // 각 노드까지 도달하는 최단거리를 최대치 값으로 초기화
    }

    for (int i = 0; i < m; ++i) {
        int start, end;
        cin >> start >> end;
        graph[start].push_back(end);
    }

    dijkstra(x);

    vector<int> result;
    int cnt = 0;
    // * 최단경로가 k인 도시의 수 세기
    for (int i = 1; i <= n; ++i) {
        if (min_d[i] == k) {
            result.push_back(i);
        }
    }

    sort(result.begin(), result.end());

    if (result.size() == 0) {
        cout << -1 << '\n';
    } else {
        for (int i = 0; i < result.size(); ++i) {
            cout << result[i] << '\n';
        }
    }

    return 0;
}
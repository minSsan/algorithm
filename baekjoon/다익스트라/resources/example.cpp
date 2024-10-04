#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 20000;

int main() {
    int v, e; // 정점, 간선
    cin >> v >> e;

    int d[v+1]; // 1번 정점 ~ i번 정점까지의 거리
    fill(d, d+v+1, INF);
    d[1] = 0;

    int pre[v+1]; // i번 정점까지의 최단경로를 위해 직전에 방문한 노드
    fill(pre, pre+v+1, INF);
    pre[1] = 0;

    vector<pair<int, int>> graph[v+1]; // 노드 번호, 가중치
    for (int i = 0; i < e; ++ i) {
        int s, e, w;
        cin >> s >> e >> w;
        graph[s].push_back({e, w});
    }

    priority_queue<pair<int ,int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 최소힙 {가중치, 노드 번호}

    pq.push({0, 1}); // 1번 노드부터 방문
    while (!pq.empty()) {
        pair<int, int> info = pq.top();
        pq.pop();

        int cur_w = info.first, cur_node = info.second;
        // ⭐️ 더 가까운 노드에 의해 최단경로 값이 이미 업데이트 된 경우
        if (d[cur_node] != cur_w) continue;

        for (pair<int, int> coord : graph[cur_node]) {
            int coord_w = coord.second, coord_node = coord.first;
            if (cur_w + coord_w < d[coord_node]) {
                d[coord_node] = cur_w + coord_w;
                pq.push({d[coord_node], coord_node});
                pre[coord_node] = cur_node;
            }
        }
    }

    // 1번 정점부터 각 정점까지의 최단경로 가중치 출력
    for (int i = 1; i <= v; ++i) {
        if (d[i] == INF) cout << "INF\n";
        else cout << d[i] << '\n';
    }

    // 각 정점까지의 최단경로 출력
    for (int dest = 1; dest <= v; ++dest) {
        cout << "1에서 " << dest << " 까지의 최단경로\n";
        if (pre[dest] == INF) {
            cout << "INF\n";
            continue;
        }

        vector<int> path;
        int cur = dest;
        while (cur != 0) {
            path.push_back(cur);
            cur = pre[cur];
        }

        reverse(path.begin(), path.end());

        for (int p : path) {
            cout << p << ' ';
        }
        cout << '\n';
    }

    return 0;
}
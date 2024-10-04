#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct bus {
    int dest; // 도착지
    int cost; // 비용
};

const int INF = 100000005;

int main() {
    int n, m;
    cin >> n >> m;

    vector<bus> graph[n+1];

    for (int i = 0; i < m; ++i) {
        int s, e, c;
        cin >> s >> e >> c;
        graph[s].push_back({e, c});
    }

    int start, dest;
    cin >> start >> dest;

    int d[n+1]; // start부터 i번 도시까지 가는 최소 비용
    fill(d, d+n+1, INF);
    d[start] = 0;
    // {비용, 노드 번호}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        pair<int, int> cur = pq.top();
        int cur_cost = cur.first, cur_node = cur.second;
        pq.pop();

        if (cur_cost != d[cur_node]) continue;
        for (bus coord : graph[cur_node]) {
            if (cur_cost + coord.cost < d[coord.dest]) {
                d[coord.dest] = cur_cost + coord.cost;
                pq.push({d[coord.dest], coord.dest});
            }
        }
    }

    cout << d[dest] << '\n';

    return 0;
}
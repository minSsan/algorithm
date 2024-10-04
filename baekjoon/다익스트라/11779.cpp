#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct bus {
    int dest;
    int cost;
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
    int start, end;
    cin >> start >> end;

    int d[n+1];
    fill(d, d+n+1, INF);
    d[start] = 0;

    // 가중치, 노드 번호
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    int pre[n+1];
    fill(pre, pre+n+1, INF);
    pre[start] = 0;

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        int cur_w = cur.first, cur_node = cur.second;

        if (d[cur_node] != cur_w) continue;

        for (bus coord : graph[cur_node]) {
            if (cur_w + coord.cost < d[coord.dest]) {
                d[coord.dest] = cur_w + coord.cost;
                pre[coord.dest] = cur_node;
                pq.push({d[coord.dest], coord.dest});
            }
        }
    }

    cout << d[end] << '\n';
    vector<int> path;
    int cur = end;
    while (cur != 0) {
        path.push_back(cur);
        cur = pre[cur];
    }

    cout << path.size() << '\n';

    reverse(path.begin(), path.end());
    for (int p : path) {
        cout << p << ' ';
    }
    cout << '\n';

    return 0;
}
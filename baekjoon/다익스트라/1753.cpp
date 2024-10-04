#include <iostream>
#include <queue>

using namespace std;

const int INF = 200001;

struct node {
    int node;
    int weight;
};

int main() {
    int v, e;
    cin >> v >> e;
    int k;
    cin >> k;

    vector<node> graph[v+1]; // 가중치, 노드 번호
    for (int i = 0; i < e; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    
    int d[v+1]; // k 부터 i 까지의 최단거리
    fill(d, d+v+1, INF);
    d[k] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, k});

    while (!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();
        int cur_node = cur.second;
        int cur_w = cur.first;

        if (cur_w != d[cur_node]) continue;

        for (node coord : graph[cur_node]) {
            if (cur_w + coord.weight < d[coord.node]) {
                d[coord.node] = cur_w + coord.weight;
                pq.push({d[coord.node], coord.node});
            }
        }
    }

    for (int i = 1; i <= v; ++i) {
        if (d[i] == INF) cout << "INF\n";
        else cout << d[i] << '\n';
    }

    return 0;
}
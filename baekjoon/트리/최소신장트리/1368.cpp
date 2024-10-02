#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//* 물을 대려면 최소 하나의 우물은 무조건 파야 한다. -> 비용이 가장 적은 우물을 파는 것이 가장 이득이 될 것이다.
//*     -> 논리 증명: 다른 논과 연결되던, 독자적으로 논을 파던, 어느 경우에서도 비용이 가장 적은 논의 우물을 파는 것이 이득임

struct vertex {
    int start;
    int end;
    int cost;
};

bool compare(vertex a, vertex b) {
    return a.cost < b.cost;
}

int n;
int self_cost[300];
vector<vertex> p;
int parent[301];

int get_parent(int n) {
    if (parent[n] == n) return n;
    return parent[n] = get_parent(parent[n]);
}

bool is_diff_group(int a, int b) {
    int a_p = get_parent(a);
    int b_p = get_parent(b);

    if (a_p == b_p) return false;
    if (a_p < b_p) parent[b_p] = a_p;
    else parent[a_p] = b_p;
    return true;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> self_cost[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int cost;
            cin >> cost;
            if (i >= j) continue;
            p.push_back({i, j, cost});
        }
    }

    for (int i = 0; i < n; ++i) {
        p.push_back({i, n, self_cost[i]}); // n이라는 가상 노드를 추가해서 우물 파는 비용으로 계산
    }

    ++n;

    sort(p.begin(), p.end(), compare);

    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }

    int cost = 0;
    int vertex_cnt = 0;

    for (vertex coord : p) {
        if (!is_diff_group(coord.start, coord.end)) continue;
        cost += coord.cost;
        vertex_cnt++;
        if (vertex_cnt == n-1) break; // 정점의 수가 n+1이 됐기 때문
    }

    cout << cost << '\n';

    return 0;
}
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct vertex {
    int start;
    int end;
    int cost;
};

bool compare(vertex a, vertex b) {
    return a.cost < b.cost;
}

int p[6];
vector<vertex> v;

int parent(int n) {
    if (p[n] == n) return n;
    p[n] = parent(p[n]);
    return p[n];
}

int cost;
int vertex_cnt;

void merge(vertex a) {
    int a_p = parent(a.start);
    int b_p = parent(a.end);
    if (a_p == b_p) return;
    cost += a.cost;
    vertex_cnt++;
    if (a_p < b_p) p[b_p] = a_p;
    else p[a_p] = b_p;
}

int main() {
    for (int i = 1; i <= 5; ++i) {
        p[i] = i;
    }

    v.push_back({1, 3, 3});
    v.push_back({1, 4, 3});
    v.push_back({3, 4, 3});

    v.push_back({1, 2, 4});

    v.push_back({3, 5, 5});

    v.push_back({4, 5, 6});

    v.push_back({2, 5, 8});

    sort(v.begin(), v.end(), compare);

    for (vertex coord : v) {
        merge(coord);
    }

    if (vertex_cnt == 4) {
        cout << "최소 신장 트리 생성 성공\n";
        cout << "최소 비용: " << cost << '\n';
    } else {
        cout << "최소 신장 트리 생성 실패\n";
        cout << "연결된 간선 수: " << vertex_cnt << '\n';
    }


    return 0;
}
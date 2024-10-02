#include <iostream>
#include <tuple>
#include <algorithm>

using namespace std;

vector<tuple<int, int, int>> vertex;
int v, e;
int p[10001];
int cost_sum;
int vertex_cnt;

int parent(int n) {
    if (p[n] == n) return n;
    p[n] = parent(p[n]);
    return p[n];
}

void union_find(int a, int b, int cost) {
    int a_p = parent(a);
    int b_p = parent(b);

    if (a_p == b_p) return;
    cost_sum += cost;
    vertex_cnt++;
    if (a_p < b_p) p[b_p] = a_p;
    else p[a_p] = b_p;
}

int main() {
    cin >> v >> e;
    for (int i = 0; i < e; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        vertex.push_back(make_tuple(c, a, b));
    }
    sort(vertex.begin(), vertex.end());

    for (int i = 1; i <= v; ++i) {
        p[i] = i;
    }

    for (int i = 0; i < e; ++i) {
        tuple<int, int, int> coord = vertex[i];
        int a = get<1>(coord);
        int b = get<2>(coord);
        union_find(a, b, get<0>(coord));

        if (vertex_cnt == v-1) break;
    }

    cout << cost_sum << '\n';
    
    return 0;
}
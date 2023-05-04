#include <iostream>
#include <algorithm>

using namespace std;

int parent[1001];

int find(int n) {
    if (parent[n] != n) return find(parent[n]);
    return n;
}

bool is_same_group(int a, int b) {
    if (find(a) == find(b)) return true;
    return false;
}

void _union(int a, int b) { 
    a = find(a); // a의 parent
    b = find(b); // b의 parent

    if (a < b) { // a(= a의 parent)가 b(= b의 parent)보다 더 작은 경우
        parent[b] = a; // b(= b의 parent)의 parent를 a(= a의 parent)로 설정
    } else {
        parent[a] = b;
    }
}

int main() {
    for (int i = 1; i < 1001; ++i) {
        parent[i] = i;
    }

    int n, m; // n: 컴퓨터 수(노드), m: 선의 수(간선)
    cin >> n >> m;

    tuple<int, int, int> edge[m];

    int a, b, weight;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> weight;
        edge[i] = {weight, a, b};
    }
    sort(edge, edge + m);

    int min_cost = 0, line_cnt = 0;
    for (int i = 0; i < m; ++i) {
        tie(weight, a, b) = edge[i];

        if (is_same_group(a, b)) continue;
        // Union
        _union(a, b);
        min_cost += weight; ++line_cnt;
        if (line_cnt == n-1) break;
    }

    cout << min_cost << '\n';

    return 0;
}
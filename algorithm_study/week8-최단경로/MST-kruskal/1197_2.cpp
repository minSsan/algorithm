#include <iostream>
#include <algorithm>

using namespace std;

int parent[10001];

// ? parent: [1, 1, 1]
// ? {1}, {2}, {3} -> {1, 2, 3}
// ? 1-2(1), 1-3(2), 2-3(3)

// ? n이 어느 그룹에 속해있는지 찾는다.
int find(int n) {
    if (parent[n] == n) return n;
    return find(parent[n]);
}

// ? Find 한 결과로 두 정점이 속한 그룹이 동일한지 확인
bool is_same_group(int a, int b) {
    int a_group = find(a);
    int b_group = find(b);

    if (a_group == b_group) return true;
    return false;
}

void _union(int a, int b) {
    int a_root = find(a);
    int b_root = find(b);
    // ? a_root가 더 작으면, b_root의 parent를 a_root로 바꾼다.
    if (a_root < b_root) {
        parent[b_root] = a_root;
    } else {
        parent[a_root] = b_root;
    }
}

int main() {
    // * parent 배열 초기화 - 각 정점이 연결되어있지 않은 상태에서, 자신의 부모는 자신이 된다.
    for (int i = 0; i < 10001; ++i) {
        parent[i] = i;
    }

    int v, e;
    cin >> v >> e;

    tuple<int, int, int> edge[e]; // 가중치 - a - b 순으로 저장 (가중치 기준으로 오름차순 정렬 위함)

    int weight, a, b;
    for (int i = 0; i < e; ++i) {
        cin >> a >> b >> weight;
        edge[i] = {weight, a, b};
    }
    // * 가중치를 기준으로 간선을 오름차순 정렬
    sort(edge, edge + e);

    int mst_sum = 0, edge_cnt = 0;
    // * 가중치가 작은 간선부터 연결 여부를 확인한다.
    for (int i = 0; i < e; ++i) {
        tie(weight, a, b) = edge[i];
        if (is_same_group(a, b)) continue;
        // TODO: Union
        _union(a, b);
        mst_sum += weight; edge_cnt++;
        if (edge_cnt == v-1) break;
    }

    cout << mst_sum << '\n';

    return 0;
}
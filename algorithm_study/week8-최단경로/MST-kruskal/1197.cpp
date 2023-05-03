#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// * 크루스칼 알고리즘            - 최소 신장 트리(MST)를 구하는 알고리즘
// ? 신장 트리(Spanning Tree)   - 모든 정점을 포함하되 순환하지 않는 그래프
// ? 최소 신장 트리(MST)         - 간선의 합이 최소인 신장 트리

// * 그리디 알고리즘
// ? 1. 각 간선에 대해서 가중치를 기준으로 오름차순 정렬을 한다. 
// ? 2. 오름차순 정렬된 간선을 하나씩 순회하면서 각 간선의 연결 여부를 판단한다(순회하지 않는 조건에서만 연결).
// ? 2-1. 현재의 간선을 채택하는 경우, 순환이 발생하는지 안 하는지 확인하는 방법으로 "Union-Find"를 사용할 수 있다.

// * Union & Find - 서로소 집합
// ? Union: 서로 다른 두 집합을 병합하는 과정
// ? Find: 값이 어느 집합에 속해있는지 찾는 과정
// ? 1. Find - 서로 다른 두 원소를 합칠 때 서로소인 집합인지 확인하기 위해(=두 정점을 합칠 때 사이클이 없는지 확인하기 위해) 각 정점의 부모가 서로 다른지 비교한다.
// ?         - 만약 서로 같은 부모를 갖는다면, 같은 집합에 속해있기 때문에 둘을 연결하게 되는 순간 사이클을 형성한다. -> Union 과정을 거치지 않는다.
// ?         - 만약 서로 다른 부모를 갖는다면, 서로 다른 집합(연결되어있지 않음)에 속해있다. -> Union 과정을 거친다.
// ? 2. Union - 두 정점을 연결하고, 두 정점의 부모 중 더 작은 값을 부모로 설정한다.

int parent[10001];

// n이 속한 그룹을 찾는다.
int find(int n) {
    if (parent[n] != n) {
        return find(parent[n]);
    }
    return n;
}

// 둘이 서로 다른 그룹에 속한 경우 -> union 진행
void _union(int a, int b) {
    a = find(a);
    b = find(b);

    if (a <= b) {
        parent[b] = a;
    } else {
        parent[a] = b;
    }
}

bool is_same_group(int a, int b) {
    a = find(a);
    b = find(b);
    // 둘이 서로 같은 그룹에 속한 경우
    if (a == b) return true;
    return false;
}

int main() {
    for (int i = 0; i < 10001; ++i) {
        parent[i] = i;
    }

    int v, e; // v: 정점, e: 간선
    cin >> v >> e;
    // vector<pair<int, pair<int, int>>> node; // {가중치, a, b} 순으로 저장
    tuple<int, int, int> edge[100001];

    int a, b, weight;
    for (int i = 0; i < e; ++i) {
        cin >> a >> b >> weight;
        // node.push_back({weight, {a, b}});
        edge[i] = {weight, a, b};
    }

    // sort(node.begin(), node.end());
    sort(edge, edge + e);

    int mst_sum = 0, edge_cnt = 0;
    for (int i = 0; i < e; ++i) {
        // a = node[i].second.first;
        // b = node[i].second.second;
        // weight = node[i].first;
        tie(weight, a, b) = edge[i];
        if (is_same_group(a, b)) continue;
        _union(a, b);
        mst_sum += weight;
        if (++edge_cnt == v-1) break; // MST에서는 간선의 갯수가 v-1개
    }

    cout << mst_sum << '\n';

    return 0;
}
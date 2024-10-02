#include <iostream>
#include <vector>
#include <queue>

#define EMPTY -1

using namespace std;

int n, m; // n: 정점 수, m: 간선 수

vector<int> graph[501];
bool visited[501];

//? BFS 탐색 
//? n개의 정점을 시작으로 각 정점을 모두 방문하고 나면, 모든 노드가 n-1번 만큼 방문되어 있어야 함 (=> n을 알 수 없음 :: 불가능)

//? DFS 탐색
//? 방문 여부 + prev 값 동시 비교 (방문을 이미 했고, prev 값이 현재 노드와 다른 경우)

bool is_tree;

void dfs(int node, int prev_node) {
    for (int coord : graph[node]) {
        if (coord == prev_node) continue;
        if (visited[coord]) is_tree = false;
        else {
            visited[coord] = true;
            dfs(coord, node);
        }
    }
}

int get_tree_cnt() {
    for (int i = 1; i <= n; ++i) {
        visited[i] = false;
    }

    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            is_tree = true;
            visited[i] = true;
            dfs(i, 0);
            if (is_tree) ++cnt;
        }
    }

    return cnt;
}

int main() {
    cin >> n >> m;
    int s, e;
    int num = 1;
    while (!(n == 0 && m == 0)) {
        for (int i = 1; i <= n; ++i) graph[i].clear();

        for (int i = 0; i < m; ++i) {
            cin >> s >> e;
            graph[s].push_back(e);
            graph[e].push_back(s);
        }

        int cnt = get_tree_cnt();

        if (cnt == 0) {
            cout << "Case " << num << ": No trees.\n";
        } else if (cnt == 1) {
            cout << "Case " << num << ": There is one tree.\n";
        } else {
            cout << "Case " << num << ": A forest of " << cnt << " trees.\n";
        }
        num++;

        cin >> n >> m;
    }

    return 0;
}
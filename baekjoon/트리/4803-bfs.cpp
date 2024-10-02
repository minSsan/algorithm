#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> graph[501];
bool visited[501];

void init_visited(int n) {
    for (int i = 1; i <= n; ++i) {
        visited[i] = false;
    }
}

void init_graph(int n) {
    for (int i = 1; i <= n; ++i) {
        graph[i].clear();
    }
}

struct info {
    int node;
    int prev;
};

bool bfs(int start_node) {
    queue<info> q;
    q.push({start_node, 0});
    visited[start_node] = true;

    bool is_tree = true;

    while (!q.empty()) {
        info cur = q.front();
        q.pop();

        for (int coord : graph[cur.node]) {
            if (coord == cur.prev) continue;
            if (visited[coord]) {
                is_tree = false;
            } else {
                visited[coord] = true;
                q.push({coord, cur.node});
            }
        }
    }
    return is_tree;
}

void print_result(int stage, int cnt) {
    if (cnt == 0) {
        cout << "Case " << stage << ": No trees.\n";
    }
    else if (cnt == 1) {
        cout << "Case " << stage << ": There is one tree.\n";
    }
    else {
        cout << "Case " << stage << ": A forest of " << cnt << " trees.\n"; 
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    int stage = 1;
    while (!(n == 0 && m == 0)) {
        int cnt = 0;
        for (int i = 0; i < m; ++i) {
            int s, e;
            cin >> s >> e;
            graph[s].push_back(e);
            graph[e].push_back(s);
        }
        init_visited(n);
        
        //* 트리 개수 계산
        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) {
                if (bfs(i)) ++cnt;
            }
        }

        //* 출력
        print_result(stage++, cnt);

        init_graph(n);
        cin >> n >> m;
    }
    return 0;
}
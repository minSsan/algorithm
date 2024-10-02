#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
vector<int> graph[32001];
int indegree[32001]; // i번 노드의 previous 노드 수

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        indegree[b]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        cout << cur << ' ';

        for (int coord : graph[cur]) {
            indegree[coord]--;
            if (indegree[coord] == 0) q.push(coord);
        }
    }
    cout << '\n';

    return 0;
}
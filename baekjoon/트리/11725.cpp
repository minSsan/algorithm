#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int parent[100001];

int main() {
    parent[1] = -1;

    int n;
    cin >> n;

    vector<int> graph[n+1];
    for (int i = 0; i < n-1; ++i) {
        int s, e;
        cin >> s >> e;
        graph[s].push_back(e);
        graph[e].push_back(s);
    }

    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int coord : graph[cur]) {
            if (parent[coord] == 0) {
                parent[coord] = cur;
                q.push(coord);
            }
        }
    }

    for (int i = 2; i <= n; ++i) {
        cout << parent[i] << '\n';
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, v;
int result;
vector<int> graph[101];
bool visited[101];

void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front(); q.pop();
        for (int i = 0; i < graph[current].size(); ++i) {
            int next = graph[current][i];
            if (!visited[next]) {
                q.push(next);
                visited[next] = true;
                result++;
            }
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> v;
    int start, end;
    for (int i = 0; i < v; ++i) {
        cin >> start >> end;
        graph[start].push_back(end);
        graph[end].push_back(start);
    }

    bfs(1);
    cout << result << '\n';

    return 0;
}
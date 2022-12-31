#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> graph[1001];
int visited[1001];

void dfs(int now) {
    for (int i = 0; i < graph[now].size(); ++i) {
        if (visited[graph[now][i]] == 0) {
            visited[graph[now][i]] = 1;
            cout << graph[now][i] << ' ';
            dfs(graph[now][i]);
        }
    }
}

int main() {
    int n, m, v;
    cin >> n >> m >> v; // n: 정점 수, m: 간선 수, v: 탐색 시작 정점 번호

    int start, end;
    for (int i = 0; i < m; ++i) {
        cin >> start >> end;
        graph[start].push_back(end);
        graph[end].push_back(start);
    }

    // ? 정점 번호가 작은 것부터 방문해야 하므로, 오름차순 정렬
    for (int i = 1; i <= n; ++i) {
        sort(graph[i].begin(), graph[i].end()); // 벡터를 정렬할 때는, 인덱스가 아닌 begin()과 end()로 시작점과 끝점을 지정해야 한다.  
    }

    // * DFS ------------------
    visited[v] = 1;
    cout << v << ' ';
    for (int i = 0; i < graph[v].size(); ++i) {
        if (visited[graph[v][i]] == 0) {
            visited[graph[v][i]] = 1;
            cout << graph[v][i] << ' ';
            dfs(graph[v][i]);
        }
    }
    
    cout << '\n';
    // * ----------------------

    // * BFS ------------------
    int bfs_visited[1001] = {0};
    queue<int> q;
    int now = v;

    q.push(now);

    while (!q.empty()) {
        now = q.front();
        q.pop();
        
        if (bfs_visited[now] == 0) {
            bfs_visited[now] = 1;
            cout << now << ' ';

            for (int i = 0; i < graph[now].size(); ++i) {
                if (bfs_visited[graph[now][i]] == 0) {
                    q.push(graph[now][i]);
                }
            }
        }
    }

    cout << '\n';
    // * ----------------------

    return 0;
}
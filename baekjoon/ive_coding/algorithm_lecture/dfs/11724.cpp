#include <iostream>
#include <vector>

using namespace std;

// TODO: 이차원 리스트로 표현하는 방법으로도 한번 풀어보기
// ex) u -> v : connects[u][v] = 1, connects[v][u] = 1

vector<int> connects[1001];
int visited[1001];

void dfs(int now) {
    for (int j = 0; j < connects[now].size(); ++j) {
        if (visited[connects[now][j]] == 0) {
            visited[connects[now][j]] = 1;
            dfs(connects[now][j]);
        }
    }
}

int main() {
    int n, m; // n: 정점의 수, m: 간선의 수
    cin >> n >> m;
    int cnt = 0; // 덩어리 수

    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        connects[u].push_back(v);
        connects[v].push_back(u); // 양방향 그래프 : u -> v, v -> u 연결
    }

    for (int i = 1; i <= n; ++i) { // 각 노드를 모두 탐색
        if (visited[i] == 0) { // 현재 노드가 아직 방문 전이라면,
            visited[i] = 1;
            cnt++; // 노드에 끝까지 연결된 것을 한번 탐색할 때마다 덩어리 수를 1 증가

            for (int j = 0; j < connects[i].size(); ++j) {
                if (visited[connects[i][j]] == 0) {
                    visited[connects[i][j]] = 1;
                    dfs(connects[i][j]);
                }
            }
        }
    }

    cout << cnt << '\n';

    return 0;
}
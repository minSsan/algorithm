#include <iostream>
#include <vector>

using namespace std;

int visited[1001];
vector<pair<int, int>> connects; // 간선 리스트

void dfs(int now) {
    for (int i = 0; i < connects.size(); ++i) {
        if (connects[i].first == now && visited[connects[i].second] == 0) {
            visited[connects[i].second] = 1;
            dfs(connects[i].second);
        }
    }
}

int main() {
    int n, m; // n: 정점의 수, m: 간선의 수
    cin >> n >> m;
    int cnt = 0;

    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        connects.push_back({u, v});
        connects.push_back({v, u});
    }

    for (int i = 1; i <= n; ++i) { // 각 정점마다 연결된 정점들을 살펴본다
        if (visited[i] == 0) {
            cnt++;
            visited[i] = 1;
            for (int j = 0; j < connects.size(); ++j) { // 연결된 그래프 중에서, i 정점과 연결된 정점들을 확인한다.
                // i 정점으로 시작되는 연결 지점이면서, 연결된 다음 정점이 아직 방문되지 않았다면,
                if (connects[j].first == i && visited[connects[j].second] == 0) {
                    visited[connects[j].second] = 1;
                    // 다음 정점과 연결된 정점들을 살펴본다.
                    dfs(connects[j].second);
                }
            }
        }
    }

    cout << cnt << '\n';

    return 0;
}
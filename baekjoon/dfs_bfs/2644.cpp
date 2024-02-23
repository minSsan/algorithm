#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n; // 전체 사람 수
int a, b; // 촌수를 계산해야하는 사람
int m; // 부모-자식 관계의 수
int x, y; // x는 y의 부모
bool visited[101];
vector<int> graph[101];

int bfs(int start) {
    queue<pair<int, int>> q;
    q.push({start, 0});

    while (!q.empty()) {
        int current = q.front().first; int accum = q.front().second; q.pop();
        if (current == b) return accum;

        for (int i = 0; i < graph[current].size(); ++i) {
            if (!visited[graph[current][i]]) {
                q.push({graph[current][i], accum + 1});
                visited[graph[current][i]] = true;
            }
        }
    }
    return -1;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> a >> b >> m;

    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    cout << bfs(a) << '\n';

    return 0;
}
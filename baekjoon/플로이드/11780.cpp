#include <iostream>
#include <vector>

#define INF 10000000

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int min_cost[n+1][n+1];
    int nxt[n+1][n+1]; // i에서 j까지 최단거리로 이동하기 위해 경유하는 바로 다음 노드
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            nxt[i][j] = 0;
            if (i == j) min_cost[i][j] = 0;
            else min_cost[i][j] = INF;
        }
    }

    for (int i = 0; i < m; ++i) {
        int s, e, c;
        cin >> s >> e >> c;
        min_cost[s][e] = min(min_cost[s][e], c);
        nxt[s][e] = e;
    }

    for (int mid = 1; mid <= n; ++mid) { //? mid: 경유지
        for (int start = 1; start <= n; ++start) {
            for (int end = 1; end <= n; ++end) {
                if (min_cost[start][mid] + min_cost[mid][end] < min_cost[start][end]) {
                    min_cost[start][end] = min_cost[start][mid] + min_cost[mid][end];
                    nxt[start][end] = nxt[start][mid]; // mid를 경유해서 가는 최단 경로
                }
            }
        }
    }

    for (int start = 1; start <= n; ++start) {
        for (int end = 1; end <= n; ++end) {
            if (min_cost[start][end] == INF) cout << "0 ";
            else cout << min_cost[start][end] << ' ';
        }
        cout << '\n';
    }

    for (int start = 1; start <= n; ++start) {
        for (int end = 1; end <= n; ++end) {
            if (nxt[start][end] == 0 || min_cost[start][end] == INF) {
                cout << "0\n";
                continue;
            }
            
            int cur = start;
            vector<int> path;
            
            while (cur != end) {
                path.push_back(cur);
                cur = nxt[cur][end];
            }
            path.push_back(end);

            cout << path.size() << ' ';
            for (int p : path) {
                cout << p << ' ';
            }
            cout << '\n';
        }
    }

    return 0;
}
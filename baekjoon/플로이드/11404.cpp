#include <iostream>

#define INF 1000000001

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    //* init
    int min_cost[n+1][n+1];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) min_cost[i][j] = 0;
            else min_cost[i][j] = INF;
        }
    }

    //* input
    for (int i = 0; i < m; ++i) {
        int s, e, c;
        cin >> s >> e >> c;
        min_cost[s][e] = min(c, min_cost[s][e]);
    }

    for (int mid = 1; mid <= n; ++mid) { //? 경유지
        for (int start = 1; start <= n; ++start) {
            for (int end = 1; end <= n; ++end) {
                min_cost[start][end] = min(min_cost[start][mid] + min_cost[mid][end], min_cost[start][end]);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (min_cost[i][j] == INF) cout << "0 ";
            else cout << min_cost[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
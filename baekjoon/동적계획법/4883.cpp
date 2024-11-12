#include <iostream>

#define INF 1000

using namespace std;

// 우, 우대각, 아래, 왼대각
int dr[4] = {0, 1, 1, 1};
int dc[4] = {1, 1, 0, -1};

bool is_valid_pos(int col) {
    return col >= 0 && col < 3;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    int step = 1;
    while (true) {
        int n;
        cin >> n;
        if (n == 0) {
            break;
        }

        int dp[n][3]; // graph[i][j] 위치에 도달하는 최소 비용
        int cost[n][3];
        fill(dp[0], dp[0] + n * 3, INF);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 3; ++j) {
                cin >> cost[i][j];
            }
        }

        dp[0][1] = cost[0][1];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (dp[i][j] == INF) continue;

                for (int d = 0; d < 4; ++d) {
                    int next_row = i + dr[d];
                    int next_col = j + dc[d];

                    if (is_valid_pos(next_col)) {
                        if (dp[next_row][next_col] == INF) {
                            dp[next_row][next_col] = dp[i][j] + cost[next_row][next_col];
                        } else {
                            dp[next_row][next_col] = min(dp[next_row][next_col], dp[i][j] + cost[next_row][next_col]);
                        }
                    }
                }
            }
        }

        // step. 결과 출력 (dp[n-1][1] 값)
        cout << step << ". " << dp[n-1][1] << '\n';

        step++;
    }
    
    return 0;
}
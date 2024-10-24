#include <iostream>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    int dp[n][n];
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> dp[i][j];

            if (i > 0) {
                dp[i][j] += dp[i-1][j];
            }
            if (j > 0) {
                dp[i][j] += dp[i][j-1];
            }
            if (i > 0 && j > 0) {
                dp[i][j] -= dp[i-1][j-1];
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--; x2--; y2--;

        int result = dp[x2][y2];
        if (x1 > 0) {
            result -= dp[x1-1][y2];
        }
        if (y1 > 0) {
            result -= dp[x2][y1-1];
        }
        if (x1 > 0 && y1 > 0) {
            result += dp[x1-1][y1-1];
        }
        cout << result << '\n';
    }

    return 0;
}
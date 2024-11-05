#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        int stick[2][n];
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> stick[i][j];
            }
        }

        int dp[2][n][2];
        fill(dp[0][0], dp[0][0] + 2 * n * 2, 0);
        dp[0][0][0] = 0; dp[0][0][1] = stick[0][0];
        dp[1][0][0] = 0; dp[1][0][1] = stick[1][0];

        for (int i = 1; i < n; ++i) {
            dp[0][i][0] = max({dp[0][i-1][0], dp[0][i-1][1], dp[1][i-1][0], dp[1][i-1][1]});
            dp[0][i][1] = stick[0][i] + max({dp[0][i-1][0], dp[1][i-1][0], dp[1][i-1][1]});
            dp[1][i][0] = dp[0][i][0];
            dp[1][i][1] = stick[1][i] + max({dp[1][i-1][0], dp[0][i-1][0], dp[0][i-1][1]});
        }

        cout << max({dp[0][n-1][0], dp[0][n-1][1], dp[1][n-1][0], dp[1][n-1][1]}) << '\n';
    }
    return 0;
}
#include <iostream>

using namespace std;

int main() {
    int T;
    cin >> T;
    int n;
    long long result = 0;

    for (int c = 0; c < T; ++c) {
        cin >> n;
        long long dp[n+1][10];
        for (int i = 0; i < 10; ++i) {
            dp[1][i] = 1;
        }

        for (int i = 2; i <= n; ++i) {
            dp[i][0] = dp[i-1][0];
            for (int j = 1; j < 10; ++j) {
                dp[i][j] = dp[i][j-1] + dp[i-1][j];
            }
        }

        result = 0;

        for (int i = 0; i < 10; ++i) {
            result += dp[n][i];
        }

        cout << result << '\n';
    }

    return 0;
}
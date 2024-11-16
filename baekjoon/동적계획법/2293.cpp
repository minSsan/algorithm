#include <iostream>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int coins[n];
    for (int i = 0; i < n; ++i) {
        cin >> coins[i];
    }

    int dp[k+1];
    fill(dp, dp + k+1, 0);
    dp[0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int cur = coins[i]; cur <= k; ++cur) {
            dp[cur] += dp[cur-coins[i]];
        }
    }

    cout << dp[k] << '\n';

    return 0;
}
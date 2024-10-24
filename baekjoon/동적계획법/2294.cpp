#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int dp[k+1];
    fill(dp, dp+k+1, 0);

    unordered_set<int> coins_set;
    for (int i = 0; i < n; ++i) {
        int coin;
        cin >> coin;
        if (coin <= k) {
            coins_set.insert(coin);
            dp[coin] = 1;
        }
    }
    
    vector<int> coins_v;
    coins_v.assign(coins_set.begin(), coins_set.end());

    for (int cur = 1; cur <= k; ++cur) {
        if (dp[cur] == 1) continue;
        for (int coin : coins_v) {
            if (cur - coin <= 0) continue;
            if (dp[cur - coin] == 0) continue;

            if (dp[cur] == 0) {
                dp[cur] = dp[cur - coin] + 1;
            } else {
                dp[cur] = min(dp[cur - coin] + 1, dp[cur]);
            }
        }
    }

    if (dp[k] == 0) cout << -1 << '\n';
    else cout << dp[k] << '\n';

    return 0;
}
#include <iostream>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        int n, target;
        cin >> n;

        int coin[n];
        for (int i = 0; i < n; ++i) {
            cin >> coin[i];
        }
        cin >> target;

        int dp[target+1];
        fill(dp, dp + target + 1, 0);
        dp[0] = 1; // 0원을 만드는 가지수 = 1
        for (int i = 0; i < n; ++i) {
            for (int cur = coin[i]; cur <= target; ++cur) {
                dp[cur] += dp[cur - coin[i]]; // 0번째 코인 ~ i번째 코인만 사용했을 때의 경우의 수
            }
        }

        cout << dp[target] << '\n';
    }
    return 0;
}
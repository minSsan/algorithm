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
        int sticker[2][n];
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> sticker[i][j];
            }
        }

        if (n == 1) {
            cout << max(sticker[0][0], sticker[1][0]) << '\n';
            continue;
        }

        int dp[2][n]; // i행 j열에 있는 스티커를 포함한 최대 점수
        fill(dp[0], dp[0] + 2 * n, 0);

        dp[0][0] = sticker[0][0]; dp[1][0] = sticker[1][0];
        dp[0][1] = sticker[1][0] + sticker[0][1];
        dp[1][1] = sticker[0][0] + sticker[1][1];

        int result = *minmax_element(dp[0], dp[0] + 2 * n).second;
        for (int i = 2; i < n; ++i) {
            dp[0][i] = max(dp[1][i-1], dp[1][i-2]) + sticker[0][i];
            dp[1][i] = max(dp[0][i-1], dp[0][i-2]) + sticker[1][i];

            result = max(dp[0][i], dp[1][i]);
        }
        cout << result << '\n';
    }
    return 0;
}
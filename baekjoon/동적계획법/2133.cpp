#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long dp[n+1];
    fill(dp, dp+n+1, 0);
    dp[2] = 3;

    for (int i = 3; i <= n; ++i) {
        if (i % 2 == 1) continue;
        //? (3 X N-2)를 채우는 경우의 수 * (3 X 2)를 채우는 경우의 수
        dp[i] = dp[i-2] * dp[2];
        for (int j = 2; j <= i-4; j += 2) {
            dp[i] += dp[j] * 2;
        }
        //? 특수 블럭 추가
        dp[i] += 2;
    }

    cout << dp[n] << '\n';

    return 0;
}
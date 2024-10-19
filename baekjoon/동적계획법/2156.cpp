#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    int quantity[n+1];
    for (int i = 1; i <= n; ++i) {
        cin >> quantity[i];
    }
    //* i번째 잔까지 j개를 연속해서 마실 때, 마실 수 있는 최대 양
    int dp[n+1][3];
    dp[1][0] = 0;
    dp[1][1] = quantity[1];
    dp[1][2] = 0;

    for (int i = 2; i <= n; ++i) {
        //? 1. 현재 와인을 마시지 않는 경우
        dp[i][0] = max({dp[i-1][0], dp[i-1][1], dp[i-1][2]});
        //? 2. 현재 와인을 포함해서 연속 한 잔을 마시는 경우 (= 연속해서 현재 와인만 마심)
        dp[i][1] = dp[i-1][0] + quantity[i];
        //? 3. 현재 와인을 포함해서 연속 두 잔을 마시는 경우
        dp[i][2] = dp[i-1][1] + quantity[i];
    }

    int result = max({dp[n][0], dp[n][1], dp[n][2]});
    cout << result << '\n';

    return 0;
}
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int dp[1000001];
    fill(dp, dp+1000001, 0);
    dp[1] = 1; // 1
    dp[2] = 2; // 1+1, 2
    dp[3] = 4; // 1+1+1, 1+2, 2+1, 3
    // dp[4] = 7; // 1+1+1+1, 1+2+1, 2+1+1, 3+1, 1+1+2, 2+2, 1+3

    

    for (int i = 4; i <= 1000000; ++i) {
        dp[i] = ((dp[i-1] + dp[i-2]) % 1000000009 + dp[i-3]) % 1000000009;
    }

    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int num;
        cin >> num;
        cout << dp[num] << '\n';
    }
    return 0;
}
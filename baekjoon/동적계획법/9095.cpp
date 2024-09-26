#include <iostream>

using namespace std;

// 1 = 1 (1)
// 2 = 1+1, 2 (2)
// 3 = 1+1+1, 2+1, 1+2, 3 (4)
// 4 = 1+1+1+1, 1+2+1, 2+1+1, 3+1, 1+1+2, 2+2, 1+3 (7)

int main() {
    int t;
    cin >> t;

    int dp[11];
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;

    for (int i = 4; i <= 10; ++i) {
        dp[i] = dp[i-1] + dp[i-2] + dp[i-3];
    }

    while (t--) {
        int n;
        cin >> n;
        cout << dp[n] << '\n';
    }
    

    return 0;
}
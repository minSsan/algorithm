#include <iostream>
#define MAX 1000000000

using namespace std;

long long dp[101][10];

int main() {
    int n;
    cin >> n;

    dp[1][0] = 0;
    for (int i = 1; i <= 9; ++i) {
        dp[1][i] = 1;
    }

    for (int i = 2; i <= n; ++i) {
        dp[i][0] = dp[i-1][1] % MAX;
        dp[i][9] = dp[i-1][8] % MAX;
        for (int j = 1; j <= 8; ++j) {
            dp[i][j] = dp[i-1][j-1] % MAX + dp[i-1][j+1] % MAX;
        }
    }

    long long result = 0;
    for (int i = 0; i <= 9; ++i) {
        result += dp[n][i] % MAX;
    }
    cout << result % MAX << '\n';

    return 0;
}
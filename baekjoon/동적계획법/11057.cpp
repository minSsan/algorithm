#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int dp[n+1][10]; //* 길이가 n이고 i로 끝나는 숫자의 개수
    fill(dp[0], dp[0] + (n+1) * 10, 0);

    for (int i = 0; i < 10; ++i) {
        dp[1][i] = 1;
    }

    for (int l = 2; l <= n; ++l) {
        dp[l][0] = dp[l-1][0];
        for (int i = 1; i < 10; ++i) {
            dp[l][i] = (dp[l][i-1] + dp[l-1][i]) % 10007;
        }
    }

    int result = 0;
    for (int i = 0; i < 10; ++i) {
        result = (result + dp[n][i]) % 10007;
    }

    cout << result << '\n';

    return 0;
}
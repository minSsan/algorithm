#include <iostream>

using namespace std;

int max(int a, int b) {
    if (a < b) return b;
    return a;
}

int main() {
    int n;
    cin >> n;
    int score[n+1]; // i번 계단에서 얻을 수 있는 점수
    for (int i = 1; i <= n; ++i) {
        cin >> score[i];
    }

    int dp[n+1];
    dp[0] = 0;
    dp[1] = score[1];
    dp[2] = score[1] + score[2];
    dp[3] = max(score[2] + dp[0], dp[1]) + score[3];

    for (int i = 3; i <= n; ++i) {
        dp[i] = max(dp[i-2], score[i-1] + dp[i-3]) + score[i];
    }

    cout << dp[n] << '\n';

    return 0;
}
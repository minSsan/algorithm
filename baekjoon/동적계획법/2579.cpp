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

    int dp[n+1][3]; // i번째 계단에서 j개의 계단을 연속해서 밟았을 때 얻을 수 있는 점수의 최대값
    dp[1][1] = score[1];
    dp[1][2] = 0;
    dp[2][1] = score[2];
    dp[2][2] = score[1] + score[2];

    for (int i = 3; i <= n; ++i) {
        dp[i][1] = max(dp[i-2][1], dp[i-2][2]) + score[i];
        dp[i][2] = dp[i-1][1] + score[i];
    }

    cout << max(dp[n][1], dp[n][2]) << '\n';

    return 0;
}
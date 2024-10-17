#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    int t[n+1];
    int p[n+1];
    int dp[n+2]; //? i번째 날짜에 도달하기까지의 최대 이익
    
    for (int i = 1; i <= n; ++i) {
        cin >> t[i] >> p[i];
    }

    //* 1. dp 초기화 및 초기값 설정
    fill(dp, dp+n+2, 0);

    if (1 + t[1] <= n+1) {
        dp[1+t[1]] = p[1];
    }

    //* 2. dp
    for (int i = 2; i < n+1; ++i) {
        if (dp[i] < dp[i-1]) {
            dp[i] = dp[i-1];
        }
        int next_date = i + t[i];
        if (next_date > n+1) continue;
        if (dp[next_date] < p[i] + dp[i]) {
            dp[next_date] = p[i] + dp[i];
        }
    }

    //* 결과 출력
    if (dp[n+1] < dp[n]) {
        cout << dp[n] << '\n';
    } else {
        cout << dp[n+1] << '\n';
    }

    return 0;
}
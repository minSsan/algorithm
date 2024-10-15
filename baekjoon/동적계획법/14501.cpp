#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    int t[n+1]; //? i일차 상담에 걸리는 시간
    int p[n+1]; //? i일차 상담으로 받을 수 있는 돈
    int dp[n+1]; //? i일차 상담일까지 벌 수 있는 최대 금액
    
    for (int i = 1; i <= n; ++i) {
        cin >> t[i] >> p[i];
        dp[i] = p[i];
    }

    int max_p;
    if (1 + t[1] <= n+1) {
        max_p = p[1];
    } else {
        max_p = 0;
    }
    
    for (int i = 2; i <= n; ++i) {
        //? i번째 상담을 진행할 수 없는 경우
        if (i + t[i] > n+1) continue;
        for (int j = 1; j < i; ++j) {
            //? i번째 상담과 j번째 상담을 함께 진행할 수 없는 경우
            if (j + t[j] > i) {
                continue;
            }
            dp[i] = max({dp[i], p[i] + dp[j]});
        }
        if (dp[i] > max_p) max_p = dp[i];
    }

    cout << max_p << '\n';

    return 0;
}
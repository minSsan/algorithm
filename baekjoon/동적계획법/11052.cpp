#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int price[n+1];
    for (int i = 1; i <= n; ++i) {
        cin >> price[i];
    }

    int dp[n+1]; //? i개의 카드를 구매할 수 있는 최대 금액
    dp[1] = price[1];
    for (int i = 2; i <= n; ++i) {
        int max_cnt = price[i];
        for (int j = 1; j <= i / 2; ++j) {
            if (dp[j] + dp[i-j] > max_cnt) {
                max_cnt = dp[j] + dp[i-j];
            }
        }
        dp[i] = max_cnt;
    }

    cout << dp[n] << '\n';

    return 0;
}
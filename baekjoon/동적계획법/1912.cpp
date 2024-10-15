#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    int dp[n], num[n];
    for (int i = 0; i < n; ++i) {
        cin >> num[i];
    }
    dp[0] = num[0];
    int max_sum = num[0];
    for (int i = 1; i < n; ++i) {
        dp[i] = max({num[i], num[i] + dp[i-1]});
        if (dp[i] > max_sum) {
            max_sum = dp[i];
        }
    }
    cout << max_sum << '\n';
    return 0;
}
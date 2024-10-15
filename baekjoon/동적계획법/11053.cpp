#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    int A[n];
    int dp[n];
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
        dp[i] = 1;
    }

    int max_len = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (A[j] < A[i]) {
                dp[i] = max({dp[i], dp[j] + 1});
            }
        }
        if (dp[i] > max_len) max_len = dp[i];
    }

    cout << max_len << '\n';
    return 0;
}
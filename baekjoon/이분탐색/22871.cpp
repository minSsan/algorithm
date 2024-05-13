#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 98765432100

using namespace std;

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    int n;
    cin >> n;

    vector<int> v(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }

    long long dp[n+1];
    for (int i = 2; i <= n; ++i) dp[i] = MAX;
    dp[1] = 0;

    //* 2. dp
    for (long long i = 2; i <= n; ++i) { // i번째 돌까지 이동하는데 필요한 최소 힘
        for (long long j = 1; j < i; ++j) { // j번째 돌을 밟고 지나가는 데 필요한 최대 힘
            long long k = max(dp[j], (i - j) * (1 + abs(v[i] - v[j])));
            dp[i] = min(dp[i], k);
        }
    }

    cout << dp[n] << '\n';

    return 0;
}
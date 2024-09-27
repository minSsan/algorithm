#include <iostream>
#include <deque>

using namespace std;

int main() {
    int n;
    cin >> n;

    int dp[n+1];
    int tracking[n+1];
    dp[1] = 0;
    tracking[1] = 0; // 0이 될 때 추적 종료
    dp[2] = 1;
    tracking[2] = 1;
    dp[3] = 1;
    tracking[3] = 1;

    for (int i = 4; i <= n; ++i) {
        dp[i] = dp[i-1];
        tracking[i] = i-1;
        if (i % 2 == 0) {
            if (dp[i/2] < dp[i]) {
                dp[i] = dp[i/2];
                tracking[i] = i/2;
            }
        }
        if (i % 3 == 0) {
            if (dp[i/3] < dp[i]) {
                dp[i] = dp[i/3];
                tracking[i] = i/3;
            }
        }
        dp[i]++;
    }
    
    cout << dp[n] << '\n';
    int index = n;
    cout << n << ' ';
    while (tracking[index] != 0) {
        cout << tracking[index] << ' ';
        index = tracking[index];
    }
    cout << '\n';

    // deque<int> dp[n+1];
    // dp[1] = {1};
    // dp[2] = {2, 1};
    // dp[3] = {3, 1};

    // for (int i = 4; i <= n; ++i) {
    //     int result = i-1;
    //     dp[i] = dp[i-1];
    //     if (i % 2 == 0) {
    //         if (dp[i/2].size() < dp[i].size()) {
    //             result = i / 2;
    //             dp[i] = dp[i/2];
    //         }
    //     }
    //     if (i % 3 == 0) {
    //         if (dp[i/3].size() < dp[i].size()) {
    //             result = i / 3;
    //             dp[i] = dp[i/3];
    //         }
    //     }
    //     dp[i] = dp[result];
    //     dp[i].push_front(i);
    // }

    // cout << dp[n].size()-1 << '\n';
    // for (int i = 0; i < dp[n].size(); ++i) {
    //     cout << dp[n][i] << ' ';
    // }
    // cout << '\n';

    return 0;
}
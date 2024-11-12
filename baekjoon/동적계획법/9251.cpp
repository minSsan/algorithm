#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string a, b;
    cin >> a >> b;

    int dp[a.length()][b.length()];
    fill(dp[0], dp[0] + a.length() * b.length(), 0);

    if (a[0] == b[0]) {
        dp[0][0] = 1;
    }

    for (int j = 1; j < b.length(); ++j) {
        if (a[0] == b[j]) {
            dp[0][j] = 1;
        }
        else {
            dp[0][j] = dp[0][j-1];
        }
    }

    for (int i = 1; i < a.length(); ++i) {
        if (a[i] == b[0]) {
            dp[i][0] = 1;
        } else {
            dp[i][0] = dp[i-1][0];
        }
        
        for (int j = 1; j < b.length(); ++j) {
            if (a[i] == b[j]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
    }

    // for (int i = 0; i < a.length(); ++i) {
    //     for (int j = 0; j < b.length(); ++j) {
    //         cout << dp[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    cout << dp[a.length() - 1][b.length() - 1] << '\n';

    return 0;
}
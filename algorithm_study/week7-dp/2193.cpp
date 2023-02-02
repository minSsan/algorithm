#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    struct node
    {
        long long cnt_end_zero;
        long long cnt_end_one;
    };

    vector<node> dp(n + 1);
    dp[1] = {0, 1};

    for (int i = 2; i <= n; ++i) {
        dp[i].cnt_end_zero = dp[i-1].cnt_end_zero + dp[i-1].cnt_end_one;
        dp[i].cnt_end_one = dp[i-1].cnt_end_zero;
    }

    cout << dp[n].cnt_end_one + dp[n].cnt_end_zero << '\n';

    return 0;
}
#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    bool vip[n+1]; // i번 좌석의 VIP 여부
    fill(vip, vip+n+1, false);
    for (int i = 0; i < m; ++i) {
        int num;
        cin >> num;
        vip[num] = true;
    }

    int dp[n+1][2];
    //* dp[n]: 왼쪽부터 n번 좌석까지 앉을 수 있는 모든 경우의 수
    //* dp[n][0]: n번 자리에 n번 사람이 앉는 경우의 수
    //* dp[n][1]: n-1번 자리에 n번 사람이 앉는 경우의 수
    
    for (int i = 0; i < n+1; ++i) {
        for (int j = 0; j < 2; ++j) {
            dp[i][j] = 0;
        }
    }
    dp[1][0] = 1;
    dp[2][0] = 1;
    if (!vip[2] && !vip[1]) {
        dp[2][1] = 1;
    }

    for (int i = 3; i <= n; ++i) {
        dp[i][0] = dp[i-1][0] + dp[i-1][1];
        if (vip[i] || vip[i-1]) continue;
        dp[i][1] = dp[i-2][0] + dp[i-2][1];
    }

    // for (int i = 0; i < n+1; ++i) {
    //     cout << "dp[" << i << "][0] : " << dp[i][0] << ", dp[" << i << "][1] : " << dp[i][1] << '\n';
    // }

    cout << dp[n][0] + dp[n][1] << '\n';

    return 0;
}
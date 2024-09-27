#include <iostream>
#include <algorithm>

#define RED 0
#define GREEN 1
#define BLUE 2

using namespace std;

int main() {
    int n;
    cin >> n;

    int cost[n+1][3];
    for (int i = 1; i <= n; ++i) {
        cin >> cost[i][RED] >> cost[i][GREEN] >> cost[i][BLUE];
    }

    // 빨간색, 초록색, 파란색으로 칠했을 때의 최소 비용
    int dp[n+1][3];
    dp[1][RED] = cost[1][RED];
    dp[1][GREEN] = cost[1][GREEN];
    dp[1][BLUE] = cost[1][BLUE];
    for (int i = 2; i <= n; ++i) {
        dp[i][RED] = min({dp[i-1][GREEN], dp[i-1][BLUE]}) + cost[i][RED];
        dp[i][GREEN] = min({dp[i-1][RED], dp[i-1][BLUE]}) + cost[i][GREEN];
        dp[i][BLUE] = min({dp[i-1][GREEN], dp[i-1][RED]}) + cost[i][BLUE];
    }
    
    cout << min({dp[n][RED], dp[n][GREEN], dp[n][BLUE]}) << '\n';
    
    return 0;
}
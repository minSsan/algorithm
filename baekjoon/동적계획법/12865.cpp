#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    pair<int, int> objects[n]; // {무게, 값}

    for (int i = 0; i < n; ++i) {
        cin >> objects[i].first >> objects[i].second;
    }

    int dp[k+1][n]; // n번째 물건까지 탐색했을 때, K kg 가방에 넣을 수 있는 최대 가치
    fill(dp[0], dp[0] + (k+1)*n, 0);

    for (int w = 1; w <= k; ++w) {
        // 초기 값 세팅: 0번째 무게가 가방 무게보다 작거나 같은 경우
        if (w >= objects[0].first) {
            dp[w][0] = objects[0].second;
        }

        for (int i = 1; i < n; ++i) {
            if (w >= objects[i].first) {
                dp[w][i] = max(dp[w-objects[i].first][i-1] + objects[i].second, dp[w][i-1]);
            } else {
                dp[w][i] = dp[w][i-1];
            }
        }
    }

    cout << dp[k][n-1] << '\n';

    return 0;
}
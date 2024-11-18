#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    char grid[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    int dp[n][m]; // i, j 지점까지의 최대 정사각형 한 변 길이
    fill(dp[0], dp[0] + n * m, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '0') continue;
            // margin
            if (i == 0 || j == 0) {
                dp[i][j] = grid[i][j] - '0';
            }
            else {
                dp[i][j] = min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]}) + 1;
            }
        }
    }

    int len = *minmax_element(dp[0], dp[0] + n*m).second;
    cout << len * len << '\n';

    return 0;
}
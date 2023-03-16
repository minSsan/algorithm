#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, input;
    cin >> n;

    vector<vector<int>> triangle(n);
    vector<vector<int>> max_sum(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            cin >> input;
            triangle[i].push_back(input);
            max_sum[i].push_back(0);
        }
    }

    max_sum[0][0] = triangle[0][0];
    int result = max_sum[0][0];
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j == 0) {
                max_sum[i][j] = triangle[i][j] + max_sum[i-1][0];
            } else if (j == i) {
                max_sum[i][j] = triangle[i][j] + max_sum[i-1][i-1];
            } else {
                max_sum[i][j] = triangle[i][j] + max(max_sum[i-1][j-1], max_sum[i-1][j]);
            }

            if (i == n-1 && max_sum[i][j] > result) {
                result = max_sum[i][j];
            }
        }
    }

    cout << result << '\n';

    return 0;
}
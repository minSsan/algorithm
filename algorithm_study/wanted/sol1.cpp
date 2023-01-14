#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> directions(n);

    for (int i = 0; i < n; ++i) {
        cin >> directions[i];
    }

    vector<int> cnt;
    int temp;
    if (directions[0] == 1) {
        temp = 1;
    } else {
        temp = -1;
    }

    for (int i = 1; i < n; ++i) {
        if (directions[i] == directions[i-1]) {
            if (temp > 0) {
                temp += 1;
            } else {
                temp -= 1;
            }
        } else {
            cnt.push_back(temp);

            if (directions[i] == 1) {
                temp = 1;
            } else {
                temp = -1;
            }
        }
    }

    cnt.push_back(temp);

    vector<int> dp(cnt.size(), 0); // 절댓값을 저장

    int all_sum = cnt[0];
    dp[0] = cnt[0] > 0 ? cnt[0] : -1 * cnt[0]; // 양수로 저장

    // [4, -1, 2, -1, 2] : 6
    // all sum = 5
    // 모두 더한 값, dp에 저장되어 있는 값, 현재 cnt 값
    // [4, 4, max(5, 2) = 5, max(4, |-1|, |0|), max()]
    for (int i = 1; i < dp.size(); ++i) {
        all_sum = all_sum + cnt[i];

        int all_sum_abs = all_sum > 0 ? all_sum : -1 * all_sum;
        int compare_value2 = cnt[i] > 0 ? cnt[i] : -1 * cnt[i];
        all_sum_abs = all_sum_abs > compare_value2 ? all_sum_abs : compare_value2;
        
        if (all_sum_abs >= dp[i-1]) {
            dp[i] = all_sum_abs;
        } else {
            dp[i] = dp[i-1];
        }

        // dp[i] = max(compare_value, dp[i-1]);
    }

    cout << dp[cnt.size() - 1] << '\n';

    return 0;
}

// 1 1 2 1 2 :: 2
// [2, -1, 1, -1]
// dp: [2, 2, 2, 2] : all_sum = -1

// 1 1 2 2 2 2
// 1 2 1 2 3 4
// cnt_1 = 2, cnt_2 = 4
// [2, -4] : all_sum = 0
// dp: [2, 2]

// 1 1 1 1 2 2 2 1 1 1 1 :: 5
// 1 2 3 4 1 2 3 1 2 3 4
// cnt_1 = 4, cnt_2 = 3, cnt_1 = 8
// [4, -3, 4] : all_sum = 1 + 4 = 5
// dp: [4, 4, 5]

// [-4, 3, -4] : all_sum = -1 + -4 = -5
// dp: [4, 4, 5]

// 10
// 1 1 1 2 2 2 2 2 1 1
// [3, -5, 2]
// all_sum = -2
// [3, ]
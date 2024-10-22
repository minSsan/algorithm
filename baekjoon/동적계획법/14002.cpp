#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    //? i번째 숫자 이전 인덱스
    int n;
    cin >> n;
    int prev[n];
    fill(prev, prev+n, -1);
    
    int A[n];
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    //? i번째 숫자를 포함하는 가장 긴 부분증가 수열
    int dp[n];
    dp[0] = 1;
    //? 결과 수열에 가장 마지막에 오는 숫자의 인덱스 번호
    int last_index = 0;
    int result_len = 1;
    for (int i = 1; i < n; ++i) {
        int max_len = 0;
        int prev_index = -1;
        for (int j = 0; j < i; ++j) {
            if (A[j] < A[i] && dp[j] > max_len) {
                max_len = dp[j];
                prev_index = j;
            }
        }
        dp[i] = max_len + 1;
        if (dp[i] > result_len) {
            result_len = dp[i];
            last_index = i;
        }
        prev[i] = prev_index;
    }

    int cur_index = last_index;
    vector<int> result;
    for (int i = 0; i < result_len; ++i) {
        result.push_back(A[cur_index]);
        cur_index = prev[cur_index];
    }
    reverse(result.begin(), result.end());

    cout << result.size() << '\n';
    for (int r : result) {
        cout << r << ' ';
    }
    cout << '\n';

    return 0;
}
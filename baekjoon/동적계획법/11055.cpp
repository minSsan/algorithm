#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    int num[n];
    int dp[n]; //? i번째 원소 값을 포함하는 수열(= 증가하는 수열)의 최대 누적합
    for (int i = 0; i < n; ++i) {
        cin >> num[i];
        dp[i] = num[i];
    }
    int max_sum = num[0];
    for (int i = 1; i < n; ++i) {
        //? 현재 원소보다 앞에 위치한 원소 탐색
        for (int j = 0; j < i; ++j) {
            //* 현재 값보다 작은 값으로 끝나는 수열
            if (num[j] < num[i]) {
                dp[i] = max({dp[j] + num[i], dp[i]});
            }
        }
        if (dp[i] > max_sum) max_sum = dp[i];
    }
    cout << max_sum << '\n';
    return 0;
}
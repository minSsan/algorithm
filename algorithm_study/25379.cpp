#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int n;
    cin >> n;
    vector<int> nums(n);

    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    long long swap_cnt = 0, even_result = 0, odd_result = 0;
    // 왼쪽에 짝수를 모는 경우
    for (int i = 0; i < n; ++i) {
        if (nums[i] % 2 == 0) { // 짝수인 경우
            even_result += swap_cnt;
        } else { // 홀수인 경우
            swap_cnt++; // 짝수의 이동 횟수 증가
        }
    }

    swap_cnt = 0;
    // 왼쪽에 홀수를 모는 경우
    for (int i = 0; i < n; ++i) {
        if (nums[i] % 2 == 0) { // 짝수인 경우
            swap_cnt++; // 홀수의 이동 횟수 증가
        } else { // 홀수인 경우
            odd_result += swap_cnt;
        }
    }

    long long result = min(even_result, odd_result);

    cout << result << '\n';

    return 0;
}
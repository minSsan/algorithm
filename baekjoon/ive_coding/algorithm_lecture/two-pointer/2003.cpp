#include <iostream>

using namespace std;

int main() {
    int n, m;

    cin >> n >> m;

    int nums[n], input_num;

    for (int i = 0; i < n; ++i) {
        cin >> input_num;
        nums[i] = input_num;
    }

    int count = 0;

    int start = 0, end = 1, sum_result = nums[start] + nums[end];

    while (start < n) {
        if (sum_result == m) {
            count++;
            
            sum_result -= nums[start]; start++; 
            end++;
            // TODO: 이어서 작성
            
            if (end == n) break;
        } else if (sum_result < m) {
            end++;
            if (end == n) break;
        } else {
            start++;
        }
    }

    cout << count << '\n';

    return 0;
}
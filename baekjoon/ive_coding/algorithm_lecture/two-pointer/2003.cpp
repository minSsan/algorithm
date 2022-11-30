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

    int start = 0, end = 0, sum_result = nums[0];

    while (start < n) {
        if (sum_result == m) {
            count++;
            end++; 
            if (end == n) break;
            sum_result += nums[end];
        } else if (sum_result < m) {
            end++;
            if (end == n) break;
            sum_result += nums[end];
        } else {
            sum_result -= nums[start]; start++;
        }
    }

    cout << count << '\n';

    return 0;
}
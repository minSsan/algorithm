#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long arr[n];

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    sort(arr, arr+n);

    int cur_cnt = 1;
    int max_cnt = 1;
    long long max_num = arr[0];

    for (int i = 1; i < n; ++i) {
        if (arr[i] == arr[i-1]) cur_cnt++;
        else {
            if (cur_cnt > max_cnt) {
                max_cnt = cur_cnt;
                max_num = arr[i-1];
            }
            cur_cnt = 1;
        }
    }
    if (cur_cnt > max_cnt) max_num = arr[n-1];

    cout << max_num << '\n';

    return 0;
}
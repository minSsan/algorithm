#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> num(n);

    for (int i = 0; i < n; ++i) {
        cin >> num[i];
    }

    sort(num.begin(), num.end());

    int max_len = 1, current_len = 0;
    for (int i = 1; i < n; ++i) {
        if (num[i] == (num[i-1] + 1)) {
            current_len++;
        } else {
            current_len = 0;
        }

        if (current_len > max_len) max_len = current_len;
    }

    cout << max_len << '\n';

    return 0;
}
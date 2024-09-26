#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool compare(string a, string b) {
    if (a.size() != b.size()) return a.size() < b.size();
    int a_sum = 0, b_sum = 0;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] >= '0' && a[i] <= '9') {
            a_sum += a[i] - '0';
        }
        if (b[i] >= '0' && b[i] <= '9') {
            b_sum += b[i] - '0';
        }
    }
    if (a_sum != b_sum) return a_sum < b_sum;
    return a < b;
}

int main() {
    int n;
    cin >> n;

    string arr[n];

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    sort(arr, arr+n, compare);
    for (string s : arr) {
        cout << s << '\n';
    }

    return 0;
}
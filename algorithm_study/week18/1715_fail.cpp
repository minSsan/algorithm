#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> bundle(n);
    for (int i = 0; i < n; ++i) {
        cin >> bundle[i];
    }

    sort(bundle.begin(), bundle.end());

    int result = 0, first = bundle[0];
    if (n == 1) {
        cout << first << '\n';
        return 0;
    }

    for (int i = 1; i < n; ++i) {
        result += first + bundle[i];
        first = first + bundle[i];
    }

    cout << result << '\n';

    return 0;
}
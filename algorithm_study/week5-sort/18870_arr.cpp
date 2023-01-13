#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    pair<int, int> inputs[n];
    for (int i = 0; i < n; ++i) {
        cin >> inputs[i].first;
        inputs[i].second = i;
    }

    sort(inputs, inputs + n);

    int result[n];

    int cnt = 0;
    int temp = inputs[0].first;
    result[inputs[0].second] = cnt;

    for (int i = 1; i < n; ++i) {
        if (temp == inputs[i].first) {
            result[inputs[i].second] = cnt;
        } else {
            cnt++;
            temp = inputs[i].first;
            result[inputs[i].second] = cnt;
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << result[i] << ' ';
    }

    cout << '\n';

    return 0;
}
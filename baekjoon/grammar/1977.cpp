#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> m >> n;

    int min_value = n, sum = 0;

    for (int i = 1; i <= n; ++i) {
        if (m <= i * i && i * i <= n) {
            if (i * i < min_value) min_value = i * i;
            sum += i * i;
        }
    }

    if (sum == 0) {
        cout << -1 << '\n';
        return 0;
    }

    cout << sum << '\n';
    cout << min_value << '\n';

    return 0;
}

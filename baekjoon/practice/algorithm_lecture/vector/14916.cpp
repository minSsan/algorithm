#include <iostream>
#include <vector>

using namespace std;

int min(int a, int b) {
    if (a > b) {
        return b;
    } else {
        return a;
    }
}

int main() {
    // 2원짜리, 5원짜리
    int n;
    cin >> n;

    vector <int> min_count(n+1, -1);
    min_count[2] = 1;
    min_count[4] = 2;
    min_count[5] = 1;

    for (int i = 6; i <= n; ++i) {
        if (min_count[i-2] != -1 && min_count[i-5] != -1) {
            min_count[i] = min(min_count[i-2], min_count[i-5]) + 1;
        } else if (min_count[i-2] != -1) {
            min_count[i] = min_count[i-2] + 1;
        } else if (min_count[i-5] != -1) {
            min_count[i] = min_count[i-5] + 1;
        }
    }

    cout << min_count[n] << '\n';

    return 0;
}

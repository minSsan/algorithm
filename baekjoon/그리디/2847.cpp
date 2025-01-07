#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int scores[n];
    for (int i = 0; i < n; ++i) {
        cin >> scores[i];
    }

    int cnt = 0;
    for (int i = n-2; i >= 0; --i) {
        if (scores[i] >= scores[i+1]) {
            cnt += scores[i] - scores[i+1] + 1;
            scores[i] = scores[i+1] - 1;
        }
    }

    cout << cnt << '\n';

    return 0;
}
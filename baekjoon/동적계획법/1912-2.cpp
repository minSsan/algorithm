#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int max_sum;
    cin >> max_sum;
    int accum = max_sum;
    for (int i = 1; i < n; ++i) {
        int num;
        cin >> num;
        if (accum + num > num) {
            accum += num;
        } else {
            accum = num;
        }

        if (accum > max_sum) {
            max_sum = accum;
        }
    }

    cout << max_sum << '\n';

    return 0;
}
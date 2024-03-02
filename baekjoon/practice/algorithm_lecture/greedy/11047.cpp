#include <iostream>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int coins[10], result = 0;

    for (int i = 0; i < n; ++i) {
        cin >> coins[i];
    }

    int index = n-1;

    while (index >= 0) {
        if (coins[index] <= k) {
            result += int(k / coins[index]);
            k = k % coins[index];
        } 
        index--;
    }

    cout << result << '\n';

    return 0;
}

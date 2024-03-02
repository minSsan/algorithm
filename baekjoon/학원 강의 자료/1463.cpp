#include <iostream>

using namespace std;

int min(int* a, int* b) {
    return *a > *b ? *b : *a;
}

int main() {
    int n;
    cin >> n;

    int min_count[n+1];

    for (int i = 0; i < n+1; ++i) {
        min_count[i] = 0;
    }

    min_count[2] = 1;
    min_count[3] = 1;

    for (int i = 4; i < n+1; ++i) {
        if (i % 3 == 0 && i % 2 == 0) {
            min_count[i] = min(min_count[i/3], min(min_count[i/2], min_count[i-1])) + 1;
        } else if (i % 3 == 0) {
            min_count[i] = min(min_count[i/3], min_count[i-1]) + 1;
        } else if (i % 2 == 0) {
            min_count[i] = min(min_count[i/2], min_count[i-1]) + 1;
        } else {
            min_count[i] = min_count[i-1] + 1;
        }
    }

    cout << min_count[n] << '\n';

    return 0;
}
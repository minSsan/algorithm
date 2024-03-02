#include <iostream>
#include <vector>

using namespace std;

bool isPrime(int n) {
    if (n == 1) return false;

    for (int i = 2; i*i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int count = 0;

    vector<int> input_num(N);

    for (int i = 0; i < N; ++i) {
        cin >> input_num[i];
    }

    for (int i = 0; i < N; ++i) {
        if (isPrime(input_num[i])) {
            ++count;
        }
    }

    cout << count;

    return 0;
}
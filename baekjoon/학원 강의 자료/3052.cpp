#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int arr[10];
    int mod[42] = {0};
    int count = 0;

    for (int i = 0; i < 10; ++i) {
        cin >> arr[i];
    }

    for (int i = 0; i < 10; ++i) {
        mod[arr[i] % 42] = 1;
    }

    for (int i = 0; i < 42; ++i) {
        if (mod[i] == 1) {
            ++count;
        }
    }

    cout << count;

    return 0;
}
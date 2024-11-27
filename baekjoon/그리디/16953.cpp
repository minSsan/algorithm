#include <iostream>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;

    int cnt = 1;
    while (true) {
        if (a == b) {
            break;
        }

        if (b < a) {
            cout << -1 << '\n';
            return 0;
        }

        if (b % 10 == 1) {
            b = b / 10;
        }
        else if (b % 2 == 0) {
            b /= 2;
        }
        else {
            cout << -1 << '\n';
            return 0;
        }
        ++cnt;
    }

    cout << cnt << '\n';

    return 0;
}
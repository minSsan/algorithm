#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i < 10; ++i) {
        cout << n << " * " << i << " = " << n*i << "\n";
    }

    return 0;
}
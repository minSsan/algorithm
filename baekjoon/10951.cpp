#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B = 0;
    while (cin >> A >> B) {
        cout << A + B << '\n';
    }

    return 0;
}
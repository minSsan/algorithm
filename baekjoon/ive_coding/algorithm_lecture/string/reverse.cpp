#include <iostream>

using namespace std;

int main() {
    string s;
    int result = 1;

    cin >> s;

    // for (int i = s.size() - 1; i >= 0; --i) {
    //     cout << s[i] << " ";
    // }

    // hiih
    // hiilih
    // hillih
    for (int i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - 1 - i]) {
            result = 0;
            break;
        }
    }

    cout << result << '\n';

    return 0;
}
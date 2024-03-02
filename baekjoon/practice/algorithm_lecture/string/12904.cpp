#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string S, T;
    cin >> S >> T;

    // 1. S.push_back('A');
    // 2. S.reverse(S.begin(), S.end()); -> S.push_back('B');

    // 1. 문자열 뒤에 'A'를 삭제한다
    // 2. 문자열 뒤에 'B'를 삭제하고, 문자열을 뒤집는다
    while (S.length() != T.length()) {
        if (T.back() == 'B') {
            T.pop_back();
            reverse(T.begin(), T.end());
        }
        else if (T.back() == 'A') {
            T.pop_back();
        }
    }

    if (S == T) {
        cout << 1 << '\n';
    } else {
        cout << 0 << '\n';
    }

    return 0;
}
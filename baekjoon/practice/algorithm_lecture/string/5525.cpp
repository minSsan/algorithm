#include <iostream>
#include <string>

using namespace std;

int main() {
    int n, m;
    cin >> n; // Pn에서 사용 될 n
    cin >> m; // 글자 수
    int result = 0;

    string s;
    cin >> s;

    // TODO: s에 Pn이 몇 개?

    // * Pn 만들기
    string Pn = "";
    for (int i = 0; i < 2 * n + 1; ++i) {
        if (i % 2 == 0) {
            Pn.push_back('I');
        } else {
            Pn.push_back('O');
        }
    }

    for (int i = 0; i < m - Pn.size() + 1; ++i) {
        if (s.substr(i, Pn.size()) == Pn) {
            result ++;
        }
    }

    cout << result << '\n';

    return 0;
}